/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game_macros.h"

#include "doticu_skypal/consts.h"

namespace doticu_skypal {

    const Version_t<u16> Consts_t::Skyrim::Required_Version()   { DEFINE_VERSION(u16, 1, 5, 97, 0); }

    const Version_t<u16> Consts_t::SKSE::Minimum_Version()  { DEFINE_VERSION(u16, 2, 0, 17); }

    const Version_t<u16> Consts_t::SkyPal::Current_Version()    { DEFINE_VERSION(u16, 1, 0, 3); }

}
