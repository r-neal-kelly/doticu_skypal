; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname SkyPal_References hidden

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
    Counters
/;

int function Count_Disabled(ObjectReference[] refs) native global
int function Count_Enabled(ObjectReference[] refs) native global



;/
    Helpers:
        If (refs == none): Passes an empty array.
/;

; Changes how references collide in their environment.
; Works only on refs that currently have 3D. Does not work on the player.
; If a ref is an actor, the setting will need to be reapplied more often, e.g. after they are enabled.
; if (collision_layer_type == invalid): Nothing is changed.
function Change_Collision_Layer_Type(ObjectReference[] refs, int collision_layer_type) native global

function Disable(ObjectReference[] refs) native global
function Enable(ObjectReference[] refs) native global



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

; if (bases == none, invalid): Uses an empty list.
; if (mode == ""): Passes all refs that have a base in the list.
; if (mode == "!"): Passes all refs that do not have a base in the list.
ObjectReference[] function Filter_Bases(ObjectReference[] refs, Form[] bases, string mode = "") native global
ObjectReference[] function Filter_Bases_Form_List(ObjectReference[] refs, FormList bases, string mode = "") native global

; if (collision_layer_types == none): Uses an empty array.
; if (mode == ""): Passes all refs that have a collision layer type in the list.
; if (mode == "!"): Passes all refs that do not have a collision layer type in the list.
; refs that have no collision layer type are invalid and never pass.
ObjectReference[] function Filter_Collision_Layer_Types(ObjectReference[] refs, int[] collision_layer_types, string mode = "") native global

; if (mode == ""): Passes all refs that are deleted.
; if (mode == "!"): Passes all refs that are not deleted.
ObjectReference[] function Filter_Deleted(ObjectReference[] refs, string mode = "") native global

; if (distance < 0.0): Uses 0.0.
; if (from == none): Uses the player reference.
; if (mode == "<"): Passes refs that are inside the distance.
; if (mode == ">"): Passes refs that are outside the distance.
ObjectReference[] function Filter_Distance(ObjectReference[] refs, float distance, ObjectReference from = none, string mode = "<") native global

; if (mode == ""): Passes all refs that are enabled.
; if (mode == "!"): Passes all refs that are disabled.
ObjectReference[] function Filter_Enabled(ObjectReference[] refs, string mode = "") native global

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

; checks Factions/ActorBase owners on Cell, EncounterZone, Worldspace, and ObjectReference
; if (owners == none): Passes an empty array.
; if (mode == "|"): Passes refs that have any of the owners. (OR Gate)
; if (mode == "&"): Passes refs that have all of the owners. (AND Gate)
; if (mode == "^"): Passes refs that have exactly one of the owners. (XOR Gate)
; if (mode == "!|"): Passes refs that have none of the owners. (NOR Gate)
; if (mode == "!&"): Passes refs that do not have all of the owners. (NAND Gate)
; if (mode == "!^"): Passes refs that have 0 or more than 1 of the owners. (XNOR Gate)
ObjectReference[] function Filter_Owners(ObjectReference[] refs, Actor[] owners, string mode = "|") native global

; checks Factions/ActorBase owners on Cell, EncounterZone, Worldspace, and ObjectReference
; if (potential_thieves == none): Passes an empty array.
; if (mode == "|"): Passes refs that have any of the potential thieves. (OR Gate)
; if (mode == "&"): Passes refs that have all of the potential thieves. (AND Gate)
; if (mode == "^"): Passes refs that have exactly one of the potential theives. (XOR Gate)
; if (mode == "!|"): Passes refs that have none of the potential thieves. (NOR Gate)
; if (mode == "!&"): Passes refs that do not have all of the potential thieves. (NAND Gate)
; if (mode == "!^"): Passes refs that have 0 or more than 1 of the potential thieves. (XNOR Gate)
ObjectReference[] function Filter_Potential_Thieves(ObjectReference[] refs, Actor[] potential_thieves, string mode = "|") native global



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
    Combiners:
        Some efficient combinations which can save time and memory. Check previous signatures for instructions.
        Getter + Filter combiners can avoid the unnecessary creation of script objects. Highly recommended.
/;

ObjectReference[] function All_Filter_Bases(Form[] bases, string mode = "") native global
ObjectReference[] function All_Filter_Bases_Form_List(FormList bases, string mode = "") native global

ObjectReference[] function Grid_Filter_Bases(Form[] bases, string mode = "") native global
ObjectReference[] function Grid_Filter_Bases_Form_List(FormList bases, string mode = "") native global
