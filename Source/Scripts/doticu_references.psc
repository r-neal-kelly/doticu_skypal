; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_references hidden

; needs an All_References and Grid_References func

; all of these functions filter out "none" references.

; You can filter for however many types you want. Checks the reference and the base.
; If you have '0' anywhere in the array, you will get all available references, making all other elements in the array irrelevant.
ObjectReference[] function Filter(int[] form_types) native global

; You can restrict your filter to the currently loaded cell grid around the player. (This dynamically checks uGridsToLoad.)
ObjectReference[] function Filter_Grid(int[] form_types) native global

; mode options: "AND", "OR", or "XOR". It's case insensitive. If nothing matches, defaults to "OR".
; if (mode == "AND"): will pass references that match all elements in the array.
; if (mode == "OR"): will pass references that match any of the elements in the array.
; if (mode == "XOR"): will pass references that match only one of the elements in the array, not 0 or more than 1.
; if (do_negate == true): "AND" == "NAND", "OR" == "NOR", and "XOR" == "XNOR". Essentially, you get the opposite for each of the above.
ObjectReference[] function Filter_Keywords(ObjectReference[] references, Keyword[] keywords, string mode = "OR", bool do_negate = false) native global

; if (distance < 0.0), it defaults to 0.0
; if (from == none), it defaults to the Player
; mode options: "<", or ">". If nothing matches, defaults to "<". (More may be added in the future.)
; if (mode == "<"), it passes only references that are less than the distance.
; if (mode == ">"), it passes only references that are greater than the distance.
ObjectReference[] function Filter_Distance(ObjectReference[] references, float distance, ObjectReference from = none, string mode = "<") native global

; It may actually be faster to let C++ iterate and invoke your callback per reference. Return true to keep iterating or false to stop.
; Callback should look like: "bool function My_Global_Callback(ObjectReference reference, int index, int end) global"
function Global_For_Each(ObjectReference[] references, string script_name, string global_name) native global

; Callback should look like: "bool function My_Form_Method_Callback(ObjectReference reference, int index, int end)"
function Form_For_Each(ObjectReference[] references, string script_name, string method_name, Form on_this) native global

; Callback should look like: "bool function My_Alias_Method_Callback(ObjectReference reference, int index, int end)"
function Alias_For_Each(ObjectReference[] references, string script_name, string method_name, Alias on_this) native global

; Callback should look like: "bool function My_Active_Magic_EffectMethod_Callback(ObjectReference reference, int index, int end)"
function Active_Magic_Effect_For_Each(ObjectReference[] references, string script_name, string method_name, ActiveMagicEffect on_this) native global
