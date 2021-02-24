/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_form_type.h"

#include "doticu_skypal/intrinsic.h"

namespace doticu_skypal {

    class Bases_t
    {
    public:
        static String_t Class_Name();
        static void     Register_Me(V::Machine_t* machine);

    public:
        static Vector_t<Form_t*> From_References(Vector_t<Reference_t*> refs, String_t mode = ".");
    };

}
