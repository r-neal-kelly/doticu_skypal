/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/skylib.h"
#include "doticu_skylib/virtual.h"

namespace doticu_skylib {}
namespace skylib = doticu_skylib;

namespace doticu_references {

    using Bool_t        = skylib::Bool_t;
    using Int_t         = skylib::Int_t;
    using Float_t       = skylib::Float_t;
    using String_t      = skylib::String_t;

    template <typename T>
    using Vector_t      = skylib::Vector_t<T>;

    using Keyword_t     = skylib::Keyword_t;
    using Reference_t   = skylib::Reference_t;

}
