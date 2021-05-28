/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_form_type.h"

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
        static Vector_t<Reference_t*>   From_Container(Reference_t* container);

    public:
        static Int_t                    Count_Disabled(Vector_t<Reference_t*> refs);
        static Int_t                    Count_Enabled(Vector_t<Reference_t*> refs);

    public:
        static void                     Change_Collision_Layer_Type(Vector_t<Reference_t*> refs, Collision_Layer_Type_e collision_layer_type);
        static void                     Disable(Vector_t<Reference_t*> refs);
        static void                     Enable(Vector_t<Reference_t*> refs);

    public:
        static Vector_t<Reference_t*>   Filter_Base_Form_Types(Vector_t<Reference_t*> refs, Vector_t<Form_Type_e> form_types, String_t mode = "");
        static Vector_t<Reference_t*>   Filter_Bases(Vector_t<Reference_t*> refs, Vector_t<Form_t*> bases, String_t mode = "");
        static Vector_t<Reference_t*>   Filter_Bases_Form_List(Vector_t<Reference_t*> refs, Form_List_t* bases, String_t mode = "");
        static Vector_t<Reference_t*>   Filter_Collision_Layer_Types(Vector_t<Reference_t*> refs, Vector_t<Collision_Layer_Type_e> collision_layer_types, String_t mode = "");
        static Vector_t<Reference_t*>   Filter_Deleted(Vector_t<Reference_t*> refs, String_t mode = "");
        static Vector_t<Reference_t*>   Filter_Distance(Vector_t<Reference_t*> refs, Float_t distance, Reference_t* from = nullptr, String_t mode = "<");
        static Vector_t<Reference_t*>   Filter_Enabled(Vector_t<Reference_t*> refs, String_t mode = "");
        static Vector_t<Reference_t*>   Filter_Form_Types(Vector_t<Reference_t*> refs, Vector_t<Form_Type_e> form_types, String_t mode = "");
        static Vector_t<Reference_t*>   Filter_Keywords(Vector_t<Reference_t*> refs, Vector_t<Keyword_t*> keywords, String_t mode = "|");
        static Vector_t<Reference_t*>   Filter_Owners(Vector_t<Reference_t*> refs, Vector_t<Actor_t*> owners, String_t mode = "|");
        static Vector_t<Reference_t*>   Filter_Potential_Thieves(Vector_t<Reference_t*> refs, Vector_t<Actor_t*> potential_thieves, String_t mode = "|");

    public:
        static Vector_t<Reference_t*>   Sort_Any_Name(Vector_t<Reference_t*> refs, String_t mode = "");
        static Vector_t<Reference_t*>   Sort_Distance(Vector_t<Reference_t*> refs, Reference_t* from = nullptr, String_t mode = "<");

    public:
        static Vector_t<Reference_t*>   All_Filter_Bases(Vector_t<Form_t*> bases, String_t mode = "");
        static Vector_t<Reference_t*>   All_Filter_Bases_Form_List(Form_List_t* bases, String_t mode = "");
        static Vector_t<Reference_t*>   Grid_Filter_Bases(Vector_t<Form_t*> bases, String_t mode = "");
        static Vector_t<Reference_t*>   Grid_Filter_Bases_Form_List(Form_List_t* bases, String_t mode = "");
    };

}
