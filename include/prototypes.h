///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/01/26   //
//   @Edited:  22/03/17   //
///=--------------------=///



/// Prototypes
// Debug
void DB_Errorlog(char *message);
void DB_InitializeErrorlog(void);
void DB_SaveErrorlog(void);
void DB_CrashError(char *message);

// Localization
char *GetRawCoreLocalization(u32 *rawRead);
char *GetRawMapLocalization(char *mapname, u32 *rawRead);

char *GrabMapName(char *file);

void LoadLocalization(char *mapname);
void FreeLocalization(bool core);

// Options
void CommitOptionsData(void);
void InitializeOptions(void);

// Lists
// Population
PopulationList   *CreatePopulationList(void);
PopulationMember *CreatePopulationMember(void);
void ReadPopulationMembers(PopulationList *list);
bool AddToPopulationList(PopulationList *provList, PopulationMember *mem);
bool RemoveFromPopulationList(PopulationList *list, PopulationMember *mem);
bool DeletePopulationList(PopulationList *list);
// Province
ProvinceList   *CreateProvinceList(void);
ProvinceMember *CreateProvinceMember(void);
ProvinceMember *LoadProvinceMember(Province *data);
Province       *GrabProvinceMember(ProvinceList *list, u32 index);
void ReadProvinceMembers(ProvinceList *list);
bool AddToProvinceList(ProvinceList *provList, ProvinceMember *mem);
bool RemoveFromProvinceList(ProvinceList *list, ProvinceMember *mem);
bool DeleteProvinceList(ProvinceList *list);
// Province Modifier
ProvinceModifierList   *CreateProvinceModifierList(void);
ProvinceModifierMember *CreateProvinceModifierMember(void);
void ReadProvinceModifierMembers(ProvinceModifierList *list);
bool AddToProvinceModifierList(ProvinceModifierList *provList, ProvinceModifierMember *mem);
bool RemoveFromProvinceModifierList(ProvinceModifierList *list, ProvinceModifierMember *mem);
bool DeleteProvinceModifierList(ProvinceModifierList *list);

// Exit
void QuitGame(void);

// Player
void InitializePlayer(void);
void PlayerControls(void);

// Map
void CropImageToChunk(Image image, u32 posX, u32 posY, Chunk *chunk);
void CalculateBorder(void);
bool CheckPixel(Image provinceMap, Color color, int x, int y);
IVector3 *SortPoints(IVector3 *array, u32 size);

void LoadMapData(void);
void FreeMap(void);

void DrawSingleChunk(u32 chunk, float xOffset);
void DrawChunks(bool lessThan, float range, float xOffset);
void DrawMap(void);

Color U32ToColor(u32 input);
u32   ColorToU32(Color input);

// GUI
void DrawMainMenu(void);

void DrawOptionsMenu(void);

void DrawPauseMenu(void);