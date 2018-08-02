#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

// Sounds
#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(ZELDA_PUZZLE)
    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(COLEMAK_SOUND), \
                                  SONG(DVORAK_SOUND) \
                                }
#endif

// Most tactile encoders have detents every 4 stages
#define ENCODER_RESOLUTION 4

// Backlighting
#undef BACKLIGHT_LEVELS
#define BACKLIGHT_LEVELS 2

// Tap dance
#define TAPPING_TERM 250

#endif
