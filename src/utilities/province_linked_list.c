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
    mem->province       = (Province*)calloc(1, sizeof(Province));
    
    return mem;
}

//  Loads province member
//     Uses:
//   - NONE
// TODO: Create longer function that does this for every member in file
ProvinceMember *LoadProvinceMember(Province *data) {
    ProvinceMember *mem = CreateProvinceMember();
    
    mem->province->localizationID       = data->localizationID;
    mem->province->color                = data->color;
    mem->province->terrain              = data->terrain;
    mem->province->type                 = data->type;
    mem->province->maximumInfrastruture = data->maximumInfrastruture;
    mem->province->currentInfrastruture = data->currentInfrastruture;
    mem->province->buildings[0]         = data->buildings[0];
    mem->province->buildings[1]         = data->buildings[1];
    mem->province->buildings[2]         = data->buildings[2];
    mem->province->buildings[3]         = data->buildings[3];
    mem->province->buildings[4]         = data->buildings[4];
    mem->province->buildings[5]         = data->buildings[5];
    
    return mem;
}

//  Print province info
//     Uses:
//   - NONE
void ReadProvinceMembers(ProvinceList *list) {
    // Test list
    if(list == 0) {
        DB_Errorlog("(F): Attempted to print from an null pointer.\n");
        return;
    }
    if(list->first == 0) {
        DB_Errorlog("(F): Attempted to print from an empty province list.\n");
        return;
    }
    
    // Initialize buffer
    char buffer[100] = {0};
    
    // Iterate through each member and print info
    sprintf(buffer, "\n---\nTotal count: %i\n---\n", list->count);
    DB_Errorlog(buffer);
    
    
    ProvinceMember *mem = list->first;
    for(int i = 0; i < list->count; i++) {
        sprintf(buffer, "MEMBER: %i:%p\nID:\t\t%i\nCol:\t\t%i,%i,%i,%i\n\nTerrain:\t%i\nType:\t\t%i\nInfrastruture:\t%i/%i\n",
                i, mem, mem->province->localizationID,
                mem->province->color.r, mem->province->color.g,
                mem->province->color.b, mem->province->color.a,
                mem->province->terrain, mem->province->type, mem->province->currentInfrastruture, mem->province->maximumInfrastruture);
        // TODO: Change to show words instead of numbers
        mem = mem->next;
        
        DB_Errorlog(buffer);
    }
    DB_Errorlog("---\n\n");
}

//  Grabs the contents of member
//     Uses:
//   - NONE
Province *GrabProvinceMember(ProvinceList *list, u32 index) {
    Province *output;
    
    ProvinceMember *current = list->first;
    for(int i = 0; i < index; i++) {
        if(current->next == 0) {
            DB_Errorlog("(F): Index of member was too high.\n");
            return 0;
        }
        
        current = current->next;
    }
    
    return current->province;
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