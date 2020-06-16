#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

void edit();
void nearby();
void search();
void read_data();
void view();
void testing_center();
void self_asses();
void end();
void login();
void g_check();
void c_menu();
void g_menu();
void system_switcher();
void open_screen();

char ans=0;
int ok,valid=0;

struct patient
{
	int age;
	char Gender;
	char First_Name[20];
	char Last_Name[20];
	char Contact_no[15];
	struct address
	{
	    char Address[50];
	    int pincode;
	}ad;
}p,temp_c;

void gotoxy(short x,short y)
{
    COORD pos ={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void edit()
{
    system("cls");
    printf("\t\t\t\t\t\t  COVID-19\n");
    printf("\t\t\t\t\t  ************************\n\n\n");
    char name[20];
	int found=0;
    FILE *ek, *ft;
	ft=fopen("temp_file2.dat","w+");
	ek=fopen("Record2.dat","r");
	printf("\n Enter name to delete: ");
	scanf("%s",name);
	name[0]=toupper(name[0]);
	while(fscanf(ek,"%s %s %c %s %i %s %i\n", p.First_Name, p.Last_Name,&p.Gender, p.Contact_no,
				 &p.age, p.ad.Address,&p.ad.pincode)!=EOF)
    {
        if (strcmp(p.First_Name,name)!=0)
        {
                fprintf(ft,"%s %s %c %s %i %s %i\n", p.First_Name, p.Last_Name,p.Gender, p.Contact_no,
				 p.age, p.ad.Address,p.ad.pincode);
        }
        else
        {
            found=1;
        }
    }
    if(found==0)
    {
        printf("Record not found\n");
        getch();
        g_menu();
    }
    else
    {
        fclose(ek);
		fclose(ft);
		remove("Record2.dat");
		rename("temp_file2.dat","Record2.dat");
		printf("Record removed ");
		getch();
		g_menu();
    }

}

void nearby()
{
    system("cls");
        printf("\t\t\t\t\t\t  COVID-19\n");
        printf("\t\t\t\t\t  ************************\n\n");
        int row=0,n;
        FILE *ek;
	    ek=fopen("Record2.dat","r");
        printf("No. of Covid patients in your area\n");
        printf("********************************\n");
        printf("Enter your area pincode\n");
        scanf("%i",&n);
        while(fscanf(ek,"%s %s %c %s %i %s %i\n", p.First_Name, p.Last_Name,&p.Gender, p.Contact_no,
				 &p.age, p.ad.Address,&p.ad.pincode)!=EOF)
        {
            if(p.ad.pincode==n)
            {
                row++;
            }
        }
        printf("%i",row);
        fclose(ek);
        getch();
        c_menu();
}

void search()
{
        system("cls");
        printf("\t\t\t\t\t\t  COVID-19\n");
        printf("\t\t\t\t\t  ************************\n\n");
        int row,n;
        FILE *ek;
	    ek=fopen("Record2.dat","r");
        printf("Covid patients list in that area\n");
        printf("********************************\n");
        printf("Enter the area pincode\n");
        scanf("%i",&n);
		gotoxy(1,8);
		printf("Full Name");
		gotoxy(20,8);
		printf("Gender");
		gotoxy(32,8);
		printf("Contact No.");
		gotoxy(49,8);
		printf("Age");
		gotoxy(55,8);
		printf("Address");
		gotoxy(94,8);
		printf("Pincode");
		gotoxy(101,8);
		row=10;
		while(fscanf(ek,"%s %s %c %s %i %s %i\n", p.First_Name, p.Last_Name,&p.Gender, p.Contact_no,
				 &p.age, p.ad.Address,&p.ad.pincode)!=EOF)
        {
            if(p.ad.pincode==n)
            {
            gotoxy(1,row);
			printf("%s %s",p.First_Name, p.Last_Name);
			gotoxy(20,row);
			printf("%c",p.Gender);
			gotoxy(32,row);
			printf("%s",p.Contact_no);
			gotoxy(49,row);
			printf("%i",p.age);
			gotoxy(55,row);
			printf("%s",p.ad.Address);
			gotoxy(94,row);
			printf("%i",p.ad.pincode);
			gotoxy(49,row);
			row++;
            }
        }
        fclose(ek);
        getch();
        g_menu();
}

void read_data()
{
    system("cls");
    printf("\t\t\t\t\t\t  COVID-19\n");
    printf("\t\t\t\t\t  ************************\n");
    printf("Enter the details\n");
    printf("*****************\n");
    FILE *ek;
    ek=fopen("Record2.dat","a");
    printf("First Name:\n");
	scanf("%s",p.First_Name);
	p.First_Name[0]=toupper(p.First_Name[0]);
	if(strlen(p.First_Name)>20||strlen(p.First_Name)<2)
	{
		printf("\nInvalid\nThe max range for first name is 20 and min range is 2\n");
		end();
	}
	printf("Last Name:\n");
    scanf("%s",p.Last_Name);
    p.Last_Name[0]=toupper(p.Last_Name[0]);
    if(strlen(p.Last_Name)>20||strlen(p.Last_Name)<2)
	{
		printf("\nInvalid\nThe max range for last name is 20 and min range is 2\n");
		end();
	}
	do
	{
	    printf("\nGender[F/M]:\n");
		scanf(" %c",&p.Gender);
		if(toupper(p.Gender)=='M'|| toupper(p.Gender)=='F')
		{
			ok =1;
		}
		else
		{
		ok =0;
		}
        if(!ok)
	    {
	    	printf("\nGender contain Invalid character\nEnter either F or M\n");
    	}
	 }	while(!ok);
     printf("\nContact no:\n");
     scanf("%s",p.Contact_no);
     if(strlen(p.Contact_no)>10||strlen(p.Contact_no)!=10)
	 {
	  	 printf("Invalid\nContact no. must contain 10 numbers.\nEnter again\n");
		 end();
	 }
    printf("\nAge:");
    scanf(" %i",&p.age);
    printf("\nAddress (without space):\n");
    scanf("%s",p.ad.Address);
    p.ad.Address[0]=toupper(p.ad.Address[0]);
    if(strlen(p.ad.Address)>40||strlen(p.ad.Address)<4)
	{
		printf("\nInvalid\nThe max range for address is 40 and min range is 4\n");
		end();
	}
    printf("\nPincode:\n");
    scanf(" %i",&p.ad.pincode);
    fprintf(ek,"%s %s %c %s %i %s %i\n", p.First_Name, p.Last_Name,p.Gender, p.Contact_no,
				 p.age, p.ad.Address,p.ad.pincode);
    printf("\n\nInformation Recorded...\n");
    fclose(ek);
    getch();
    system_switcher();
}


void view()
{
        system("cls");
        printf("\t\t\t\t\t\t  COVID-19\n");
        printf("\t\t\t\t\t  ************************\n\n");
        int row;
        FILE *ek;
	    ek=fopen("Record2.dat","r");
        printf("Covid patients list\n");
        printf("*******************\n");
		gotoxy(1,5);
		printf("Full Name");
		gotoxy(20,5);
		printf("Gender");
		gotoxy(32,5);
		printf("Contact No.");
		gotoxy(49,5);
		printf("Age");
		gotoxy(55,5);
		printf("Address");
		gotoxy(94,5);
		printf("Pincode");
		gotoxy(101,5);
		row=8;
		while(fscanf(ek,"%s %s %c %s %i %s %i\n", p.First_Name, p.Last_Name,&p.Gender, p.Contact_no,
				 &p.age, p.ad.Address,&p.ad.pincode)!=EOF)
        {
            gotoxy(1,row);
			printf("%s %s",p.First_Name, p.Last_Name);
			gotoxy(20,row);
			printf("%c",p.Gender);
			gotoxy(32,row);
			printf("%s",p.Contact_no);
			gotoxy(49,row);
			printf("%i",p.age);
			gotoxy(55,row);
			printf("%s",p.ad.Address);
			gotoxy(94,row);
			printf("%i",p.ad.pincode);
			gotoxy(49,row);
			row++;
        }
        fclose(ek);
        getch();
        g_menu();
}

void testing_center()
{
    system("cls");
    printf("\t\t\t\t\t\t  COVID-19\n");
    printf("\t\t\t\t\t  ************************\n");
    FILE *fptr;
    char  c;
    fptr = fopen("list.dat", "r");
    c = fgetc(fptr);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fptr);
    }

    fclose(fptr);
    getch();
    c_menu();
}

