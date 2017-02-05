/* Author
 * Student Name: Bülent Koray Öz
 * Student ID: 150130281
 * Date: 18.10.2016
 */
#ifndef STRUCT_H
#define STRUCT_H


#define NAME 30
#define DOCTORNAME 30
#define DIAGNOSIS 30
#define BRANCHNAME 20

typedef struct patient_record { // kayitlarin tutuldugu struct
	
	char name[NAME], doctorName[DOCTORNAME], diagnosis[DIAGNOSIS];
	int patientNumber, polyclinicNum;
	char branchName[BRANCHNAME];

}RECORD;

/* Requirement struct i insert ve remove islemlerini yaparken istenen requirementlarin saglanip saglanmadiginin daha kolay kontrol edilmesi icin
	olusturuldu. requirement struct turunde bir array e(info) her branch name icin, o branch name in sahip oldugu toplam polyclinic sayisi (1 veya 2)
	tutuluyor. Ayrica polyclinicNum matrix inde, her satir bir polyclinic i temsil ediyor. Birinci sutunda polyclinic number, ikinci sutunda ise 
	o polyclinic number a ait siradaki boslugun indis i tutuluyor. Ornegin, polyclinicNum[0][0] = 13, polyclinicNum[0][1] = 14 ise 
	13 numarali polyclinic e yeni kayit records dizisinin 14 numarali indisine yazilabilir.*/
typedef struct requirement { 

	int polyclinicNum [2][2];
	char branchName[BRANCHNAME];
	int polyclinicSayisi;

}INFO;

enum STATUS { ON, OFF }; // programin acik/kapali konumunun kontrol edilmesini saglayan degiskenler.

#endif // !STRUCT_H