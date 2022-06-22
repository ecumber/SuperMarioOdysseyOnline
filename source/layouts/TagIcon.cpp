#include "layouts/TagIcon.h"
#include <cstdio>
#include <cstring>
#include "puppets/PuppetInfo.h"
#include "al/string/StringTmp.h"
#include "prim/seadSafeString.h"
#include "server/gamemode/GameModeTimer.hpp"
#include "server/TagMode.hpp"
#include "server/Client.hpp"
#include "al/util.hpp"
#include "logger.hpp"
#include "rs/util.hpp"
#include "main.hpp"

TagIcon::TagIcon(const char* name, const al::LayoutInitInfo& initInfo) : al::LayoutActor(name) {

    al::initLayoutActor(this, initInfo, "TagIcon", 0);

    mInfo = (TagInfo*)Client::getModeInfo();

    initNerve(&nrvTagIconEnd, 0);

    //what do you even call these
    al::hidePane(this, "TaggedIcon");
    al::hidePane(this, "UntaggedIcon");

    
    kill();

}

void TagIcon::appear() {

    al::startAction(this, "Appear", 0);

    al::setNerve(this, &nrvTagIconAppear);

    al::LayoutActor::appear();
}

bool TagIcon::tryEnd() {
    if (!al::isNerve(this, &nrvTagIconEnd)) {
        al::setNerve(this, &nrvTagIconEnd);
        return true;
    }
    return false;
}

bool TagIcon::tryStart() {

    if (!al::isNerve(this, &nrvTagIconWait) && !al::isNerve(this, &nrvTagIconAppear)) {

        appear();

        return true;
    }

    return false;
}

void TagIcon::exeAppear() {
    if (al::isActionEnd(this, 0)) {
        al::setNerve(this, &nrvTagIconWait);
    }
}

void TagIcon::exeWait() {
    if (al::isFirstStep(this)) {
        al::startAction(this, "Wait", 0);
    }

    GameTime &curTime = mInfo->mTimeLimit;

    if (curTime.mHours > 0) {
        al::setPaneStringFormat(this, "TxtCounter", "%01d:%02d:%02d", curTime.mHours, curTime.mMinutes,
                            curTime.mSeconds);
    } else {
        al::setPaneStringFormat(this, "TxtCounter", "%02d:%02d", curTime.mMinutes,
                            curTime.mSeconds);
    }

    

    int playerCount = Client::getConnectCount();

    if (playerCount > 0) {

        char playerNameBuf[0x100] = {0}; // max of 16 player names if player name size is 0x10

        sead::BufferedSafeStringBase<char> playerList =
            sead::BufferedSafeStringBase<char>(playerNameBuf, 0x200);
    
        for (size_t i = 0; i < playerCount; i++) {
            PuppetInfo* curPuppet = Client::getPuppetInfo(i);
            if (curPuppet->isConnected && (curPuppet->isIt == mInfo->mIsPlayerIt)) {
                playerList.appendWithFormat("%s\n", curPuppet->puppetName);
            }
        }
        
        al::setPaneStringFormat(this, "TxtPlayerList", playerList.cstr());
    }
    
}

void TagIcon::exeEnd() {

    if (al::isFirstStep(this)) {
        al::startAction(this, "End", 0);
    }

    if (al::isActionEnd(this, 0)) {
        kill();
    }
}

void TagIcon::showHiding() {
    al::hidePane(this, "SeekingIcon");
    al::showPane(this, "HidingIcon");
}

void TagIcon::showSeeking() {
    al::hidePane(this, "HidingIcon");
    al::showPane(this, "SeekingIcon");
}

namespace {
    NERVE_IMPL(TagIcon, Appear)
    NERVE_IMPL(TagIcon, Wait)
    NERVE_IMPL(TagIcon, End)
}