//CSV Database
//Something Stupidly Simple.
//Newbie:Hong,XiaoYu @ ChengDu College of UESTC
//About this file: Generic Database functions
void FlushCharArr(char Arr[],int Length)
{
	int i;
	for(i=0; i<Length; i++ )Arr[i]=0;
}
void PrintIndex()
{
	char x,y;
	for(x=0; x<RowNum; x++)
	{
		for (y=0; y<64; y++)
			if(EntryTitle[y][x]!=0)
				printf("%c",EntryTitle[y][x]);
			else break;
		printf("\t");
	}
	printf("\n");
}
void PrintColumn(char column)
{
	char Prop,MemShift,count,countX,temp;
	for (count=0; count<RowNum; count++)
	{
		Prop=RowIndex[count]>>14;
		MemShift=(char)RowIndex[count];
		countX=0;
		temp=1;
		switch (Prop)
		{
			case 0:
			{
				printf("%d\t",MemIntArrIO(IntRowTable[MemShift],column,0));
				break;
			}
			case 1:
			{
				printf("%f\t",MemFloatArrIO(FloatRowTable[MemShift],column,0));
				break;
			}
			case 2:
			{
				while(countX<64&&temp!=0)
				{
					temp=MemCharArrIO(ShortStrRowTable[MemShift],column*64+countX,0);
					printf("%c",temp);
					countX++;
				}
				printf("\t");
				break;
			}
			case 3:
			{
				while(countX<512&&temp!=0)
				{
					temp=MemCharArrIO(LongStrRowTable[MemShift],column*512+countX,0);
					printf("%c",temp);
					countX++;
				}
				printf("\t");
				break;
			}
		}
	}

}
void PrintAll()
{
	char count,column;
	PrintIndex();
	for (count=0; count<ColumnNum; count++)
	{
		PrintColumn(ColumnLUT[count]);
		printf("\n");
	}
	printf("\n");
}
void BSort(char sign,char Row)//Sign for choose ascend or descend
{
	char countA,countB,Swap,Prop,Shift;
	int datA,datB;
	Prop=RowIndex[Row]>>14;
	Shift=(char)RowIndex[Row];
	for (countA=ColumnNum; countA>=0; countA--)
	{
		for (countB=0; countB<countA-1; countB++)
		{
			switch (Prop)
			{
				case 0:
				{
					datA=MemIntArrIO(IntRowTable[Shift],ColumnLUT[countB],0);
					datB=MemIntArrIO(IntRowTable[Shift],ColumnLUT[countB+1],0);
					break;
				}
				case 1:
				{
					datA=(int)MemFloatArrIO(FloatRowTable[Shift],ColumnLUT[countB],0);
					datB=(int)MemFloatArrIO(FloatRowTable[Shift],ColumnLUT[countB],0);
					break;
				}
				case 2:
				{
					for (Swap=0; Swap<5; Swap++)
					{
						datA=(datA<<8)+MemCharArrIO(ShortStrRowTable[Shift],ColumnLUT[countB]*64+Swap,0);
						datB=(datB<<8)+MemCharArrIO(ShortStrRowTable[Shift],ColumnLUT[countB]*64+Swap,0);
					}
					break;
				}
				case 3:
				{
					for (Swap=0; Swap<5; Swap++)
					{
						datA=(datA<<8)+MemCharArrIO(LongStrRowTable[Shift],ColumnLUT[countB]*512,0);
						datB=(datB<<8)+MemCharArrIO(LongStrRowTable[Shift],ColumnLUT[countB]*512,0);
					}

					break;
				}
			}
			if(datA>datB&&sign==0)
			{
				Swap=ColumnLUT[countB];
				ColumnLUT[countB]=ColumnLUT[countB+1];
				ColumnLUT[countB+1]=Swap;
			}
			else if (datA<datB&&sign!=0)
			{
				Swap=ColumnLUT[countB];
				ColumnLUT[countB]=ColumnLUT[countB+1];
				ColumnLUT[countB+1]=Swap;
			}
		}
	}
}
void AddCol()
{
	char countX,Prop,Shift;
	int temp;
	float ftemp;
	short countY;
	ColumnNum++;
	ColumnLUT[ColumnNum-1]=ColumnNum-1;
	printf("%d",ColumnNum);
	getchar();
	for(countX=0; countX<RowNum; countX++)
	{
		Prop=RowIndex[countX]>>14;
		Shift=(char)RowIndex[countX];
		countY=0;
		printf("Please Insert Data#%d\n",countX+1);
		switch (Prop)
		{
			case 0:
			{
				scanf("%d",&temp);
				MemIntArrIO(IntRowTable[Shift],0x8000+ColumnNum-1,temp);
				getchar();
				//printf("Row:%d,Column:%d",Shift,ColumnNum);
				break;
			}

			case 1:
			{
				scanf("%f",&ftemp);
				MemFloatArrIO(FloatRowTable[Shift],0x8000+ColumnNum-1,ftemp);
				getchar();
				break;
			}

			case 2:
			{
				do
				{
					temp=getchar();
					if(temp!=10)
						MemCharArrIO(ShortStrRowTable[Shift],0x80000000+((ColumnNum-1)*64)+countY,(char)temp);
					countY++;
				}
				while(countY<64&&temp!=10);
				break;
			}

			case 3:
			{
				do
				{
					temp=getchar();
					if(temp!=10)
						MemCharArrIO(LongStrRowTable[Shift],0x80000000+((ColumnNum-1)*512)+countY,(char)temp);
					countY++;
				}
				while(countY<512&&temp!=10);
				break;
			}

		}
	}

}
void RemoveCol(unsigned char ColNum)
{
	char count,Prop,Shift,countX,temp;
	for (count=0; count<RowNum; count++)
	{
		Prop=RowIndex[count]>>14;
		Shift=(char)RowIndex[count];
		switch (Prop)
		{
			case 0:
			{
				MemIntArrIO(IntRowTable[Shift],0x8000+ColNum-1,MemIntArrIO(IntRowTable[Shift],ColumnNum-1,0));
				break;
			}
			case 1:
			{
				MemFloatArrIO(FloatRowTable[Shift],0x8000+ColNum-1,MemFloatArrIO(FloatRowTable[Shift],ColumnNum-1,0));
				break;
			}
			case 2:
			{
				for(countX=0; countX<64; countX++)
				{
					temp=MemCharArrIO(ShortStrRowTable[Shift],(ColumnNum-1)*64+countX,0);
					MemCharArrIO(ShortStrRowTable[Shift],0x80000000+(ColNum-1)*64+countX,temp);
				}

				break;
			}
			case 3:
			{
				for(countX=0; countX<64; countX++)
				{
					temp=MemCharArrIO(LongStrRowTable[Shift],(ColumnNum-1)*512+countX,0);
					MemCharArrIO(LongStrRowTable[Shift],0x80000000+(ColNum-1)*512+countX,temp);
				}
				break;
			}
		}
	}
	//for (count=ColNum-1; count<ColumnNum; count++)
	//	ColumnLUT[count]=ColumnLUT[count+1];

	ColumnNum--;
}
void ModCol(unsigned char ColNum)
{
	char row,Prop,Shift;
	int temp;
	short countY;
	float ftemp;
	PrintColumn(ColNum-1);
	printf("Which row?\n");
	scanf("%d",&row);
	Prop=RowIndex[row-1]>>14;
	Shift=(char)RowIndex[row-1];
	printf("Please Enter Data.\n");
	getchar();
	switch (Prop)
	{
		case 0:
		{
			scanf("%d",&temp);
			MemIntArrIO(IntRowTable[Shift],0x8000+ColNum-1,temp);
			getchar();
			//printf("Row:%d,Column:%d",Shift,ColumnNum);
			break;
		}

		case 1:
		{
			scanf("%f",&ftemp);
			MemFloatArrIO(FloatRowTable[Shift],0x8000+ColNum-1,ftemp);
			getchar();
			break;
		}

		case 2:
		{
			do
			{
				temp=getchar();
				if(temp!=10)
					MemCharArrIO(ShortStrRowTable[Shift],0x80000000+((ColNum-1)*64)+countY,(char)temp);
				countY++;
			}
			while(countY<64&&temp!=10);
			break;
		}

		case 3:
		{
			do
			{
				temp=getchar();
				if(temp!=10)
					MemCharArrIO(LongStrRowTable[Shift],0x80000000+((ColNum-1)*512)+countY,(char)temp);
				countY++;
			}
			while(countY<512&&temp!=10);
			break;
		}

	}
}

