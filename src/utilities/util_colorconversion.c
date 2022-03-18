///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/02/06   //
//   @Edited:  22/03/17   //
///=--------------------=///



// Converts a u32 to color
//     Uses:
//   - NONE
Color U32ToColor(u32 input) {
    Color output = {0};
    
    output.r = (u8)input;
    input    = input >> 8;
    output.g = (u8)input;
    input    = input >> 8;
    output.b = (u8)input;
    output.a = 255;
    
    return output;
}

// Converts a color to a u32
//     Uses:
//   - NONE
u32   ColorToU32(Color input) {
    u32 output;
    
    output  = output << 8;
    output  = input.b;
    output  = output << 8;
    output |= input.g;
    output  = output << 8;
    output |= input.r;
    
    return output;
}