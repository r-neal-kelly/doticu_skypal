/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/form_type.h"

#include "doticu_skypal/intrinsic.h"

namespace doticu_skypal {

    class References_t
    {
    public:
        static String_t Class_Name();
        static void     Register_Me(V::Machine_t* machine);

    public:
        static Vector_t<Reference_t*>   All();
        static Vector_t<Reference_t*>   Grid();

    public:
        static Vector_t<Reference_t*>   Filter_Base_Form_Types(Vector_t<Reference_t*> refs, Vector_t<Form_Type_e> form_types, String_t mode = "");
        static Vector_t<Reference_t*>   Filter_Bases_Form_List(Vector_t<Reference_t*> refs, Form_List_t* bases, String_t mode = "");
        static Vector_t<Reference_t*>   Filter_Distance(Vector_t<Reference_t*> refs, Float_t distance, Reference_t* from = nullptr, String_t mode = "<");
        static Vector_t<Reference_t*>   Filter_Form_Types(Vector_t<Reference_t*> refs, Vector_t<Form_Type_e> form_types, String_t mode = "");
        static Vector_t<Reference_t*>   Filter_Keywords(Vector_t<Reference_t*> refs, Vector_t<Keyword_t*> keywords, String_t mode = "|");

    public:
        static Vector_t<Reference_t*>   Sort_Distance(Vector_t<Reference_t*> refs, Reference_t* from = nullptr, String_t mode = "<");
    };

}