void self_asses()
{
    system("cls");
    printf("\t\t\t\t\t\t  COVID-19\n");
    printf("\t\t\t\t\t  ************************\n");
    printf("Self assessment\n\n");
    printf("***************\n");
    int n=0,i;
    printf("Press 1 if yes else press 0\n");
    printf("Do u have cough\n");
    scanf("%i",&i);
    if(i==1){n++;}
    printf("Do u have fever\n");
    scanf("%i",&i);
    if(i==1){n++;}
    printf("Do u have breathing issue\n");
    scanf("%i",&i);
    if(i==1){n++;}
    printf("Do u have diabetes ,hypertension ,lung diseases ,heart diseases\n");
    scanf("%i",&i);
    if(i==1){n++;}
    printf("Did u travel abroad\n");
    scanf("%i",&i);
    if(i==1){n++;}
    printf("Do u meet anyone with corona positive\n");
    scanf("%i",&i);
    if(i==1){n=n+5;}
    if(n>4)
    {
        printf("\n\nYou have chances of Covid-19\nThe officials will contact you");
        read_data();
    }
    else
    {
        printf("\n...You are safe...");
    }
    c_menu();
}
void end()
{
    system("cls");
    printf("\t\t\t\t\t\t  COVID-19\n");
    printf("\t\t\t\t\t  ************************\n\n");
    printf("\n\t\t\t\t\t\tTHANK YOU");
    getch();
}

