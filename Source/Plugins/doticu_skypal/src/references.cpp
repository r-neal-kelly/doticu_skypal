/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <algorithm>

#include "doticu_skylib/enum_logic_gate.h"
#include "doticu_skylib/enum_operator.h"

#include "doticu_skylib/component_keywords.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/form_type.h"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/keyword.h"
#include "doticu_skylib/player.h"
#include "doticu_skylib/reference.h"

#include "doticu_skylib/virtual_macros.h"

#include "doticu_skylib/filter_base_form_types.h"
#include "doticu_skylib/filter_bases.h"
#include "doticu_skylib/filter_distances.h"
#include "doticu_skylib/filter_form_types.h"
#include "doticu_skylib/filter_keywords.h"

#include "doticu_skypal/references.h"

namespace doticu_skypal {

    String_t References_t::Class_Name()
    {
        DEFINE_CLASS_NAME("skypal_references");
    }

    void References_t::Register_Me(V::Machine_t* machine)
    {
        String_t class_name = Class_Name();

        #define STATIC(STATIC_NAME_, ARG_COUNT_, RETURN_TYPE_, STATIC_, ...)    \
        SKYLIB_M                                                                \
            BIND_STATIC(machine, class_name,                                    \
                        STATIC_NAME_, ARG_COUNT_,                               \
                        RETURN_TYPE_, STATIC_, __VA_ARGS__);                    \
        SKYLIB_W

        STATIC("All", 0, Vector_t<Reference_t*>, All);
        STATIC("Grid", 0, Vector_t<Reference_t*>, Grid);

        STATIC("Filter_Base_Form_Types", 3, Vector_t<Reference_t*>, Filter_Base_Form_Types, Vector_t<Reference_t*>, Vector_t<Form_Type_e>, String_t);
        STATIC("Filter_Bases_Form_List", 3, Vector_t<Reference_t*>, Filter_Bases_Form_List, Vector_t<Reference_t*>, Form_List_t*, String_t);
        STATIC("Filter_Distance", 4, Vector_t<Reference_t*>, Filter_Distance, Vector_t<Reference_t*>, Float_t, Reference_t*, String_t);
        STATIC("Filter_Form_Types", 3, Vector_t<Reference_t*>, Filter_Form_Types, Vector_t<Reference_t*>, Vector_t<Form_Type_e>, String_t);
        STATIC("Filter_Keywords", 3, Vector_t<Reference_t*>, Filter_Keywords, Vector_t<Reference_t*>, Vector_t<Keyword_t*>, String_t);

        STATIC("Sort_Distance", 3, Vector_t<Reference_t*>, Sort_Distance, Vector_t<Reference_t*>, Reference_t*, String_t);

        STATIC("Global_For_Each", 3, void, Global_For_Each, Vector_t<Reference_t*>, String_t, String_t);
        STATIC("Form_For_Each", 4, void, Form_For_Each, Form_t*, Vector_t<Reference_t*>, String_t, String_t);
        STATIC("Alias_For_Each", 4, void, Alias_For_Each, Alias_Base_t*, Vector_t<Reference_t*>, String_t, String_t);
        STATIC("Active_Magic_Effect_For_Each", 4, void, Active_Magic_Effect_For_Each, Active_Magic_Effect_t*, Vector_t<Reference_t*>, String_t, String_t);

        #undef STATIC
    }

    template <typename Formable_t, std::enable_if_t<std::is_convertible<Formable_t, Form_t>::value, Bool_t> = true>
    static inline Vector_t<some<Formable_t*>>& Validate_Formables(Vector_t<Formable_t*>& formables)
    {
        for (size_t idx = 0, end = formables.size(); idx < end; idx += 1) {
            some<Formable_t*> formable = formables[idx];
            if (!formable || !formable->Is_Valid()) {
                end -= 1;
                if (idx < end) {
                    formables[idx] = formables[end];
                }
                formables.erase(formables.begin() + end);
                idx -= 1;
            }
        }
        return reinterpret_cast<Vector_t<some<Formable_t*>>&>(formables);
    }

