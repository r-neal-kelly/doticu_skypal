# doticu-skypal
*A Papyrus library providing optimized functionality for The Elder Scrolls V: Skyrim Special Edition.*

### User and Developer Requirements:
- [Skyrim SE 1.5.97](https://store.steampowered.com/app/489830/The_Elder_Scrolls_V_Skyrim_Special_Edition/)
- [SKSE 2.0.17+](https://skse.silverlock.org/)

## skypal_references:
-  provides getters, filters, sorters, and iterators for references.

### Examples:
```Papyrus
    Scriptname MyQuest extends Quest

    ObjectReference property player auto

    function MyFunc()
        ; Get all refs currently in the cell grid around the player
        ObjectReference[] grid_refs = skypal_references.Grid()

        ; Filter out any refs that are 5000.0 or more units away from the player
        grid_refs = skypal_references.Filter_Distance(grid_refs, 5000.0, player, "<")

        ; Sort them from closest to farthest away from the player
        grid_refs = skypal_references.Sort_Distance(grid_refs, player, "<")

        ; skypal can iterate for you, which can help speed up loops
        ; (We'll use the correct iterator for the "self" variable, which is a Form in this case)
        skypal_references.Form_For_Each(self, grid_refs, "MyQuest", "MyCallback")
    endFunction

    
    bool function MyCallback(ObjectReference ref, int idx, int end)
        ; handle each ref here
        return true; to continue looping. else false to break
    endFunction
```
