///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 21/12/30   //
//   @Edited:  22/03/12   //
///=--------------------=///



// Compare Colors
//     Uses:
//   - Map
bool CompareColor(Color c1, Color c2) {
    if(c1.r == c2.r &&
       c1.g == c2.g &&
       c1.b == c2.b) return 1;
    else return 0;
}