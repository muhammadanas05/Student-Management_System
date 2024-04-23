#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <conio.h>
#include <windows.h>

#define Student struct Stud

void add(FILE * fptr);
void modify(FILE * fptr);
void display(FILE * fptr);
void Individual(FILE *fptr);
FILE * del(FILE * fptr);
void printChar(char ch,int n);
void header();
void title();
void menu();
int emailcheck();
long long int numbercheck();
void intro();
FILE *tptr;

struct Stud {
	char name[100];
	int phone;
	char email[100];
	char guardianname[100];
	int guardianphone;
	char address[100];
	char dept[50];
	int roll;
	float sgpa[8];
	float cgpa;
};


int main() {
	system("color 3");
	int ch,id,i;
	char c;
	FILE * fptr;
	Student s;
	int option;
	char another;

	if((fptr=fopen("db.txt","a+"))==NULL) {
		printf("Can't create or open Database.");
		return 0;
	}

	char username[20];
	char password[20];

	system("color 70");
	printf("Enter Username: ");
	gets(username);
	printf("Enter Password: ");
	gets(password);

	if(strcmp(username,"Anas")==0 || strcmp(username,"anas")==0 ) {
		if(strcmp(password,"cs221004")==0) {
//		printf(" ");
			intro();
			header();
			title();
			getch();

			while(1) {
				header();
				printf("\n\t");
				menu();
				printf("\n\n\t\t\t\tEnter Your Option :--> ");
				scanf("%d",&option);

				switch(option) {
					case 1:
						add(fptr);
						break;
					case 2:
						modify(fptr);
						break;
					case 3:
						display(fptr);
						break;
					case 4:
						Individual(fptr);
						break;
					case 5:
						fptr=del(fptr);
						break;
					case 6:
						return 1;
						break;
					default:
						printf("\n\t\tNo Action Detected");
						printf("\n\t\tPress Any Key\n\n\n");
						getch();
						system("pause");
				}
			}
			return 1;
		} else {
			system ("color 40");
			printf("\nINVALID PASSWORD !!!\n");
			system("pause");
			main();
		}
	} else {
		system ("color 40");
		printf("\nINVALID USERNAME !!!\n");
		system("pause");
		main();
	}
}



void printChar(char ch,int n) {
	while(n--) {
		putchar(ch);
	}
}


void intro() {
	system("CLS");
	system("color 3");
	system("COLOR 20");
	printf("\n\n\t");
	printChar('=',19);
	printf(" Student Management System ");
	printChar('=',19);
	printf("\n\n\n\n\t*    *    *  *******    *         *********   ***********   *       *   *******\n");
	printf("\t*   * *   *  *          *         *           *         *   * *   * *   *\n");
	printf("\t*  *   *  *  *******    *         *           *         *   *   *   *   *******\n");
	printf("\t* *     * *  *          *         *           *         *   *       *   *\n");
	printf("\t*         *  *******    ********  *********   ***********   *       *   *******\n");
	printf("\n\n\n\n\n\t\t\tPress any key to continue...... ");
	getch();
}

void header() {
	system("cls");
	system("color 3");
	printf("\n\n\t");
	printChar('=',19);
	printf(" Student Management System ");
	printChar('=',19);
	printf("\n");
}

void title() {
	system("color 70");
	printf("\n\n\t\t\t\tPF LAB PROJECT");
	printf("\n\n\t\t\t\t  DHA SUFFA\n\t\t\t");
	printf("\n\t\t\t         Muhammad Anas \n\t\t\t");
	printChar('=',36);
	printf("\n\n\n\t\t\t       press any key to Enter");
}

void menu() {
	printChar('*',64);
	printf("\n\n\t\t\t\t1. Add Student");
	printf("\n\n\t\t\t\t2. Modify Student");
	printf("\n\n\t\t\t\t3. Show All Student");
	printf("\n\n\t\t\t\t4. Individual View");
	printf("\n\n\t\t\t\t5. Remove Student");
	printf("\n\n\t\t\t\t6. Logout\n\t");
	printChar('*',64);
}


