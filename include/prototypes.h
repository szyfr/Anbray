///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/26    //
///=-------------------=///



/// Prototypes
// Debug
void DB_Errorlog(Gamestate *gamestate, char *message);
void DB_InitializeErrorlog(Gamestate *gamestate);
void DB_SaveErrorlog(Gamestate *gamestate);
void DB_CrashError(Gamestate *gamestate);

// Localization
char *GetRawCoreLocalization(Gamestate *gamestate, u32 *rawRead);
char *GetRawMapLocalization(Gamestate *gamestate, char *mapname, u32 *rawRead);

char *GrabMapName(char *file);

void LoadLocalization(Gamestate *gamestate, char *mapname);
void FreeLocalization(Gamestate *gamestate, bool core);

// Options
void CommitOptionsData(Gamestate *gamestate);
void InitOptions(Gamestate *gamestate);

// Lists
/*
PopulationList *CreatePopulationList();
void AddToPopulationList(PopulationList *popList, PopulationMember *mem);
void AddNewToPopulationList(PopulationList *popList, u32 number, u8 race, u8 culture);
void RemoveFromPopulationList(PopulationList *popList, PopulationMember *mem);
void DeletePopulationList(PopulationList *popList);
void SwitchPopulationList(PopulationList *destPopList, PopulationList *srcPopList, PopulationMember *mem);

ProvinceList *CreateProvinceList();
void AddToProvinceList(ProvinceList *provList, ProvinceMember *mem);
void RemoveFromProvinceList(ProvinceList *provList, ProvinceMember *mem);
void DeleteProvinceList(ProvinceList *provList);
void SwitchProvinceList(ProvinceList *destProvList, ProvinceList *srcProvList, ProvinceMember *mem);

ProvinceModifierList *CreateProvinceModifierList();
void AddToProvinceModifierList(ProvinceModifierList *provModList, ProvinceModifierMember *mem);
void RemoveFromProvinceModifierList(ProvinceModifierList *provModList, ProvinceModifierMember *mem);
void DeleteProvinceModifierList(ProvinceModifierList *provModList);
void SwitchProvinceModifierList(ProvinceModifierList *destProvModList, ProvinceModifierList *srcProvModList, ProvinceModifierMember *mem);
//*/

// Exit
void QuitGame(Gamestate *gamestate);

// Player
void InitializePlayer(Gamestate *gamestate);
void PlayerControls(Gamestate *gamestate);

// Map
void LoadMapData(Gamestate *gamestate);
void FreeMap(Gamestate *gamestate);

void DrawSingleChunk(Gamestate *gamestate, u32 chunk, float xOffset);
void DrawChunks(Gamestate *gamestate, bool lessThan, float range, float xOffset);
void DrawMap(Gamestate *gamestate);

// GUI
void DrawMainMenu(Gamestate *gamestate);

void DrawOptionsMenu(Gamestate *gamestate);

void DrawPauseMenu(Gamestate *gamestate);