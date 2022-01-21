///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/19    //
///=-------------------=///



/// Functions

// Logging errors/messages
void DB_Errorlog(Gamestate *gamestate, char *message) {
    if(gamestate->optionsData->messageLogging) {
        printf(message);
        
        if((strlen(gamestate->errorlog) + strlen(message)) > gamestate->errorlogSize) {
            printf("\nErrorlog size insufficient at: %i\n- Increasing by 1000b\n",gamestate->errorlogSize);
            
            gamestate->errorlogSize += 1000;
            char *tempPtr            = (char*)realloc(gamestate->errorlog, gamestate->errorlogSize);
            
            if(tempPtr != 0) {
                gamestate->errorlog = tempPtr;
                
                printf("- New size: %i\n\n",gamestate->errorlogSize);
            } else {
                gamestate->errorlogSize -= 1000;
                
                printf("- Failed to allocate new space\n\n");
                return;
            }
        }
        
        strcat(gamestate->errorlog, message);
    }
}

// Initialize message log
void DB_InitializeErrorlog(Gamestate *gamestate) {\
    gamestate->errorlogSize = 1000;
    gamestate->errorlog = (char*)calloc(gamestate->errorlogSize, sizeof(char));
}

// Save message log to file and free
void DB_SaveErrorlog(Gamestate *gamestate) {
    SaveFileText("log.txt", gamestate->errorlog);
    free(gamestate->errorlog);
}

// Save message log and exit game
void DB_CrashError(Gamestate *gamestate) {
    if(gamestate->optionsData->messageLogging) {
        SaveFileText("log.txt", gamestate->errorlog);
        free(gamestate->errorlog);
        
        EndDrawing();
        exit(1);
    }
}