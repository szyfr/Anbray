///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/02/09   //
//   @Edited:  22/03/17   //
///=--------------------=///



/// Functions

//  Initializes core game variables
//     Uses:
//   - All
void InitializeGameData(void) {
    // Init Raylib
    SetTraceLogLevel(LOG_NONE);       // Disables Raylib Logging
    InitWindow(1280, 720, "Anbray");  // Inits window
    SetTargetFPS(60);                 // Sets atrget FPS to 60
    SetExitKey(KEY_END);              // Sets exit key to END
    
    // Init global structures
    gamestate    = (Gamestate*)calloc(1, sizeof(Gamestate));
    gui          = (GUI*)calloc(1, sizeof(GUI));
    player       = (Player*)calloc(1, sizeof(Player));
    localization = (Localization*)calloc(1, sizeof(Localization));
    map          = (Map*)calloc(1, sizeof(Map));
    debugLogger  = (DebugLogger*)calloc(1, sizeof(DebugLogger));
    
    InitializeOptions();
    DB_InitializeErrorlog();
    InitializePlayer();
    LoadLocalization(0);
    
    
    
    
}







//  TEMPLATE
//     Uses:
//   - NONE