/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>

#include "skse64_common/skse_version.h"

#include "doticu_skylib/form_type.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/keyword.h"
#include "doticu_skylib/reference.h"

#include "doticu_skylib/virtual_macros.h"

#include "doticu_references/intrinsic.h"
#include "doticu_references/main.h"

namespace doticu_references {

    const   SKSEInterface*          Main_t::SKSE                = nullptr;
    const   SKSEPapyrusInterface*   Main_t::SKSE_PAPYRUS        = nullptr;
            PluginHandle            Main_t::SKSE_PLUGIN_HANDLE  = 0;
            IDebugLog               Main_t::SKSE_LOG;

    Bool_t Main_t::SKSE_Query_Plugin(const SKSEInterface* skse, PluginInfo* info)
    {
        if (skse && info) {
            info->infoVersion = PluginInfo::kInfoVersion;
            info->name = "doticu_references";
            info->version = 1;
            return skse->skseVersion >= MAKE_EXE_VERSION(2, 0, 17);
        } else {
            return false;
        }
    }

    Bool_t Main_t::SKSE_Load_Plugin(const SKSEInterface* skse)
    {
        SKSE_LOG.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\doticu_references.log");

        if (skse) {
            SKSE = skse;
            SKSE_PAPYRUS = static_cast<const SKSEPapyrusInterface*>(SKSE->QueryInterface(kInterface_Papyrus));
            SKSE_PLUGIN_HANDLE = SKSE->GetPluginHandle();
            if (SKSE_PAPYRUS) {
                if (SKSE_PAPYRUS->Register(reinterpret_cast<SKSEPapyrusInterface::RegisterFunctions>(SKSE_Register_Functions))) {
                    return true;
                } else {
                    _FATALERROR("Unable to register functions.");
                    return false;
                }
            } else {
                _FATALERROR("Unable to get papyrus and/or messaging interface.");
                return false;
            }
        } else {
            _FATALERROR("Unable to get skse interface.");
            return false;
        }
    }

