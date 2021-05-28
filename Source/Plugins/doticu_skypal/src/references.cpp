/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <algorithm>

#include "doticu_skylib/enum_form_type.h"
#include "doticu_skylib/enum_logic_gate.h"
#include "doticu_skylib/enum_operator.h"

#include "doticu_skylib/component_keywords.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/form_factory.h"
#include "doticu_skylib/form_list.h"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/keyword.h"
#include "doticu_skylib/os.h"
#include "doticu_skylib/player.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/script.h"

#include "doticu_skylib/virtual_macros.h"

#include "doticu_skylib/filter_base_form_types.h"
#include "doticu_skylib/filter_bases.h"
#include "doticu_skylib/filter_collision_layer_types.h"
#include "doticu_skylib/filter_deleted.h"
#include "doticu_skylib/filter_distances.h"
#include "doticu_skylib/filter_enabled.h"
#include "doticu_skylib/filter_form_types.h"
#include "doticu_skylib/filter_keywords.h"
#include "doticu_skylib/filter_owners.h"
#include "doticu_skylib/filter_potential_thieves.h"

#include "doticu_skypal/main.h"
#include "doticu_skypal/references.h"

namespace doticu_skypal {

    String_t References_t::Class_Name()
    {
        DEFINE_CLASS_NAME("skypal_references");
    }

    void References_t::Register_Me(V::Machine_t* machine)
    {
        String_t class_name = Class_Name();

        #define STATIC(STATIC_NAME_, WAITS_FOR_FRAME_, RETURN_TYPE_, STATIC_, ...)  \
        SKYLIB_M                                                                    \
            BIND_STATIC(machine, class_name, STATIC_NAME_, WAITS_FOR_FRAME_,        \
                        RETURN_TYPE_, STATIC_, __VA_ARGS__);                        \
        SKYLIB_W

        STATIC("All", false, Vector_t<Reference_t*>, All);
        STATIC("Grid", false, Vector_t<Reference_t*>, Grid);
        STATIC("From_Container", false, Vector_t<Reference_t*>, From_Container, Reference_t*);

        STATIC("Count_Disabled", false, Int_t, Count_Disabled, Vector_t<Reference_t*>);
        STATIC("Count_Enabled", false, Int_t, Count_Enabled, Vector_t<Reference_t*>);

        STATIC("Change_Collision_Layer_Type", false, void, Change_Collision_Layer_Type, Vector_t<Reference_t*>, Collision_Layer_Type_e);
        STATIC("Disable", false, void, Disable, Vector_t<Reference_t*>);
        STATIC("Enable", false, void, Enable, Vector_t<Reference_t*>);

        STATIC("Filter_Base_Form_Types", false, Vector_t<Reference_t*>, Filter_Base_Form_Types, Vector_t<Reference_t*>, Vector_t<Form_Type_e>, String_t);
        STATIC("Filter_Bases", false, Vector_t<Reference_t*>, Filter_Bases, Vector_t<Reference_t*>, Vector_t<Form_t*>, String_t);
        STATIC("Filter_Bases_Form_List", false, Vector_t<Reference_t*>, Filter_Bases_Form_List, Vector_t<Reference_t*>, Form_List_t*, String_t);
        STATIC("Filter_Collision_Layer_Types", false, Vector_t<Reference_t*>, Filter_Collision_Layer_Types, Vector_t<Reference_t*>, Vector_t<Collision_Layer_Type_e>, String_t);
        STATIC("Filter_Deleted", false, Vector_t<Reference_t*>, Filter_Deleted, Vector_t<Reference_t*>, String_t);
        STATIC("Filter_Distance", false, Vector_t<Reference_t*>, Filter_Distance, Vector_t<Reference_t*>, Float_t, Reference_t*, String_t);
        STATIC("Filter_Enabled", false, Vector_t<Reference_t*>, Filter_Enabled, Vector_t<Reference_t*>, String_t);
        STATIC("Filter_Form_Types", false, Vector_t<Reference_t*>, Filter_Form_Types, Vector_t<Reference_t*>, Vector_t<Form_Type_e>, String_t);
        STATIC("Filter_Keywords", false, Vector_t<Reference_t*>, Filter_Keywords, Vector_t<Reference_t*>, Vector_t<Keyword_t*>, String_t);
        STATIC("Filter_Owners", false, Vector_t<Reference_t*>, Filter_Owners, Vector_t<Reference_t*>, Vector_t<Actor_t*>, String_t);
        STATIC("Filter_Potential_Thieves", false, Vector_t<Reference_t*>, Filter_Potential_Thieves, Vector_t<Reference_t*>, Vector_t<Actor_t*>, String_t);

        STATIC("Sort_Distance", false, Vector_t<Reference_t*>, Sort_Distance, Vector_t<Reference_t*>, Reference_t*, String_t);

        STATIC("All_Filter_Bases", false, Vector_t<Reference_t*>, All_Filter_Bases, Vector_t<Form_t*>, String_t);
        STATIC("All_Filter_Bases_Form_List", false, Vector_t<Reference_t*>, All_Filter_Bases_Form_List, Form_List_t*, String_t);
        STATIC("Grid_Filter_Bases", false, Vector_t<Reference_t*>, Grid_Filter_Bases, Vector_t<Form_t*>, String_t);
        STATIC("Grid_Filter_Bases_Form_List", false, Vector_t<Reference_t*>, Grid_Filter_Bases_Form_List, Form_List_t*, String_t);

        #undef STATIC
    }

