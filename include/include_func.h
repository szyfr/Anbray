///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/01/26   //
//   @Edited:  22/03/17   //
///=--------------------=///



/// Includes

//- Debug
#include "../src/debug/debug_crasherror.c"
#include "../src/debug/debug_errorlog.c"
#include "../src/debug/debug_init.c"
#include "../src/debug/debug_savelog.c"

//- Utilities
#include "../src/utilities/util_colorcomp.c"
#include "../src/utilities/util_colorconversion.c"
// Linked lists
#include "../src/utilities/linked_list/population_linked_list.c"
#include "../src/utilities/linked_list/province_linked_list.c"
#include "../src/utilities/linked_list/province_modifier_linked_list.c"

//- Core
#include "../src/core/exitgame.c"
#include "../src/core/initgame.c"
// Localization
#include "../src/core/localization/local_free.c"
#include "../src/core/localization/local_getcore.c"
#include "../src/core/localization/local_getmap.c"
#include "../src/core/localization/local_load.c"
#include "../src/core/localization/local_mapname.c"
// Map
#include "../src/core/map/map_calcborder.c"
#include "../src/core/map/map_checkpixel.c"
#include "../src/core/map/map_drawchunksingle.c"
#include "../src/core/map/map_drawchunkmulti.c"
#include "../src/core/map/map_drawmap.c"
#include "../src/core/map/map_free.c"
#include "../src/core/map/map_imagetochunk.c"
#include "../src/core/map/map_load.c"
#include "../src/core/map/map_loadprovince.c"
#include "../src/core/map/map_sortpoints.c"
// Options
#include "../src/core/options/opt_commit.c"
#include "../src/core/options/opt_init.c"
// Player
#include "../src/core/player/player_controls.c"
#include "../src/core/player/player_init.c"
#include "../src/core/player/player_mapmode.c"

//- GUI
#include "../src/gui/mainmenu_gui.c"
#include "../src/gui/optionsmenu_gui.c"
#include "../src/gui/pausemenu_gui.c"
#include "../src/gui/provincemenu_gui.c"