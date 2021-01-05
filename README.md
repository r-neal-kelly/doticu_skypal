# doticu-skypal
*A Papyrus library providing optimized functionality for The Elder Scrolls V: Skyrim Special Edition.*

### User and Developer Requirements:
- [Skyrim SE 1.5.97](https://store.steampowered.com/app/489830/The_Elder_Scrolls_V_Skyrim_Special_Edition/)
- [SKSE 2.0.17+](https://skse.silverlock.org/)

## skypal_references:
- getters, filters, sorters

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
    endFunction
```

## skypal_bases:
- converters

### Examples:
```Papyrus
    Scriptname MyQuest extends Quest

    function MyFunc()
        ; Convert all references to their base forms, with no repeats
        Form[] bases = skypal_bases.From_References(skypal_references.Grid(), ".")
    endFunction
```
