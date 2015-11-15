
/*****************************************************************************
 * Copyright (C) Pratik H. Mahajan mahajanph13.it@coep.ac.in
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
 
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "phonebook.h"
#define SIZE 100
#define AR 1
#define MR 2
#define SR 3
#define DR 4

/* loading
   Input : int sec : take number of seconds for loading
   output : sleep for given num of sec */
void loading(int sec) {
	printf("\n\n\t\t\t\t\t\t\t     Opening Application\n");
	printf("\t\t\t\t\t\t\t\tPlease wait...\n");
	sleep(sec);
}

/* For Authentication
   Input : take the string as input if input matches to password 'admin' then
   Output : open application else repeat process for 2 times */
void login() {
	struct phonebook p;
	char *pass;
	static int count = 3;
	system("clear");
	printf("------------------------------------------------------------------------------------------------------------------------------------------------\n");
   up:	printf("\t\t\t\t\t\t\t    Enter the password: ");
	//scanf("%s", pass);
	pass = getpass("");
	count--;
	printf("------------------------------------------------------------------------------------------------------------------------------------------------");
	if(strcmp(pass, "admin") == 0) {
		loading(5);
		menu(&p);
		menuchoice(&p);
	}
	else {
		if(count > 0) {
			loading(2);
			system("clear");
			printf("\n\t\t\t\t\t\t\t      Attempt remaining : %d\n", count);
			printf("\n\t\t\t\t\t\t\tInvalid password, please try again.\n");
			goto up;
		}
		else {
			printf("\n\n\t\t\t\t\t\t\tLogin attemp failed more than 3 times.\n\n");
			printf("************************************************************************************************************************************************\n");
			exit(0);
		}
	}	
}

/* Display the menu of phonebook*/
void menu(phonebook *p) {
	//while(1) {
		system("clear");
		
		printf("************************************************************************************************************************************************\n");
		printf("\t\t\t\t\t\t**********WELCOME TO PHONEBOOK*************");
		printf("\n\n\t\t\t\t\t\t\t\t  MENU\t\t\n");
		printf("\t\t\t\t\t\t\t\t -------\t\t\n\n");
		printf("\t\t\t\t\t\t1.Add New   \t2.List   \t3.Modify \n\t\t\t\t\t\t4.Search\t5.Delete\t6.Exit\n");
		printf("************************************************************************************************************************************************\n");
		
	
}

/* For choosing the specific operation 
   Input: Take the choice for perform the operation
   output: call the function according to the choice */
void menuchoice(phonebook *p) {
		int choice;
	up:	printf("Enter your choice for operation: ");
		scanf("%d", &choice);
		//printf("------------------------------------\n");
		switch(choice) {
			case 1: addrecord(p);
				break;
			case 2: listrecord(p, 0);
				break;
			case 3: modifyrecord(p);
				break;
			case 4: searchrecord(p);
				break;
			case 5: deleterecord(p);
				break;
			case 6: printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tClosing Application\n");
				printf("\t\t\t\t\t\t\t\t   Please wait...\n");
				sleep(5);
				printf("\n\n\t\t\t\t\t\t\tApplication closed. Thank you for visiting.\n");
				printf("\t\t\t\t\t\t**********************************************************\n\n\n");
				exit(0);
			default: printf("your choice is wrong.\n");
				 printf("------------------------------------------\n");
				 goto up;
				 
		}
		
	//}
}

/* For inserting the new record in the database
   Input: it take First name, middle name, last name, mobile no, city,
   gender and E-mail id 
   Output: passes all this input to convert funtion for convert it to std input 
   and then call confirmrecord() function */
