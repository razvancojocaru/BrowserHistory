//Cojocaru Mihail-Razvan 313CA
#include <iostream>
#include <stdlib.h>
using namespace std;

template <typename T>struct Node {
//Fiecare nod al listei retine un vector si dimensiunea acestuia
public:
 	int size;
	T* v;
	Node<T> *next;
	Node<T> *prev;
};
 
template <typename T>class LinkedList{
public:
 
	Node<T> *pfirst, *plast;
 

 
	//Constructor
	LinkedList(){
      	pfirst = plast = NULL;
    }
	//Destructor
	~LinkedList(){
		Node<T> *paux;
		paux = pfirst;
		while (paux) {
			paux = paux->next;
			delete paux->prev;
		}
		delete paux;
	}
 
	/*Adauga un nod cu valoarea == value la inceputul listei */
	void addFirst(T* value, int dim){
		Node<T> *paux;

		paux = new Node<T>;
		paux->v = value;
		paux->size = dim;
		paux->prev = NULL;
		paux->next = pfirst;

		if (pfirst != NULL) pfirst->prev = paux;
		pfirst = paux;

		if (plast==NULL) plast=pfirst;	
	}
	
	/*Adauga un nod cu valoarea == value la sfarsitul listei */
	void addLast(T* value, int dim){
		Node<T> *paux;
		paux = new Node<T>;
		paux->v = value;
		paux->size = dim;
		paux->prev = plast;
		paux->next = NULL;

		if (plast != NULL) plast->next = paux;
		plast = paux;
		if (pfirst == NULL) pfirst = plast;
	}
 
	/*Elimina elementul de la inceputul listei si intoarce valoarea acestuia*/
	T* removeFirst(){
		Node<T> *paux; T* aux;
		if (pfirst != NULL) {
			paux = pfirst->next;
			aux = pfirst->v; //???
			if (pfirst == plast) plast = NULL;
			delete pfirst;
			pfirst = paux;
			if (pfirst != NULL) pfirst->prev = NULL;
		}
		else cout<<"Error 101 - The list is empty"<<endl; 
		return aux;
	}
 
	/*Elimina elementul de la sfarsitul listei listei si intoarce valoarea acestuia*/
	T* removeLast(){
		Node<T> *paux; T* aux;
		if (plast != NULL) {
			paux = plast->prev;
			aux = plast->v; //???
			if (pfirst == plast) pfirst = NULL;
			delete plast;
			plast = paux;
			if (plast != NULL) plast->next = NULL;
		}
		else cout<<"Error 102 - The list is empty"<<endl;
		return aux;
	}
 
 	void removeNode(int ind) {
 		Node<T> *paux;
 		paux = pfirst;
 		//indexul numeroteaza primul nod(pfirst) cu 0, ultimul cu size-1;
 		for (int i=0; i<ind; i++) {
 			paux = paux->next;
 		}
 		paux->prev->next = paux->next;
 		paux->next->prev = paux->prev;
 		delete paux;	
 	}
 
	/*Intoarce 1 daca lista este vida, 0 altfel*/
	int isEmpty() {
		return (pfirst == NULL);
	}

};
