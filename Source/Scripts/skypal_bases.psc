; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname SkyPal_Bases hidden

;/
    Converters:
        if (mode == invalid): Passes the default mode listed in each signature.
/;

; if (refs == none): Passes an empty array.
; if (mode == "."): Passes all unique bases, not allowing any repeats.
; if (mode == "..."): Passes one base per reference, allowing repeats.
Form[] function From_References(ObjectReference[] refs, string mode = ".") native global
