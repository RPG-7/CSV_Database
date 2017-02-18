//Pointers and global variables
int *IntRowTable[64];
float *FloatRowTable[64];
char *ShortStrRowTable[64];
char *LongStrRowTable[64];
char EntryTitle[64][256];
unsigned char RowNum=0,ColumnNum=0; 
unsigned char ColumnLUT[256];
unsigned short RowIndex[256];
//menu.c
int mainmenu();
int file_menu();
int mod_menu();
int calc_menu();
int sort_menu();
int query_menu();
int output_menu();
char prop_menu();
char db_err(char filename[]);
//funcs.c
void FlushCharArr(char Arr[],int Length);
void PrintIndex();
void PrintColumn(char column);
void PrintAll();
void BSort(char sign,char Row);
void AddCol();
void RemoveCol(char ColNum);

//CSV_db.c
short db_create(char filename[]);
int db_repair();
char db_DataFill(FILE *database);
char db_IndexGen(FILE *database);
short db_check(char filename[]);
//RAM_op.c
int MemIntArrIO(int *pMemBlk,unsigned short Wr_Addr,int data);
float MemFloatArrIO(float *pMemBlk,unsigned short Wr_Addr,float data);
char MemCharArrIO(char *pMemBlk,unsigned int Wr_TotalShift,char data);
void CreateLUT();