    /* Getters */

    Vector_t<Reference_t*> References_t::All()
    {
        return *reinterpret_cast<Vector_t<Reference_t*>*>(&Reference_t::All_References());
    }

    Vector_t<Reference_t*> References_t::Grid()
    {
        return *reinterpret_cast<Vector_t<Reference_t*>*>(&Reference_t::Grid_References());
    }

    Vector_t<Reference_t*> References_t::From_Container(Reference_t* container)
    {
        if (container) {
            return *reinterpret_cast<Vector_t<Reference_t*>*>(&container->Contained_References());
        } else {
            return Vector_t<Reference_t*>();
        }
    }

    /* Counters */

    Int_t References_t::Count_Disabled(Vector_t<Reference_t*> refs)
    {
        Int_t count = 0;

        for (size_t idx = 0, end = refs.size(); idx < end; idx += 1) {
            maybe<Reference_t*> ref = refs[idx];
            if (ref && ref->Is_Disabled()) {
                count += 1;
            }
        }

        return count;
    }

    Int_t References_t::Count_Enabled(Vector_t<Reference_t*> refs)
    {
        Int_t count = 0;

        for (size_t idx = 0, end = refs.size(); idx < end; idx += 1) {
            maybe<Reference_t*> ref = refs[idx];
            if (ref && ref->Is_Enabled()) {
                count += 1;
            }
        }

        return count;
    }

    /* Helpers */

    void References_t::Change_Collision_Layer_Type(Vector_t<Reference_t*> refs, Collision_Layer_Type_e collision_layer_type)
    {
        if (collision_layer_type) {
            for (size_t idx = 0, end = refs.size(); idx < end; idx += 1) {
                maybe<Reference_t*> ref = refs[idx];
                if (ref) {
                    ref->Collision_Layer_Type(collision_layer_type);
                }
            }
        }
    }

    void References_t::Disable(Vector_t<Reference_t*> refs)
    {
        some<Script_t*> script = Script_t::Create();
        script->Command("Disable");
        for (size_t idx = 0, end = refs.size(); idx < end; idx += 1) {
            maybe<Reference_t*> ref = refs[idx];
            if (ref) { // check if valid, deleted?
                script->Execute(ref());
            }
        }
        Script_t::Destroy(script);
    }

