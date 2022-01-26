///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/07    //
///=-------------------=///



/// Defines
#define TYPE_DEFAULT      0
#define TYPE_WATER        1
#define TYPE_CONTROLLABLE 2
#define TYPE_IMPASSABLE   3

/// Structs
typedef struct {
    u16 localID;
    u8  terrain;
    u8  type;
    
    s16 maximumInfrastruture;
    s16 currentInfrastruture;
    
    PopulationList *population;
    
    u8 buildings[6];
    
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