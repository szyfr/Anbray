///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/02/23    //
///=-------------------=///



/// Functions

//  Draws options menu
//     Uses:
//   - Player
void DrawProvinceMenu(void) {
    Province *ref = player->selectedProvince;
    if(ref == 0) return;
    if(ref->type > controllable) return;
    
    GuiPanel((Rectangle){0, options->resolutionHeight-500, 400, 500});
    
    GuiLabel((Rectangle){50, 500, 200, 25}, localization->mapLocalization[9+ColorToU32(ref->color)]);
}