///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/07    //
///=-------------------=///



/// Functions
// Create list
PopulationList *CreatePopulationList() {
    PopulationList *list = (PopulationList*)calloc(1, sizeof(PopulationList));
    return list;
}

// Add member to list
void AddToPopulationList(PopulationList *popList, PopulationMember *mem) {
    // Find last member
    PopulationMember *member = popList->first;
    while(member != 0) member = (PopulationMember*)member->next;
    
    // If there are no members
    if(member == 0) popList->first = (void*)mem;
    else            member->next   = (void*)mem;
    
    popList->count++;
}

// Add new member to list
void AddNewToPopulationList(PopulationList *popList,
                            u32 number,
                            u8 race,
                            u8 culture,
                            u8 religion) {
    // Allocate space for new member
    PopulationMember *member = (PopulationMember*)calloc(1, sizeof(PopulationMember));
    
    // Set data
    member->population = number;
    member->race       = race;
    member->culture    = culture;
    member->religion   = religion;
    
    // Add to list
    AddToPopulationList(popList, member);
}

//
void RemoveFromPopulationList(PopulationList *popList, PopulationMember *mem);

// Delete list and it's members
void DeletePopulationList(PopulationList *popList) {
    // Check if list has ANY members
    if(popList->first == 0) {
        free(popList);
        popList = 0;
        return;
    }
    
    // Itterate through list and free each previous
    PopulationMember *current = popList->first;
    for(int i = 0; i < popList->count; i++) {
        PopulationMember *temp = current;
        current = current->next;
        free(temp);
    }
    
    free(popList);
    popList = 0;
}
void SwitchPopulationList(PopulationList *destPopList, PopulationList *srcPopList, PopulationMember *mem);