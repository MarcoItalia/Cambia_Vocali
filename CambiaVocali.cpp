#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

class Nodo{
public:
    char vocale;
    char vocale2;
    Nodo* succ;
    Nodo* prec;

    friend ostream& operator<<(ostream& out, const Nodo& nd);
};

ostream& operator<<(ostream& out, const Nodo& nd){
    char val=nd.vocale2;
    out<<val;
    return out;
}

class Lista{
Nodo* testa;
public:
    Lista() {testa=nullptr;}
    ~Lista();
    Nodo* getTesta() {return testa;}

    // inserimento in testa
    void inserisci(char val);
    void inserisci(Nodo* precedente, char val);
    void inserisci_in_coda(char val);
    void mod_val2(Nodo* puntato, char voc);

    Nodo* ricerca(char val);
    void rimuovi(char val);

    friend ostream& operator<<(ostream& out, const Lista& ls);
};

Lista::~Lista(){
    Nodo* iter = this->testa;

    while(iter!=nullptr){
        Nodo* temp = iter->succ;
        delete iter;
        iter = temp;
    }
}

ostream& operator<<(ostream& out, const Lista& ls){
    Nodo* iter=ls.testa; //get testa
    while(iter!=nullptr){
        out << iter->vocale << ":" << iter->vocale2<<" --> ";
        iter = iter->succ;
    }
    out << "NULL" << endl;
    return out;
}

void Lista::inserisci(char val){
    Nodo* nuovo = new Nodo;
    nuovo->vocale = val;
    nuovo->prec=nullptr;
    nuovo->succ = this->testa;
    if(this->testa)
        this->testa->prec=nuovo;

    this->testa = nuovo;
}

void Lista::inserisci(Nodo* precedente, char val){
    Nodo* nuovo = new Nodo;
    nuovo->vocale = val;
    nuovo->succ=precedente->succ;
    precedente->succ->prec = nuovo;
    precedente->succ = nuovo;
    nuovo->prec = precedente;
}

void Lista::inserisci_in_coda(char val){
    
    if(this->testa == nullptr){
        inserisci(val);
        return;
    }

    Nodo* nuovo = new Nodo;
    Nodo* iter = this->testa;
    nuovo->vocale = val;
    while(iter->succ!=nullptr)
        iter = iter->succ;
    iter->succ=nuovo;
    nuovo->succ=nullptr;
    nuovo->prec=iter;

}

Nodo* Lista::ricerca(char val){
    Nodo *p;

    for(p=this->testa;p!=nullptr;p = p->succ)
        if(p->vocale==val)
            return p;

    return nullptr;
}

void Lista::rimuovi(char val){

    Nodo* nd;

    if(this->testa == nullptr)
        cout << "Lista vuota: impossibile rimuovere elementi."<<endl;
    else if(this->testa->vocale == val){
        nd = this->testa;
        this->testa = this->testa->succ;
        this->testa->prec=nullptr;
        delete nd;
    }
    else{
        
        nd = this->testa->succ;
        while((nd!=nullptr)&&(nd->vocale!= val)){
            nd = nd->succ;
        }

        if(nd!=nullptr){
            if(nd->succ==nullptr)
                nd->prec->succ = nullptr;
            else {
                nd->prec->succ = nd->succ;
                nd->succ->prec = nd->prec;
            }
            
            delete nd;
        }
        else
            cout << "Elemento non presente nella lista." << endl;

    }
}

void Lista::mod_val2(Nodo* puntato, char voc){
    puntato->vocale2=voc;
}

int main(){
    Lista lista;
    Nodo* p;
    string S;


    lista.inserisci('u');
    lista.inserisci('o');
    lista.inserisci('i');
    lista.inserisci('e');
    lista.inserisci('a');

    for(int task=0;task<100;task++){
        for(int vi=0;vi<5;vi++){
            in>>S;

            p=lista.ricerca(S[0]);
            lista.mod_val2(p, S[2]);
        }
        getline(in,S);
        S=S.substr(1);
        for(int i=0;i<S.length();i++){
            p=lista.ricerca(S[i]);
            if(p)
                out<<*p;
            else out<<S[i];
        }
        out<<endl;
    }


return 0;
}
