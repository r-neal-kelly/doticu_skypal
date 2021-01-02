; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname skypal_references hidden

;/
    Getters:
        You can use these to start your filters.
/;

; Gets all available refs in the game.
ObjectReference[] function All() native global

; Gets all refs currently in the cell grid around the player. (Dynamically checks uGridsToLoad.)
; This is your go-to method to start your filter, as it's more performant to work with less refs.
ObjectReference[] function Grid() native global



;/
    Filters:
        Each filter has its modes listed above its signature.
        if (refs == none): Passes an empty array.
        if (mode == invalid): Passes the default mode listed in each signature.
/;

; if (form_types == none): Uses an empty array.
; if (mode == ""): Passes all refs that have a base type in the list.
; if (mode == "!"): Passes all refs that do not have a base type in the list.
ObjectReference[] function Filter_Base_Form_Types(ObjectReference[] refs, int[] form_types, string mode = "") native global

; if (bases == none, invalid): Uses an empty form list.
; if (mode == ""): Passes all refs that have a base in the list.
; if (mode == "!"): Passes all refs that do not have a base in the list.
ObjectReference[] function Filter_Bases_Form_List(ObjectReference[] refs, FormList bases, string mode = "") native global

; if (distance < 0.0): Uses 0.0.
; if (from == none): Uses the player reference.
; if (mode == "<"): Passes refs that are inside the distance.
; if (mode == ">"): Passes refs that are outside the distance.
ObjectReference[] function Filter_Distance(ObjectReference[] refs, float distance, ObjectReference from = none, string mode = "<") native global

; if (form_types == none): Uses an empty array.
; if (mode == ""): Passes all refs that have a type in the list.
; if (mode == "!"): Passes all refs that do not have a type in the list.
ObjectReference[] function Filter_Form_Types(ObjectReference[] refs, int[] form_types, string mode = "") native global

; if (keywords == none): Passes an empty array.
; if (mode == "|"): Passes refs that match any keyword. (OR Gate)
; if (mode == "&"): Passes refs that match all keywords. (AND Gate)
; if (mode == "^"): Passes refs that match exactly one keyword. (XOR Gate)
; if (mode == "!|"): Passes refs that match no keywords. (NOR Gate)
; if (mode == "!&"): Passes refs that do not match all of the keywords. (NAND Gate)
; if (mode == "!^"): Passes refs that match 0 or more than 1 keyword. (XNOR Gate)
ObjectReference[] function Filter_Keywords(ObjectReference[] refs, Keyword[] keywords, string mode = "|") native global



;/
    Sorters:
        Each sorter has its modes listed above its signature.
        if (refs == none): Passes an empty array.
/;

; if (from == none): Uses the player reference.
; if (mode == "<"): Sorts from closer to farther distance.
; if (mode == ">"): Sorts from farther to closer distance.
ObjectReference[] function Sort_Distance(ObjectReference[] refs, ObjectReference from = none, string mode = "<") native global



;/
    Iterators:
        It may actually be faster to let C++ iterate for you. Return true to keep iterating or false to stop.
        If the script with the callback is extended from a Form (e.g. Quest) use Form_For_Each.
        If the script with the callback is extended from an Alias, use Alias_For_Each.
        If the script with the callback is extended from an ActiveMagicEffect, use Active_Magic_Effect_For_Each.
        Global_For_Each can be used on any script, as long as the callabck has the global keyword on it.
/;

; callback: bool function My_Global_Callback(ObjectReference reference, int index, int end) global
function Global_For_Each(ObjectReference[] refs, string script_name, string global_name) native global

; callback: bool function My_Form_Method_Callback(ObjectReference reference, int index, int end)
function Form_For_Each(Form this, ObjectReference[] refs, string script_name, string method_name) native global

; callback: bool function My_Alias_Method_Callback(ObjectReference reference, int index, int end)
function Alias_For_Each(Alias this, ObjectReference[] refs, string script_name, string method_name) native global

; callback: bool function My_Active_Magic_EffectMethod_Callback(ObjectReference reference, int index, int end)
function Active_Magic_Effect_For_Each(ActiveMagicEffect this, ObjectReference[] refs, string script_name, string method_name) native global
