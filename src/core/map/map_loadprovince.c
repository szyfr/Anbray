///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/02/16   //
//   @Edited:  22/03/17   //
///=--------------------=///



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