int addrecord(phonebook *p) {
	int count = 0;
	char *temp = (char *) malloc(sizeof(temp));
	printf("Enter first name: ");
	scanf(" %s", p->fname);
	temp = convert(p->fname);
	p->fname[0] = *temp;

        printf("Enter middle name: ");
        scanf(" %s", p->mname);
        temp = convert(p->mname);
	p->mname[0] = *temp;
	
        printf("Enter last name: ");
	scanf(" %s", p->lname);
        temp = convert(p->lname);
	p->lname[0] = *temp;
	
  up:   printf("Enter mobile no: ");
	scanf(" %lf", &p->mobile_no);
	unsigned long long no = (unsigned long long) p->mobile_no;
	while(no != 0) {
		no /= 10;             /* n=n/10 */
        	++count;
        }
        if(count != 10) {
        	printf("mobile number should be 10 digit.\n");
        	count = 0;
        	goto up;
        }
        
        printf("Enter City:");
	scanf(" %s",p->address);
	temp = convert(p->address);
	p->address[0] = *temp;
	
        printf("Enter Gender:");
        scanf(" %s", p->sex);
        temp = convert(p->sex);
	p->sex[0] = *temp;
	
        printf("Enter e-mail:");
        scanf(" %s", p->mail);
       	
        confirmaddrecord(p);	
	
	confirm(p, AR);
	return 0;
}

/* Convert string into first char to upper case and remaining to lower
   Input: char *name , name of person
   Output: convert it and return char (i.e, base address of converted string) */
char *convert(char *name) {
	int i = 0;
	while(name[i] != '\0') {
		if(i == 0) {
			name[0] = toupper(name[0]);
		}
		else { 
			name[i] = tolower(name[i]);	
		}
		i++;
	}
	return name;
}

/* For confirmation Is have to add record or not 
   Input: struct phonebook p and take choice for whether save 
	  the or not
   Output: If choice = y then call isavailable() ,if choice = n, call confirm(),
   	   if choice is any other then repeat from Input . */
void confirmaddrecord(phonebook *p) {
	char choice;
  up:	printf("Are you sure you want to save?[y/n] ");
	scanf(" %c", &choice);
	if(choice == 'Y' || choice == 'y') {
		if(isavailable(p) == 0) {
			printf("----------------------------------------------------------\n");
			printf("Data is already present\n");
			printf("----------------------------------------------------------\n");
		}
		else {
			save(p->fname);
			save(p->mname);
			save(p->lname);
			FILE *fp = fopen("record.txt", "a+");
			if(fp == NULL) {
				printf("Database File opened failed:");
			}
			else {
				fprintf(fp, "%0.0lf\t", p->mobile_no);
					 
			}
			save(p->address);
			save(p->sex);
		
			save(p->mail);
			fprintf(fp, "\n");
			fclose(fp);
			printf("******************************\n");
			printf("Record saved successfully.\n");
			printf("------------------------------\n");
		}
	}
	else if(choice == 'N' || choice == 'n') {
		//menu(p);
		//menuchoice(p);
		confirm(p, AR);
	}
	else {
		printf(" Choose proper option.\n");
		goto up;
	}
}

/* check whether the record is already present or not
   Input: phonebook *pp, currently entered all informtion by user to add record 
   Ouput: if record is present return 0 i.e., returned as a int */
int isavailable(phonebook *pp) {
	phonebook *p = (phonebook *)malloc(sizeof(phonebook));
	FILE *fp = fopen("record.txt", "a+");
	if(fp == NULL) {
		perror("File opened failed:");
		return errno;
	}
	else {
		while(fscanf(fp, "%s %s %s %s %s %s %lf", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, &p->mobile_no) 
		!= EOF){
			if(strcmp(p->fname, pp->fname) == 0 && strcmp(p->mname, pp->mname) == 0 && strcmp(p->lname, pp->lname) == 0 && 
			strcmp(p->address, pp->address) == 0 && strcmp(p->sex, pp->sex) == 0 && strcmp(p->mail, pp->mail) == 0  && 
			p->mobile_no == pp->mobile_no) {
				return 0;
			}
			
		}
	}
	return 1;
}

/* Save the record into the file 
   Input: char *data, take first, middle and last name, city, gender and E-mail id as input
   Output: if file is present write to file, else returned error num as int*/
int save(char *data) {
	FILE *fp = fopen("record.txt", "a+");
	if(fp == NULL) {
		perror("Database File opened failed:");
		return errno;
	}
	else {
		fprintf(fp, "%s ", data);
		//fprintf(fp, "|");
		fclose(fp); 
	}
	return 0;	
}

