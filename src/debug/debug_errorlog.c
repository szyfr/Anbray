///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/01/19   //
//   @Edited:  22/03/17   //
///=--------------------=///



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