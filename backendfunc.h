/* Author
* Student Name: Bülent Koray Öz
* Student ID: 150130281
* Date: 18.10.2016
*/

#ifndef BACKENDFUNC_H
#define BACKENDFUNC_H

#include <iostream>
#include "structs.h"

typedef struct backend{

	FILE* record_book;
	RECORD* records;
	INFO* info;
	STATUS create(); // records ve info dizilerini olusturur. Dosyayi acar ve bilgileri records dizisine kaydeder.
	void print(); // kayitlari ekrana yazdirilir.
	int search_branch(char selection[]); // branch name ile arama yapilir.
	int search_polyclinic(int selection);// polyclinic number ile arama yapilir.
	void insert(RECORD* newRecord, int indisno); // yeni kayit eklenir.
	void remove(int patientNum); // Kayit silinir.
	STATUS exit(); // dizi dosyaya kaydedilir ve program sonlandirilir.
	void sort(); // dizide ki kayitlar sort edilir.
	int requirement(RECORD newrecord); // yeni kayit eklenecegi zaman girilen bilgilerin sartlari saglayip saglamadigi kontrol edilir.
	int maxrecord = 30, maxbranch = 2;
	int total_record;
	bool start; // sort fonksiyonunun kontrolunde kulaniliyor. true ise dosya acilisi, false ise sonraki donguler.
	void increase(int kayit, int bilgi); // verilerin tutuldugu dizi boyutlarinin programin calismasi sirasinda dynamic olarak arttirilmasini sagliyor.
}backoop;
#endif