void add(FILE * fptr) {
	
	header();
	system("color 5");

	char another='y';
	Student s;
	int i,semester,temp;
	int size=sizeof(s);
	long int num;
	float cgpa;

	fseek(fptr,0,SEEK_END);
	while(another=='y'||another=='Y') {
		printf("\n\n\t\tEnter Full Name of Student: ");
		fflush(stdin);
		gets(s.name);
		fflush(stdin);
		printf("\n\n\t\tPhone number: ");
		num=numbercheck();
		s.phone=num;
		fflush(stdin);
		printf("\n\n\t\tEnter Student Email: ");
		fflush(stdin);
		while(1) {
			char temp[50];
			gets(temp);
			if(emailcheck(temp)) {
				strcpy(s.email,temp);
				break;
			} else {
				printf("\n\n\t\tIncorrect Email, Re-enter: ");
			}
		}
		printf("\n\n\t\tEnter Full Name of Student Guardian: ");
		fflush(stdin);
		gets(s.guardianname);
		printf("\n\n\t\tEnter Guardian Phone number: ");
		num=numbercheck();
		s.guardianphone=num;
		fflush(stdin);
		printf("\n\n\t\tEnter Student's address: ");
		fflush(stdin);
		fgets(s.address,100,stdin);
		printf("\n\n\t\tEnter Department Name: ");
		fflush(stdin);
		gets(s.dept);
		printf("\n\n\t\tEnter Roll number: ");
		scanf("%d",&s.roll);
		for(i=0; i<8; i++) {
			s.sgpa[i]=0;
		}
		printf("\n\n\t\tEnter Current Semester: ");
		scanf("%d",&semester);
		printf("\n\n\tEnter SGPA for %d semesters\n",semester);
		for(i=0,cgpa=0; i<semester; i++) {
			while(1) {
				scanf("%f",&s.sgpa[i]);
				if((s.sgpa[i]<0)||(s.sgpa[i]>4)) {
					printf("Enter correct SGPA: \n");
					continue;
				} else {
					break;
				}
			}
			cgpa+=s.sgpa[i];
		}
		cgpa/=semester;
		s.cgpa=cgpa;
		fwrite(&s,sizeof(s),1,fptr);
		printf("\n\n\t\tAdd another student?(Y/N)?");
		fflush(stdin);
		another=getchar();
	}
}


FILE * del(FILE * fptr) {
	header();
	system("color 5");
	Student s;
	int flag=0,tempRoll,size=sizeof(s);
	FILE *tptr;
	if((tptr=fopen("temp.txt","w+"))==NULL) {
		printf("\n\n\t\t\t\\t!!! ERROR !!!\n\t\t");
		system("pause");
		return fptr;
	}
	printf("\n\n\tEnter Roll number of Student to Delete the Record");
	printf("\n\n\t\t\tRoll No. : ");
	scanf("%d",&tempRoll);
	rewind(fptr);
	while((fread(&s,size,1,fptr))==1) {
		if(s.roll==tempRoll) {
			flag=1;
			printf("\n\tRecord Deleted for");
			printf("\n\n\t\t%s\n\n\t\t%s\n\n\t\t%d\n\t",s.name,s.dept,s.roll);
			continue;
		}
		fwrite(&s,size,1,tptr);
	}
	fclose(fptr);
	fclose(tptr);
	remove("db.txt");
	rename("temp.txt","db.txt");
	if((fptr=fopen("db.txt","r+"))==NULL) {
		printf("ERROR");
		return  NULL;
	}
	if(flag==0) printf("\n\n\t\tNO STUDENT FOUND WITH THE INFORMATION\n\t");
	printChar('-',65);
	printf("\n\t");
	system("pause");
	return fptr;
}


