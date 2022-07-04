#include "server/TagMode.hpp"
#include <cmath>
#include "al/async/FunctorV0M.hpp"
#include "al/util.hpp"
#include "al/util/ControllerUtil.h"
#include "game/GameData/GameDataHolderAccessor.h"
#include "game/Layouts/CoinCounter.h"
#include "game/Layouts/MapMini.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "layouts/TagIcon.h"
#include "logger.hpp"
#include "rs/util.hpp"
#include "server/gamemode/GameModeBase.hpp"
#include "server/Client.hpp"
#include "server/gamemode/GameModeTimer.hpp"

#include "basis/seadNew.h"
#include "server/TagConfigMenu.hpp"

TagMode::TagMode(const char* name) : GameModeBase(name) {}

void TagMode::init(const GameModeInitInfo& info) {
    mSceneObjHolder = info.mSceneObjHolder;
    mMode = info.mMode;
    mCurScene = (StageScene*)info.mScene;
    mPuppetHolder = info.mPuppetHolder;

    GameModeInfoBase* curGameInfo = Client::getModeInfo();

    if (curGameInfo && curGameInfo->mMode == mMode) {
        mInfo = (TagInfo*)curGameInfo;
        mModeTimer = new GameModeTimer(mInfo->mTimeLimit);
    } else {
        sead::system::DeleteImpl(
            curGameInfo);  // attempt to destory previous info before creating new one
        
        mInfo = createModeInfo<TagInfo>();
        Client::setModeInfo(mInfo);
        mModeTimer = new GameModeTimer();
    }

    mModeLayout = new TagIcon("TagIcon", *info.mLayoutInitInfo);

    mModeLayout->showTagged();

    mModeTimer->disableTimer();

}

void TagMode::begin() {

    mModeLayout->appear();

    mIsFirstFrame = true;

    if (!mInfo->mIsPlayerIt) {
        mModeTimer->enableTimer();
        mModeLayout->showUntagged();
    } else {
        mModeTimer->disableTimer();
        mModeLayout->showTagged();
    }

    CoinCounter *coinCollect = mCurScene->stageSceneLayout->mCoinCollectLyt;
    CoinCounter* coinCounter = mCurScene->stageSceneLayout->mCoinCountLyt;
    MapMini* compass = mCurScene->stageSceneLayout->mMapMiniLyt;
    al::SimpleLayoutAppearWaitEnd* playGuideLyt = mCurScene->stageSceneLayout->mPlayGuideMenuLyt;

    if(coinCounter->mIsAlive)
        coinCounter->tryEnd();
    if(coinCollect->mIsAlive)
        coinCollect->tryEnd();
    if (compass->mIsAlive)
        compass->end();
    if (playGuideLyt->mIsAlive)
        playGuideLyt->end();

    GameModeBase::begin();
}

void TagMode::end() {

    mModeLayout->tryEnd();

    mModeTimer->disableTimer();

    CoinCounter *coinCollect = mCurScene->stageSceneLayout->mCoinCollectLyt;
    CoinCounter* coinCounter = mCurScene->stageSceneLayout->mCoinCountLyt;
    MapMini* compass = mCurScene->stageSceneLayout->mMapMiniLyt;
    al::SimpleLayoutAppearWaitEnd* playGuideLyt = mCurScene->stageSceneLayout->mPlayGuideMenuLyt;

    if(!coinCounter->mIsAlive)
        coinCounter->tryStart();
    if(!coinCollect->mIsAlive)
        coinCollect->tryStart();
    if (!compass->mIsAlive)
        compass->appearSlideIn();
    if (!playGuideLyt->mIsAlive)
        playGuideLyt->appear();

    GameModeBase::end();
}

