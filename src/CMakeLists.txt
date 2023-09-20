SET(SOURCES screens/ui_Configuration.c
    screens/ui_Color_Chooser.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c)

add_library(ui ${SOURCES})