void g_menu()
{
    system("cls");
    printf("\t\t\t\t\t\t  COVID-19\n");
    printf("\t\t\t\t\t  ************************\n\n\n");
    printf("1.View the record\n2.No. of patients in a area\n3.Update the list if the person is safe or dead \n4.Exit\n");
    int n;
    scanf("%i",&n);
    if (n==1)
    {
        view();
    }
    else if (n==2)
    {
        search();
    }
    else if (n==3)
    {
        edit();
    }
    else if (n==4)
    {
        end();
    }
    else
    {
        system_switcher();
    }
    getch();
}

void login()
{
    system("cls");
    printf("\t\t\t\t\t\t  COVID-19\n");
    printf("\t\t\t\t\t  ************************\n\n");
    int e=0	;
    char Username[15];
    char Password[15];
    char original_Username[25]="GOVERNMENT";
    char original_Password[15]="COVID-19";

    do
    {
        printf("\nEnter your Username and Password");
        printf("\nUSERNAME:");
        scanf("%s",Username);
        printf("\nPASSWORD:");
        scanf("%s",Password);
        if (strcmp(Username,original_Username)==0 && strcmp(Password,original_Password)==0)
        {
            printf("\nLogin Successfull...\npress any key to continue");
            getch();
            g_menu();
            break;
        }
        else
        {
            printf("\nPassword in incorrect,Try Again ");
            e++;
            getch();
        }
    }while(e<=2);
    if(e>2)
    {
    printf("\nYou have crossed the limit. You cannot login");
    getch();
    end();
    }
}

void g_check()
{
    system("cls");
    printf("\t\t\t\t\t\t  COVID-19\n");
    printf("\t\t\t\t\t  ************************\n");
    login();
}

void c_menu()
{
    system("cls");
    printf("\t\t\t\t\t\t  COVID-19\n");
    printf("\t\t\t\t\t  ************************\n");
    printf("1.Self assess\n2.Number of affected people nearby\n3.Testing centers list\n4.Exit\n");
    int n;
    scanf("%i",&n);
    if (n==1)
    {
        self_asses();
    }
    else if (n==2)
    {
        nearby();
    }
    else if (n==3)
    {
        testing_center();
    }
    else if (n==4)
    {
        end();
    }
    else
    {
        system_switcher();
    }
    getch();
}

void system_switcher()
{
    system("cls");
    printf("\t\t\t\t\t\t  COVID-19\n");
    printf("\t\t\t\t\t  ************************\n");
    int n;
    printf("1.Government officials\n2.Citizens\n");
    scanf("%i",&n);
    if(n==1)
    {
        g_check();
    }
    else if(n==2)
    {
        c_menu();
    }
    else
    {
        system_switcher();
    }
    getch();
}

void open_screen()
{
    printf("\t\t\t\t\t\t  COVID-19\n");
    printf("\t\t\t\t\t  ************************\n\n\n");
    printf("\t\t\t\t    ALL INDIA CORONA MONITORING SYSTEM\n\n\n");
    printf("\t\t\t\t\t  ************************\n\n\n");
    printf("Press any key...");
    getch();
    system("cls");
}

int main()
{
    open_screen();
    system_switcher();
}
