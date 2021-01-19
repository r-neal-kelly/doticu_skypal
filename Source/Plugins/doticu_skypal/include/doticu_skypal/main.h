/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PluginAPI.h"

#include "doticu_skypal/intrinsic.h"

namespace doticu_skypal {

    class Main_t
    {
    public:
        static const    SKSEInterface*          SKSE;
        static const    SKSEPapyrusInterface*   SKSE_PAPYRUS;
        static          PluginHandle            SKSE_PLUGIN_HANDLE;
        static          IDebugLog               SKSE_LOG;

    public:
        static Bool_t SKSE_Query_Plugin(const SKSEInterface* skse, PluginInfo* info);
        static Bool_t SKSE_Load_Plugin(const SKSEInterface* skse);
        static Bool_t SKSE_Register_Functions(V::Machine_t* machine);

    public:
        static String_t Class_Name();
        static void     Register_Me(V::Machine_t* machine);

    public:
        static Vector_t<some<Form_t*>>&     Validate_Forms(Vector_t<Form_t*>& forms);
        static Vector_t<some<Form_Type_e>>& Validate_Form_Types(Vector_t<Form_Type_e>& form_types);

        template <typename Formable_t, std::enable_if_t<std::is_convertible<Formable_t, Form_t>::value, Bool_t> = true>
        static Vector_t<some<Formable_t*>>& Validate_Formables(Vector_t<Formable_t*>& formables)
        {
            return reinterpret_cast<Vector_t<some<Formable_t*>>&>(Validate_Forms(reinterpret_cast<Vector_t<Form_t*>&>(formables)));
        }

    public:
        static Bool_t Has_DLL();
        static Bool_t Has_Version(Int_t major, Int_t minor, Int_t patch, String_t mode = "==");

    public:
        static Float_t Microseconds();
        static Float_t Milliseconds();
        static Float_t Seconds();
    };

}
