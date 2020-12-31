; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_references_test extends Quest

Keyword property keyword_JobMerchant auto
Keyword property keyword_WeapTypeSword auto

; Runs only once.
event OnInit()
    Test_Filter_Keywords()
    Test_Filter_Distance()
    ;Test_Filter()
    ;Test_Filter_Grid()
    ;Test_Filter_Grid_Actor()
    ;Test_Filter_Grid_Flora()
    ;Test_Filter_Grid_Actor_Flora()
    ;Test_Global_For_Each()
    ;Test_Form_For_Each()
endEvent

; tests
function Test_Filter_Keywords()
    Debug.Trace("Begin: Test_Filter_Keywords")
    Debug.Trace("")

    ObjectReference[] all_refs = All_References()
    Keyword[] keywords = new Keyword[2]

    keywords[0] = keyword_WeapTypeSword
    Debug.Trace("    (all_refs, WeapTypeSword, or, dont_negate)")
    Trace_References(doticu_references.Filter_Keywords(all_refs, keywords, "or", false), 15)
    Debug.Trace("")
    Debug.Trace("    (all_refs, WeapTypeSword, or, do_negate)")
    Trace_References(doticu_references.Filter_Keywords(all_refs, keywords, "or", true), 15)
    Debug.Trace("")

    keywords[0] = keyword_JobMerchant
    Debug.Trace("    (all_refs, JobMerchant, or, dont_negate)")
    Trace_References(doticu_references.Filter_Keywords(all_refs, keywords, "or", false), 15)
    Debug.Trace("")
    Debug.Trace("    (all_refs, JobMerchant, or, do_negate)")
    Trace_References(doticu_references.Filter_Keywords(all_refs, keywords, "or", true), 15)
    Debug.Trace("")

    keywords[0] = keyword_WeapTypeSword
    keywords[1] = keyword_JobMerchant
    Debug.Trace("    (all_refs, WeapTypeSword + JobMerchant, or, dont_negate)")
    Trace_References(doticu_references.Filter_Keywords(all_refs, keywords, "or", false), 15)
    Debug.Trace("")
    Debug.Trace("    (all_refs, WeapTypeSword + JobMerchant, and, dont_negate)")
    Trace_References(doticu_references.Filter_Keywords(all_refs, keywords, "and", false), 15)
    Debug.Trace("")
    Debug.Trace("    (all_refs, WeapTypeSword + JobMerchant, and, do_negate)")
    Trace_References(doticu_references.Filter_Keywords(all_refs, keywords, "and", true), 15)
    Debug.Trace("")
    
    Debug.Trace("End: Test_Filter_Keywords")
    Debug.Trace("")
endFunction

function Test_Filter_Distance()
    Debug.Trace("Begin: Test_Filter_Distance")
    Debug.Trace("")

    ObjectReference[] grid_refs = Grid_References()

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

function Test_Filter() global
    Debug.Trace("Begin: Test_Filter")

    int[] form_types = new int[1]
    form_types[0] = 0; the 'NONE' or 'FORM' form type, which filters for everything

    ObjectReference[] references = doticu_references.Filter(form_types)
    Trace_References(references)

    Debug.Trace("End: Test_Filter")
endFunction

function Test_Filter_Grid() global
    Debug.Trace("Begin: Test_Filter_Grid")

    int[] form_types = new int[1]
    form_types[0] = 0; the 'NONE' or 'FORM' form type, which filters for everything

    ObjectReference[] references = doticu_references.Filter_Grid(form_types)
    Trace_References(references)

    Debug.Trace("End: Test_Filter_Grid")
endFunction

function Test_Filter_Grid_Actor() global
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
endFunction

function Test_Global_For_Each()
    Debug.Trace("Begin: Test_Global_For_Each")

    int[] form_types = new int[2]
    form_types[0] = 62; FormType.kCharacter (this is a reference form_type)
    form_types[1] = 39; FormType.kFlora (this is a base form_type)

    doticu_references.Global_For_Each(doticu_references.Filter_Grid(form_types), "doticu_references_test", "My_Global_Callback")
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

    doticu_references.Form_For_Each(doticu_references.Filter_Grid(form_types), "doticu_references_test", "My_Method_Callback", self)
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
ObjectReference[] function All_References()
    int[] form_types = new int[1]
    form_types[0] = 0; the 'NONE' or 'FORM' form type, which filters for everything

    return doticu_references.Filter(form_types)
endFunction

ObjectReference[] function Grid_References()
    int[] form_types = new int[1]
    form_types[0] = 0
    return doticu_references.Filter_Grid(form_types)
endFunction

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
