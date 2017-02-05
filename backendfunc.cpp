/* Author
* Student Name: Bülent Koray Öz
* Student ID: 150130281
* Date: 18.10.2016
*/

#include "backendfunc.h"
#include "frontendfunc.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>

using namespace std;

STATUS backend::create() {
	int control;
	records = new RECORD[maxrecord];
	info = new INFO[maxbranch];
	for (int i = 0; i < maxrecord; i++) {
		*(records + i) = { ' ', ' ', ' ', ' ', ' ', ' ' };
	}
	strcpy(info->branchName, "internal");
	strcpy((info + 1)->branchName, "ophthalmology");
	info->polyclinicNum[0][0] = 12;
	info->polyclinicNum[0][1] = 9;
	info->polyclinicNum[1][0] = 13;
	info->polyclinicNum[1][1] = 14;
	info->polyclinicSayisi = 2;
	(info + 1)->polyclinicNum[0][0] = 10;
	(info + 1)->polyclinicNum[0][1] = 30;
	(info + 1)->polyclinicNum[1][0] = 0;
	(info + 1)->polyclinicNum[1][1] = 0;
	(info + 1)->polyclinicSayisi = 1;
	
	if (record_book = fopen("database.txt", "r+")) {
		if (record_book == NULL) {		
			cerr << "File could not be openned!" << endl;
			return OFF;
		}

		for (int i = 0; !(feof(record_book)); i++) {
			fscanf(record_book, "\n%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%s", records[i].name, records[i].doctorName, records[i].diagnosis, &records[i].patientNumber, &records[i].polyclinicNum, records[i].branchName);
			if (feof(record_book)) break;	
		}
		start = true;
		backoop::sort(); // diziye aktarilan kayitlar alfabetik siraya dizilir.
	}
	else {
		start = false;
		if (!(record_book = fopen("database.txt", "w+"))) {
			cerr << "File could not be openned!" << endl;
			return OFF;
		}
	}
	return ON; // Dosya ve diziler sorunsuz olusturuldu. Program baslayabilir.
}


void backend::print() {

	for (int i = 0; i < maxrecord; i++) {
		if ((records + i)->polyclinicNum == 0) {
			cout << endl;
		}
		else {
			cout << (records + i)->name << "\t" << (records + i)->doctorName << "\t" << (records + i)->diagnosis;
			cout << "\t" << (records + i)->patientNumber << "\t" << (records + i)->polyclinicNum << "\t" << (records + i)->branchName << endl;
		}	
	}
}

int backend::search_branch(char selection[]) {
	int count = 0;
	for (int i = 0; i < maxrecord; i++) {
		if ((strcmp(selection, (records + i)->branchName) == 0)) {
			cout << count + 1 << "\t" << (records + i)->name << "\t" << (records + i)->doctorName << "\t" << (records + i)->diagnosis;
			cout << "\t" << (records + i)->patientNumber << "\t" << (records + i)->polyclinicNum << "\t" << (records + i)->branchName << endl;
			count++;
		}
	}
	return count;
}

int backend::search_polyclinic(int selection) {
	int count = 0;
	for (int i = 0; i < maxrecord; i++) {
		if (selection == ((records + i)->polyclinicNum)) {
			cout << count + 1 << "\t" << (records + i)->name << "\t" << (records + i)->doctorName << "\t" << (records + i)->diagnosis;
			cout << "\t" << (records + i)->patientNumber << "\t" << (records + i)->polyclinicNum << "\t" << (records + i)->branchName << endl;
			count++;
		}
	}
	return count;
}

void backend::insert(RECORD* newRecord, int indisno) { 
	*(records + indisno) = *newRecord;
}

void backend::remove(int patientNum) {
	for (int i = 0; i < maxrecord; i++) {
		if ((records + i)->patientNumber == patientNum) {
			*(records + i) = { ' ', ' ', ' ', ' ', ' ', ' ' };
		}
	}
}

void backend::sort() { 
	if (start == true) { // program acilisinda veriler dosyadan diziye atildiktan sonra siralama islemi.
		RECORD* temp = new RECORD[maxrecord];
		for (int i = 0; i < maxrecord; i++) {
			*(temp + i) = { ' ', ' ', ' ', ' ', ' ', ' ' };
		}
		int count[3];
		count[0] = 9;
		count[1] = 14;
		count[2] = 30;
		for (int i = 0; i < maxrecord; i++) {

			if ((records + i)->polyclinicNum == info->polyclinicNum[0][0]) {
				temp[count[0] - 1] = *(records + i);
				count[0]--;
			}
			else if ((records + i)->polyclinicNum == info->polyclinicNum[1][0]) {
				temp[count[1] - 1] = *(records + i);
				count[1]--;
			}
			else if ((records + i)->polyclinicNum == (info + 1)->polyclinicNum[0][0]) {
				temp[count[2] - 1] = *(records + i);
				count[2]--;
			}
		}
		for (int i = 0; i < maxrecord; i++) {
			*(records + i) = *(temp + i);
		}

		delete[] temp;
		start = false;
	}
	else { // insert ve remove islemlerinden sonra siralayamadim.
		RECORD* temp = new RECORD[maxrecord];
//////////////////////////////////////////////////////////////
		delete[] temp;
	}
}

