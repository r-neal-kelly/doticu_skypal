; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname SkyPal hidden

; Use this to check if the user installed the plugin correctly
bool function Has_DLL() native global

; if (mode == "=="): Tests if the dll version matches args exactly
; if (mode == "!="): Tests if the dll version does not match args exactly
; if (mode == "<="): Tests if the dll version is less than or equal to args
; if (mode == ">="): Tests if the dll version is greater than or equal to args
; if (mode == "<"): Tests if the dll version is less than args
; if (mode == ">"): Tests if the dll version is greater than args
; if (mode == invalid): Passes the default mode listed in the signature.
bool function Has_Version(int major, int minor, int patch, string mode = "==") native global

; These can be used for performance timers.
float function Microseconds() native global
float function Milliseconds() native global
float function Seconds() native global
