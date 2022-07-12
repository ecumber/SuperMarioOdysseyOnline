#pragma once

#include <cstddef>
#include "crc32.h"
#include "basis/seadTypes.h"

namespace CaptureAnims {

    enum class Type : s16 {
        Unknown = -1,
        // Capture Anims
        BubbleCannonJump,
        Down,
        HackCancelJump,
        HackHighJump,
        HackJump,
        HackStart,
        HackStartDown,
        HackWait,
        HackWaitSpeedy,
        LandFrontDown,
        LandFrontUp,
        MoveSpeedy,
        Up,
        Angry,
        AppearSign,
        AppearStart,
        AttackSuccess,
        Blow,
        BlowDown,
        Clash,
        Coverd,
        DamageCap,
        Find,
        HackCharge,
        HackChargeFull,
        HackChargeTurn,
        HackRunCoverd,
        PressDown,
        RunCoverd,
        RunNaked,
        Swoon,
        SwoonEnd,
        SwoonStart,
        Trampled,
        TrampledEnd,
        TurnCoverd,
        TurnNaked,
        BlowEnd,
        BlowSign,
        BlowStart,
        BlowWide,
        Reaction,
        Charge,
        ChargeStart,
        Dummy,
        Idle,
        ReactionCap,
        ReactionCapSand,
        ReactionJump,
        ReactionJumpSand,
        RunHack,
        RunStartHack,
        WaitHack,
        Attack,
        AttackHit,
        AttackSecond,
        AttackSecondSign,
        AttackSign,
        HackAttack,
        HackAttackJump,
        HackAttackMiss,
        HackAttackQuick,
        HackJumpEnd,
        HackJumpHigh,
        JumpEnd,
        JumpStart,
        PressDownBlow,
        PressDownPress,
        SwoonStartLand,
        HighFall,
        HighJump,
        LandSwim,
        NpcFall,
        NpcJump,
        NpcJumpStart,
        RunFast,
        RunSlow,
        RunStay,
        Swim,
        SwimHackStart,
        SwimReaction,
        SwimSwoon,
        SwimSwoonEnd,
        SwimSwoonStart,
        SwimSwoonStartLand,
        SwoonStartFall,
        UpperPunch,
        Appear,
        Shot,
        SwoonTrampled,
        AttackEnd,
        AttackStart,
        MoveEnd,
        MoveStart,
        Recover,
        Trample,
        Expand,
        ExpandAir,
        ExpandEnemy,
        ExpandSign,
        ExpandSignEnemy,
        ExpandWait,
        ExpandWaitEnd,
        Hold,
        Shrink,
        ShrinkAir,
        ShrinkReactionHead,
        ShrinkReactionHip,
        TurnEnemy,
        TurnHack,
        WaitAir,
        FallNormal,
        Glide,
        GlideDrop,
        GlideL,
        GlideLStart,
        GlideR,
        GlideRStart,
        GlideRise,
        GlideStart,
        HackEnd,
        HackEndFly,
        JumpEndNormal,
        ReactionTrampled,
        Talk,
        WaitNormal,
        WaitSandSink,
        AttackTrample,
        AttackUp,
        Break,
        BreakGroundHit,
        BreakReaction,
        BreakWait,
        FallFly,
        Fly,
        FlyChase,
        FlyWait,
        RecoverSign,
        Boost,
        BoostStart,
        Explosion,
        FallDown,
        FlyWaitStart,
        Standby,
        Turbo,
        AttackTower,
        DashTower,
        DashTowerBottom,
        FallTower,
        FindTower,
        HackEndTower,
        JumpTower,
        LandTower,
        Miss,
        MissTower,
        PressDownTower,
        Reset,
        RideOn,
        RideOnTower,
        RunTower,
        RunTowerBottom,
        SandGeyser,
        SandGeyserTower,
        SandWaitTower,
        SandWalkTower,
        SlideTower,
        SwoonLoop,
        WaitTower,
        WalkTower,
        WalkTowerBottom,
        EnemyRun,
        HackRun,
        Choke,
        ChokeEnd,
        ChokeStart,
        HackStartChoke,
        Look,
        Swallow,
        SwoonChoke,
        SwoonEndChoke,
        SwoonStartChoke,
        Vomit,
        WaitChoke,
        DashR,
        FishingUp,
        FishingUpGold,
        JumpGround,
        ReactionWall,
        RollingRail,
        RollingRailReverse,
        RollingReverse,
        SwimStart,
        SwimSurfaceEnemy,
        SwimWaitStart,
        TurnPlayer,
        WaitGround,
        AdlibWait,
        Generate,
        JumpEndHigh,
        JumpEndLow,
        Stretch,
        StretchFall,
        StretchRun,
        StretchWait,
        UpperObjStart,
        UpperObjWait,
        BlowDownCommon,
        PressDownCommon,
        Reload,
        Shoot,
        SwoonReaction,
        AttackMove,
        AttackMoveForest,
        AttackWaitL,
        AttackWaitR,
        DashAfterL,
        DashAfterR,
        DashL,
        EnemyAttack,
        EnemyAttackL,
        EnemyAttackLEnd,
        EnemyAttackLStart,
        EnemyAttackR,
        EnemyAttackREnd,
        EnemyAttackRStart,
        EnemyAttackSign,
        EnemyFall,
        EnemyFallStart,
        EnemyLand,
        EnemyRunStart,
        FindMario,
        FootHoldJumpL,
        FootHoldJumpR,
        FootHoldL,
        FootHoldR,
        HackStartShort,
        HackStartWithTurn,
        ListPose,
        Lost,
        MoveTouch,
        NoticeSniff,
        ReactionSeaOfTrees,
        RunAfterL,
        RunAfterR,
        RunL,
        RunR,
        RunStartL,
        RunStartR,
        SleepReactionHipDrop,
        SleepSeaOfTrees,
        SwoonStartDashClash,
        TurnEndL,
        TurnEndR,
        TurnL180,
        TurnL90,
        TurnR180,
        TurnR90,
        WaitL,
        WaitR,
        WaitSniff,
        WakeUpSwoonStart,
        WalkAfterL,
        WalkAfterR,
        WalkEndL,
        WalkEndR,
        WalkGroundL,
        WalkGroundR,
        WalkL,
        WalkR,
        WalkStart,
        WalkStartL,
        WalkStartR,
        AppearBall,
        JumpStick,
        SpinL,
        SpinR,
        SpinThrustL,
        SpinThrustR,
        Stick,
        StickBendHorizontal,
        StickBendVertical,
        Thrust,
        ThrustCancel,
        ThrustEnd,
        ThrustSign,
        ThrustWait,
        TrampleDown,
        AttackPull,
        Back,
        BackEnd,
        BackReturn,
        HackDash,
        HackDashPull,
        HackMove,
        HackPull,
        HackPullStart,
        HitAction,
        HitEnd,
        HoleIn,
        Return,
        Bubble,
        // All Capture Actions
        Bull,
        Byugo,
        BlowStartEnemy,
        BlowStartHack,
        IdleHack,
        Stop,
        FireBros,
        Frog,
        HackLand,
        HackOff,
        HackOn,
        NpcLand,
        HammerBros,
        Imomu,
        ExpandAirEnemy,
        ExpandAirHack,
        ExpandHack,
        ExpandSignHack,
        ShrinkAirHack,
        ShrinkEnemy,
        ShrinkHack,
        ShrinkReactionHeadEnemy,
        ShrinkReactionHeadHack,
        ShrinkReactionHipEnemy,
        ShrinkReactionHipHack,
        Kakku,
        FallHack,
        KaronWing,
        EnemyFly,
        HackFly,
        Killer,
        Default,
        SignExplosion,
        Kuribo,
        KuriboWing,
        PackunFire,
        ChokeDefault,
        ChokeCap,
        Eat,
        VomitCap,
        VomitDefault,
        PackunPoison,
        EatDown,
        Pukupuku,
        DashRSurface,
        DashRWater,
        RollingRSurface,
        RollingRWater,
        RollingLSurface,
        RollingLWater,
        SwimStartSurface,
        SwimStartWater,
        SwimWaitStartSurface,
        SwimWaitStartWater,
        SwimWaitSurface,
        SwimWaitWater,
        SwimWaitWaterHack,
        SwimWater,
        WaitMove,
        AdlibWaitMove,
        RunMove,
        FallMove,
        JumpEndEnemy,
        JumpEndLowHack,
        JumpEndHighHack,
        Tank,
        BlowDownCaptureParade,
        PressDownCaptureParade,
        MoveL,
        MoveR,
        MoveAfterL,
        MoveAfterR,
        MoveStartL,
        MoveStartR,
        Tsukkun,
        StickBend,
        ThrustEnemy,
        ThrustHack,
        ThrustWaitEnemy,
        ThrustWaitHack,
        Wanwan,
        BackChain,
        BackDirect,
        WanwanBig,
        End
    };