/* Display the whole available records
   Input: phonebook *p, structure: int flag, to ensure after printing the record
   	  should continue or close application
   Output: Disply all available record, if flag = 1, indicate just print the records, 
   	   if flag = 0, indicate printf record and also takes choice to continue or not */
int listrecord(phonebook *p , int flag) {
	int count = 0;
	FILE *fp = fopen("record.txt", "a+");//r
	if(fp == NULL) {
		perror("File opened failed:");
		return errno;
	}
	printf("---------------------\n");
	printf("Your records...\n");
	printf("---------------------\n");
	printf("================================================================================================================================================\n");
	printf("Sr No.\t First Name\t Middle Name\t Last  Name\t   Address\t \t  Sex\t \tE-mail\t\t\t Mobile No.\n");
	printf("================================================================================================================================================\n");
	while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, &p->mobile_no) != 		EOF) {
		count++;
		printf("%-10d %-15s %-15s %-15s %-20s %-10s %-25s\t %0.0lf\n ", count, p->fname, p->mname, p->lname, p->address,
		p->sex,p->mail, p->mobile_no);                	        
		
	}
	fclose(fp);
	printf("===============================================================================================================================================\n");
	/* flag = 1 indicate just print the list of all available records and flag = 0 indicates, printf the list and give
	   option for doing the operations */
	if(flag != 1)
	confirmlistcont(p);
	return 0;
}

/* for confirmation of user to use the application for next operations after seeing the all list of records.
   this function if only for the listrecord(p) 
   Input: phonebook *p, structure; int choice, to peroform any opeartion
   Output: If choice = y, call menu(p) and menuchoice(p),else if choice = n, call exitapp(), else do recursion */
void confirmlistcont(phonebook *p) {
	char choice;
	printf("Do you want to perform any operation[y/n]");
	scanf(" %c", &choice);
	if(choice == 'y' || choice == 'Y') {
		system("clear");
		menu(p);
		menuchoice(p);
	}
	else if(choice == 'n' || choice == 'N') 
		exitapp();
	else {
		printf(" Choose proper option.\n");
		confirmlistcont(p);
	}
}

/* Confirmation about is we have to do that operation again
   Input: phonebook *p, struture; int fun, to call specific function according to fun
   Output:if confirmtion choice = y then call function according to int fun,
   	  else if choice = n, call menu(p) and menuchoice(p) 
   	  else choice is any other then repeat steps again from taking choice */
void confirm(phonebook *p, int fun) {
	char choice;
   up:  printf("Do you want to continue [y/n]");
	scanf(" %c", &choice);
	if(choice == 'y' || choice == 'Y') {
		system("clear"); 
		menu(p);
		switch(fun) {
			case 1: menu(p);
				addrecord(p);
				break;
			case 2: modifyrecord(p);
				break;
			case 3: menu(p);
				searchrecord(p);
				break;
			case 4:	deleterecord(p);
				break;
			default:
				break;
				
		}
	}
	else if(choice == 'n' || choice == 'N') {
		menu(p);
		menuchoice(p);
	}
	else {
		printf(" Choose proper option.\n");
		goto up;
	}
}

/* Update the record with new given information
   Input:phonebook *p, i.e char fname[35] and char lname[35] 
   Output: if data match, update the record and call listrecord() , else gives message and call confirm(p, MR) */
