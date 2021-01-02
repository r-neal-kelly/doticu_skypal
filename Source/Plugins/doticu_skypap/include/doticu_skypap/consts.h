/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skypap/intrinsic.h"

namespace doticu_skypap {

    class Consts_t
    {
    public:
        class Skyrim
        {
        public:
            static const Version_t<u16> Required_Version();
        };

        class SKSE
        {
        public:
            static const Version_t<u16> Minimum_Version();
        };

        class Skylib
        {
        public:
            static const Version_t<u16> Current_Version();
        };
    };

}
