///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/01/19   //
//   @Edited:  22/03/17   //
///=--------------------=///



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