    void References_t::Enable(Vector_t<Reference_t*> refs)
    {
        some<Script_t*> script = Script_t::Create();
        script->Command("Enable");
        for (size_t idx = 0, end = refs.size(); idx < end; idx += 1) {
            maybe<Reference_t*> ref = refs[idx];
            if (ref) { // check if valid, deleted?
                script->Execute(ref());
            }
        }
        Script_t::Destroy(script);
    }

    /* Filters */

    Vector_t<Reference_t*> References_t::Filter_Base_Form_Types(Vector_t<Reference_t*> refs,
                                                                Vector_t<Form_Type_e> form_types,
                                                                String_t mode)
    {
        Vector_t<Reference_t*>& read = refs;
        Vector_t<Reference_t*> write;
        write.reserve(read.size() / 2);

        Filter::State_c<Reference_t*> state(&read, &write);

        Vector_t<some<Form_Type_e>>& some_form_types = Main_t::Validate_Form_Types(form_types);

        Logic_Gate_e logic_gate = Logic_Gate_e::From_Symbol(mode, true);
        if (logic_gate == Logic_Gate_e::NOT) {
            Filter::Base_Form_Types_t<Reference_t*>(state).NOR<Vector_t<some<Form_Type_e>>&>(some_form_types);
        } else {
            Filter::Base_Form_Types_t<Reference_t*>(state).OR<Vector_t<some<Form_Type_e>>&>(some_form_types);
        }

        return *state.Results();
    }

    Vector_t<Reference_t*> References_t::Filter_Bases(Vector_t<Reference_t*> refs,
                                                      Vector_t<Form_t*> bases,
                                                      String_t mode)
    {
        Vector_t<Reference_t*>& read = refs;
        Vector_t<Reference_t*> write;
        write.reserve(read.size() / 2);

        Filter::State_c<Reference_t*> state(&read, &write);

        Vector_t<some<Form_t*>>& some_bases = Main_t::Validate_Formables(bases);

        Logic_Gate_e logic_gate = Logic_Gate_e::From_Symbol(mode, true);
        if (logic_gate == Logic_Gate_e::NOT) {
            Filter::Bases_t<Reference_t*>(state).OR<Vector_t<some<Form_t*>>&>(some_bases, true);
        } else {
            Filter::Bases_t<Reference_t*>(state).OR<Vector_t<some<Form_t*>>&>(some_bases, false);
        }

        return *state.Results();
    }

    Vector_t<Reference_t*> References_t::Filter_Bases_Form_List(Vector_t<Reference_t*> refs,
                                                                Form_List_t* bases,
                                                                String_t mode)
    {
        Vector_t<Reference_t*>& read = refs;
        Vector_t<Reference_t*> write;
        write.reserve(read.size() / 2);

        Filter::State_c<Reference_t*> state(&read, &write);

        Logic_Gate_e logic_gate = Logic_Gate_e::From_Symbol(mode, true);
        if (logic_gate == Logic_Gate_e::NOT) {
            Filter::Bases_t<Reference_t*>(state).OR(bases, true);
        } else {
            Filter::Bases_t<Reference_t*>(state).OR(bases, false);
        }

        return *state.Results();
    }

    Vector_t<Reference_t*> References_t::Filter_Collision_Layer_Types(Vector_t<Reference_t*> refs,
                                                                      Vector_t<Collision_Layer_Type_e> collision_layer_types,
                                                                      String_t mode)
    {
        Vector_t<Reference_t*>& read = refs;
        Vector_t<Reference_t*> write;
        write.reserve(read.size() / 2);

        Filter::State_c<Reference_t*> state(&read, &write);

        Vector_t<some<Collision_Layer_Type_e>> some_collision_layer_types;
        for (size_t idx = 0, end = collision_layer_types.size(); idx < end; idx += 1) {
            maybe<Collision_Layer_Type_e> collision_layer_type = collision_layer_types[idx];
            if (collision_layer_type) {
                some_collision_layer_types.push_back(collision_layer_type());
            }
        }

        if (CString_t::Starts_With("!", mode, true)) {
            Filter::Collision_Layer_Types_t<Reference_t*>(state).NOR<Vector_t<some<Collision_Layer_Type_e>>&>(some_collision_layer_types);
        } else {
            Filter::Collision_Layer_Types_t<Reference_t*>(state).OR<Vector_t<some<Collision_Layer_Type_e>>&>(some_collision_layer_types);
        }

        return *state.Results();
    }

