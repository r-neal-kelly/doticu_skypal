/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/skylib.h"
#include "doticu_skylib/virtual.h"
#include "doticu_skylib/filter.h"

#include "doticu_skylib/enum_collision_layer_type.h"

namespace doticu_skylib {}
namespace skylib = doticu_skylib;

namespace doticu_skypal {

    using u8                        = skylib::u8;
    using u16                       = skylib::u16;

    using Bool_t                    = skylib::Bool_t;
    using Int_t                     = skylib::Int_t;
    using Float_t                   = skylib::Float_t;
    using Double_t                  = skylib::Double_t;
    using String_t                  = skylib::String_t;
    using CString_t                 = skylib::CString_t;

    using Word_t                    = skylib::Word_t;

    template <typename T>
    using Vector_t                  = skylib::Vector_t<T>;

    template <typename T>
    using some                      = skylib::some<T>;
    template <typename T>
    using maybe                     = skylib::maybe<T>;
    template <typename T>
    using none                      = skylib::none<T>;

    template <typename ...Ts>
    using Filter_i                  = skylib::Filter_i<Ts...>;

    template <typename T>
    using Version_t                 = skylib::Version_t<T>;

    using Collision_Layer_Type_e    = skylib::Collision_Layer_Type_e;
    using Form_Type_e               = skylib::Form_Type_e;
    using Logic_Gate_e              = skylib::Logic_Gate_e;
    using Operator_e                = skylib::Operator_e;

    using Active_Magic_Effect_t     = skylib::Active_Magic_Effect_t;
    using Actor_t                   = skylib::Actor_t;
    using Alias_Base_t              = skylib::Alias_Base_t;
    using Form_t                    = skylib::Form_t;
    using Form_Factory_i            = skylib::Form_Factory_i;
    using Form_List_t               = skylib::Form_List_t;
    using Game_t                    = skylib::Game_t;
    using Keyword_t                 = skylib::Keyword_t;
    using OS_t                      = skylib::OS_t;
    using Player_t                  = skylib::Player_t;
    using Reference_t               = skylib::Reference_t;
    using Script_t                  = skylib::Script_t;

    namespace V {

        using Arguments_i           = skylib::Virtual::Arguments_i;
        using Arguments_t           = skylib::Virtual::Arguments_t;
        using Callback_i            = skylib::Virtual::Callback_i;
        using Callback_t            = skylib::Virtual::Callback_t;
        using Handle_t              = skylib::Virtual::Handle_t;
        using Machine_t             = skylib::Virtual::Machine_t;
        using Object_t              = skylib::Virtual::Object_t;
        using Stack_ID_t            = skylib::Virtual::Stack_ID_t;
        using Type_e                = skylib::Virtual::Type_e;
        using Variable_t            = skylib::Virtual::Variable_t;

        template <typename Intrinsic_t>
        using Variable_tt           = skylib::Virtual::Variable_tt<Intrinsic_t>;

    }

    namespace Filter {

        template <typename T> using State_c                 = skylib::Filter::State_c<T>;

        template <typename T> using Base_Form_Types_t       = skylib::Filter::Base_Form_Types_t<T>;
        template <typename T> using Bases_t                 = skylib::Filter::Bases_t<T>;
        template <typename T> using Collision_Layer_Types_t = skylib::Filter::Collision_Layer_Types_t<T>;
        template <typename T> using Deleted_t               = skylib::Filter::Deleted_t<T>;
        template <typename T> using Distances_t             = skylib::Filter::Distances_t<T>;
        template <typename T> using Enabled_t               = skylib::Filter::Enabled_t<T>;
        template <typename T> using Form_Types_t            = skylib::Filter::Form_Types_t<T>;
        template <typename T> using Keywords_t              = skylib::Filter::Keywords_t<T>;
        template <typename T> using Owners_t                = skylib::Filter::Owners_t<T>;
        template <typename T> using Potential_Thieves_t     = skylib::Filter::Potential_Thieves_t<T>;

    }

}