int backend::requirement(RECORD newrecord) {

	int branch;
	int polynumber;

	for (int i = 0; i < maxbranch; i++) { //girilen polyclinic numberin daha once assign edilip edilmedigi ve yer olup olmadigi kontrol ediliyor. 

		if ((info + i)->polyclinicNum[0][0] == newrecord.polyclinicNum) {

			if (strcmp((info + i)->branchName, newrecord.branchName) == 0) {

				if ((info + i)->polyclinicNum[0][1] % 10 != 0) { // yer varsa. 	polyclinicNum[0][1] yeni kayit icin indis degeri tututuyordu. 
																//Eger 10 un katlarinda bir deger tutuyorsa bu polyclinic e kayit edilmis 10 kayit vardir.				
				}
				else
				{
					cerr << endl << "There is not enough space in this polyclinic!" << endl;
					return 0;
				}
			}
			else {
				cerr << endl << "Same polyclinic was assigned to another branch!" << endl; // ayni polyclinic number baska branche atanmis.
				return 0;
			}
		}
		else if ((info + i)->polyclinicNum[1][0] == newrecord.polyclinicNum) {
			if (strcmp((info + i)->branchName, newrecord.branchName) == 0) {

				if ((info + i)->polyclinicNum[1][1] % 10 != 0) { // yer varsa
				}
				else
				{
					cerr << endl << "There is not enough space in this polyclinic!" << endl;
					return 0;
				}
			}
			else {
				cerr << endl << "Same polyclinic was assigned to another branch!" << endl; // ayni poly num baska branchte
				return 0;
			}
		}
	}
	for (int i = 0; i < maxbranch; i++) {
		if (strcmp((info + i)->branchName, newrecord.branchName) == 0) {
			branch = i;
			if ((info + i)->polyclinicSayisi == 1) {// polyclinic sayisi 1 ise
				if ((info + i)->polyclinicNum[0][0] == newrecord.polyclinicNum) {//var olan polyclinic num
					if ((info + i)->polyclinicNum[0][1] % 10 != 0) {// yer varsa
						(info + i)->polyclinicNum[0][1]++;
						return (info + i)->polyclinicNum[0][1] - 1; // siradaki yazilacak yer i burada arttiriyotum yani simdi yazilacak yer  in indisi-1
					}
					else {
						cerr << endl << "There is not enough space in this polyclinic!" << endl;
						return 0;
					}
				}
				else// var olmayan polyclinic number
				{
					increase(10, 0);
					(info + maxbranch - 1)->polyclinicNum[1][0] = newrecord.polyclinicNum;
					(info + maxbranch - 1)->polyclinicNum[1][1] = maxrecord - 10 + 1;
					(info + maxbranch - 1)->polyclinicSayisi = 2;
					return (info + maxbranch - 1)->polyclinicNum[1][1] - 1;
				}
			}
			else if ((info + i)->polyclinicSayisi == 2) {// polyclinic sayisi 2 ise
				if ((info + i)->polyclinicNum[0][0] == newrecord.polyclinicNum) {//var olan polyclinic num 1
					if ((info + i)->polyclinicNum[0][1] % 10 != 0) {// yer varsa
						(info + i)->polyclinicNum[0][1]++;
						return (info + i)->polyclinicNum[0][1] - 1;
					}
					else {
						cerr << endl << "There is not enough space in this polyclinic!" << endl;
						return 0;
					}
				}
				else if ((info + i)->polyclinicNum[1][0] == newrecord.polyclinicNum) // var olan polyclinic num 2
				{
					if ((info + i)->polyclinicNum[1][1] % 10 != 0) {// yer varsa
						(info + i)->polyclinicNum[1][1]++;
						return (info + i)->polyclinicNum[1][1] - 1;
					}
					else {
						cerr << endl << "There is not enough space in this polyclinic!" << endl;
						return 0;
					}
				}
				else// var olmayan polyclinic num
				{
					cerr << endl << "there are already 2 polyclinics assigned to this branch!" << endl;
					return 0;
				}
			}
		}
		else if (i == maxbranch - 1) { // varolmayan branch
			increase(10, 1);
			
			strcpy((info + maxbranch - 1)->branchName, newrecord.branchName);
			(info + maxbranch - 1)->polyclinicNum[0][0] = newrecord.polyclinicNum;
			(info + maxbranch - 1)->polyclinicNum[0][1] = maxrecord - 10 + 1;
			(info + maxbranch - 1)->polyclinicSayisi = 1;
			return (info + maxbranch - 1)->polyclinicNum[0][1] - 1;
		}
	}
}

void backend::increase(int kayit, int bilgi) {
	if (kayit != 0) {
		
		RECORD* temp = new RECORD[maxrecord];
		for (int i = 0; i < maxrecord; i++) {
			*(temp + i) = *(records + i);		
		}
		delete[]records;
		maxrecord += kayit;
		records = new RECORD[maxrecord];
		for (int i = 0; i < maxrecord; i++) {
			*(records + i) = { ' ', ' ', ' ', ' ', ' ', ' ' };
		}
		for (int i = 0; i < maxrecord; i++) {
			*(records + i) = *(temp + i);
		}
		delete[]temp;
	}
	if (bilgi != 0) {
		INFO* temp = new INFO[maxbranch];
		for (int i = 0; i < maxbranch; i++) {
			*(temp + i) = *(info + i);
		}
		delete[]info;
		maxbranch += bilgi;
		info = new INFO[maxbranch];
		for (int i = 0; i < maxbranch; i++) {
			*(info + i) = { 0,' ',0 };
		}
		for (int i = 0; i < maxbranch; i++) {
			*(info + i) = *(temp + i);
		}
		delete[]temp;
	}
}

STATUS backend::exit() {
	/// Dizideki bilgiler dosyaya kaydedilir.
	rewind(record_book);
	for (int i = 0; i < maxrecord; i++) {
		fprintf(record_book, "%s\t%s\t%s\t%d\t%d\t%s\n", records[i].name, records[i].doctorName, records[i].diagnosis, records[i].patientNumber, records[i].polyclinicNum, records[i].branchName);
	}
	fclose(record_book);
	delete[] records;
	delete[] info;
	return OFF;
}
