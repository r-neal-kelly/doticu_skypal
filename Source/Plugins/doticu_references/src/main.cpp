/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>

#include "skse64_common/skse_version.h"

#include "doticu_references/intrinsic.h"
#include "doticu_references/main.h"

namespace doticu_references {

    const   SKSEInterface*          Main_t::SKSE                = nullptr;
    const   SKSEPapyrusInterface*   Main_t::SKSE_PAPYRUS        = nullptr;
    const   SKSEMessagingInterface* Main_t::SKSE_MESSAGING      = nullptr;
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
        SKYLIB_LOG("working.");

        return true;
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
