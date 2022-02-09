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
} Gamestate;

typedef struct {
    // Main menu GUI
    u8    mmFlags;
    
    // Options
    u8    omFlags;
    u32   resolutionActive;
    bool  fullscreenCheck;
    u32   languageActive;
    float LOD;
    bool  messageCheck;
    
    // Map
    u16   pmFlags;
} GUI;

typedef struct {
    Camera3D camera;
} Player;

typedef struct {
    char **coreLocalization;
    u16 coreLength;
    char **mapLocalization;
    u16 mapLength;
} Localization;

typedef struct {
    char *errorlog;
    u32   errorlogSize;
} DebugLogger;