int modifyrecord(phonebook *p) {
	listrecord(p, 1);
	char fname[20], lname[20];
	int flag = 0, count = 0;
	char *temp = (char *) malloc(sizeof(temp));
	FILE *fp = fopen("record.txt", "a+");
	FILE *fpb = fopen("backup.txt", "a+");
	if(fp == NULL) {
		perror("File opened failed:");
		return errno;
	}
	if(fpb == NULL) {
		perror("File opened failed:");
		return errno;
	}
	printf("Enter First Name which have to be modify: ");
	scanf(" %s",fname);
	temp = convert(fname);
	fname[0] = *temp;
	
	printf("Enter Last Name: ");
	scanf(" %s",lname);
	temp = convert(lname);
	lname[0] = *temp;
	
	backup(fname, lname, p);
	while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
	&p->mobile_no) != EOF) {
		if(strcmp(fname, p->fname) == 0 && strcmp(lname, p->lname) == 0) {
			printf("Data found..\n");
			printf("Enter New Data to modify the record\n");
			printf("----------------------------------------\n");
			printf("Enter first name: ");
			scanf(" %s", p->fname);
			temp = convert(p->fname);
			p->fname[0] = *temp;
			
			printf("Enter middle name: ");
			scanf(" %s", p->mname);
			temp = convert(p->mname);
			p->mname[0] = *temp;
	
			printf("Enter last name: ");
			scanf(" %s", p->lname);
			temp = convert(p->lname);
			p->lname[0] = *temp;
	
		up:	printf("Enter mobile no: ");
			scanf(" %lf", &p->mobile_no);
			unsigned long long no = (unsigned long long) p->mobile_no; //casting into long int
			while(no != 0) {
				no /= 10;             /* n=n/10 ; counting the number of digits*/
				++count;
			}
			if(count != 10) {
				printf("mobile number should be 10 digit.\n");
				count = 0;
				goto up;
			}
			
			printf("Enter City:");
			scanf(" %s",p->address);
			temp = convert(p->address);
			p->address[0] = *temp;
	
			printf("Enter Gender:");
			scanf(" %s", p->sex);
			temp = convert(p->sex);
			p->sex[0] = *temp;
			
			printf("Enter e-mail:");
			scanf(" %s", p->mail);
			printf("-------------------------------\n");
			char choice;
  		up1:	printf("Are you sure you want to update?[y/n] ");
			scanf(" %c", &choice);
			if(choice == 'Y' || choice == 'y') {
			
				fprintf(fp, "\n");
				fprintf(fpb,"%s %s %s %s %s %s %0.0lf", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
				p->mobile_no);
				fclose(fpb);
				flag = 1;
			}
			else if(choice == 'N' || choice == 'n') {
				//menu(p);
				confirm(p, MR);
			}
			else {
				printf(" Choose proper option.\n");
				goto up1;
			}
		}
	}
	
	/* if flag set to 1 then update the files means rename record.txt file and delete backup.txt file*/
	
	if(flag == 1) {
		system("rm record.txt");
		system("mv backup.txt record.txt");
		printf("*******************************\n");
		printf("record updated successfully.\n");
		printf("*******************************\n");
		listrecord(p, 1);
	}
	else {
		printf("*******************\n");
		printf("Data not found.\n");
		printf("-------------------\n");
	}
	fclose(fp);
	confirm(p, MR);
	return 0;
}

/* Copying records of record.txt into backup.txt except the record which have to delete
   Input: char *fname, first name; char * lname, last name; phonebook *p, structure 
   Output: Copy all records of record.txtx to backup.txt except record which have to delete and returned as int */
int backup(char *fname, char* lname, phonebook *p) {
	FILE *fp = fopen("record.txt","a+");//r
	FILE *fpb = fopen("backup.txt","a+");//w
	if(fpb == NULL) {
		perror("File opened failed:");
		return errno;
	}
	if(fp == NULL) {
		perror("File opened failed:");
		return errno;
	}
	while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
	&p->mobile_no) != EOF) {
		if(strcmp(fname, p->fname) == 0 && strcmp(lname, p->lname) == 0) {
			
		}
		else {
		      		fprintf(fpb,"%s %s %s %s %s %s %0.0lf", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
				p->mobile_no);
				fprintf(fpb, "\n");
		}
	}
	fclose(fpb);
	fclose(fp);
	return 0;
}

/* call searchmenu(p) for display Search record in the given database based on first name, last name, gender, Mobile no and city
   Input: phonebook *p, structure, take input for search as string based on first name, last name, gender, Mobile no and city 
   Output: call search(p, char *searchinput, char *searchon) */
