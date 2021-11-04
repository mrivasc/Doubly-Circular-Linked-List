#include <iostream>
using namespace std;

/*-Con el uso de una lista circular:
~Hacer una administración de una veterinaria, 
En donde se pida el id, nombre del dueño, raza, peso, edad de la mascota
Que pueda agregar, mostrar por id, y borrar.*/

void menu();

struct Pet{
    int id, age;
    string owner, breed, petName;
    float weight;
    Pet *next, *prev;
};

class CircularList{
    private:
        Pet *head, *last;
    public:
        CircularList();
        ~CircularList();
        void addPet();
        void deletePet();
        void showByID();
        void printAll();
};

CircularList::CircularList(){
    head = last = nullptr;
}

CircularList::~CircularList(){
    Pet *aux=head, *q=nullptr; int n=0;

    if(!head) cout << "~ No hay nodos para eliminar en la lista ~";
    else{
        do{
            q = aux;
            aux = aux->next;
            delete q; n++;
        } while (aux != head);

        if(n==1) cout << "Eliminando 1 nodo...";
        else cout << "Eliminando " << n << " nodos...";

        delete aux, head, last;
    }
}

void CircularList::addPet(){
    Pet *p = new Pet;

    cout << "ID: "; cin >> p->id; cin.ignore();
    cout << "Nombre propietario: "; getline(cin, p->owner);
    cout << "Nombre de la mascota: "; getline(cin, p->petName);
    cout << "Raza: "; getline(cin, p->breed);
    cout << "Peso: "; cin >> p->weight; cin.ignore();
    cout << "Edad mascota: "; cin >> p->age; cin.ignore();

    if(!head){
        head = p;
        last = p;
        head->next = head;
        last->prev = last;
    } else {
        last->next = p;
        p->next = head;
        last = p;
    }
}

void CircularList::deletePet(){
    Pet *aux=head, *q=nullptr; 
    bool found=false; int id=0;

    if(head){
        cout << "ID a eliminar: "; cin >> id;

        do{
            if(aux->id == id){ 
                if(aux == head && aux == last){
                    head = last = nullptr;
                    delete aux;
                } else if(aux == head){
                    head = head->next; 
                    head->prev = last;                  
                    last->next = head;
                    delete aux;
                } else if(aux == last){
                    last = q;
                    q->next = head;
                    head->prev = last;
                    delete aux;
                } else {
                    q->next = aux->next;    
                    aux->next->prev = q;
                    delete aux;
                }
                cout << "Perfil con ID #" << id << " eliminado!\n";
                found = true;
            }
            q = aux;
            aux = aux->next;
        } while(aux != head && found != true);

        if(found==false) cout << "El ID no fue encontrado :(\n";    
    } else
        cout << "La lista esta vacia.\n";
}

void CircularList::printAll(){
    Pet *aux=head;

    if(head){
        do{
            cout << "ID: " << aux->id << endl;
            cout << "Nombre propietario: " << aux->owner << endl;
            cout << "Nombre de la mascota: " << aux->petName << endl;
            cout << "Raza: " << aux->breed << endl;
            cout << "Peso: " << aux->weight << endl;
            cout << "Edad mascota: " << aux->age << endl << endl;    
            aux = aux->next;
        } while(aux != head);
    } else
        cout << "La lista esta vacia.\n";
}

void CircularList::showByID(){
    Pet *aux=head, *q=nullptr; 
    int id=0; bool found=false;

    if(head){
        cout << "ID que desea ver: "; cin >> id; cout<<endl;

        do{
            if(aux->id == id){
                cout << "-- MOSTRANDO #" << id << " --" << endl;
                cout << "Nombre propietario: " << aux->owner << endl;
                cout << "Nombre de la mascota: " << aux->petName << endl;
                cout << "Raza: " << aux->breed << endl;
                cout << "Peso: " << aux->weight << endl;
                cout << "Edad mascota: " << aux->age << endl;
                found = true;
            }  
            aux = aux->next;
        } while (aux != head && found != true);

        if(found==false)
            cout << "El ID no se encuentra en la lista.\n";
    } else
        cout << "La lista esta vacia.\n";
}

int main(){ menu(); }

void menu(){
    int r=0; CircularList L;

    do{
        cout << "\nVETERINARIA KOOL-AID\n\n";
        cout << "1. Agregar datos \n2. Borrar \n3. Mostrar por id \n4. Mostrar lista completa \n5. Salir \n-> "; cin >> r; cout<<endl;

        switch(r){
            case 1: L.addPet();
                break;
            case 2: L.deletePet();
                break;
            case 3: L.showByID();
                break;
            case 4: L.printAll();
                break;
            case 5: break;
            default: cout << "-> Ingrese una opcion valida! <-\n";
                break;
        }
    } while (r!=5);
}