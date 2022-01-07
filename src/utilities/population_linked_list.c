///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/07    //
///=-------------------=///



///
// TODO: Fill out Linked list functions
PopulationList CreatePopulationList();
void AddToPopulationList(PopulationList *popList, PopulationMember *mem);
void RemoveFromPopulationList(PopulationList *popList, PopulationMember *mem);
void DeletePopulationList(PopulationList *popList);
void SwitchPopulationList(PopulationList *destPopList, PopulationList *srcPopList, PopulationMember *mem);