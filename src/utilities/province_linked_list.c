///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/07    //
///=-------------------=///



/// Member Functions

//  Create province member
//     Uses:
//   - NONE
ProvinceMember *CreateProvinceMember(void) {
    ProvinceMember *mem = (ProvinceMember*)calloc(1, sizeof(ProvinceMember));
    mem->province      = (Province*)calloc(1, sizeof(Province));
    
    return mem;
}

//  Print province info
//     Uses:
//   - NONE
// NOTE: gamestate
void ReadProvinceMembers(Gamestate *gamestate, ProvinceList *list) {
    // Test list
    if(list == 0) {
        DB_Errorlog(gamestate, "(F): Attempted to print from an null pointer.\n");
        return;
    }
    if(list->first == 0) {
        DB_Errorlog(gamestate, "(F): Attempted to print from an empty province list.\n");
        return;
    }
    
    // Initialize buffer
    char buffer[100] = {0};
    
    // Iterate through each member and print info
    sprintf(buffer, "\n---\nTotal count: %i\n---\n", list->count);
    DB_Errorlog(gamestate, buffer);
    
    
    ProvinceMember *mem = list->first;
    for(int i = 0; i < list->count; i++) {
        sprintf(buffer, "MEMBER: %i:%p\nID:\t\t%i\n\nTerrain:\t%i\nType:\t\t%i\nInfrastruture:\t%i/%i\n",
                i, mem, mem->province->localID, mem->province->terrain, mem->province->type, mem->province->currentInfrastruture, mem->province->maximumInfrastruture);
        // TODO: Change to show words instead of numbers
        mem = mem->next;
        
        DB_Errorlog(gamestate, buffer);
    }
    DB_Errorlog(gamestate, "---\n\n");
}


/// List Functions

//  Creates province list
//     Uses:
//   - NONE
ProvinceList *CreateProvinceList(void) {
    return (ProvinceList*)calloc(1, sizeof(ProvinceList));
}

//  Adds to province list
//     Uses:
//   - NONE
bool AddToProvinceList(ProvinceList *provList, ProvinceMember *mem) {
    // Input testing
    if(provList == 0 || mem == 0) return false;
    
    // Check if list is empty
    if(provList->first == 0) {
        provList->first = mem;
        provList->count++;
        return true;
    }
    
    // Iterate through members
    ProvinceMember *currentMember = provList->first;
    for(int i = 1; i < provList->count; i++) {
        currentMember = currentMember->next;
    }
    // Append onto end
    currentMember->next = mem;
    provList->count++;
    
    return true;
}

//  Remove from province list
//     Uses:
//   - NONE
bool RemoveFromProvinceList(ProvinceList *list, ProvinceMember *mem) {
    // Input testing
    if(list == 0 || mem == 0) return false;
    if(list->first == 0)      return false;
    
    ProvinceMember *last = 0;
    ProvinceMember *current = list->first;
    for(int i = 0; i < list->count; i++) {
        if(current == mem) {
            // If it's the first member of the list
            if(last == 0) {
                // If it's the only member
                if(current->next == 0) {
                    free(current->province);
                    free(current);
                    list->first = 0;
                    list->count--;
                    return true;
                }
                
                // If it's not the only member
                list->first = current->next;
                free(current->province);
                free(current);
                list->count--;
                return true;
            }
            
            // If it's not the first
            // And it's last
            if(current->next == 0) {
                free(current->province);
                free(current);
                last->next = 0;
                list->count--;
                return true;
            }
            
            // if it's not last
            last->next = current->next;
            free(current->province);
            free(current);
            list->count--;
            return true;
        }
        last    = current;
        current = current->next;
    }
    
    return false;
}

//  Delete province list
//     Uses:
//   - NONE
bool DeleteProvinceList(ProvinceList *list) {
    // Input testing
    if(list == 0) return false;
    
    // Remove each member
    while(list->first != 0) {
        RemoveFromProvinceList(list, list->first);
    }
    
    free(list);
    
    return true;
}