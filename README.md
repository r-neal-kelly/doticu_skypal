# doticu-references
*A small Papyrus library to assist with handling references speedily in The Elder Scrolls V: Skyrim Special Edition.*

### User and Developer Requirements:
- [Skyrim SE 1.5.97](https://store.steampowered.com/app/489830/The_Elder_Scrolls_V_Skyrim_Special_Edition/)
- [SKSE 2.0.17+](https://skse.silverlock.org/)

### Examples:
```Papyrus
    ; You can filter for any number of form types
    int[] form_types = new int[2]

    ; Using Reference form types
    form_types[0] = 62; Actor, FormType.kCharacter

    ; And/or Base form types
    form_types[1] = 39; Flora, FormType.kFlora

    ; Get all loaded references in the entire game that are Actors or Flora
    ObjectReference[] references = doticu_references.Filter(form_types)

    ; Or just get references on the player grid (the uGridsToLoad ini setting)
    ObjectReference[] nearby_player = doticu_references.Filter_Grid(form_types)
```

### Notes:
You don't need to use the .esp file or the test Papyrus script. Only the .dll and the "doticu_references" script are necessary.