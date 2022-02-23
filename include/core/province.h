///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/07    //
///=-------------------=///



/// Defines


/// Enums
typedef enum {
    plains = 1,
    swamp,
    dwarf_tunnel,
    dwarf_hold,
    cave,
} Terrain;

typedef enum {
    base = 1,
    controllable,
    water,
    impassable
} ProvinceType;


/// Structs
typedef struct {
    u32          localizationID;
    Color        color;
    Terrain      terrain;
    ProvinceType type;
    
    s16 maximumInfrastruture;
    s16 currentInfrastruture;
    
    PopulationList *population;
    
    u8 buildings[8];
    
    ProvinceModifierList *modifiers;
} Province;

typedef struct {
    Province *province;
    
    void *next;
} ProvinceMember;

typedef struct {
    u32 count;
    
    ProvinceMember *first;
} ProvinceList;