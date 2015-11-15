
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
 
/* structure of phonebook */
typedef struct phonebook {
	char fname[35];
	char mname[35];
	char lname[30];
	double mobile_no;
	char address[50];
	char sex[8];
	char mail[100];
}phonebook;
void menu(phonebook *p);			//for display menu
void menuchoice(phonebook *p);			//for choosing any choice to do operations
int addrecord(phonebook *p);			// for adding records
int listrecord(phonebook *p, int flag);		// for display records
int modifyrecord(phonebook *p);			// for modify the records
int deleterecord(phonebook *p);			// for delete the records
int searchrecord(phonebook *p);			// for searching the records
int save(char *data);				// for saving the record into file called by addrecord(p)
int backup(char *fname, char*lname, phonebook *p);// for copying the all data of record.txt file into backup.txt except record which have 							  //to delete
void confirm(phonebook *p, int fun);		// for confirmation about whether to do continue or not
void confirmlistcont(phonebook *p);		/*for confirmation of user to use the application for next operations after seeing the all 							list of records.this function is only for listrecord(p)*/
char *convert(char *name);			// for converting the all input into first letter to upper and remaining all to lower
void search(phonebook *p, char *str, char *column); // called by searchrecord(p) for searching the records
void searchmenu(phonebook *p);			// Print the search menu
void exitapp(); 				// after calling exit the application after 5 seconds.
void login();					// for authentication
void loading(int sec);				// for loading
void confirmaddrecord(phonebook *p);		// for confirmation of adding the record
int isavailable(phonebook *p);			// for checking record is present or not

