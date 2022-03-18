///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/03/09   //
//   @Edited:  22/03/17   //
///=--------------------=///



/// Enums
typedef enum {
    surface = 0,
    terrain,
    nation,
    race,
    culture,
    religion,
} Mapmode;


/// Structures
typedef struct {
    Camera3D  camera;
    
    Province *selectedProvince;
} Player;