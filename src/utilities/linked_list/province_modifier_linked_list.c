///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/07    //
///=-------------------=///



/// Member Functions

//  Create province modifier member
//     Uses:
//   - NONE
ProvinceModifierMember *CreateProvinceModifierMember(void) {
    return (ProvinceModifierMember*)calloc(1, sizeof(ProvinceModifierMember));
}

//  Print province modifier info
//     Uses:
//   - NONE
void ReadProvinceModifierMembers(ProvinceModifierList *list) {
    // Test list
    if(list == 0) {
        DB_Errorlog("(F): Attempted to print from an null pointer.\n");
        return;
    }
    if(list->first == 0) {
        DB_Errorlog("(F): Attempted to print from an empty province modifier list.\n");
        return;
    }
    
    // Initialize buffer
    char buffer[100] = {0};
    
    // Iterate through each member and print info
    sprintf(buffer, "\n---\nTotal count: %i\n---\n", list->count);
    DB_Errorlog(buffer);
    
    
    ProvinceModifierMember *mem = list->first;
    for(int i = 0; i < list->count; i++) {
        sprintf(buffer, "MEMBER: %i:%p\nID:\t\t%i\nDate ending:\t%i\n",
                i, mem, mem->provModID, mem->date);
        // TODO: Change to show words instead of numbers
        mem = mem->next;
        
        DB_Errorlog(buffer);
    }
    DB_Errorlog("---\n\n");
}


/// List Functions

//  Creates province modifier list
//     Uses:
//   - NONE
ProvinceModifierList *CreateProvinceModifierList(void) {
    return (ProvinceModifierList*)calloc(1, sizeof(ProvinceModifierList));
}

//  Adds to province modifier list
//     Uses:
//   - NONE
bool AddToProvinceModifierList(ProvinceModifierList *provList, ProvinceModifierMember *mem) {
    // Input testing
    if(provList == 0 || mem == 0) return false;
    
    // Check if list is empty
    if(provList->first == 0) {
        provList->first = mem;
        provList->count++;
        return true;
    }
    
    // Iterate through members
    ProvinceModifierMember *currentMember = provList->first;
    for(int i = 0; i < provList->count; i++) {
        if(currentMember->provModID == mem->provModID) {
            currentMember->date = mem->date;
            return true;
        }
        if(currentMember->next != 0) currentMember = currentMember->next;
    }
    // Append onto end
    currentMember->next = mem;
    provList->count++;
    
    return true;
}

//  Remove from province modifier list
//     Uses:
//   - NONE
bool RemoveFromProvinceModifierList(ProvinceModifierList *list, ProvinceModifierMember *mem) {
    // Input testing
    if(list == 0 || mem == 0) return false;
    if(list->first == 0)      return false;
    
    ProvinceModifierMember *last = 0;
    ProvinceModifierMember *current = list->first;
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

//  Delete province modifier list
//     Uses:
//   - NONE
bool DeleteProvinceModifierList(ProvinceModifierList *list) {
    // Input testing
    if(list == 0) return false;
    
    // Remove each member
    while(list->first != 0) {
        RemoveFromProvinceModifierList(list, list->first);
    }
    
    free(list);
    
    return true;
}