       TITLE: Phonebook Application   (Password = admin )
       NAME: Pratik H. Mahajan
       MIS: 111308042
--------------------------------------------------------------
Phonebook Application is a command line based application which can used for storing all our personal information 
in good and required mannar. In some cases there are lot many chances that when we store contact information in 
mobile there may be chance of minimum size or if we store more information then their is no space for storing contact
information so this problem may be reduces by this application.It can be used so easily to store personal information 
quicky and also we can access it quickly.
	This application handle the all personal data like storing name of person, their mobile numbers, address, gender and Email id.
And this is the most important information which can be used to identify any of the person. It also handle data efficiently when 
there is a huge data in database.

Steps to use the Phonebook Application
--------------------------------------------------
There are 3 main files in which the Phonebook Application is divided and they are :
i) Phonebook.h :
	This file includes the all required structure typedef and name of all functions which are used in the another files for inserting, modifying, deleting, searching and display all available records.

ii) Master.c :
	- This file include all implementation of Phonebook.h file. 
	- This file contains code for  validating whether the user is authorized or not. If user fails to attempt more than 3 times then automatically appliction exit.
	- It printf all the menus for doing the various operations on phonebook application.
	- It includes all implementation code of inserting, modifying, deleting, searching and displaying the records.
	- It also contains code for converting the user input into one standard form i.e First letter in capital form and remaining in small form except email
	  Id. 
	
iii) user.c :
	- This file is the user file which is used to call or use all above two files.
	- It contais main() function which contains main login to call all operation of Phonebook Application.

After running the Phonebook Application so the first step is 
	- the Authentication, it ask to enter the password (Default password is : admin)
	- If user is authorized user and enters the correct password then the Phonebook Application is start to opening and then user can perform the operation whatever he wants.

Phonebook Application stores all the data in a file i.e, record.txt.

