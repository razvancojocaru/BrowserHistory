//Cojocaru Mihail-Razvan 313CA
#include <stdio.h>
#include "list.h"
using namespace std;

template <typename T>class deque {

private:
	LinkedList<T> l;
	int Size;
	int n;
public:
	deque(int N) {
		n = N;
		Size = 0;
		//Indiferent daca deque este gol, ramane in permanenta un nod in lista
		T *v = (T*)malloc(n*sizeof(T));
		l.addFirst(v,0);
	}
	~deque() {
		//Dezalocam vectorii din nodurile ramase
		Node<T> *nod;
		nod = l.pfirst;
		free(nod->v);
		if (nod==l.plast) return;
		while (nod!=l.plast) {
			nod = nod->next;
			free(nod->v);
		}
		free(nod->v);
	}

	//adauga element la inceputul deque
	void push_front( T elem ) {
		Size++;
		//caz special pentru primul element
		if (Size==1) {
			l.pfirst->v[0] = elem;
			l.pfirst->size++;
			return;
		}
		//verifica daca e nevoie de vector nou in lista
		if (l.pfirst->size == n) {
			T *v = (T*)malloc(n*sizeof(T));
			l.addFirst(v,0);		
		}
		
		//elementul este adaugat la sfarsitul vectorului din primul nod
		l.pfirst->v[l.pfirst->size] = elem;
		l.pfirst->size++;
	}
	
	//adauga element la sfarsitul deque	
	void push_back( T elem ) {
		Size++;
		//verifica daca e nevoie de nod nou in lista
		//in caz afirmativ, adauga nod la sfarsitul listei si insereaza elementul
		//la inceputul vectorului creat
		if (l.plast->size == n) {
			T *v = (T*)malloc(n*sizeof(T));
			l.addLast(v,1);
			l.plast->v[0] = elem;
			return;		
		}
		//toate elementele din ultimul nod sunt mutate cu o pozitie la dreapta
		for ( int i=(l.plast->size); i>0; i-- ) {
			l.plast->v[i] = l.plast->v[i-1];
		}
		
		//elementul este adaugat la inceputul vectorului din ultimul nod
		l.plast->v[0] = elem;
		l.plast->size++;
	}
	
	//sterge primul element din deque
	void pop_front() {
		Size--;
		l.pfirst->size--;
		//Verifica daca primul nod este gol, si il sterge in caz afirmativ
		//Daca lista devine goala, ramane un singur nod vid
		if (Size==0) {
			return;
		}
		if ( l.pfirst->size == 0 ) {
			free(l.pfirst->v);
			l.removeFirst();
			return;
		}		
	}
	
	//sterge ultimul element din deque
	void pop_back() {
		Size--;
		l.plast->size--;
		//Verifica daca ultimul nod este gol, si il sterge in caz afirmativ
		//Daca lista devine goala, ramane un singur nod vid
		if (Size==0) {
			return;
		}
		if ( l.plast->size == 0 ) {
			free(l.plast->v);
			l.removeLast();
			return;
		}	
		
		//toate elementele din vectorul ultimului nod,
		//in afara de primul, care se sterge, sunt mutate cu o pozitie
		//spre stanga	
		for ( int i=0; i<(l.plast->size); i++ ) {
			l.plast->v[i] = l.plast->v[i+1];
		}
	}
	
	//Returneaza elementul de pe pozitia index
	T at(int index) {
		Node<T> *nod;
		int i, s=0;
		if (index==0) {
			return this->front();
		}
		if (index==Size-1) {
			return this->back();
		}
		
		//identificam nodul in care se afla elementul cautat
		nod = l.pfirst;
		s = nod->size;
		while ( s <= index ) {
			nod = nod->next;
			s = s + nod->size;
		}
		//returnam elementul, considerand indicii deque 
		//invers fata de indicii vectorului(de la coada spre cap)
		i = s - nod->size;
		return nod->v[nod->size - (index - i + 1)];
	}
	
	//Sterge elementul de pe pozitia index
	void erase(int index) {
		//Folosim o metoda asemanatoare cu at pentru a identifica elementul
		if (index==0) {
			this->pop_front();
			return;
		}
		if (index==Size-1) {
			this->pop_back();
			return;
		}
		Size--;
		Node<T> *nod;
		int i, s=0, ct=0;
		nod = l.pfirst;
		s = nod->size;
		while ( s <= index ) {
			nod = nod->next;
			ct++;
			s = s + nod->size;
		}
		//Daca dupa stergerea elementului, nodul se goleste, stergem nodul
		if (nod->size == 1) {
			free(nod->v);
			l.removeNode(ct);
			return;
		}
		i = s - nod->size;
		i = nod->size - (index - i + 1);

		//Mutam toate elementele de dupa elementul sters cu o pozitie la stanga
		//Astfel, elementele sunt intotdeauna aliniate la stanga
		//(pozitia 0 dintr-un vector nu este niciodata libera)
		nod->size--;
		for ( int j=i; j<(nod->size); j++ ) {
			nod->v[j] = nod->v[j+1];
		}
		
	}
	
	//Intoarce elementul de pe prima pozitie
	T front() {
		return l.pfirst->v[l.pfirst->size - 1];
	}
	
	//Intoarce elementul de pe ultima pozitie
	T back() {
		return l.plast->v[0];
	}
	
	//Returneaza 1 daca deque e gol, 0 in caz contrar
	int empty() {
		return (!Size);
	}
	
	//Returneaza dimensiunea deque
	int getsize() {
		return Size;
	} 
	
};