void TagMode::update() {

    PlayerActorHakoniwa* mainPlayer = rs::getPlayerActor(mCurScene);

    if (mIsFirstFrame) {

        //if (mInfo->mIsUseGravityCam && mTicket) {
        //    al::startCamera(mCurScene, mTicket, -1);
        //}
        //
        mIsFirstFrame = false;
    }

    if (!mInfo->mIsPlayerIt) {
        //if (mInvulnTime <= 5) {  
            if (mainPlayer) {
                for (size_t i = 0; i < mPuppetHolder->getSize(); i++)
                {
                    PuppetInfo *curInfo = Client::getPuppetInfo(i);

                    if(curInfo->isConnected && curInfo->isInSameStage && curInfo->isIt) { 

                        float pupDist = al::calcDistance(mainPlayer, curInfo->playerPos); // TODO: remove distance calculations and use hit sensors to determine this

                        if(pupDist < 200.f && mainPlayer->mDimKeeper->is2DModel == curInfo->is2D) {
                            if(!PlayerFunction::isPlayerDeadStatus(mainPlayer)) {
                                //we need to put this first because it will cause an infinite loop where each player tags each other indefinitely
                                mInvulnTime += Time::deltaTime;
                                mInfo->mIsPlayerIt = true;
                                //GameDataFunction::killPlayer(GameDataHolderAccessor(this));
                                //mainPlayer->startDemoPuppetable();
                                al::setVelocityZero(mainPlayer);
                                //rs::faceToCamera(mainPlayer);
                                mainPlayer->mPlayerAnimator->endSubAnim();
                                mainPlayer->mPlayerAnimator->startAnim("DamageLand");

                                

                                mModeTimer->disableTimer();
                                mModeLayout->showTagged();
                                
                                Client::sendTagInfPacket();
                            }
                        } else if (PlayerFunction::isPlayerDeadStatus(mainPlayer)) {

                            mInfo->mIsPlayerIt = true;
                            mModeTimer->disableTimer();
                            mModeLayout->showTagged();

                            Client::sendTagInfPacket();
                            
                        }
                    }
                }
            }
        //} 
    }
    else {
            {
                //if (mInvulnTime <= 5) {
                if (mainPlayer) {
                    for (size_t i = 0; i < mPuppetHolder->getSize(); i++)
                    {
                        PuppetInfo *curInfo = Client::getPuppetInfo(i);
    
                        if(curInfo->isConnected && curInfo->isInSameStage && curInfo->isIt) { 
                        
                            float pupDist = al::calcDistance(mainPlayer, curInfo->playerPos); // TODO: remove distance calculations and use hit sensors to determine this
    
                            if(pupDist < 200.f && mainPlayer->mDimKeeper->is2DModel == curInfo->is2D) {
                                if(!PlayerFunction::isPlayerDeadStatus(mainPlayer)) {
                                    mInvulnTime += Time::deltaTime;
                                    mInfo->mIsPlayerIt = false;
                                    //GameDataFunction::killPlayer(GameDataHolderAccessor(this));
                                    //mainPlayer->startDemoPuppetable();
                                    al::setVelocityZero(mainPlayer);
                                    //rs::faceToCamera(mainPlayer);
                                    mainPlayer->mPlayerAnimator->endSubAnim();
                                    mainPlayer->mPlayerAnimator->startAnim("Punch");
                                    
                                    //mainPlayer->mPlayerAnimator->startAnim("Punch");
    
                                    //mInvulnTime += Time::deltaTime;
                                    mModeTimer->disableTimer();
                                    mModeLayout->showUntagged();
                                    
                                    Client::sendTagInfPacket();
                                }
                            } else if (PlayerFunction::isPlayerDeadStatus(mainPlayer)) {
                            
                                mInfo->mIsPlayerIt = false;
                                mModeTimer->disableTimer();
                                mModeLayout->showUntagged();
    
                                Client::sendTagInfPacket();
                                
                            }
                        }
                    }
                }
            //}
        }
        mModeTimer->updateTimer();
    }

    //if (mInfo->mIsUseGravity) {
    //    sead::Vector3f gravity;
    //    if (rs::calcOnGroundNormalOrGravityDir(&gravity, mainPlayer, mainPlayer->mPlayerCollider)) {
    //        gravity = -gravity;
    //        al::normalize(&gravity);
    //        al::setGravity(mainPlayer, gravity);
    //        al::setGravity(mainPlayer->mHackCap, gravity);
    //    }
    //    
    //    if (al::isPadHoldL(-1)) {
    //        if (al::isPadTriggerRight(-1)) {
    //            if (al::isActiveCamera(mTicket)) {
    //                al::endCamera(mCurScene, mTicket, -1, false);
    //                mInfo->mIsUseGravityCam = false;
    //            } else {
    //                al::startCamera(mCurScene, mTicket, -1);
    //                mInfo->mIsUseGravityCam = true;
    //            }
    //        }
    //    } else if (al::isPadTriggerZL(-1)) {
    //        if (al::isPadTriggerLeft(-1)) {
    //            killMainPlayer(mainPlayer);
    //        }
    //    }
    //}

    if (al::isPadTriggerUp(-1) && !al::isPadHoldZL(-1))
    {
        mInfo->mIsPlayerIt = !mInfo->mIsPlayerIt;

        mModeTimer->toggleTimer();

        if(!mInfo->mIsPlayerIt) {
            mInvulnTime = 0;
            mModeLayout->showUntagged();
        } else {
            mModeLayout->showTagged();
        }

        Client::sendTagInfPacket();
        //mInfo->mTimeLimit = mModeTimer->getTime();
        }  
    }