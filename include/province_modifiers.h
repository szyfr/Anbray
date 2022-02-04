///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/07    //
///=-------------------=///



///
typedef struct {
    u16 provModID;
    u16 date;
    
    void *next;
} ProvinceModifierMember;

typedef struct {
    u32 count;
    
    ProvinceModifierMember *first;
} ProvinceModifierList;