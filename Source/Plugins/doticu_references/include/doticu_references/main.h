/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PluginAPI.h"

#include "doticu_skylib/form_type.h"

#include "doticu_references/intrinsic.h"

namespace doticu_references {

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
        static Bool_t SKSE_Register_Functions(skylib::Virtual::Machine_t* machine);

    public:
        static String_t Class_Name();
        static void     Register_Me(skylib::Virtual::Machine_t* machine);

    public:
        static Vector_t<Reference_t*>   Filter(Vector_t<Form_Type_e> form_types);
        static Vector_t<Reference_t*>   Filter_Grid(Vector_t<Form_Type_e> form_types);

    public:
        static void Global_For_Each(Vector_t<Reference_t*> ureferences,
                                    String_t script_name,
                                    String_t global_name);
        static void Form_For_Each(Vector_t<Reference_t*> ureferences,
                                  String_t script_name,
                                  String_t method_name,
                                  Form_t* on_this);
        static void Alias_For_Each(Vector_t<Reference_t*> ureferences,
                                   String_t script_name,
                                   String_t method_name,
                                   Alias_Base_t* on_this);
        static void Active_Magic_Effect_For_Each(Vector_t<Reference_t*> ureferences,
                                                 String_t script_name,
                                                 String_t method_name,
                                                 Active_Magic_Effect_t* on_this);
    };

}