    Vector_t<Reference_t*> References_t::Filter_Deleted(Vector_t<Reference_t*> refs, String_t mode)
    {
        Vector_t<Reference_t*>& read = refs;
        Vector_t<Reference_t*> write;
        write.reserve(read.size() / 2);

        Filter::State_c<Reference_t*> state(&read, &write);

        if (CString_t::Starts_With("!", mode, true)) {
            Filter::Deleted_t<Reference_t*>(state).NOT_EQUAL_TO();
        } else {
            Filter::Deleted_t<Reference_t*>(state).EQUAL_TO();
        }

        return *state.Results();
    }

    Vector_t<Reference_t*> References_t::Filter_Distance(Vector_t<Reference_t*> refs,
                                                         Float_t distance,
                                                         Reference_t* from,
                                                         String_t mode)
    {
        Vector_t<Reference_t*>& read = refs;
        Vector_t<Reference_t*> write;
        write.reserve(read.size() / 2);

        Filter::State_c<Reference_t*> state(&read, &write);

        Operator_e operator_e = Operator_e::From_String(mode);
        if (operator_e == Operator_e::GREATER_THAN) {
            Filter::Distances_t<Reference_t*>(state).GREATER_THAN(distance, from, false);
        } else {
            Filter::Distances_t<Reference_t*>(state).LESS_THAN(distance, from, false);
        }

        return *state.Results();
    }

    Vector_t<Reference_t*> References_t::Filter_Enabled(Vector_t<Reference_t*> refs,
                                                        String_t mode)
    {
        Vector_t<Reference_t*>& read = refs;
        Vector_t<Reference_t*> write;
        write.reserve(read.size() / 2);

        Filter::State_c<Reference_t*> state(&read, &write);

        if (CString_t::Starts_With("!", mode, true)) {
            Filter::Enabled_t<Reference_t*>(state).NOT_EQUAL_TO();
        } else {
            Filter::Enabled_t<Reference_t*>(state).EQUAL_TO();
        }

        return *state.Results();
    }

    Vector_t<Reference_t*> References_t::Filter_Form_Types(Vector_t<Reference_t*> refs,
                                                           Vector_t<Form_Type_e> form_types,
                                                           String_t mode)
    {
        Vector_t<Reference_t*>& read = refs;
        Vector_t<Reference_t*> write;
        write.reserve(read.size() / 2);

        Filter::State_c<Reference_t*> state(&read, &write);

        Vector_t<some<Form_Type_e>>& some_form_types = Main_t::Validate_Form_Types(form_types);

        Logic_Gate_e logic_gate = Logic_Gate_e::From_Symbol(mode, true);
        if (logic_gate == Logic_Gate_e::NOT) {
            Filter::Form_Types_t<Reference_t*>(state).NOR<Vector_t<some<Form_Type_e>>&>(some_form_types);
        } else {
            Filter::Form_Types_t<Reference_t*>(state).OR<Vector_t<some<Form_Type_e>>&>(some_form_types);
        }

        return *state.Results();
    }