void modify(FILE * fptr) {
	header();
	system("color 5");
	Student s;
	int i,flag=0,semester,tempRoll,siz=sizeof(s);
	char option;
	float cgpa;
	printf("\n\n\tEnter Roll Number of Student to MODIFY the Record : ");
	scanf("%d",&tempRoll);
	rewind(fptr);

	while((fread(&s,siz,1,fptr))==1) {
		if(s.roll==tempRoll) {
			flag=1;
			break;
		}
	}

	if(flag==1) {
		fseek(fptr,-siz,SEEK_CUR);
		printf("\n\n\t\t\t\tRecord Found\n\t\t\t");
		printChar('=',38);
		printf("\n\n\t\t\tStudent Name: %s",s.name);
		printf("\n\n\t\t\tStudent Roll: %d \n\t\t\t",s.roll);
		printChar('=',38);
		printf("\n\n\t\tIs the department same? ");
		scanf(" %c",&option);
		if (option=='N'||option=='n') {
			printf("\n\n\t\t\tEnter Department: ");
			fflush(stdin);
			gets(s.dept);
		}
		printf("Enter the semester");
		scanf("%d",&semester);
		printf("\n\n\t\tEnter SGPA for %d semesters\n",semester);
		for(i=0,cgpa=0; i<semester; i++) {
			scanf("%f",&s.sgpa[i]);
			cgpa+=s.sgpa[i];
		}
		cgpa=cgpa/semester;
		printf("%f",cgpa);
		fwrite(&s,sizeof(s),1,fptr);
	} else printf("\n\n\t!!!! ERROR !!!! RECORD NOT FOUND");
	printf("\n\n\t");
	system("pause");
}

void display(FILE * fptr) {
	header();
	Student s;
	int i,size=sizeof(s);
	rewind(fptr);
	while((fread(&s,size,1,fptr))==1) {
		printf("\n\n\tName : %s",s.name);
		printf("\n\n\tPhone : %lld",s.phone);
		printf("\n\n\tGuardian : %s",s.guardianname);
		printf("\n\n\tGuardian Phone : %lld",s.guardianphone);
		printf("\n\n\tAddress : %s",s.address);
		printf("\n\n\tDepartment : %s",s.dept);
		printf("\n\n\tRoll : %d",s.roll);
		printf("\n\n\tSGPA: ");
		for(i=0; i<8; i++)
			printf("| %.2f |",s.sgpa[i]);
		printf("\n\n\t\tCGPA : %.2f\n\t",s.cgpa);
		printChar('-',65);
	}
	printf("\n\n\n\t");
	printChar('*',65);
	printf("\n\n\t");
	system("pause");
}

void Individual(FILE *fptr) {
	header();
	system("color 5");

	int tempRoll,flag,siz,i;
	Student s;
	char another='y';
	int size=sizeof(s);

	while(another=='y'||another=='Y') {
		printf("\n\n\tEnter Roll Number: ");
		scanf("%d",&tempRoll);
		rewind(fptr);
		while((fread(&s,size,1,fptr))==1) {
			if(s.roll==tempRoll) {
				flag=1;
				break;
			}
		}
		if(flag==1) {
			printf("\n\t\tName : %s",s.name);
			printf("\n\t\tNumber : %lld",s.phone);
			printf("\n\n\t\tDepartment : %s",s.dept);
			printf("\n\n\t\tRoll : %d",s.roll);
			printf("\n\n\t\tSGPA: ");
			for(i=0; i<8; i++)
				printf("| %.2f |",s.sgpa[i]);
			printf("\n\n\t\tCGPA : %.2f\n\t",s.cgpa);
			printChar('-',65);
		} else printf("\n\n\t\t!!!! ERROR RECORD NOT FOUND !!!!");
		printf("\n\n\t\tShow another student information? (Y/N)?");
		fflush(stdin);
		another=getchar();
	}
}

int emailcheck(char email[]) {
	int flag=0,i,size;
	size = strlen(email);
	if (email[size-4]=='.' && email[size-3]=='c' && email[size-2]=='o' && email[size-1]=='m') {
		flag=flag+1;
	}
	for (i=0; i<size; i++) {
		if (email[i]=='@') {
			flag=flag+1;
		}
	}
	if(flag == 2) {
		return 1;
	}
	return 0;
}

long long int numbercheck() {
	long long int number;
	int count=1;
	int num;
	long long int phone;
	scanf("%lld",&number);
	phone=number;
	while (number!=0) {
		num=number%10;
		number=number/10;
		count=count+1;
	}
	if (count<11 || count>11) {
		printf("\n\n\t\tInvalid phone number,re-enter: ");
		scanf("%lld",&number);
	}
	return phone;
}


