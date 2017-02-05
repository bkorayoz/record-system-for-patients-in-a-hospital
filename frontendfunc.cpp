/* Author
* Student Name: Bülent Koray Öz
* Student ID: 150130281
* Date: 18.10.2016
*/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include "backendfunc.h"
#include "frontendfunc.h"

STATUS status;

backoop back;

using namespace std;

int main(void) {

	char choice;
	status = back.create();
	while (status == ON) {
		//system("cls");  //windows icin
		//system("clear") //ubuntu icin
		menu_print();
		cin >> choice;
		functions(choice);
	}
	return EXIT_SUCCESS;
}

void menu_print() {
	cout << endl;
	cout << "Please select the operation to perforn and enter the operation code" << endl;
	cout << "(P) Print all of the patient records," << endl;
	cout << "(B) Search the data by the branch name," << endl;
	cout << "(C) Search the data by the polyclinic number," << endl;
	cout << "(I) Insert a new patient record," << endl;
	cout << "(R) Remove the patient record," << endl;
	cout << "(E) Exit the program," << endl;
	cout << "Your selection is:";

}

void functions(char operation) {
	switch (operation) {	
	case 'P': case 'p':
		front_print();
		break;
	case 'B': case 'b':
		front_searchBranch();
		break;
	case 'C': case 'c':
		front_searchPolyclinic();
		break;
	case 'I': case 'i':
		front_insert();
		break;
	case 'R': case 'r':
		front_remove();
		break;
	case 'E': case 'e':
		status = back.exit();
		break;
	default:
		cout << endl << "Wrong choice! Try again!" << endl;
		break;
	}
}

void front_print() {

	back.print();

}

void front_searchBranch() {
	char search_term[BRANCHNAME];
	int found = 0;
	cout << endl << "The program is case sensitive. Use uppercase letters!";
	cout << endl << "Enter the branch name you want to search: ";
	cin.ignore(1000, '\n');
	cin.getline(search_term, BRANCHNAME);
	found = back.search_branch(search_term);
	cout << endl;
	cout << found << " records have been found." << endl;	
}

void front_searchPolyclinic() {

	int search_term, found;
	cout << "\n" << "Enter polyclinic number you want to search: ";
	cin >> search_term;
	found = back.search_polyclinic(search_term);
	cout << endl;
	cout << found << " records have been found." << endl;
}

void front_insert() {
	
	RECORD newrecord;
	int sira;
	bool control = true;
	cout << endl << "The program is case sensitive. Use uppercase letters!";
	cout << endl << "Enter the name of new patient :";
	cin.ignore(1000, '\n');
	cin.getline(newrecord.name, NAME);
	cout << "Enter the doctor's name :";
	cin.getline(newrecord.doctorName, DOCTORNAME);
	cout << "What is the diagnosis : ";
	cin.getline(newrecord.diagnosis, DIAGNOSIS);
	while (control) {
		cout << "What is the patient number :";
		cin >> newrecord.patientNumber;
		if (newrecord.patientNumber >= 1000) control = false;
		else cout << "Patient number must be an interger with 4 digits." << endl;
	}
	cout << "What is the polyclinic number :";
	cin >> newrecord.polyclinicNum;
	cout << "Enter the branch name :";
	cin.ignore(1000, '\n');
	cin.getline(newrecord.branchName, BRANCHNAME);
	sira = back.requirement(newrecord); // yeni kayit in eklenebilecegi indis fonksiyondan donuyor. 0 donerse sartlar saglanmamis.
	if (sira) {
		back.insert(&newrecord, sira);
		cout << endl << "kayit eklendi!" << endl;
	}
}

void front_remove() {

	int patientnumber;
	cout << "Enter the patient number you want to remove: ";
	cin >> patientnumber;
	back.remove(patientnumber);
	cout << endl << "Record specified by the patient number is removed." << endl;
}