    Vector_t<Reference_t*> References_t::Filter_Keywords(Vector_t<Reference_t*> refs,
                                                         Vector_t<Keyword_t*> keywords,
                                                         String_t mode)
    {
        Vector_t<Reference_t*>& read = refs;
        Vector_t<Reference_t*> write;
        write.reserve(read.size() / 2);

        Filter::State_c<Reference_t*> state(&read, &write);

        Vector_t<some<Keyword_t*>>& some_keywords = Main_t::Validate_Formables(keywords);

        Logic_Gate_e logic_gate = Logic_Gate_e::From_Symbol(mode, true);
        if (logic_gate == Logic_Gate_e::OR) {
            Filter::Keywords_t<Reference_t*>(state).OR<Vector_t<some<Keyword_t*>>&>(some_keywords);
        } else if (logic_gate == Logic_Gate_e::AND) {
            Filter::Keywords_t<Reference_t*>(state).AND<Vector_t<some<Keyword_t*>>&>(some_keywords);
        } else if (logic_gate == Logic_Gate_e::XOR) {
            Filter::Keywords_t<Reference_t*>(state).XOR<Vector_t<some<Keyword_t*>>&>(some_keywords);
        } else if (logic_gate == Logic_Gate_e::NOR) {
            Filter::Keywords_t<Reference_t*>(state).NOR<Vector_t<some<Keyword_t*>>&>(some_keywords);
        } else if (logic_gate == Logic_Gate_e::NAND) {
            Filter::Keywords_t<Reference_t*>(state).NAND<Vector_t<some<Keyword_t*>>&>(some_keywords);
        } else if (logic_gate == Logic_Gate_e::XNOR) {
            Filter::Keywords_t<Reference_t*>(state).XNOR<Vector_t<some<Keyword_t*>>&>(some_keywords);
        } else {
            Filter::Keywords_t<Reference_t*>(state).OR<Vector_t<some<Keyword_t*>>&>(some_keywords);
        }

        return *state.Results();
    }

    Vector_t<Reference_t*> References_t::Filter_Owners(Vector_t<Reference_t*> refs,
                                                       Vector_t<Actor_t*> owners,
                                                       String_t mode)
    {
        Vector_t<Reference_t*>& read = refs;
        Vector_t<Reference_t*> write;
        write.reserve(read.size() / 2);

        Filter::State_c<Reference_t*> state(&read, &write);

        Vector_t<some<Actor_t*>>& some_owners = Main_t::Validate_Formables(owners);

        Logic_Gate_e logic_gate = Logic_Gate_e::From_Symbol(mode, true);
        if (logic_gate == Logic_Gate_e::OR) {
            Filter::Owners_t<Reference_t*>(state).OR<Vector_t<some<Actor_t*>>&>(some_owners);
        } else if (logic_gate == Logic_Gate_e::AND) {
            Filter::Owners_t<Reference_t*>(state).AND<Vector_t<some<Actor_t*>>&>(some_owners);
        } else if (logic_gate == Logic_Gate_e::XOR) {
            Filter::Owners_t<Reference_t*>(state).XOR<Vector_t<some<Actor_t*>>&>(some_owners);
        } else if (logic_gate == Logic_Gate_e::NOR) {
            Filter::Owners_t<Reference_t*>(state).NOR<Vector_t<some<Actor_t*>>&>(some_owners);
        } else if (logic_gate == Logic_Gate_e::NAND) {
            Filter::Owners_t<Reference_t*>(state).NAND<Vector_t<some<Actor_t*>>&>(some_owners);
        } else if (logic_gate == Logic_Gate_e::XNOR) {
            Filter::Owners_t<Reference_t*>(state).XNOR<Vector_t<some<Actor_t*>>&>(some_owners);
        } else {
            Filter::Owners_t<Reference_t*>(state).OR<Vector_t<some<Actor_t*>>&>(some_owners);
        }

        return *state.Results();
    }

