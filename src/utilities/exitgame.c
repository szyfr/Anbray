///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/21    //
///=-------------------=///



/// Functions

// Exits the game
void QuitGame(Gamestate *gamestate) {
    EndDrawing();
    FreeLocalization(gamestate,true);
    FreeLocalization(gamestate,false);
    FreeMap(gamestate);
    DB_SaveErrorlog(gamestate);
    exit(0);
}