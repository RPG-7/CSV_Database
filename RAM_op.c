//CSV Database
//Something Stupidly Simple.
//Newbie:Hong,XiaoYu @ ChengDu College of UESTC
//These are some RAM operations for this database.
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
char pAlloc(char Prop)
{
	char count,pcount=0,pPrev=0,pNow=0;

	switch (Prop)
	{
		case 1:
		{
			for(count=0; count<RowNum-2; count++)
				if(RowIndex[count]>>14==0)
				{
					pPrev=pNow;
					pNow=(char)RowIndex[count];
					if (pPrev!=pNow+1||pPrev==pNow)
						return pNow+1;
				}
			break;
		}
		case 2:
		{
			for(count=0; count<RowNum-2; count++)
				if(RowIndex[count]>>14==1)
				{
					pPrev=pNow;
					pNow=(char)RowIndex[count];
					if (pPrev!=pNow+1||pPrev==pNow)
						return pNow+1;
				}
			break;
		}
		case 3:
		{
			for(count=0; count<RowNum-2; count++)
				if(RowIndex[count]>>14==2)
				{
					pPrev=pNow;
					pNow=(char)RowIndex[count];
					if (pPrev!=pNow+1||pPrev==pNow)
						return pNow+1;
				}
			break;
		}
		case 4:
		{
			for(count=0; count<RowNum-2; count++)
				if(RowIndex[count]>>14==3)
				{
					pPrev=pNow;
					pNow=(char)RowIndex[count];
					if (pPrev!=pNow+1||pPrev==pNow)
						return pNow+1;
				}
			break;
		}

	}
}
void CreateLUT()
{
	char count;
	for (count=0;count<ColumnNum;count++)
	ColumnLUT[count]=count;
}

