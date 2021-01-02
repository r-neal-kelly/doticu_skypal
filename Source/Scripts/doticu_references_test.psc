; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_references_test extends Quest

FormList property form_list_SoulGemsAll auto
Keyword property keyword_JobMerchant auto
Keyword property keyword_unique_dragonborn auto
Keyword property keyword_unique_player auto
Keyword property keyword_WeapTypeSword auto

; Runs only once.
event OnInit()
    ;RegisterForSingleUpdate(2)

    ;Test_Sort_Distance()
    ;Test_Filter_Bases_Form_List()
    Test_Filter_Keywords()
    ;Test_Filter_Distance()
    ;Test_Filter()
    ;Test_Filter_Grid()
    ;Test_Filter_Grid_Actor()
    ;Test_Filter_Grid_Flora()
    ;Test_Filter_Grid_Actor_Flora()
    ;Test_Global_For_Each()
    ;Test_Form_For_Each()
endEvent

event OnUpdate()
    Test_IHarvest()
    RegisterForSingleUpdate(5)
endEvent

; tests
function Test_IHarvest()
    ; simple simulation
    ObjectReference[] grid_refs = doticu_references.Grid()

    int[] form_types = new int[1]
    form_types[0] = 62; Character

    grid_refs = doticu_references.Filter_Form_Types(grid_refs, form_types, "!")
    grid_refs = doticu_references.Filter_Distance(grid_refs, 5000.0, none, "<")
    grid_refs = doticu_references.Sort_Distance(grid_refs, none, "<")

    Trace_References(grid_refs, 5)
endFunction

function Test_Sort_Distance()
    Debug.Trace("Begin: Test_Sort_Distance")
    Debug.Trace("")

    ObjectReference[] grid_refs = doticu_references.Grid()

    Debug.Trace("    (grid_refs, 5000.0, none, <)")
    ObjectReference[] filtered_refs1 = doticu_references.Filter_Distance(grid_refs, 5000.0, none, "<")
    Trace_References(filtered_refs1, 15)
    Debug.Trace("")
    Debug.Trace("    (sorted <)")
    Trace_References(doticu_references.Sort_Distance(filtered_refs1, none, "<"), 15)
    Debug.Trace("    (sorted >)")
    Trace_References(doticu_references.Sort_Distance(filtered_refs1, none, ">"), 15)

    Debug.Trace("    (grid_refs, 5000.0, none, >)")
    ObjectReference[] filtered_refs2 = doticu_references.Filter_Distance(grid_refs, 5000.0, none, ">")
    Trace_References(filtered_refs2, 15)
    Debug.Trace("")
    Debug.Trace("    (sorted <)")
    Trace_References(doticu_references.Sort_Distance(filtered_refs2, none, "<"), 15)
    Debug.Trace("    (sorted >)")
    Trace_References(doticu_references.Sort_Distance(filtered_refs2, none, ">"), 15)

    Debug.Trace("End: Test_Sort_Distance")
    Debug.Trace("")
endFunction

function Test_Filter_Bases_Form_List()
    Debug.Trace("Begin: Test_Filter_Bases_Form_List")
    Debug.Trace("")

    ObjectReference[] all_refs = doticu_references.All()

    Debug.Trace("    (all_refs, SoulGemsAll, dont_negate)")
    Trace_References(doticu_references.Filter_Bases_Form_List(all_refs, form_list_SoulGemsAll, false), 15)
    Debug.Trace("")
    ;Debug.Trace("    (all_refs, SoulGemsAll, do_negate)")
    ;Trace_References(doticu_references.Filter_Bases_Form_List(all_refs, form_list_SoulGemsAll, true), 15)
    ;Debug.Trace("")

    ObjectReference[] grid_refs = doticu_references.Grid()
    Debug.Trace("    (grid_refs, SoulGemsAll, dont_negate)")
    Trace_References(doticu_references.Filter_Bases_Form_List(grid_refs, form_list_SoulGemsAll, false), 15)
    Debug.Trace("")
    Debug.Trace("    (grid_refs, SoulGemsAll, do_negate)")
    Trace_References(doticu_references.Filter_Bases_Form_List(grid_refs, form_list_SoulGemsAll, true), 15)
    Debug.Trace("")

    Debug.Trace("End: Test_Filter_Bases_Form_List")
    Debug.Trace("")
