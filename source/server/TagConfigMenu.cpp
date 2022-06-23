#include "server/TagConfigMenu.hpp"
#include <cmath>
#include "logger.hpp"
#include "server/HideAndSeekMode.hpp"
#include "server/Client.hpp"

TagConfigMenu::TagConfigMenu() : GameModeConfigMenu() {}

void TagConfigMenu::initMenu(const al::LayoutInitInfo &initInfo) {
    
}

const sead::WFixedSafeString<0x200> *TagConfigMenu::getStringData() {
    sead::SafeArray<sead::WFixedSafeString<0x200>, mItemCount>* gamemodeConfigOptions =
        new sead::SafeArray<sead::WFixedSafeString<0x200>, mItemCount>();

    gamemodeConfigOptions->mBuffer[0].copy(u"Hi");
    gamemodeConfigOptions->mBuffer[1].copy(u"Toggle H&S Gravity Off");

    return gamemodeConfigOptions->mBuffer;
}

bool TagConfigMenu::updateMenu(int selectIndex) {

    TagInfo *curMode = (TagInfo*)Client::getModeInfo();

    Logger::log("Setting Gravity Mode.\n");

    if (!curMode) {
        Logger::log("Unable to Load Mode info!\n");
        return true;   
    }
    
    switch (selectIndex) {
        case 0: {
            if (Client::isSelectedMode(GameMode::TAG)) {
                //curMode->mIsUseGravity = true;
            }
            return true;
        }
        case 1: {
            if (Client::isSelectedMode(GameMode::TAG)) {
                //curMode->mIsUseGravity = false;
            }
            return true;
        }
        default:
            Logger::log("Failed to interpret Index!\n");
            return false;
    }
    
}