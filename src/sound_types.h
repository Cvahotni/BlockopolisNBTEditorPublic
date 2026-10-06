#pragma once

enum SoundType {
    MusicSound = 0,
    BlockSound = 1,
    UISound = 2,
    PlayerSound = 3,

    SoundTypeCount = 4
};

enum BlockSoundType {
    BlockBreak = 0, 
    BlockPlace = 1,
    BlockCrack = 2, 
    BlockStep = 3,
    BlockTransition = 4,
    BlockInteract = 5
};

enum WorldSoundType {
    ItemPickup = 0,
    ItemDrop = 1,
    Hurt = 2,
    Eat = 3
};