    static inline Vector_t<some<Form_Type_e>>& Validate_Form_Types(Vector_t<Form_Type_e>& form_types)
    {
        for (size_t idx = 0, end = form_types.size(); idx < end; idx += 1) {
            Form_Type_e form_type = form_types[idx];
            if (form_type == none<Form_Type_e>()) {
                end -= 1;
                if (idx < end) {
                    form_types[idx] = form_types[end];
                }
                form_types.erase(form_types.begin() + end);
                idx -= 1;
            }
        }
        return reinterpret_cast<Vector_t<some<Form_Type_e>>&>(form_types);
    }

    Vector_t<Reference_t*> References_t::All()
    {
        return *reinterpret_cast<Vector_t<Reference_t*>*>(&Reference_t::Loaded_References());
    }

    Vector_t<Reference_t*> References_t::Grid()
    {
        return *reinterpret_cast<Vector_t<Reference_t*>*>(&Reference_t::Loaded_Grid_References());
    }

    Vector_t<Reference_t*> References_t::Filter_Base_Form_Types(Vector_t<Reference_t*> refs,
                                                                Vector_t<Form_Type_e> form_types,
                                                                String_t mode)
    {
        Vector_t<Reference_t*>& read = refs;
        Vector_t<Reference_t*> write;
        write.reserve(read.size() / 2);

        Filter::State_c<Reference_t*> state(&read, &write);

        Vector_t<some<Form_Type_e>>& some_form_types = Validate_Form_Types(form_types);

        Logic_Gate_e logic_gate = Logic_Gate_e::From_String(mode.data);
        if (logic_gate == Logic_Gate_e::NOT) {
            Filter::Base_Form_Types_t<Reference_t*>(state).NOR<Vector_t<some<Form_Type_e>>&>(some_form_types);
        } else {
            Filter::Base_Form_Types_t<Reference_t*>(state).OR<Vector_t<some<Form_Type_e>>&>(some_form_types);
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

        Logic_Gate_e logic_gate = Logic_Gate_e::From_String(mode.data);
        if (logic_gate == Logic_Gate_e::NOT) {
            Filter::Bases_t<Reference_t*>(state).OR(bases, true);
        } else {
            Filter::Bases_t<Reference_t*>(state).OR(bases, false);
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

        Operator_e operator_e = Operator_e::From_String(mode.data);
        if (operator_e == Operator_e::GREATER_THAN) {
            Filter::Distances_t<Reference_t*>(state).GREATER_THAN(distance, from, false);
        } else {
            Filter::Distances_t<Reference_t*>(state).LESS_THAN(distance, from, false);
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

        Vector_t<some<Form_Type_e>>& some_form_types = Validate_Form_Types(form_types);

        Logic_Gate_e logic_gate = Logic_Gate_e::From_String(mode.data);
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

        Vector_t<some<Keyword_t*>>& some_keywords = Validate_Formables(keywords);

        Logic_Gate_e logic_gate = Logic_Gate_e::From_String(mode.data);
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

    Vector_t<Reference_t*> References_t::Sort_Distance(Vector_t<Reference_t*> refs,
                                                       Reference_t* from,
                                                       String_t mode)
    {
        Vector_t<some<Reference_t*>> some_refs = Validate_Formables(refs);

        some<Reference_t*> some_from = from && from->Is_Valid() ?
            from : static_cast<some<Reference_t*>>(Player_t::Self());

        Operator_e operator_e = Operator_e::From_String(mode.data);
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

    class For_Each_Arguments_t : public V::Arguments_t
    {
    public:
        const some<Reference_t*>    reference;
        const Int_t                 index;
        const Int_t                 end;
        For_Each_Arguments_t(const some<Reference_t*> reference, const Int_t index, const Int_t end) :
            reference(reference), index(index), end(end)
        {
        }
        Bool_t operator()(Buffer_t<V::Variable_t>* arguments)
        {
            if (arguments) {
                arguments->Resize(3);
                arguments->At(0)->As<Reference_t*>(reference());
                arguments->At(1)->As<Int_t>(index);
                arguments->At(2)->As<Int_t>(end);
                return true;
            } else {
                return false;
            }
        }
    };

    void References_t::Global_For_Each(Vector_t<Reference_t*> ureferences, String_t script_name, String_t global_name)
    {
        class Callback_t : public V::Callback_t
        {
        public:
            const String_t                      script_name;
            const String_t                      global_name;
            const Vector_t<some<Reference_t*>>  references;
            const Int_t                         index;
            Callback_t(const String_t script_name,
                       const String_t global_name,
                       const Vector_t<some<Reference_t*>>&& references,
                       Int_t index) :
                script_name(script_name),
                global_name(global_name),
                references(std::move(references)),
                index(index)
            {
            }
            void operator()(V::Variable_t* result)
            {
                if (result == nullptr || result->Is_None() || result->Bool() == true) {
                    const size_t reference_count = references.size();
                    if (index < reference_count) {
                        For_Each_Arguments_t args(references[index], index, reference_count);
                        V::Machine_t::Self()->Call_Global(
                            script_name,
                            global_name,
                            &args,
                            new Callback_t(
                                script_name,
                                global_name,
                                std::move(references),
                                index + 1)
                        );
                    }
                }
            }
        };

        if (script_name && global_name) {
            const Vector_t<some<Reference_t*>> references = Validate_Formables(ureferences);
            const Int_t index = 0;
            const size_t reference_count = references.size();
            if (index < reference_count) {
                For_Each_Arguments_t args(references[index], index, reference_count);
                V::Machine_t::Self()->Call_Global(
                    script_name,
                    global_name,
                    &args,
                    new Callback_t(
                        script_name,
                        global_name,
                        std::move(references),
                        index + 1
                    )
                );
            }
        }
    }

    template <typename Scriptable_t>
    static void Method_For_Each(Scriptable_t scriptable,
                                Vector_t<Reference_t*>&& ureferences,
                                String_t script_name,
                                String_t method_name)
    {
        class Callback_t : public V::Callback_t
        {
        public:
            const Scriptable_t                  scriptable;
            const String_t                      script_name;
            const String_t                      method_name;
            const Vector_t<some<Reference_t*>>  references;
            const Int_t                         index;
            Callback_t(const Scriptable_t scriptable,
                       const String_t script_name,
                       const String_t method_name,
                       const Vector_t<some<Reference_t*>>&& references,
                       Int_t index) :
                scriptable(scriptable),
                script_name(script_name),
                method_name(method_name),
                references(std::move(references)),
                index(index)
            {
            }
            void operator()(V::Variable_t* result)
            {
                if (result == nullptr || result->Is_None() || result->Bool() == true) {
                    const size_t reference_count = references.size();
                    if (index < reference_count) {
                        For_Each_Arguments_t args(references[index], index, reference_count);
                        V::Machine_t::Self()->Call_Method(
                            scriptable,
                            script_name,
                            method_name,
                            &args,
                            new Callback_t(
                                scriptable,
                                script_name,
                                method_name,
                                std::move(references),
                                index + 1
                            )
                        );
                    }
                }
            }
        };

        if (scriptable && script_name && method_name) {
            const Vector_t<some<Reference_t*>> references = Validate_Formables(ureferences);
            const Int_t index = 0;
            const size_t reference_count = references.size();
            if (index < reference_count) {
                For_Each_Arguments_t args(references[index], index, reference_count);
                V::Machine_t::Self()->Call_Method(
                    scriptable,
                    script_name,
                    method_name,
                    &args,
                    new Callback_t(
                        scriptable,
                        script_name,
                        method_name,
                        std::move(references),
                        index + 1
                    )
                );
            }
        }
    }

    void References_t::Form_For_Each(Form_t* self,
                                     Vector_t<Reference_t*> references,
                                     String_t script_name,
                                     String_t method_name)
    {
        Method_For_Each(self, std::move(references), script_name, method_name);
    }

    void References_t::Alias_For_Each(Alias_Base_t* self,
                                      Vector_t<Reference_t*> references,
                                      String_t script_name,
                                      String_t method_name)
    {
        Method_For_Each(self, std::move(references), script_name, method_name);
    }

    void References_t::Active_Magic_Effect_For_Each(Active_Magic_Effect_t* self,
                                                    Vector_t<Reference_t*> references,
                                                    String_t script_name,
                                                    String_t method_name)
    {
        Method_For_Each(self, std::move(references), script_name, method_name);
    }

}
