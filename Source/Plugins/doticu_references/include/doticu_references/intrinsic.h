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

    using Index_t       = skylib::Index_t;

    template <typename T>
    using Vector_t      = skylib::Vector_t<T>;
    template <typename T>
    using Buffer_t      = skylib::Buffer_t<T>;

    template <typename T>
    using some          = skylib::some<T>;
    template <typename T>
    using maybe         = skylib::maybe<T>;
    template <typename T>
    using none          = skylib::none<T>;

    template <typename ...Ts>
    using Filter_i      = skylib::Filter_i<Ts...>;

    using Form_Type_e   = skylib::Form_Type_e;

    using Active_Magic_Effect_t = skylib::Active_Magic_Effect_t;
    using Alias_Base_t          = skylib::Alias_Base_t;
    using Form_t                = skylib::Form_t;
    using Keyword_t             = skylib::Keyword_t;
    using Reference_t           = skylib::Reference_t;

    namespace V {

        using Arguments_i   = skylib::Virtual::Arguments_i;
        using Arguments_t   = skylib::Virtual::Arguments_t;
        using Callback_i    = skylib::Virtual::Callback_i;
        using Callback_t    = skylib::Virtual::Callback_t;
        using Handle_t      = skylib::Virtual::Handle_t;
        using Machine_t     = skylib::Virtual::Machine_t;
        using Variable_t    = skylib::Virtual::Variable_t;

        template <typename Intrinsic_t>
        using Variable_tt   = skylib::Virtual::Variable_tt<Intrinsic_t>;

    }

}
