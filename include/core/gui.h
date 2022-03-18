///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/03/09   //
//   @Edited:  22/03/17   //
///=--------------------=///



/// Structures
typedef struct {
    // Main menu GUI
    u8    mmFlags;
    
    // Options
    u8    omFlags;
    u32   resolutionActive;
    bool  fullscreenCheck;
    u32   languageActive;
    float LOD;
    bool  messageCheck;
    
    // Map
    u16   pmFlags;
} GUI;