int searchrecord(phonebook *p) {
	char str[20];
	int choice, count = 0;
	double mn;
	char *temp = (char *) malloc(sizeof(temp));
	printf("------------------------------\n");
	printf("Search on..\n");
	printf("------------------------------\n");
	searchmenu(p);
	scanf("%d", &choice);
	printf("------------------------------\n");
	switch(choice) {
		case 1:	printf("Enter First Name: ");
			scanf(" %s", str);
			temp = convert(str);
			str[0] = *temp;
			printf("searching...\n");
			sleep(1);
			printf("------------------------------\n");
			search(p, str, "fname");
			break;
			
		case 2: printf("Enter Last Name: ");
			scanf(" %s", str);
			temp = convert(str);
			str[0] = *temp;
			printf("searching...\n");
			sleep(1);
			printf("------------------------------\n");
			search(p, str, "lname");
			break;
			
		case 3: printf("Enter Gender: ");
			scanf(" %s", str);
			temp = convert(str);
			str[0] = *temp;
			printf("searching...\n");
			sleep(1);
			printf("------------------------------\n");
			search(p, str, "sex");
			break;
			
		case 4: printf("Enter Mobile No: ");
			scanf(" %lf", &mn);
			FILE *fp = fopen("record.txt", "a+");//r
			if(fp == NULL) {
				printf("File opened failed.");
		
			}
			else {
				printf("================================================================================================================================================\n");
				printf("Sr No.\t First Name\t Middle Name\t Last  Name\t   Address\t \t  Sex\t \tE-mail\t\t\t Mobile No.\n");
				printf("================================================================================================================================================\n");
				while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
				&p->mobile_no) != EOF) {
					if(mn == p->mobile_no) {
						count++;
						printf("%-10d %-15s %-15s %-15s %-20s %-10s %-25s\t %0.0lf\n ", count, p->fname, p->mname, 
						p->lname, p->address,p->sex,p->mail, p->mobile_no); 
					}
				}
	
	
				fclose(fp);
				printf("===============================================================================================================================================\n");
				if(count == 0) {
					printf("Record not found.\n");
					printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");
				}
				else {
					printf("Records found.\n");
					printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");
				}
			}
			break;
		case 5:	printf("Enter City Name: ");
			scanf(" %s", str);
			temp = convert(str);
			str[0] = *temp;
			printf("searching...\n");
			sleep(1);
			printf("------------------------------\n");
			search(p, str, "address");
			break;
		default:
			printf("Wrong choice");
			break;
	}
	confirm(p, SR);
	return 0;
}

/* print search menu */
void searchmenu(phonebook *p) {
	printf("1. First Name\n");
	printf("2. Last Name\n");
	printf("3. Gender\n");
	printf("4. Mobile No\n");
	printf("5. City\n");
	printf("------------------------------\n");
}

/* search the records in database based on first name, last name, gender, mobile no and city name
   Input: phonebook *p, structure; char *str, string as search input; char *column, string as search on 
   Output: if records found, display the records, else give proper message. */
void search(phonebook *p, char *str, char *column) {
	int count = 0;
	FILE *fp = fopen("record.txt", "a+");//r
	if(fp == NULL) {
		printf("File opened failed.");
		
	}
	else {
		if(strcmp(column, "fname") == 0) {
			printf("================================================================================================================================================\n");
			printf("Sr No.\t First Name\t Middle Name\t Last  Name\t   Address\t \t  Sex\t \tE-mail\t\t\t Mobile No.\n");
			printf("================================================================================================================================================\n");
			while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
			&p->mobile_no) != EOF) {
				if(strcmp(str, p->fname) == 0) {
					count++;
					printf("%-10d %-15s %-15s %-15s %-20s %-10s %-25s\t %0.0lf\n ", count, p->fname, p->mname, 
					p->lname, p->address,p->sex,p->mail, p->mobile_no); 
				}
			}
	
	
			fclose(fp);
			printf("===============================================================================================================================================\n");
		}
		else if(strcmp(column, "lname")== 0) {
			printf("================================================================================================================================================\n");
			printf("Sr No.\t First Name\t Middle Name\t Last  Name\t   Address\t \t  Sex\t \tE-mail\t\t\t Mobile No.\n");
			printf("================================================================================================================================================\n");
			while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
			&p->mobile_no) != EOF) {
				if(strcmp(str, p->lname) == 0) {
					count++;
					printf("%-10d %-15s %-15s %-15s %-20s %-10s %-25s\t %0.0lf\n ", count, p->fname, p->mname, 
					p->lname, p->address,p->sex,p->mail, p->mobile_no); 
				}
			}
	
	
			fclose(fp);
			printf("===============================================================================================================================================\n");
		}	
		else if(strcmp(column, "sex") == 0) {
			printf("================================================================================================================================================\n");
			printf("Sr No.\t First Name\t Middle Name\t Last  Name\t   Address\t \t  Sex\t \tE-mail\t\t\t Mobile No.\n");
			printf("================================================================================================================================================\n");
			while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
			&p->mobile_no) != EOF) {
				if(strcmp(str, p->sex) == 0) {
					count++;
					printf("%-10d %-15s %-15s %-15s %-20s %-10s %-25s\t %0.0lf\n ", count, p->fname, p->mname, 
					p->lname, p->address,p->sex,p->mail, p->mobile_no); 
				}
			}
	
	
			fclose(fp);
			printf("===============================================================================================================================================\n");
		}
		else if(strcmp(column, "address") == 0) {
			printf("================================================================================================================================================\n");
			printf("Sr No.\t First Name\t Middle Name\t Last  Name\t   Address\t \t  Sex\t \tE-mail\t\t\t Mobile No.\n");
			printf("================================================================================================================================================\n");
			while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
			&p->mobile_no) != EOF) {
				if(strcmp(str, p->address) == 0) {
					count++;
					printf("%-10d %-15s %-15s %-15s %-20s %-10s %-25s\t %0.0lf\n ", count, p->fname, p->mname, 
					p->lname, p->address,p->sex,p->mail, p->mobile_no); 
				}
			}
	
	
			fclose(fp);
			printf("===============================================================================================================================================\n");
		}
		if(count == 0) {
			printf("Record not found.\n");
			printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");
		}
		else {
			printf("Records found.\n");
			printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");
		}
		
	}
}

