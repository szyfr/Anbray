///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/07    //
///=-------------------=///



///
// TODO: Fill out Linked list functions
ProvinceModifierList *CreateProvinceModifierList();
void AddToProvinceModifierList(ProvinceModifierList *provModList, ProvinceModifierMember *mem);
void RemoveFromProvinceModifierList(ProvinceModifierList *provModList, ProvinceModifierMember *mem);
void DeleteProvinceModifierList(ProvinceModifierList *provModList);
void SwitchProvinceModifierList(ProvinceModifierList *destProvModList, ProvinceModifierList *srcProvModList, ProvinceModifierMember *mem);