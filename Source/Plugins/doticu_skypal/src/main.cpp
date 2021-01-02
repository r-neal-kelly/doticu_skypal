/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>

#include "doticu_skylib/virtual_macros.h"

#include "doticu_skypal/consts.h"
#include "doticu_skypal/main.h"
#include "doticu_skypal/references.h"

namespace doticu_skypal {

    const SKSEInterface*        Main_t::SKSE                        = nullptr;
    const SKSEPapyrusInterface* Main_t::SKSE_PAPYRUS                = nullptr;
    PluginHandle                Main_t::SKSE_PLUGIN_HANDLE          = 0;
    IDebugLog                   Main_t::SKSE_LOG;

    Bool_t Main_t::SKSE_Query_Plugin(const SKSEInterface* skse, PluginInfo* info)
    {
        if (skse && info) {
            info->infoVersion = PluginInfo::kInfoVersion;
            info->name = "doticu_skypal";
            info->version = 1;

            if (Version_t<u16>::From_MM_mm_ppp_b(skse->runtimeVersion) == Consts_t::Skyrim::Required_Version()) {
                if (Version_t<u16>::From_MM_mm_ppp_b(skse->skseVersion) >= Consts_t::SKSE::Minimum_Version()) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    Bool_t Main_t::SKSE_Load_Plugin(const SKSEInterface* skse)
    {
        SKSE_LOG.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\doticu_skypal.log");

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
            SKYLIB_LOG("Added " #TYPE_ " functions.");  \
        SKYLIB_W

        REGISTER(doticu_skypal::Main_t);
        REGISTER(doticu_skypal::References_t);

        #undef REGISTER

        SKYLIB_LOG("Added all functions.\n");

        return true;
    }

    String_t Main_t::Class_Name()
    {
        DEFINE_CLASS_NAME("skypal");
    }

    void Main_t::Register_Me(V::Machine_t* machine)
    {
        String_t class_name = Class_Name();

        #define STATIC(STATIC_NAME_, ARG_COUNT_, RETURN_TYPE_, STATIC_, ...)    \
        SKYLIB_M                                                                \
            BIND_STATIC(machine, class_name,                                    \
                        STATIC_NAME_, ARG_COUNT_,                               \
                        RETURN_TYPE_, STATIC_, __VA_ARGS__);                    \
        SKYLIB_W

        STATIC("Has_DLL", 0, Bool_t, Has_DLL);

        #undef STATIC
    }

    Bool_t Main_t::Has_DLL()
    {
        return true;
    }

}

extern "C" {

    _declspec(dllexport) skylib::Bool_t SKSEPlugin_Query(const SKSEInterface*, PluginInfo*);
    _declspec(dllexport) skylib::Bool_t SKSEPlugin_Load(const SKSEInterface*);

    skylib::Bool_t SKSEPlugin_Query(const SKSEInterface* skse, PluginInfo* info)
    {
        return doticu_skypal::Main_t::SKSE_Query_Plugin(skse, info);
    }

    skylib::Bool_t SKSEPlugin_Load(const SKSEInterface* skse)
    {
        return doticu_skypal::Main_t::SKSE_Load_Plugin(skse);
    }

}
