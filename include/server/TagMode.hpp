#pragma once

#include <math.h>
#include "al/camera/CameraTicket.h"
#include "gamemode/GameModeBase.hpp"
#include "gamemode/GameModeInfoBase.hpp"
#include "server/gamemode/GameModeConfigMenu.hpp"
#include "server/gamemode/GameModeTimer.hpp"
#include "server/TagConfigMenu.hpp"

struct TagInfo : GameModeInfoBase {
    TagInfo() { mMode = GameMode::TAG; }
    bool mIsPlayerIt = false;
    GameTime mTimeLimit;
};

class TagMode : public GameModeBase {
    public:
        TagMode(const char* name);

        void init(GameModeInitInfo const& info) override;

        virtual void begin() override;
        virtual void update() override;
        virtual void end() override;

        bool isPlayerIt() const { return mInfo->mIsPlayerIt; };

        void setPlayerTagState(bool state) { mInfo->mIsPlayerIt = state; }

        void setCameraTicket(al::CameraTicket *ticket) {mTicket = ticket;}

    private:
        float mInvulnTime = 0.0f;
        GameModeTimer* mModeTimer = nullptr;
        TagIcon *mModeLayout = nullptr;
        TagInfo* mInfo = nullptr;
        al::CameraTicket *mTicket = nullptr;

};