    Bool_t Main_t::SKSE_Register_Functions(V::Machine_t* machine)
    {
        #define REGISTER(TYPE_)                         \
        SKYLIB_M                                        \
            TYPE_::Register_Me(machine);                \
            SKYLIB_LOG("Added " #TYPE_ " functions.");    \
        SKYLIB_W

        REGISTER(Main_t);

        #undef REGISTER

        SKYLIB_LOG("Added all functions.\n");

        return true;
    }

    String_t Main_t::Class_Name()
    {
        DEFINE_CLASS_NAME("doticu_references");
    }

    void Main_t::Register_Me(V::Machine_t* machine)
    {
        #define STATIC(STATIC_NAME_, ARG_COUNT_, RETURN_TYPE_, STATIC_, ...)    \
        SKYLIB_M                                                                \
            BIND_STATIC(machine, Class_Name(),                                  \
                        STATIC_NAME_, ARG_COUNT_,                               \
                        RETURN_TYPE_, STATIC_, __VA_ARGS__);                    \
        SKYLIB_W

        STATIC("Filter",        1,  Vector_t<Reference_t*>, Filter,         Vector_t<Form_Type_e>);
        STATIC("Filter_Grid",   1,  Vector_t<Reference_t*>, Filter_Grid,    Vector_t<Form_Type_e>);

        STATIC("Global_For_Each",               3,  void,   Global_For_Each,                Vector_t<Reference_t*>, String_t, String_t);
        STATIC("Form_For_Each",                 4,  void,   Form_For_Each,                  Vector_t<Reference_t*>, String_t, String_t, Form_t*);
        STATIC("Alias_For_Each",                4,  void,   Alias_For_Each,                 Vector_t<Reference_t*>, String_t, String_t, Alias_Base_t*);
        STATIC("Active_Magic_Effect_For_Each",  4,  void,   Active_Magic_Effect_For_Each,   Vector_t<Reference_t*>, String_t, String_t, Active_Magic_Effect_t*);
    }

    class Loaded_References_Filter_t : public Filter_i<some<Reference_t*>>
    {
    public:
        Vector_t<Form_Type_e>   form_types;
        Bool_t                  allow_all = false;

        Loaded_References_Filter_t(const Vector_t<Form_Type_e>& uform_types)
        {
            size_t uform_type_count = uform_types.size();
            this->form_types.reserve(uform_type_count);
            for (Index_t idx = 0, end = uform_type_count; idx < end; idx += 1) {
                Form_Type_e uform_type = uform_types[idx];
                if (uform_type == Form_Type_e::FORM) {
                    allow_all = true;
                    return;
                } else if (uform_type < Form_Type_e::_END_) {
                    this->form_types.push_back(uform_type);
                }
            }
        }

        Bool_t operator()(some<Reference_t*> reference) override
        {
            if (allow_all || form_types.Has(reference->form_type)) {
                return true;
            } else {
                Form_t* base_form = reference->base_form;
                return base_form && base_form->Is_Valid() && form_types.Has(base_form->form_type);
            }
        }
    };

    Vector_t<Reference_t*> Main_t::Filter(Vector_t<Form_Type_e> form_types)
    {
        Loaded_References_Filter_t filter(form_types);
        return *reinterpret_cast<Vector_t<Reference_t*>*>(&Reference_t::Loaded_References(&filter));
    }

    Vector_t<Reference_t*> Main_t::Filter_Grid(Vector_t<Form_Type_e> form_types)
    {
        Loaded_References_Filter_t filter(form_types);
        return *reinterpret_cast<Vector_t<Reference_t*>*>(&Reference_t::Loaded_References_In_Grid(&filter));
    }

    static Vector_t<some<Reference_t*>> Valid_User_References(Vector_t<Reference_t*>& ureferences)
    {
        Vector_t<some<Reference_t*>> results;

        size_t ureference_count = ureferences.size();
        results.reserve(ureference_count);
        for (Index_t idx = 0, end = ureference_count; idx < end; idx += 1) {
            Reference_t* ureference = ureferences[idx];
            if (ureference && ureference->Is_Valid()) {
                results.push_back(ureference);
            }
        }

        return results;
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

    void Main_t::Global_For_Each(Vector_t<Reference_t*> ureferences, String_t script_name, String_t global_name)
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
            const Vector_t<some<Reference_t*>> references = Valid_User_References(ureferences);
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
    static void Method_For_Each(Vector_t<Reference_t*>&& ureferences,
                                String_t script_name,
                                String_t method_name,
                                Scriptable_t scriptable)
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

        if (script_name && method_name && scriptable) {
            const Vector_t<some<Reference_t*>> references = Valid_User_References(ureferences);
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

    void Main_t::Form_For_Each(Vector_t<Reference_t*> ureferences,
                               String_t script_name,
                               String_t method_name,
                               Form_t* on_this)
    {
        Method_For_Each(std::move(ureferences), script_name, method_name, on_this);
    }

    void Main_t::Alias_For_Each(Vector_t<Reference_t*> ureferences,
                                String_t script_name,
                                String_t method_name,
                                Alias_Base_t* on_this)
    {
        Method_For_Each(std::move(ureferences), script_name, method_name, on_this);
    }

    void Main_t::Active_Magic_Effect_For_Each(Vector_t<Reference_t*> ureferences,
                                              String_t script_name,
                                              String_t method_name,
                                              Active_Magic_Effect_t* on_this)
    {
        Method_For_Each(std::move(ureferences), script_name, method_name, on_this);
    }

}

extern "C" {

    _declspec(dllexport) skylib::Bool_t SKSEPlugin_Query(const SKSEInterface*, PluginInfo*);
    _declspec(dllexport) skylib::Bool_t SKSEPlugin_Load(const SKSEInterface*);

    skylib::Bool_t SKSEPlugin_Query(const SKSEInterface* skse, PluginInfo* info)
    {
        return doticu_references::Main_t::SKSE_Query_Plugin(skse, info);
    }

    skylib::Bool_t SKSEPlugin_Load(const SKSEInterface* skse)
    {
        return doticu_references::Main_t::SKSE_Load_Plugin(skse);
    }

}
