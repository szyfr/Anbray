///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/07    //
///=-------------------=///



///
// TODO: Fill out Linked list functions
ProvinceList *CreateProvinceList();
void AddToProvinceList(ProvinceList *provList, ProvinceMember *mem);
void RemoveFromProvinceList(ProvinceList *provList, ProvinceMember *mem);
void DeleteProvinceList(ProvinceList *provList);
void SwitchProvinceList(ProvinceList *destProvList, ProvinceList *srcProvList, ProvinceMember *mem);