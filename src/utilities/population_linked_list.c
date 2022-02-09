///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/07    //
///=-------------------=///



/// Member Functions

//  Create population member
//     Uses:
//   - NONE
PopulationMember *CreatePopulationMember(void) {
    return (PopulationMember*)calloc(1, sizeof(PopulationMember));
}

//  Print population info
//     Uses:
//   - 
void ReadPopulationMembers(PopulationList *list) {
    // Test list
    if(list == 0) {
        DB_Errorlog("(F): Attempted to print from an null pointer.\n");
        return;
    }
    if(list->first == 0) {
        DB_Errorlog("(F): Attempted to print from an empty population list.\n");
        return;
    }
    
    // Initialize buffer
    char buffer[100] = {0};
    
    // Iterate through each member and print info
    sprintf(buffer, "\n---\nTotal count: %i\n---\n", list->count);
    DB_Errorlog(buffer);
    
    
    PopulationMember *mem = list->first;
    for(int i = 0; i < list->count; i++) {
        sprintf(buffer, "MEMBER: %i:%p\nPopulation:\t%i\nRace:\t\t%i\nCulture:\t%i\nReligion:\t%i\n",
                i, mem, mem->population, mem->race, mem->culture, mem->religion);
        // TODO: Change to show words instead of numbers
        mem = mem->next;
        
        DB_Errorlog(buffer);
    }
    DB_Errorlog("---\n\n");
}


/// List Functions

//  Creates population list
//     Uses:
//   - NONE
PopulationList *CreatePopulationList(void) {
    return (PopulationList*)calloc(1, sizeof(PopulationList));
}

//  Adds to population list
//     Uses:
//   - NONE
bool AddToPopulationList(PopulationList *provList, PopulationMember *mem) {
    // Input testing
    if(provList == 0 || mem == 0) return false;
    
    // Check if list is empty
    if(provList->first == 0) {
        provList->first = mem;
        provList->count++;
        return true;
    }
    
    // Iterate through members
    PopulationMember *currentMember = provList->first;
    for(int i = 0; i < provList->count; i++) {
        if(currentMember->race     == mem->race    &&
           currentMember->culture  == mem->culture &&
           currentMember->religion == mem->religion) {
            currentMember->population += mem->population;
            return true;
        }
        if(currentMember->next != 0) currentMember = currentMember->next;
    }
    // Append onto end
    currentMember->next = mem;
    provList->count++;
    
    return true;
}

//  Remove from population list
//     Uses:
//   - NONE
bool RemoveFromPopulationList(PopulationList *list, PopulationMember *mem) {
    // Input testing
    if(list == 0 || mem == 0) return false;
    if(list->first == 0)      return false;
    
    PopulationMember *last = 0;
    PopulationMember *current = list->first;
    for(int i = 0; i < list->count; i++) {
        if(current == mem) {
            // If it's the first member of the list
            if(last == 0) {
                // If it's the only member
                if(current->next == 0) {
                    free(current);
                    list->first = 0;
                    list->count--;
                    return true;
                }
                
                // If it's not the only member
                list->first = current->next;
                free(current);
                list->count--;
                return true;
            }
            
            // If it's not the first
            // And it's last
            if(current->next == 0) {
                free(current);
                last->next = 0;
                list->count--;
                return true;
            }
            
            // if it's not last
            last->next = current->next;
            free(current);
            list->count--;
            return true;
        }
        last    = current;
        current = current->next;
    }
    
    return false;
}

//  Delete population list
//     Uses:
//   - NONE
bool DeletePopulationList(PopulationList *list) {
    // Input testing
    if(list == 0) return false;
    
    // Remove each member
    while(list->first != 0) {
        RemoveFromPopulationList(list, list->first);
    }
    
    free(list);
    
    return true;
}