    static constexpr size_t ToValue(Type type) { return static_cast<std::uint16_t>(type); }

    static constexpr Type ToType(std::uint16_t value) {return static_cast<Type>(value);}

    static constexpr std::array<const char*, ToValue(Type::End)> s_Strs {
        // Capture Anims
        "BubbleCannonJump", "Down", "HackCancelJump", "HackHighJump", "HackJump", "HackStart",
        "HackStartDown", "HackWait", "HackWaitSpeedy", "LandFrontDown", "LandFrontUp",
        "MoveSpeedy", "Up", "Angry", "AppearSign", "AppearStart", "AttackSuccess", "Blow",
        "BlowDown", "Clash", "Coverd", "DamageCap", "Find", "HackCharge", "HackChargeFull",
        "HackChargeTurn", "HackRunCoverd", "PressDown", "RunCoverd", "RunNaked", "Swoon",
        "SwoonEnd", "SwoonStart", "Trampled", "TrampledEnd", "TurnCoverd", "TurnNaked",
        "BlowEnd", "BlowSign", "BlowStart", "BlowWide", "Reaction", "Charge", "ChargeStart",
        "Dummy", "Idle", "ReactionCap", "ReactionCapSand", "ReactionJump", "ReactionJumpSand",
        "RunHack", "RunStartHack", "WaitHack", "Attack", "AttackHit", "AttackSecond",
        "AttackSecondSign", "AttackSign", "HackAttack", "HackAttackJump", "HackAttackMiss",
        "HackAttackQuick", "HackJumpEnd", "HackJumpHigh", "JumpEnd", "JumpStart",
        "PressDownBlow", "PressDownPress", "SwoonStartLand", "HighFall", "HighJump", "LandSwim",
        "NpcFall", "NpcJump", "NpcJumpStart", "RunFast", "RunSlow", "RunStay", "Swim",
        "SwimHackStart", "SwimReaction", "SwimSwoon", "SwimSwoonEnd", "SwimSwoonStart",
        "SwimSwoonStartLand", "SwoonStartFall", "UpperPunch", "Appear", "Shot", "SwoonTrampled",
        "AttackEnd", "AttackStart", "MoveEnd", "MoveStart", "Recover", "Trample", "Expand",
        "ExpandAir", "ExpandEnemy", "ExpandSign", "ExpandSignEnemy", "ExpandWait",
        "ExpandWaitEnd", "Hold", "Shrink", "ShrinkAir", "ShrinkReactionHead",
        "ShrinkReactionHip", "TurnEnemy", "TurnHack", "WaitAir", "FallNormal", "Glide",
        "GlideDrop", "GlideL", "GlideLStart", "GlideR", "GlideRStart", "GlideRise",
        "GlideStart", "HackEnd", "HackEndFly", "JumpEndNormal", "ReactionTrampled", "Talk",
        "WaitNormal", "WaitSandSink", "AttackTrample", "AttackUp", "Break", "BreakGroundHit",
        "BreakReaction", "BreakWait", "FallFly", "Fly", "FlyChase", "FlyWait", "RecoverSign",
        "Boost", "BoostStart", "Explosion", "FallDown", "FlyWaitStart", "Standby", "Turbo",
        "AttackTower", "DashTower", "DashTowerBottom", "FallTower", "FindTower", "HackEndTower",
        "JumpTower", "LandTower", "Miss", "MissTower", "PressDownTower", "Reset", "RideOn",
        "RideOnTower", "RunTower", "RunTowerBottom", "SandGeyser", "SandGeyserTower",
        "SandWaitTower", "SandWalkTower", "SlideTower", "SwoonLoop", "WaitTower", "WalkTower",
        "WalkTowerBottom", "EnemyRun", "HackRun", "Choke", "ChokeEnd", "ChokeStart",
        "HackStartChoke", "Look", "Swallow", "SwoonChoke", "SwoonEndChoke", "SwoonStartChoke",
        "Vomit", "WaitChoke", "DashR", "FishingUp", "FishingUpGold", "JumpGround",
        "ReactionWall", "RollingRail", "RollingRailReverse", "RollingReverse", "SwimStart",
        "SwimSurfaceEnemy", "SwimWaitStart", "TurnPlayer", "WaitGround", "AdlibWait",
        "Generate", "JumpEndHigh", "JumpEndLow", "Stretch", "StretchFall", "StretchRun",
        "StretchWait", "UpperObjStart", "UpperObjWait", "BlowDownCommon", "PressDownCommon",
        "Reload", "Shoot", "SwoonReaction", "AttackMove", "AttackMoveForest", "AttackWaitL",
        "AttackWaitR", "DashAfterL", "DashAfterR", "DashL", "EnemyAttack", "EnemyAttackL",
        "EnemyAttackLEnd", "EnemyAttackLStart", "EnemyAttackR", "EnemyAttackREnd",
        "EnemyAttackRStart", "EnemyAttackSign", "EnemyFall", "EnemyFallStart", "EnemyLand",
        "EnemyRunStart", "FindMario", "FootHoldJumpL", "FootHoldJumpR", "FootHoldL",
        "FootHoldR", "HackStartShort", "HackStartWithTurn", "ListPose", "Lost", "MoveTouch",
        "NoticeSniff", "ReactionSeaOfTrees", "RunAfterL", "RunAfterR", "RunL", "RunR",
        "RunStartL", "RunStartR", "SleepReactionHipDrop", "SleepSeaOfTrees",
        "SwoonStartDashClash", "TurnEndL", "TurnEndR", "TurnL180", "TurnL90", "TurnR180",
        "TurnR90", "WaitL", "WaitR", "WaitSniff", "WakeUpSwoonStart", "WalkAfterL",
        "WalkAfterR", "WalkEndL", "WalkEndR", "WalkGroundL", "WalkGroundR", "WalkL", "WalkR",
        "WalkStart", "WalkStartL", "WalkStartR", "AppearBall", "JumpStick", "SpinL", "SpinR",
        "SpinThrustL", "SpinThrustR", "Stick", "StickBendHorizontal", "StickBendVertical",
        "Thrust", "ThrustCancel", "ThrustEnd", "ThrustSign", "ThrustWait", "TrampleDown",
        "AttackPull", "Back", "BackEnd", "BackReturn", "HackDash", "HackDashPull", "HackMove",
        "HackPull", "HackPullStart", "HitAction", "HitEnd", "HoleIn", "Return",
        // All Capture Actions
        "Bubble", "Bull", "Byugo", "BlowStartEnemy", "BlowStartHack", "IdleHack", "Stop",
        "FireBros", "Frog", "HackLand", "HackOff", "HackOn", "NpcLand", "HammerBros", "Imomu",
        "ExpandAirEnemy", "ExpandAirHack", "ExpandHack", "ExpandSignHack", "ShrinkAirHack",
        "ShrinkEnemy", "ShrinkHack", "ShrinkReactionHeadEnemy", "ShrinkReactionHeadHack",
        "ShrinkReactionHipEnemy", "ShrinkReactionHipHack", "Kakku", "FallHack", "KaronWing",
        "EnemyFly", "HackFly", "Killer", "Default", "SignExplosion", "Kuribo", "KuriboWing",
        "PackunFire", "ChokeDefault", "ChokeCap", "Eat", "VomitCap", "VomitDefault",
        "PackunPoison", "EatDown", "Pukupuku", "DashRSurface", "DashRWater", "RollingRSurface",
        "RollingRWater", "RollingLSurface", "RollingLWater", "SwimStartSurface",
        "SwimStartWater", "SwimWaitStartSurface", "SwimWaitStartWater", "SwimWaitSurface",
        "SwimWaitWater", "SwimWaitWaterHack", "SwimWater", "WaitMove", "AdlibWaitMove",
        "RunMove", "FallMove", "JumpEndEnemy", "JumpEndLowHack", "JumpEndHighHack", "Tank",
        "BlowDownCaptureParade", "PressDownCaptureParade", "MoveL", "MoveR", "MoveAfterL",
        "MoveAfterR", "MoveStartL", "MoveStartR", "Tsukkun", "StickBend", "ThrustEnemy",
        "ThrustHack", "ThrustWaitEnemy", "ThrustWaitHack", "Wanwan", "BackChain", "BackDirect",
        "WanwanBig"
    };

    // these ifdefs are really dumb but it makes clangd happy so /shrug
#ifndef ANALYZER
    static constexpr crc32::HashArray s_Hashes(s_Strs);
#endif

    static constexpr Type FindType(std::string_view const& str) {
#ifndef ANALYZER
        return ToType(s_Hashes.FindIndex(str));
#else
        return Type::Unknown;
#endif
    }

    static constexpr const char *FindStr(Type type) {
        const s16 type_ = (s16)type;
        if (0 <= type_ && type_ < s_Strs.size())
            return s_Strs[type_];
        else
            return "";
    }
}