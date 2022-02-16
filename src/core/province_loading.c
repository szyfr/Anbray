///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/02/16    //
///=-------------------=///



/// Functions

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

// Loads all provinces from data into memory
//     Uses:
//   - Localization
//   - Map
void LoadProvinceData(void) {
    map->provinces = CreateProvinceList();
    
    // Load data from file
    char buffer[100] = {0};
    strcat(buffer, "data/maps/");
    strcat(buffer, localization->mapLocalization[0]);
    strcat(buffer, "/map/provinces.bin");
    
    u32 bytes = 0;
    Province *data = (Province*)LoadFileData(buffer, &bytes);
    
    u32 total = bytes / sizeof(Province);
    
    for(int i = 0; i < total; i++) {
        AddToProvinceList(map->provinces, LoadProvinceMember(&data[i]));
    }
    
    DB_Errorlog("(S): Loaded province data from file\n");
}