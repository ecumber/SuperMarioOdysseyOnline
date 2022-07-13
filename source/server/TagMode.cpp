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
        mModeTimer = new GameModeTimer(mInfo->mTimeLimit, false);
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
        mIsFirstFrame = false;
    }
    //make sure the player isn't invulnerable so we can tag them
    if (mInvulnTime <= 0) { 
        if (!mInfo->mIsPlayerIt) {
                if (mainPlayer) {
                    for (size_t i = 0; i < mPuppetHolder->getSize(); i++)
                    {
                        PuppetInfo *curInfo = Client::getPuppetInfo(i);
                        if(curInfo->isConnected && curInfo->isInSameStage && curInfo->isIt) { 
                            float pupDist = al::calcDistance(mainPlayer, curInfo->playerPos); // TODO: remove distance calculations and use hit sensors to determine this
                            if(pupDist < 200.f && mainPlayer->mDimKeeper->is2DModel == curInfo->is2D) {
                                if(!PlayerFunction::isPlayerDeadStatus(mainPlayer)) {
                                    mInvulnTime = 5;
                                    mInfo->mIsPlayerIt = true;
                                    //mainPlayer->startDemoPuppetable();
                                    al::setVelocityZero(mainPlayer);

                                    // if you're not it and you get tagged, play the "bonk" animation
                                    mainPlayer->mPlayerAnimator->endSubAnim();
                                    mainPlayer->mPlayerAnimator->startAnim("DamageLand");
                                    //mModeTimer->disableTimer();
                                    mModeLayout->showTagged();

                                    Client::sendTagInfPacket();
                                }
                            } else if (PlayerFunction::isPlayerDeadStatus(mainPlayer)) {

                                mInfo->mIsPlayerIt = true;
                                //mModeTimer->disableTimer();
                                mModeLayout->showTagged();

                                Client::sendTagInfPacket();

                            }
                        }
                    }
                }
        }
        else {
                if (mainPlayer) {
                    for (size_t i = 0; i < mPuppetHolder->getSize(); i++)
                    {
                        PuppetInfo *curInfo = Client::getPuppetInfo(i);
                        if(curInfo->isConnected && curInfo->isInSameStage && curInfo->isIt) { 
                            float pupDist = al::calcDistance(mainPlayer, curInfo->playerPos); // TODO: remove distance calculations and use hit sensors to determine this

                            if(pupDist < 200.f && mainPlayer->mDimKeeper->is2DModel == curInfo->is2D) {
                                if(!PlayerFunction::isPlayerDeadStatus(mainPlayer)) {
                                    mInvulnTime = 5;
                                    mInfo->mIsPlayerIt = false;
                                    //mainPlayer->startDemoPuppetable();
                                    al::setVelocityZero(mainPlayer);

                                    // play the punch animation if you're it and you tag someone. this is very hit or miss right now so it'll have to be fixed later
                                    mainPlayer->mPlayerAnimator->endSubAnim();
                                    mainPlayer->mPlayerAnimator->startAnim("Punch");
                                    
                                    //mModeTimer->disableTimer();
                                    mModeLayout->showUntagged();

                                    Client::sendTagInfPacket();
                                }
                            } else if (PlayerFunction::isPlayerDeadStatus(mainPlayer)) {
                            
                                mInfo->mIsPlayerIt = false;
                                //mModeTimer->disableTimer();
                                mModeLayout->showUntagged();

                                Client::sendTagInfPacket();

                            }
                        }
                    }
                }
            }
            
    }
    mModeTimer->updateTimer();
    // make sure the invulnerability timer always ticks down until 0
    if (mInvulnTime > 0)
        mInvulnTime -= Time::deltaTime;

    if (al::isPadTriggerUp(-1) && !al::isPadHoldZL(-1))
    {
        mInfo->mIsPlayerIt = !mInfo->mIsPlayerIt;

        mModeTimer->toggleTimer();

        if(!mInfo->mIsPlayerIt) {
            mInvulnTime = 0;
            mModeLayout->showUntagged();
        } 
        else {
            mModeLayout->showTagged();
        }

        Client::sendTagInfPacket();
    }  
    mInfo->mTimeLimit = mModeTimer->getTime();
}