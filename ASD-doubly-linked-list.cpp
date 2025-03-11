// FILE DA MODIFICARE
#include <iostream>
#include <fstream>
#include "ASD-doubly-linked-list.h"

using namespace list;
using namespace std;

/*Descrizione da come e' fatta  la struttura node. */
/*I dettagli interni non saranno visibili dal main*/
struct list::node {  
  Elem info;
  node *prev;
  node *next;
};

/**************************************************/
/*      funzioni da implementare                    */
/**************************************************/
  
/* crea la lista vuota */
void list::createEmpty(List& li){
  li = new node;
  li->next = li;
  li->prev = li;
}

/* "smantella" la lista (tranne la sentinella) */
void list::clear(List& li){
  node* current = li->next;
  while (current != li) {
    node* toDelete = current;
    current = current->next;
    delete toDelete;
  }
  li->next = li;
  li->prev = li;
}

/* restituisce true se la lista e' vuota */
bool list::isEmpty(const List& li){
  return li->next == li;
}

/* restituisce la dimensione della lista */
unsigned int list::size(const List& li){
  unsigned int size = 0;
  node* current = li->next;
  while (current != li) {
    size++;
    current = current->next;
  }
  return size;
}

/* restituisce l'elemento in posizione pos */
/* se pos non e corretta, solleva una eccezione di tipo string*/
Elem list::get(unsigned int pos, const List& li){
    node* current = li->next;
    unsigned int index = 0;
    while (current != li && index < pos) {
      current = current->next;
      index++;
    }
    if (current == li) {
      throw string("Position out of bounds");
    }
    return current->info;
}

/* modifica l'elemento in posizione pos */
/* se pos non e' corretta, solleva una eccezione di tipo string*/
void list::set(unsigned int pos, Elem el, const List& li){
  node* current = li->next;
  unsigned int index = 0;

  while (current != li && index < pos) {
    current = current->next;
    index++;
  }

  if (current == li) {
    throw string("Position out of bounds");
  }

  current->info = el;
}

/* inserisce l'elemento in posizione pos*/
/*shiftando a destra gli altri elementi */
/*se pos non e' corretta, solleva una eccezione di tipo string*/
void list::add(unsigned int pos, Elem el, const List& li){
  node* current = li->next;
  unsigned int index = 0;

  while (current != li && index < pos) {
    current = current->next;
    index++;
  }

  if (current == li && index != pos) {
    throw string("Position out of bounds");
  }

  node* newNode = new node;
  newNode->info = el;
  newNode->next = current;
  newNode->prev = current->prev;
  current->prev->next = newNode;
  current->prev = newNode;
}

/* inserisce l'elemento alla fine della lista */
void list::addRear(Elem el, const List& li){
  node* newNode = new node;
  newNode->info = el;
  newNode->next = li;
  newNode->prev = li->prev;
  li->prev->next = newNode;
  li->prev = newNode;
}

/* inserisce l'elemento all'inizio della lista */
void list::addFront(Elem el, const List& li) {
  node* newNode = new node;
  newNode->info = el;
  newNode->next = li->next;
  newNode->prev = li;
  li->next->prev = newNode;
  li->next = newNode;
}

/* cancella l'elemento in posizione pos dalla lista */
/* se pos non e' corretta, solleva una eccezione di tipo string*/
void list::removePos(unsigned int pos, const List& li){
  node* current = li->next;
  unsigned int index = 0;

  while (current != li && index < pos) {
    current = current->next;
    index++;
  }

  if (current == li) {
    throw string("Position out of bounds");
  }

  current->prev->next = current->next;
  current->next->prev = current->prev;
  delete current;
}

/* cancella tutte le occorrenze dell'elemento elem*/
/*se presenti, dalla lista */
void list::removeEl(Elem el, const List& li){
  node* current = li->next;
  while (current != li) {
    if (current->info == el) {
      node* toDelete = current;
      current->prev->next = current->next;
      current->next->prev = current->prev;
      current = current->next;
      delete toDelete;
    } else {
      current = current->next;
    }
  }
}

/**************************************************/
/*      funzioni implementate                    */
/**************************************************/
  
/* riempie una lista da file */
void list::readFromFile(string name_file, const List& li){
  ifstream infile;
  string read_data;
  infile.open(name_file);
  while (getline (infile,read_data)){
    if(read_data.length()>0){
      addRear(stoi(read_data),li);
    }
  }
}

/* riempie una lista da standard input */
void list::readFromStdin(const List& li){
  cout << "Inserire una sequenza di numeri separati da spazi seguiti da END per terminare\n";
  string read_data;
  cin>>read_data;
  while(read_data!="END"){
    addRear(stoi(read_data),li);
    cin>>read_data;
  }
}

/* stampa la lista */
void list::print(const List& li){
  if(li==li->next){
    cout<<"vuota";
  }
  List cur = li->next;  // q "salta la sentinella" e va alla testa della lista
  while (cur != li) {   
    cout << cur->info;
    cur= cur->next;
    if(cur!=li) cout<<" <-> ";
  }
  cout<<endl;
}

/* produce una string contenendo la lista*/
std::string list::tostring(const List& li){
  string out="";
  if(li==li->next){
    out+="vuota";
  }
  List cur = li->next;  // q "salta la sentinella" e va alla testa della lista
  while (cur != li) {   
    out+=to_string(cur->info);
    cur= cur->next;
    if(cur!=li) out+=" <-> ";
  }
  return out;
}
