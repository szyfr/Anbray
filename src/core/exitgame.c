///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/21    //
///=-------------------=///



/// Functions

// Exits the game
//     Uses:
//   - Localization
//   - Map
//   - DebugLogger
void QuitGame(void) {
    EndDrawing();
    
    // Clear localization
    FreeLocalization(true);
    FreeLocalization(false);
    
    // Clear map
    FreeMap();
    
    // Clear debugger
    DB_SaveErrorlog();
    
    exit(0);
}