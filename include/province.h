///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/07    //
///=-------------------=///



///
typedef struct {
    u16 localID;
    u8  terrain;
    
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