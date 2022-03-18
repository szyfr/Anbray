///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/03/18   //
//   @Edited:  22/03/18   //
///=--------------------=///



//
//     Uses:
//   - NONE
int comp(const void *elem1, const void *elem2) {
    
    IVector3 *ele1 = (IVector3*)elem1;
    IVector3 *ele2 = (IVector3*)elem2;
    
    double calc1 = -1 * atan2((double)ele1->z - center.z, (double)ele1->x - center.x);
    double calc2 = -1 * atan2((double)ele2->z - center.z, (double)ele2->x - center.x);
    
    if(calc1 < calc2) return 1;
    else              return -1;
}

// Sorts the points of a province border
//     Uses:
//   - NONE
IVector3 *SortPoints(IVector3 *array, u32 size) {
    
    IVector3 *copy = (IVector3*)realloc(array, size * sizeof(IVector3));
    
    for(int i = 0; i < size; i++) {
        center.x += (float)test[i].x;
        center.z += (float)test[i].z;
    }
    center.x /= (float)size;
    center.z /= (float)size;
    
    qsort(copy, size, sizeof(IVector3), comp);
    
    return copy;
    
}