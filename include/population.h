///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/07    //
///=-------------------=///



///
typedef struct {
    u32 population;
    u8  race;
    u8  culture;
    
    void *next;
} PopulationMember;

typedef struct {
    u32 count;
    
    PopulationMember *first;
} PopulationList;