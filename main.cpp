//Cojocaru Mihail-Razvan 313CA

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "deque.h"
#include <stdlib.h>
using namespace std;

//structura folosita in deque, pentru a retine ziua si numele fiecarui
//url accesat
struct entry {
	int day;
	char url[60];
};


int maxday=30;

//Facem verificari pentru a ne asigura ca nu accesam elemente invalide din deque
//Bucla while realizeaza stergerea intrarilor mai vechi decat maxday
void day_passes(int curentday, deque<entry> *q) {
	entry curent;
	if ( q->empty() ) return;
	curent = q->back();
	while ( curent.day <= curentday - maxday ) {
		q->pop_back();
		if ( q->empty() ) return;
		curent = q->back();
	}
}

//Introducem in deque un url (cu push_front)
//Folosim structura de tipul entry pentru a retine ziua accesarii si numele url
void access_page(int curentday, deque<entry> *q) {
	entry curent;
	curent.day = curentday;
	cin >> curent.url;
	q->push_front(curent);
}

//Citim ziua pana la care va fi sters istoricul
//Facem verificari pentru a nu accesa zone de memorie invalide
//Stergem elementele mai noi decat ziua citita, 
//de la front spre back, cu pop_front
void clear_recent_history(int curentday, deque<entry> *q) {
	int no_days;
	cin >> no_days;
	entry curent;
	if ( q->empty() ) return;
	curent = q->front();
	while ( curent.day > curentday - no_days ) { //???
		q->pop_front();
		if ( q->empty() ) return;
		curent = q->front();
	}
}

//Citim noul numar maxim de zile
//Facem verificari pentru a nu accesa zone de memorie invalide
//Stergem elementele mai vechi decat noul maxday, 
//de la back spre front, cu pop_back
void set_max_days(int curentday, deque<entry> *q) {
	cin >> maxday;
	entry curent;
	if ( q->empty() ) return;
	curent = q->back();
	while ( curent.day <= curentday - maxday ) { //???
		q->pop_back();
		if ( q->empty() ) return;
		curent = q->back();
	}	
}

//Afiseaza intrarea din deque de pe pozitia index, folosind "at"
void show_entry(deque<entry> *q) {
	int index;
	entry curent;
	
	cin >> index;
	curent = q->at(index);
	cout << "ENTRY " << index << ":" << endl;
	cout << curent.day << " " << curent.url << endl;
}

//Sterge intrarea din deque de la pozitia index, folosind "erase"
void delete_entry(deque<entry> *q) {
	int index;
	cin >> index;
	q->erase( index );
}

//Afiseaza toate elementele din deque, printr-o bucla for de la 
//0 la dimensiunea deque-ului("getsize"), folosind "at"
void show_history(int curentday, deque<entry> *q) {
	entry curent;
	cout << "HISTORY:" << endl;
	cout << "Current day: " << curentday << endl;
	for (int i=0 ; i<q->getsize() ; i++ ) {
		curent = q->at(i);
		cout << curent.day << " " << curent.url << endl;
	}
}

//Citeste intrari din fisierul "name"
void recover_history(int curentday, deque<entry> *q) {
	FILE *f;
	char name[40];
	int n;
	entry curent;
	
	cin >> name;
	//Verificare daca fisierul este valid
	if ( (f = fopen( name, "rt")) == NULL ) {
		cout << "Error!";
	return;
	}
	
	fscanf(f, "%d", &n);
	for ( int i=0; i<n; i++ ) {
		fscanf(f, "%d", &curent.day);
		fscanf(f, "%s", curent.url);
		//Daca intrarile din fisierul primit sunt prea vechi, se iese
		//din bucla for
		if (curent.day <= curentday - maxday) continue;
		
		//Intrarile sunt adaugate la sfarsitul deque-ului
		q->push_back(curent);
	}
	
	fclose(f);
}



int main() {

char command[30];
int n;
int curentday=0;
//Citim numarul de elemente ale vectorilor din implementarea deque-ului
cin >> n;
//Definim deque ca pointer, pentru a putea fi modificat de functii
deque<entry> *q = new deque<entry>(n);

while (cin >> command) {
	if ( strcmp(command, "DAY_PASSES") == 0 ) { 
		//Ziua curenta este modificata in afara functiei,
		//deoarece este variabila locala
		curentday++;
		day_passes(curentday,q);
	}
	
	if ( strcmp(command, "ACCESS_PAGE") == 0 ) { 
		access_page(curentday,q);
	}
	
	if ( strcmp(command, "CLEAR_RECENT_HISTORY") == 0 ) { 
		clear_recent_history(curentday,q);
	}
	
	if ( strcmp(command, "SET_MAX_DAYS") == 0 ) { 
		set_max_days(curentday,q);
	}

	if ( strcmp(command, "SHOW_ENTRY") == 0 ) { 
		show_entry(q);
	}

	if ( strcmp(command, "DELETE_ENTRY") == 0 ) { 
		delete_entry(q);
	}

	if ( strcmp(command, "SHOW_HISTORY") == 0 ) { 
		show_history(curentday,q);
	}

	if ( strcmp(command, "RECOVER_HISTORY") == 0 ) { 
		recover_history(curentday,q);
	}

}

return 0;
}
