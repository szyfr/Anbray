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
    u8    mmFlags;
    
    // Options
    OptionsData *optionsData;
    u8           omFlags;
    u32          resolutionActive;
    bool         fullscreenCheck;
    u32          languageActive;
    float        LOD;
    
    // Map
    u16      pmFlags;
    Camera3D camera;
    Map      map;
    
    // Localization
    char **coreLocalization;
    u16 coreLength;
    char **mapLocalization;
    u16 mapLength;
} Gamestate;