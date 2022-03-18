///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/14    //
///=-------------------=///



/// Enum
typedef enum {
    english = 0,
    french,
    italian,
    german,
    spanish,
} Languages;


/// Structures
typedef struct {
    u32  resolutionWidth;
    u32  resolutionHeight;
    bool fullscreen;
    
    u8   mapLOD;
    
    u8   language;
    
    bool messageLogging;
} OptionsData;