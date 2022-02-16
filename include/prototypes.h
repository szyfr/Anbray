///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/26    //
///=-------------------=///



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
// TODO: off-stream create prototypes

// Exit
void QuitGame(void);

// Player
void InitializePlayer(void);
void PlayerControls(void);

// Map
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