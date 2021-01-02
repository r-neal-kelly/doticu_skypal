# doticu-skypap
*A Papyrus library providing skylib functionality for The Elder Scrolls V: Skyrim Special Edition.*

### User and Developer Requirements:
- [Skyrim SE 1.5.97](https://store.steampowered.com/app/489830/The_Elder_Scrolls_V_Skyrim_Special_Edition/)
- [SKSE 2.0.17+](https://skse.silverlock.org/)

## skypap_references:
-  provides getters, filters, sorters, and iterators for references.

### Examples:
```Papyrus
    ObjectReference property player auto

    ; Gets all refs currently in the cell grid around the player
    ObjectReference[] grid_refs = skypap_references.Grid()

    ; Filter out any refs that are 5000.0 or more units away from the player.
    grid_refs = skypap_references.Filter_Distance(grid_refs, 5000.0, player, "<")

    ; Sort them from close to far
    grid_refs = skypap_references.Sort_Distance(grid_refs, player, "<")
```
