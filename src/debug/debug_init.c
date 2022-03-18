///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/01/19   //
//   @Edited:  22/03/17   //
///=--------------------=///



// Initialize message log
//     Uses:
//   - DebugLogger
void DB_InitializeErrorlog(void) {
    debugLogger->errorlogSize = 1000;
    debugLogger->errorlog = (char*)calloc(debugLogger->errorlogSize, sizeof(char));
}