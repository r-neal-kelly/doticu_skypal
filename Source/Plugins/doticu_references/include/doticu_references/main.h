/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PluginAPI.h"

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
        static Vector_t<Reference_t*> Lookup(Vector_t<Int_t> form_types, Vector_t<Keyword_t*> keywords);
    };

}
