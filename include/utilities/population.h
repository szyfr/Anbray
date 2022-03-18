///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/07    //
///=-------------------=///



/// Structures
typedef struct {
    u32 population;
    u8  race;
    u8  culture;
    u8  religion;
    
    void *next;
} PopulationMember;

typedef struct {
    u32 count;
    
    PopulationMember *first;
} PopulationList;