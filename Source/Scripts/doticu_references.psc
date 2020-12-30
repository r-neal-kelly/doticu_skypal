; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_references hidden

; needs an All References func

; You can filter for however many types you want. Checks the reference and the base.
; If you have '0' anywhere in the array, you will get all available references, making all other elements in the array irrelevant.
ObjectReference[] function Filter(int[] form_types) native global

; You can restrict your filter to the currently loaded cell grid around the player. (This dynamically checks uGridsToLoad.)
ObjectReference[] function Filter_Grid(int[] form_types) native global

; Possible modes are "AND", "OR", AND "XOR".
; With do_negate toggled, "AND" == "NAND", "OR" == "NOR", and "XOR" == "XNOR".
; XOR will pass references that match exactly one element.
; Mode is case insensitive and matches only the first necessary letters, e.g. "oRdAIn da YARL" == "OR". If nothing matches, defaults to "OR".
ObjectReference[] function Filter_Keywords(ObjectReference[] references, Keyword[] keywords, string mode = "OR", bool do_negate = false) native global

; It may actually be faster to let C++ iterate and invoke your callback per reference. Return true to keep iterating or false to stop.
; Callback should look like: "bool function My_Global_Callback(ObjectReference reference, int index, int end) global"
function Global_For_Each(ObjectReference[] references, string script_name, string global_name) native global

; Callback should look like: "bool function My_Form_Method_Callback(ObjectReference reference, int index, int end)"
function Form_For_Each(ObjectReference[] references, string script_name, string method_name, Form on_this) native global

; Callback should look like: "bool function My_Alias_Method_Callback(ObjectReference reference, int index, int end)"
function Alias_For_Each(ObjectReference[] references, string script_name, string method_name, Alias on_this) native global

; Callback should look like: "bool function My_Active_Magic_EffectMethod_Callback(ObjectReference reference, int index, int end)"
function Active_Magic_Effect_For_Each(ObjectReference[] references, string script_name, string method_name, ActiveMagicEffect on_this) native global
