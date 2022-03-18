///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/03/18   //
//   @Edited:  22/03/18   //
///=--------------------=///



// Checks surrounding pixels for pixels of the same color
//     Uses:
//   - NONE
bool CheckPixel(Image provinceMap, Color color, int x, int y) {
    Vector2 location = (Vector2){x,y};
    u8 empty = 0;
    
    // Check for map edges
    //if(x == 0 || x == provinceMap.width)  empty++;
    //if(y == 0 || y == provinceMap.height) empty++;
    
    if(!CompareColor(color, GetImageColor(provinceMap, x,   y-1))) empty++;
    if(!CompareColor(color, GetImageColor(provinceMap, x,   y+1))) empty++;
    if(!CompareColor(color, GetImageColor(provinceMap, x-1, y  ))) empty++;
    if(!CompareColor(color, GetImageColor(provinceMap, x+1, y  ))) empty++;
    
    if(empty >= 1) return true;
    else           return false;
}