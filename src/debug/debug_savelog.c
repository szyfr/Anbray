///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/01/19   //
//   @Edited:  22/03/17   //
///=--------------------=///



// Save message log to file and free
//     Uses:
//   - DebugLogger
void DB_SaveErrorlog(void) {
    SaveFileText("log.txt", debugLogger->errorlog);
    free(debugLogger->errorlog);
}