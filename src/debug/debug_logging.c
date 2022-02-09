///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/19    //
///=-------------------=///



/// Functions

// Logging errors/messages
//     Uses:
//   - Options
//   - DebugLogger
void DB_Errorlog(char *message) {
    if(options->messageLogging) {
        printf(message);
        
        if((strlen(debugLogger->errorlog) + strlen(message)) > debugLogger->errorlogSize) {
            printf("\nErrorlog size insufficient at: %i\n- Increasing by 1000b\n", debugLogger->errorlogSize);
            
            debugLogger->errorlogSize += 1000;
            char *tempPtr            = (char*)realloc(debugLogger->errorlog, debugLogger->errorlogSize);
            
            if(tempPtr != 0) {
                debugLogger->errorlog = tempPtr;
                
                printf("- New size: %i\n\n", debugLogger->errorlogSize);
            } else {
                debugLogger->errorlogSize -= 1000;
                
                printf("- Failed to allocate new space\n\n");
                return;
            }
        }
        
        strcat(debugLogger->errorlog, message);
    }
}

// Initialize message log
//     Uses:
//   - DebugLogger
void DB_InitializeErrorlog(void) {
    debugLogger->errorlogSize = 1000;
    debugLogger->errorlog = (char*)calloc(debugLogger->errorlogSize, sizeof(char));
}

// Save message log to file and free
//     Uses:
//   - DebugLogger
void DB_SaveErrorlog(void) {
    SaveFileText("log.txt", debugLogger->errorlog);
    free(debugLogger->errorlog);
}

// Save message log and exit game
//     Uses:
//   - Options
//   - DebugLogger
void DB_CrashError(char *message) {
    DB_Errorlog(message);
    if(options->messageLogging) {
        SaveFileText("log.txt", debugLogger->errorlog);
        free(debugLogger->errorlog);
        
        EndDrawing();
        exit(1);
    }
}