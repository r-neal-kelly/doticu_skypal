/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>

#include "skse64_common/skse_version.h"

#include "doticu_skylib/form_type.h"
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
                if (SKSE_PAPYRUS->Register(reinterpret_cast<Bool_t(*)(skylib::Virtual::Registry_t*)>(SKSE_Register_Functions))) {
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

    Bool_t Main_t::SKSE_Register_Functions(skylib::Virtual::Machine_t* machine)
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

    void Main_t::Register_Me(skylib::Virtual::Machine_t* machine)
    {
        #define STATIC(STATIC_NAME_, ARG_COUNT_, RETURN_TYPE_, STATIC_, ...)    \
        SKYLIB_M                                                                \
            BIND_STATIC(machine, Class_Name(),                                  \
                        STATIC_NAME_, ARG_COUNT_,                               \
                        RETURN_TYPE_, STATIC_, __VA_ARGS__);                    \
        SKYLIB_W

        STATIC("Lookup", 2, Vector_t<Reference_t*>, Lookup, Vector_t<Int_t>, Vector_t<Keyword_t*>);
    }

    Vector_t<Reference_t*> Main_t::Lookup(Vector_t<Int_t> form_types, Vector_t<Keyword_t*> keywords)
    {
        Vector_t<Reference_t*> results;
        return results;
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
