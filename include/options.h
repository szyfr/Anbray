///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/14    //
///=-------------------=///



///
enum Languages {
    english = 0,
    french,
    italian,
    german,
    spanish,
};

typedef struct {
    u32  resolutionWidth;
    u32  resolutionHeight;
    bool fullscreen;
    
    u8   mapLOD;
    
    u8   language;
} OptionsData;