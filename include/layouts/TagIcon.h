#pragma once

#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"
#include "al/util/NerveUtil.h"

#include "logger.hpp"
#include "server/gamemode/GameModeTimer.hpp"

// TODO: kill layout if going through loading zone or paused

class TagIcon : public al::LayoutActor {
    public:
        TagIcon(const char* name, const al::LayoutInitInfo& initInfo);

        void appear() override;

        bool tryStart();
        bool tryEnd();

        void showUntagged();
        void showTagged();
        
        void exeAppear();
        void exeWait();
        void exeEnd();

    private:
        struct TagInfo *mInfo;
};

namespace {
    NERVE_HEADER(TagIcon, Appear)
    NERVE_HEADER(TagIcon, Wait)
    NERVE_HEADER(TagIcon, End)
}