int MemIntArrIO(int *pMemBlk,unsigned short Wr_Addr,int data)
{
	int *pWork;
	if(Wr_Addr>>15)
	{
		pWork=pMemBlk+(Wr_Addr-0x8000);
		*pWork=data;
	}	
	else
	{
		pWork=pMemBlk+Wr_Addr;
		return *pWork;
	} 
}
float MemFloatArrIO(float *pMemBlk,unsigned short Wr_Addr,float data)
{
	float *pWork;
	if(Wr_Addr>>15)
	{
		pWork=pMemBlk+(Wr_Addr-0x8000);
		*pWork=data;
	}	
	else
	{
		pWork=pMemBlk+Wr_Addr;
		return *pWork;
	} 
}
char MemCharArrIO(char *pMemBlk,unsigned int Wr_TotalShift,char data)
{
	char *pWork;
//	printf("\n %ld",pMemBlk);
	if(Wr_TotalShift>>31)
	{
		pWork=pMemBlk+(Wr_TotalShift-0x80000000);
//		printf("\n %ld",pWork);
		*pWork=data;
	}	
	else
	{
		pWork=pMemBlk+Wr_TotalShift;
		return *pWork;
	} 
}
void CreateLUT()
{
	char count;
	for (count=0;count<ColumnNum;count++)
	ColumnLUT[count]=count;
}

