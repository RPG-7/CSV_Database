//CSV Database
//Something Stupidly Simple.Code quite a lot of bug.
//Newbie:Hong,XiaoYu @ ChengDu College of UESTC
//Head Format:Entries count(ACSII Number),Entry Name,Entry Data Format(Integer,Float,Short String,Long String

short db_create(char filename[])//Pass
{
	FILE *dbfile;
	char DataBuff[100]= {0};
	char Tabcount,countX,countY,temp;
	dbfile=fopen(filename,"at");
	if(dbfile==NULL)
	{
		printf("File ERROR!Program Terminated");
		exit(-1);
	}

	printf("How many rows are there?\n");
	scanf("%d",&Tabcount);
	itoa(Tabcount,&DataBuff[0],10);
	countY=0;
	do
	{
		temp=DataBuff[countY];
		printf("%c",temp);//dbg
		fputc(temp,dbfile);
		countY++;
	}
	while(temp!=0&&countY<20);
	fputc(',',dbfile);
	for(countY=1; countY<=Tabcount; countY++)
	{
		printf("Please Insert Name of row #%d\n",countY);
		getchar();
		while(countX<255)
		{
			temp=getchar();
			if(temp!='\n')
			{
				fputc(temp,dbfile);
			}
			else break;
			countX++;
		}
		fputc(',',dbfile);
		printf("Please choose Property of the row #%d  \n",countY);
		fputc(prop_menu()+'0'-1,dbfile);
		fputc(',',dbfile);
		FlushCharArr(DataBuff,100);
	}
	fputc(0x0d,dbfile);
	fputc(0x0a,dbfile);
	fclose(dbfile);
	printf("Index generated successfully!\n");
	return 0;


}
int db_repair()//Suspend
{
	printf("Nothing here!");
}
char db_DataFill(FILE *database)//So fucking buggy......Now pass.
{
	char CtrlSig;
	char keybuff[64]= {0},countX=0,countY=0,temp,Prop,MemShift                                                                                                                                                                                                   ;
	FlushCharArr(keybuff,64);
	printf("Start to Fill Data into RAM.....\n");
	CtrlSig=0;
	countX=0;
	countY=0;//Load Data into RAM Blocks
	while(CtrlSig>=0)
	{
		temp=fgetc(database);
		Prop=RowIndex[CtrlSig]>>14;
		MemShift=(char)RowIndex[CtrlSig];
		//printf ("%c",temp);
		if(temp==',')
		{
			keybuff[countX]=0; 
			//printf("\nProp:%d \tEntry:(%d,%d) \n",Prop,CtrlSig,MemShift);
			switch (Prop)
			{
				case 0:
				{
					MemIntArrIO(IntRowTable[MemShift],0x8000+countY,atoi(&keybuff[0]));
					break;
				}
				case 1:
				{
					MemFloatArrIO(FloatRowTable[MemShift],0x8000+countY,(float)atof(&keybuff[0]));
					break;
				}
				case 2:
				{
					MemCharArrIO(ShortStrRowTable[MemShift],0x80000000+countY*64+countX,0);//write end
					break;
				}
				case 3:
				{
					MemCharArrIO(LongStrRowTable[MemShift],0x80000000+countY*512+countX,0);//write end
					break;
				}
			}
			countX=0;
			FlushCharArr(keybuff,64);
			if (CtrlSig==RowNum-1)
			{
				CtrlSig=0;
				countY++;
				ColumnNum++;
			}
			else CtrlSig++;

		}
		else if(temp==0x0d||temp==0x0a)
		{
			continue;
		}
		else if (temp!=EOF)
		{
			switch (Prop)
			{
				case 0:
					keybuff [countX]=temp;
					break;
				case 1:
					keybuff [countX]=temp;
					break;
				case 2:
					MemCharArrIO(ShortStrRowTable[MemShift],0x80000000+(countY*64)+countX,temp);
					break;
				case 3:
					MemCharArrIO(LongStrRowTable[MemShift],0x80000000+(countY*512)+countX,temp);
					break;
			}
			countX++;
		}
		else
		{
			printf("End of file!Read Complete!\n");
			fclose(database);
			CtrlSig=-1;
			break;
		}
	}
}
char db_IndexGen(FILE *database)//Pass
{
	char CtrlSig,data;
	char keybuff[64]= {0},countX=0,countY=0,temp;
	char countI=0,countF=0,countSS=0,countLS=0;
	rewind(database);
	CtrlSig=1;
	while(CtrlSig>0)
	{
		data=fgetc(database);
		//	printf("%c",data);//Dbg
		if(data>='0'&&data<='9'&&CtrlSig==1)
		{
			RowNum=RowNum*10+(data-'0');
			//	printf("%d",RowNum);
			CtrlSig=1;
		}
		else if (data==',')
		{
			switch(CtrlSig)
			{
				case 1:
				{
					CtrlSig++;
					countX=0;
					countY=0;
					break;
				}
				case 2:
					CtrlSig++;
					countX=0;
					break;
				case 3:
					CtrlSig--;
					countY++;
					break;
			}
		}
		else if(data==0x0d||data==0x0a)
		{
			printf("Index read successfully!\n");
			//printf("%d\n",ftell(database));
			db_DataFill(database);
			return 0;
		}
		else
		{
			switch(CtrlSig)
			{
				case 2:
				{
					EntryTitle[countX][countY]=data;
					countX++;
					break;
				}
				case 3:
				{
					temp=data-'0';
					switch(temp)// Allocate RAM for each column
					{
						case 0:
						{
							IntRowTable[countI]=(int*)malloc(sizeof(int)*256);
							RowIndex[countY]=(temp<<14)+countI;
							countI++;
							break;
						}
						case 1:
						{
							FloatRowTable[countF]=(float*)malloc(sizeof(float)*256);
							RowIndex[countY]=(temp<<14)+countF;
							countF++;
							break;
						}
						case 2:
						{
							ShortStrRowTable[countSS]=(char*)malloc(sizeof(char)*64*256);
							RowIndex[countY]=(temp<<14)+countSS;
							countSS++;
							break;
						}
						case 3:
						{
							LongStrRowTable[countLS]=(char*)malloc(sizeof(char)*512*256);
							RowIndex[countY]=(temp<<14)+countLS;
							countLS++;
							break;
						}
					}
				}
			}
		}
	}
}

short db_check(char filename[])//Pass
{
	FILE *database;
	int size,RowNum;
	char CtrlSig,data;
	char countX=0,countY=0;
	//char countI=0,countF=0,countSS=0,countLS=0;
	short temp;
	database=fopen(filename,"rt");
	if(database==NULL)
	{
		printf("Database Not Found! \n ");
		fclose(database);
		db_err(filename);
		return -1;
	}
	else
	{
		fseek( database, 0L, SEEK_END );
		size=ftell(database);
		if(size==0)
		{
			printf("Database Empty!");
			fclose(database);
			db_err(filename);
			return -1;
		}
		else
		{
			db_IndexGen(database);
		}
	}
}




