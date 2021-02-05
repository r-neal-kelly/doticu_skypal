; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname SkyPal_Enum_Collision_Layer_Type hidden

; Sadly, these can't be used directly unless a .esp file is added.
; So just use it as a reference and copy the number.

int property    k_UNIDENTIFIED                  = 0     autoReadOnly
int property    k_STATIC                        = 1     autoReadOnly
int property    k_ANIMATED_STATIC               = 2     autoReadOnly
int property    k_TRANSPARENT                   = 3     autoReadOnly
int property    k_CLUTTER                       = 4     autoReadOnly
int property    k_WEAPON                        = 5     autoReadOnly
int property    k_PROJECTILE                    = 6     autoReadOnly
int property    k_SPELL                         = 7     autoReadOnly
int property    k_BIPED                         = 8     autoReadOnly
int property    k_TREES                         = 9     autoReadOnly
int property    k_PROPS                         = 10    autoReadOnly
int property    k_WATER                         = 11    autoReadOnly
int property    k_TRIGGER                       = 12    autoReadOnly
int property    k_TERRAIN                       = 13    autoReadOnly
int property    k_TRAP                          = 14    autoReadOnly
int property    k_NON_COLLIDABLE                = 15    autoReadOnly
int property    k_CLOUD_TRAP                    = 16    autoReadOnly
int property    k_GROUND                        = 17    autoReadOnly
int property    k_PORTAL                        = 18    autoReadOnly
int property    k_SMALL_DEBRIS                  = 19    autoReadOnly
int property    k_LARGE_DEBRIS                  = 20    autoReadOnly
int property    k_ACOUSTIC_SPACE                = 21    autoReadOnly
int property    k_ACTOR_ZONE                    = 22    autoReadOnly
int property    k_PROJECTILE_ZONE               = 23    autoReadOnly
int property    k_GAS_TRAP                      = 24    autoReadOnly
int property    k_SHELL_CASING                  = 25    autoReadOnly
int property    k_SMALL_TRANSPARENT             = 26    autoReadOnly
int property    k_INVISIBLE_WALL                = 27    autoReadOnly
int property    k_SMALL_ANIMATED_TRANSPARENT    = 28    autoReadOnly
int property    k_WARD                          = 29    autoReadOnly
int property    k_CHARACTER_CONTROLLER          = 30    autoReadOnly
int property    k_STAIR_HELPER                  = 31    autoReadOnly
int property    k_DEAD_BIPED                    = 32    autoReadOnly
int property    k_NO_CHARACTER_CONTROLLER_BIPED = 33    autoReadOnly
int property    k_AVOID_BOX                     = 34    autoReadOnly
int property    k_COLLISION_BOX                 = 35    autoReadOnly
int property    k_CAMERA_SPHERE                 = 36    autoReadOnly
int property    k_DOOR_DETECTION                = 37    autoReadOnly
int property    k_CONE_PROJECTILE               = 38    autoReadOnly
int property    k_CAMERA                        = 39    autoReadOnly
int property    k_ITEM_PICKER                   = 40    autoReadOnly
int property    k_LINE_OF_SIGHT                 = 41    autoReadOnly
int property    k_PATH_PICKER                   = 42    autoReadOnly
int property    k_CUSTOM_PICKER_1               = 43    autoReadOnly
int property    k_CUSTOM_PICKER_2               = 44    autoReadOnly
int property    k_SPELL_EXPLOSION               = 45    autoReadOnly
int property    k_DROP_PICKER                   = 46    autoReadOnly
int property    k_DEAD_ACTOR_ZONE               = 47    autoReadOnly
int property    k_FALLING_TRAP_TRIGGER          = 48    autoReadOnly
int property    k_NAVCUT                        = 49    autoReadOnly
int property    k_CRITTER                       = 50    autoReadOnly
int property    k_SPELL_TRIGGER                 = 51    autoReadOnly
int property    k_LIVING_AND_DEAD_ACTORS        = 52    autoReadOnly
int property    k_DETECTION                     = 53    autoReadOnly
int property    k_TRAP_TRIGGER                  = 54    autoReadOnly