/* Delete the perticular record based on mobile no.
   Input: phonebook *p, structure; take double mn, mobile no
   Output: If c = y, delete the record, else if c = n call menu(p), listrecord(p, 1) and confirm(p, DR) */
int deleterecord(phonebook *p) {
	listrecord(p, 1);
	double mn;
	int count = 0;
	printf("Enter Mobile No: ");
	scanf(" %lf", &mn);
	FILE *fp = fopen("record.txt","a+");//r
	FILE *fpb = fopen("backup.txt","a+");//w
	if(fpb == NULL) {
		perror("File opened failed:");
		return errno;
	}
	if(fp == NULL) {
		perror("File opened failed:");
		return errno;
	}
	else {
		char c;
	up:	printf("Are you sure want to delete?[y/n]");
		scanf(" %c", &c);
		if(c == 'y' || c == 'Y') {
			while(fscanf(fp,"%s\n %s\n %s\n %s\n %s\n %s\n %lf\n", p->fname, p->mname, p->lname, p->address, p->sex, p->mail, 
			&p->mobile_no) != EOF) {
				if(mn == p->mobile_no) {
					count ++;
				}
				else {
				      		fprintf(fpb,"%s %s %s %s %s %s %0.0lf", p->fname, p->mname, p->lname, p->address, p->sex, 							p->mail, p->mobile_no);
						fprintf(fpb, "\n");
				}
			}
			fclose(fpb);
			fclose(fp);
			//copyfile
			system("rm record.txt");
			system("mv backup.txt record.txt");
			if(count > 0) {
				printf("*******************************\n");
				printf("record deleted successfully.\n");
				printf("*******************************\n");
				listrecord(p, 1);
			}
			
			else {
				printf("--------------------------------------\n");
				printf("Record not found.\n");
				printf("--------------------------------------\n");
			}
		}
		else if(c == 'n' || c == 'N') {
			menu(p);
			listrecord(p, 1);
		}
		else {
			printf("--------------------------------------\n");
			printf(" Choose proper option.\n");
			printf("--------------------------------------\n");
			goto up;
		}
	}
	
	confirm(p, DR);
	return 0;
}

/* Exit the Application after 5 seconds*/
void exitapp() {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tClosing Application\n");
	printf("\t\t\t\t\t\t\t\t   Please wait...\n");
	sleep(5);
	printf("\n\n\t\t\t\t\t\t\tApplication closed. Thank you for visiting.\n");
	printf("\t\t\t\t\t\t**********************************************************\n\n\n");
	exit(0);
}

















