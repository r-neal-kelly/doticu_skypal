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
        static Vector_t<Reference_t*>   All();
        static Vector_t<Reference_t*>   Grid();

        static Vector_t<Reference_t*>   Filter_Base_Form_Types(Vector_t<Reference_t*> refs, Vector_t<Form_Type_e> form_types, String_t mode = "");
        static Vector_t<Reference_t*>   Filter_Bases_Form_List(Vector_t<Reference_t*> refs, Form_List_t* bases, String_t mode = "");
        static Vector_t<Reference_t*>   Filter_Distance(Vector_t<Reference_t*> refs, Float_t distance, Reference_t* from = nullptr, String_t mode = "<");
        static Vector_t<Reference_t*>   Filter_Form_Types(Vector_t<Reference_t*> refs, Vector_t<Form_Type_e> form_types, String_t mode = "");
        static Vector_t<Reference_t*>   Filter_Keywords(Vector_t<Reference_t*> refs, Vector_t<Keyword_t*> keywords, String_t mode = "|");

        static Vector_t<Reference_t*>   Sort_Distance(Vector_t<Reference_t*> refs, Reference_t* from = nullptr, String_t mode = "<");

    public:
        static void Global_For_Each(Vector_t<Reference_t*> ureferences,
                                    String_t script_name,
                                    String_t global_name);
        static void Form_For_Each(Form_t* self,
                                  Vector_t<Reference_t*> references,
                                  String_t script_name,
                                  String_t method_name);
        static void Alias_For_Each(Alias_Base_t* self,
                                   Vector_t<Reference_t*> references,
                                   String_t script_name,
                                   String_t method_name);
        static void Active_Magic_Effect_For_Each(Active_Magic_Effect_t* self,
                                                 Vector_t<Reference_t*> references,
                                                 String_t script_name,
                                                 String_t method_name);
    };

}