    Vector_t<Reference_t*> References_t::Filter_Potential_Thieves(Vector_t<Reference_t*> refs,
                                                                  Vector_t<Actor_t*> potential_thieves,
                                                                  String_t mode)
    {
        Vector_t<Reference_t*>& read = refs;
        Vector_t<Reference_t*> write;
        write.reserve(read.size() / 2);

        Filter::State_c<Reference_t*> state(&read, &write);

        Vector_t<some<Actor_t*>>& some_potential_thieves = Main_t::Validate_Formables(potential_thieves);

        Logic_Gate_e logic_gate = Logic_Gate_e::From_Symbol(mode, true);
        if (logic_gate == Logic_Gate_e::OR) {
            Filter::Potential_Thieves_t<Reference_t*>(state).OR<Vector_t<some<Actor_t*>>&>(some_potential_thieves);
        } else if (logic_gate == Logic_Gate_e::AND) {
            Filter::Potential_Thieves_t<Reference_t*>(state).AND<Vector_t<some<Actor_t*>>&>(some_potential_thieves);
        } else if (logic_gate == Logic_Gate_e::XOR) {
            Filter::Potential_Thieves_t<Reference_t*>(state).XOR<Vector_t<some<Actor_t*>>&>(some_potential_thieves);
        } else if (logic_gate == Logic_Gate_e::NOR) {
            Filter::Potential_Thieves_t<Reference_t*>(state).NOR<Vector_t<some<Actor_t*>>&>(some_potential_thieves);
        } else if (logic_gate == Logic_Gate_e::NAND) {
            Filter::Potential_Thieves_t<Reference_t*>(state).NAND<Vector_t<some<Actor_t*>>&>(some_potential_thieves);
        } else if (logic_gate == Logic_Gate_e::XNOR) {
            Filter::Potential_Thieves_t<Reference_t*>(state).XNOR<Vector_t<some<Actor_t*>>&>(some_potential_thieves);
        } else {
            Filter::Potential_Thieves_t<Reference_t*>(state).OR<Vector_t<some<Actor_t*>>&>(some_potential_thieves);
        }

        return *state.Results();
    }

    /* Sorters */

    Vector_t<Reference_t*> References_t::Sort_Distance(Vector_t<Reference_t*> refs,
                                                       Reference_t* from,
                                                       String_t mode)
    {
        Vector_t<some<Reference_t*>> some_refs = Main_t::Validate_Formables(refs);

        some<Reference_t*> some_from = from && from->Is_Valid() ?
            from : static_cast<some<Reference_t*>>(Player_t::Self());

        Operator_e operator_e = Operator_e::From_String(mode);
        if (operator_e == Operator_e::GREATER_THAN) {
            class Distance_Comparator_t
            {
            public:
                some<Reference_t*> some_from;
                Distance_Comparator_t(some<Reference_t*> some_from) :
                    some_from(some_from)
                {
                }

                Bool_t operator ()(some<Reference_t*> a, some<Reference_t*> b)
                {
                    return a->Distance_Between(some_from) > b->Distance_Between(some_from);
                }
            };
            std::sort(some_refs.begin(), some_refs.end(), Distance_Comparator_t(some_from));
        } else {
            class Distance_Comparator_t
            {
            public:
                some<Reference_t*> some_from;
                Distance_Comparator_t(some<Reference_t*> some_from) :
                    some_from(some_from)
                {
                }

                Bool_t operator ()(some<Reference_t*> a, some<Reference_t*> b)
                {
                    return a->Distance_Between(some_from) < b->Distance_Between(some_from);
                }
            };
            std::sort(some_refs.begin(), some_refs.end(), Distance_Comparator_t(some_from));
        }

        return *reinterpret_cast<Vector_t<Reference_t*>*>(&some_refs);
    }

    /* Combiners */

    Vector_t<Reference_t*> References_t::All_Filter_Bases(Vector_t<Form_t*> bases, String_t mode)
    {
        return Filter_Bases(std::move(All()), std::move(bases), mode);
    }

    Vector_t<Reference_t*> References_t::All_Filter_Bases_Form_List(Form_List_t* bases, String_t mode)
    {
        return Filter_Bases_Form_List(std::move(All()), bases, mode);
    }

    Vector_t<Reference_t*> References_t::Grid_Filter_Bases(Vector_t<Form_t*> bases, String_t mode)
    {
        return Filter_Bases(std::move(Grid()), std::move(bases), mode);
    }

    Vector_t<Reference_t*> References_t::Grid_Filter_Bases_Form_List(Form_List_t* bases, String_t mode)
    {
        return Filter_Bases_Form_List(std::move(Grid()), bases, mode);
    }

}
