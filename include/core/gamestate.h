///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 21/12/30   //
//   @Edited:  22/03/17   //
///=--------------------=///



/// Enums
typedef enum {
    STATE_MAINMENU = 0,
    STATE_MAP
} State;


/// Structures
typedef struct {
    State state;
} Gamestate;