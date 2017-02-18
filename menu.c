//CSV Database
//Something Stupidly Simple.
//Newbie:Hong,XiaoYu @ ChengDu College of UESTC
//No Need to say, Menus.
int mainmenu()
{
	char sel;
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("*           Main Menu               *\n");
	printf("* 1. File                           *\n");
	printf("* 2. Modify                         *\n");
	printf("* 3. Calculate                      *\n");
	printf("* 4. Sort                           *\n");
	printf("* 5. Query                          *\n");
	printf("* 6. Output                         *\n");
	printf("* 0. Exit                           *\n");
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("Please enter your choice:");
	scanf("%d",&sel);
	switch(sel)
	{
		case 1:
			file_menu();
			break;
		case 2:
			mod_menu();
			break;
		case 3:
			calc_menu();
			break;
		case 4:
			sort_menu();
			break;
		case 5:
			query_menu();
			break;
		case 6:
			output_menu();
			break;
		case 0:
			exit(0);
			break;

	}

}
int file_menu()
{
	char filename[64]= {0},countX=0,temp,sel;
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("*           File Menu               *\n");
	printf("* 1. Create a new database          *\n");
	printf("* 2. Open a CSV database            *\n");
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("Please enter your choice:");
	scanf("%d",&sel);
	getchar();
	printf("Please enter the filename of your database.\n");//get filename
	while(countX<64)
	{
		temp=getchar();
		if(temp!='\n')
		{
			filename[countX]=temp;
			countX++;
		}
		else
		{
			filename[countX]=0;
			break;
		}
	}
	switch(sel)
	{
		case 1:
		{
			db_create(filename);
			db_check(filename);
			break;
		}
		case 2:
			db_check(filename);
			CreateLUT();
			PrintAll();
			break;
	}
}
int mod_menu()
{
	char sel;
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("*           Modify Menu             *\n");
	printf("* 1. Append a column                *\n");
	printf("* 2. Append a row                   *\n");
	printf("* 3. Delete a column                *\n");
	printf("* 4. Delete a row                   *\n");
	printf("* 5. Modify a column                *\n");
	printf("* 6. Rename a row                   *\n");
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("Please enter your choice:");
	scanf("%d",&sel);
	switch(sel)
	{
		case 1:
			AddCol();
			break;
		case 2:
			AddRow();
			break;
		case 3:
		{
			PrintAll();
			printf("Which Column?");
			scanf("%d",&sel);
			RemoveCol(sel);
			break;
		}
		case 4:
		{
			PrintIndex();
			printf("Which Row?");
			scanf("%d",&sel);
			RemoveRow(sel);
			break;
		}
		case 5:
		{
			PrintAll();
			printf("Which Column?");
			scanf("%d",&sel);
			ModCol(sel);
			break;
		}
		case 6:
		{
			PrintIndex();
			printf("Which Row?");
			scanf("%d",&sel);
			RenameRow(sel);
			break;
		}
	}
}
int calc_menu()
{
	int sel;
	printf("* * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("*             Caculate Menu                 *\n");
	printf("* 1.Calculate Sum of chosen data            *\n");
	printf("* 2.Calculate Average of chosen data        *\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("Please enter your choice:");
	scanf("%d",&sel);
	return(sel);
}
int sort_menu()
{
	int sel,RowNum;
	printf("* * * * * * * * * * * * * * * * * *\n");
	printf("*             Sort Menu           *\n");
	printf("* 1. Sort in ascending order      *\n");
	printf("* 2. Sort in desecending order    *\n");
	printf("* 3. Flush current order          *\n");
	printf("* * * * * * * * * * * * * * * * * *\n");
	printf("Please enter your choice:");
	scanf("%d",&sel);
	getchar();
	PrintIndex();
	printf("Which row?");
	scanf("%d",&RowNum);
	switch(sel)
	{
		case 1:
			BSort(0,RowNum-1);
			break;
		case 2:
			BSort(1,RowNum-1);
			break;
		case 3:
			CreateLUT();
			break;
	}
	PrintAll();
}
int query_menu()
{
	int sel;
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("*           Query Menu              *\n");
	printf("* 1. Search by String               *\n");
	printf("* 2. Search by digit                *\n");
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("Please enter your choice:");
	scanf("%d",&sel);
	return(sel);
}

int output_menu()
{
	int sel;
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("*           Output Menu             *\n");
	printf("* 1. Print all records on screen    *\n");
	printf("* 2. Save changes                   *\n");
	printf("* 3. Save as another database       *\n");
	printf("* 4. Save as original CSV file      *\n");
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("Please enter your choice:");
	scanf("%d",&sel);
	switch (sel)
	{
		case 1:
		{
			PrintAll(0);
			break;
		}
		case 2:
		{

			break;
		}
	}
}
char prop_menu()
{
	int sel;
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("*     Property of This Row?         *\n");
	printf("* 1. Integer                        *\n");
	printf("* 2. Float                          *\n");
	printf("* 3. Short String                   *\n");
	printf("* 4. Long String                    *\n");
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("Please enter your choice:");
	scanf("%d",&sel);
	return(sel);
}
char db_err(char filename[])
{
	printf("(C)reate new/(A)bort/(R)epair/(E)xit?\n");
	switch(getchar())
	{
		case 'C':
			db_create(filename);
			break;
		case 'c':
			db_create(filename);
			break;
		case 'R':
			db_repair(filename);
			break;
		case 'r':
			db_repair(filename);
			break;
		case 'E':
			exit(0);
			break;
		case 'e':
			exit(0);
			break;
		default:
			return -1;
			break;
	}
}
