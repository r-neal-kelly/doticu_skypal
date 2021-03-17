/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/enum_operator.h"

#include "doticu_skylib/reference.h"

#include "doticu_skylib/virtual_macros.h"

#include "doticu_skypal/main.h"
#include "doticu_skypal/bases.h"

namespace doticu_skypal {

    String_t Bases_t::Class_Name()
    {
        DEFINE_CLASS_NAME("skypal_bases");
    }

    void Bases_t::Register_Me(V::Machine_t* machine)
    {
        String_t class_name = Class_Name();

        #define STATIC(STATIC_NAME_, WAITS_FOR_FRAME_, RETURN_TYPE_, STATIC_, ...)  \
        SKYLIB_M                                                                    \
            BIND_STATIC(machine, class_name, STATIC_NAME_, WAITS_FOR_FRAME_,        \
                        RETURN_TYPE_, STATIC_, __VA_ARGS__);                        \
        SKYLIB_W

        STATIC("From_References", false, Vector_t<Form_t*>, From_References, Vector_t<Reference_t*>, String_t);

        #undef STATIC
    }

    Vector_t<Form_t*> Bases_t::From_References(Vector_t<Reference_t*> refs, String_t mode)
    {
        Vector_t<some<Reference_t*>>& some_refs = Main_t::Validate_Formables(refs);
        size_t some_ref_count = some_refs.size();

        Vector_t<some<Form_t*>> some_bases;
        some_bases.reserve(some_ref_count);

        Operator_e operator_e = Operator_e::From_String(mode);
        if (operator_e == Operator_e::ELLIPSIS) {
            for (size_t idx = 0, end = some_ref_count; idx < end; idx += 1) {
                some<Reference_t*> ref = some_refs[idx];
                if (ref->base_form) {
                    some_bases.push_back(ref->base_form());
                }
            }
        } else {
            for (size_t idx = 0, end = some_ref_count; idx < end; idx += 1) {
                some<Reference_t*> ref = some_refs[idx];
                if (ref->base_form && !some_bases.Has(ref->base_form())) {
                    some_bases.push_back(ref->base_form());
                }
            }
        }

        return reinterpret_cast<Vector_t<Form_t*>&>(some_bases);
    }

}