endFunction

function Test_Filter_Keywords()
    Debug.Trace("Begin: Test_Filter_Keywords")
    Debug.Trace("")

    ObjectReference[] all_refs = doticu_references.All()
    ObjectReference[] grid_refs = doticu_references.Grid()
    Keyword[] keywords = new Keyword[2]

    keywords[0] = keyword_WeapTypeSword
    Debug.Trace("    (all_refs, WeapTypeSword, |)")
    Trace_References(doticu_references.Filter_Keywords(all_refs, keywords, "|"), 15)
    Debug.Trace("")
    Debug.Trace("    (all_refs, WeapTypeSword, !|)")
    Trace_References(doticu_references.Filter_Keywords(all_refs, keywords, "!|"), 15)
    Debug.Trace("")

    keywords[0] = keyword_unique_player
    Debug.Trace("    (grid_refs, keyword_unique_player, |)")
    Trace_References(doticu_references.Filter_Keywords(grid_refs, keywords, "|"), 15)
    Debug.Trace("")
    Debug.Trace("    (grid_refs, keyword_unique_player, !|)")
    Trace_References(doticu_references.Filter_Keywords(grid_refs, keywords, "!|"), 15)
    Debug.Trace("")

    keywords[0] = keyword_unique_player
    keywords[1] = keyword_unique_dragonborn
    Debug.Trace("    (grid_refs, keyword_unique_player + keyword_unique_dragonborn, |)")
    Trace_References(doticu_references.Filter_Keywords(grid_refs, keywords, "|"), 15)
    Debug.Trace("")
    Debug.Trace("    (grid_refs, keyword_unique_player + keyword_unique_dragonborn, !|)")
    Trace_References(doticu_references.Filter_Keywords(grid_refs, keywords, "!|"), 15)
    Debug.Trace("")

    keywords[0] = keyword_JobMerchant
    Debug.Trace("    (all_refs, JobMerchant, |)")
    Trace_References(doticu_references.Filter_Keywords(all_refs, keywords, "|"), 15)
    Debug.Trace("")
    Debug.Trace("    (all_refs, JobMerchant, !|)")
    Trace_References(doticu_references.Filter_Keywords(all_refs, keywords, "!|"), 15)
    Debug.Trace("")

    keywords[0] = keyword_WeapTypeSword
    keywords[1] = keyword_JobMerchant
    Debug.Trace("    (all_refs, WeapTypeSword + JobMerchant, |)")
    Trace_References(doticu_references.Filter_Keywords(all_refs, keywords, "|"), 15)
    Debug.Trace("")
    Debug.Trace("    (all_refs, WeapTypeSword + JobMerchant, &)")
    Trace_References(doticu_references.Filter_Keywords(all_refs, keywords, "&"), 15)
    Debug.Trace("")
    Debug.Trace("    (all_refs, WeapTypeSword + JobMerchant, !&)")
    Trace_References(doticu_references.Filter_Keywords(all_refs, keywords, "!&"), 15)
    Debug.Trace("")
    
    Debug.Trace("End: Test_Filter_Keywords")
    Debug.Trace("")
endFunction

function Test_Filter_Distance()
    Debug.Trace("Begin: Test_Filter_Distance")
    Debug.Trace("")

    ObjectReference[] grid_refs = doticu_references.Grid()

    Debug.Trace("    (grid_refs, 500.0, none, <)")
    Trace_References(doticu_references.Filter_Distance(grid_refs, 500.0, none, "<"), 15)
    Debug.Trace("")
    Debug.Trace("    (grid_refs, 500.0, none, >)")
    Trace_References(doticu_references.Filter_Distance(grid_refs, 500.0, none, ">"), 15)
    Debug.Trace("")
    Debug.Trace("    (grid_refs, 5000.0, none, <)")
    Trace_References(doticu_references.Filter_Distance(grid_refs, 5000.0, none, "<"), 15)
    Debug.Trace("")
    Debug.Trace("    (grid_refs, 5000.0, none, >)")
    Trace_References(doticu_references.Filter_Distance(grid_refs, 5000.0, none, ">"), 15)
    Debug.Trace("")

    Debug.Trace("End: Test_Filter_Distance")
    Debug.Trace("")
