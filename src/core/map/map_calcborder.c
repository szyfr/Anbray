///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/03/05   //
//   @Edited:  22/03/18   //
///=--------------------=///



// 
//     Uses:
//   - Map
void CalculateBorder(void) {
    // Init variables
    int pixelCount = map->provincesImg.height * map->provincesImg.width;
    int count = 0;
    Color *colors = LoadImagePalette(map->provincesImg, 10000, &count);
    test = (IVector3*)calloc(10000,sizeof(IVector3));
    u32 counter = 0;
    
    char buff[50] = "data/maps/";
    strcat(buff,localization->mapLocalization[0]);
    strcat(buff,"/map/heightmap.png");
    Image heightmap = LoadImage(buff);
    
    u32 y = 1;
    
    // Iterate through each pixel,
    // saving the locations of same color bordering 2 or more of different color pixels
    for(int i = 0; i < pixelCount; i++) {
        Color pixel = GetImageColor(map->provincesImg,
                                    i%map->provincesImg.height,
                                    i/map->provincesImg.height);
        if(CompareColor(pixel, colors[0])) {
            if(CheckPixel(map->provincesImg, colors[0], i%map->provincesImg.height, i/map->provincesImg.height)) {
                test[counter] = (IVector3){
                    i%map->provincesImg.height,
                    y,
                    i/map->provincesImg.height};
                counter++;
            }
        }
    }
    printf("%i\n",counter);
    
    // Sort
    IVector3 *copy = (IVector3*)calloc(counter,sizeof(IVector3));
    copy[0] = test[0];
    
    u32 orgpos = 1;
    u32 newpos = 1;
    u32 endpos = counter-1;
    
    center = (Vector3){0.0f,0.0f,0.0f};
    
    for(int i = 0; i < counter; i++) {
        center.x += (float)test[i].x;
        center.z += (float)test[i].z;
    }
    center.x /= (float)counter;
    center.z /= (float)counter;
    
    
    test = SortPoints(test, counter);
    
    // Free
    UnloadImagePalette(colors);
    
    // Save variables
    testCount = counter;
}