void AddRow()
{
	char temp,countY;
	printf("Please enter the title of the new row");
	getchar();
	countY=0;
	RowNum++;
	do
	{
		temp=getchar();
		if(temp!=10)
			EntryTitle[countY][RowNum-1]=temp;
		countY++;
	}
	while(countY<64&&temp!=10);
	Select:
	switch(prop_menu())
	{
		case 1:
		{
			temp=pAlloc(0);
			RowIndex[RowNum-1]=temp;
			IntRowTable[temp]=malloc(256*sizeof(int));
			break;
		}
		case 2:
		{
			temp=pAlloc(1);
			RowIndex[RowNum-1]=0x4000+temp;
			FloatRowTable[temp]=malloc(256*sizeof(float));
			break;
		}
		case 3:
		{
			temp=pAlloc(2);
			RowIndex[RowNum-1]=0x8000+temp;
			ShortStrRowTable[temp]=malloc(256*64*sizeof(char));
			break;
		}
		case 4:
		{
			temp=pAlloc(3);
			RowIndex[RowNum-1]=0x4000+temp;
			LongStrRowTable[temp]=malloc(256*512*sizeof(char));
			break;
		}
		
	}

}
void RemoveRow(unsigned char Row)
{

}
void RenameRow(unsigned char Row)
{

}