endFunction

;/function Test_Filter_Grid_Actor() global
    Debug.Trace("Begin: Test_Filter_Grid_Actor")

    int[] form_types = new int[1]
    form_types[0] = 62; FormType.kCharacter (this is a reference form_type)

    ObjectReference[] references = doticu_references.Filter_Grid(form_types)
    Trace_References(references)

    Debug.Trace("End: Test_Filter_Grid_Actor")
endFunction

function Test_Filter_Grid_Flora() global
    Debug.Trace("Begin: Test_Filter_Grid_Flora")

    int[] form_types = new int[1]
    form_types[0] = 39; FormType.kFlora (this is a base form_type)

    ObjectReference[] references = doticu_references.Filter_Grid(form_types)
    Trace_References(references)

    Debug.Trace("End: Test_Filter_Grid_Flora")
endFunction

function Test_Filter_Grid_Actor_Flora() global
    Debug.Trace("Begin: Test_Filter_Grid_Actor_Flora")

    int[] form_types = new int[2]
    form_types[0] = 62; FormType.kCharacter (this is a reference form_type)
    form_types[1] = 39; FormType.kFlora (this is a base form_type)

    ObjectReference[] references = doticu_references.Filter_Grid(form_types)
    Trace_References(references)

    Debug.Trace("End: Test_Filter_Grid_Actor_Flora")
endFunction/;

function Test_Global_For_Each()
    Debug.Trace("Begin: Test_Global_For_Each")

    int[] form_types = new int[1]
    form_types[0] = 62; FormType.kCharacter (this is a reference form_type)

    doticu_references.Global_For_Each(doticu_references.Filter_Form_Types(doticu_references.Grid(), form_types), "doticu_references_test", "My_Global_Callback")
endFunction

bool function My_Global_Callback(ObjectReference reference, int index, int end) global
    Debug.Trace("    index:" + index + ", form_id: " + reference.GetFormID() + ", display_name: " + reference.GetDisplayName())

    if (index + 1 == 50 || index + 1 == end)
        Debug.Trace("End: Test_Global_For_Each")
        return false
    else
        return true
    endIf
endFunction

function Test_Form_For_Each()
    Debug.Trace("Begin: Test_Form_For_Each")

    int[] form_types = new int[2]
    form_types[0] = 62; FormType.kCharacter (this is a reference form_type)
    form_types[1] = 39; FormType.kFlora (this is a base form_type)

    doticu_references.Form_For_Each(self, doticu_references.Grid(), "doticu_references_test", "My_Method_Callback")
endFunction

bool function My_Method_Callback(ObjectReference reference, int index, int end); notice there is no global here
    Debug.Trace("    index:" + index + ", form_id: " + reference.GetFormID() + ", display_name: " + reference.GetDisplayName())

    if (index + 1 == 50 || index + 1 == end)
        Debug.Trace("End: Test_Form_For_Each")
        return false
    else
        return true
    endIf
endFunction

; helpers
function Trace_References(ObjectReference[] references, int MAX_TO_DISPLAY = 50) global
    Debug.Trace("    total: " + references.length + ". Will only show up to " + MAX_TO_DISPLAY + " refs.")

    int idx = 0
    int end = 0
    if (references.length > MAX_TO_DISPLAY)
        end = MAX_TO_DISPLAY
    else
        end = references.length
    endIf

    while idx < end
        Debug.Trace("    idx:" + idx + ", form_id: " + references[idx].GetFormID() + ", display_name: " + references[idx].GetDisplayName())
        idx += 1
    endWhile
endFunction
