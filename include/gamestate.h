///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 21/12/30    //
///=-------------------=///



/// Enums
typedef enum {
    STATE_MAINMENU = 0,
    STATE_MAP
} State;


/// Structures
typedef struct {
    State state;
    bool  debug;
    
    // Main menu GUI
    u8 mmFlags;
    
    // Map data
    Camera3D camera;
    char    *mapName;
    Map      map;
    
    // Localization
    char **coreLocalization;
    u16 coreLength;
    char **mapLocalization;
    u16 mapLength;
} Gamestate;