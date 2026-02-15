#include <iostream>
using namespace std;


struct Node{
    int data;     // brojot sto go cuvame vo nodot
    Node* next;   // pokazuvac kon sledniot node
};

// FUNKCIJA ZA DODAVANJE NA KRAJ NA LISTATA
void add(Node*& head, int val){
    Node* nov = new Node; // kreirame nov node
    nov->data = val;
    nov->next = nullptr;

    // ako listata e prazna (head e NULL)
    if(head == nullptr){
        head = nov; // noviot jazol stanuva prvi (head)
        return;     // zavrsuvame so funkcijata
    }

    // ako ima elementi, odime do krajot
    Node* t = head;
    while(t->next != nullptr){
        t = t->next;
    }

    // na krajot go dodavame noviot node
    t->next = nov;
}

// FUNKCIJA ZA PECATENJE NA LISTATA
void print(Node* head){
    Node* t = head;
    while(t != nullptr){
        cout << t->data << " ";
        t = t->next;
    }
    cout << endl;
}

// ZADACHA 1: VNESUVANJE I SORTIRANJE PO SEKOE VNESUVANJE
void zadacha1(){
    int n;
    Node* head = nullptr;
    cout << "Kolku elementi: ";
    cin >> n;

    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        add(head, x); // dodavame nov element

        // sega ja sortirame listata so insertion sort
        Node* sorted = nullptr;
        Node* tekoven = head;
        while(tekoven != nullptr){
            Node* sledbenik = tekoven->next;

            // ako sortirana lista e prazna ili treba da se stavi napred
            if(sorted == nullptr || tekoven->data < sorted->data){
                tekoven->next = sorted;
                sorted = tekoven;
            }
            else{
                // najdi pozicija kadе treba da se stavi elementot
                Node* t = sorted;
                while(t->next != nullptr && t->next->data < tekoven->data){
                    t = t->next;
                }
                tekoven->next = t->next;
                t->next = tekoven;
            }
            tekoven = sledbenik;
        }
        head = sorted;
        print(head); // ja pecatime listata po sekoe vnesuvanje
    }
}

// FUNKCIJA ZA SPOJUVANJE NA DVE SORTIRANI LISTI BEZ DUPLIKATI
Node* mergeSorted(Node* a, Node* b){
    if(a == nullptr) return b;
    if(b == nullptr) return a;

    Node* rezultat = nullptr;

    if(a->data < b->data){
        rezultat = a;
        rezultat->next = mergeSorted(a->next, b);
    }else if(a->data > b->data){
        rezultat = b;
        rezultat->next = mergeSorted(a, b->next);
    }else{
        rezultat = a;
        rezultat->next = mergeSorted(a->next, b->next); // preskokni duplikat
    }
    return rezultat;
}

// FUNKCIJA ZA BUBBLE SORT
void bubbleSort(Node* head){
    if(head == nullptr) return;
    bool smena;
    do{
        smena = false;
        Node* t = head;
        while(t->next != nullptr){
            if(t->data > t->next->data){
                int temp = t->data;
                t->data = t->next->data;
                t->next->data = temp;
                smena = true;
            }
            t = t->next;
        }
    }while(smena);
}

// FUNKCIJA ZA INSERTION SORT
Node* insertionSort(Node* head){
    Node* sorted = nullptr;
    Node* tekoven = head;
    while(tekoven != nullptr){
        Node* sledbenik = tekoven->next;
        if(sorted == nullptr || tekoven->data < sorted->data){
            tekoven->next = sorted;
            sorted = tekoven;
        }else{
            Node* t = sorted;
            while(t->next != nullptr && t->next->data < tekoven->data){
                t = t->next;
            }
            tekoven->next = t->next;
            t->next = tekoven;
        }
        tekoven = sledbenik;
    }
    return sorted;
}

// ZADACHA 2 I 3: SPOJUVANJE I SORTIRANJE NA LISTI
void zadacha23(){
    Node* A = nullptr;
    Node* B = nullptr;
    int n, m, x;

    cout << "Kolku elementi ima vo lista A: ";
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> x;
        add(A, x);
    }

    cout << "Kolku elementi ima vo lista B: ";
    cin >> m;
    for(int i=0;i<m;i++){
        cin >> x;
        add(B, x);
    }

    // gi sortirame dvete listi ako ne se sortirani
    A = insertionSort(A);
    B = insertionSort(B);

    Node* C = mergeSorted(A, B);
    cout << "Spoena i sortirana lista: ";
    print(C);
}

// STRUKTURA ZA DVOJNA LISTA
struct DNode{
    int data;
    DNode* next;
    DNode* prev;
};

// DODAVANJE VO DVOJNA LISTA
void addD(DNode*& head, int val, int pos = -1){
    DNode* nov = new DNode;
    nov->data = val;
    nov->next = nullptr;
    nov->prev = nullptr;

    if(head == nullptr){
        head = nov;
        return;
    }

    if(pos <= 0){
        DNode* t = head;
        while(t->next != nullptr){
            t = t->next;
        }
        t->next = nov;
        nov->prev = t;
        return;
    }

    DNode* t = head;
    int i = 0;
    while(t->next != nullptr && i < pos - 1){
        t = t->next;
        i++;
    }

    nov->next = t->next;
    if(t->next != nullptr){
        t->next->prev = nov;
    }
    t->next = nov;
    nov->prev = t;
}

// BRISENJE OD DVOJNA LISTA
void removeD(DNode*& head, int val){
    DNode* t = head;
    while(t != nullptr && t->data != val){
        t = t->next;
    }
    if(t == nullptr) return;

    if(t->prev != nullptr){
        t->prev->next = t->next;
    }else{
        head = t->next;
    }

    if(t->next != nullptr){
        t->next->prev = t->prev;
    }

    delete t;
}

// BARANJE VO DVOJNA LISTA
bool searchD(DNode* head, int val){
    DNode* t = head;
    while(t != nullptr){
        if(t->data == val) return true;
        t = t->next;
    }
    return false;
}

// PECATENJE NA DVOJNA LISTA
void printD(DNode* head){
    DNode* t = head;
    while(t != nullptr){
        cout << t->data << " ";
        t = t->next;
    }
    cout << endl;
}

// ZADACHA 4: TEST ZA DVOJNA LISTA
void zadacha4(){
    DNode* head = nullptr;
    addD(head, 5);
    addD(head, 10);
    addD(head, 15);
    cout << "Lista: ";
    printD(head);
    cout << "Dodavame 20 na kraj: ";
    addD(head, 20);
    printD(head);
    cout << "Briseme 10: ";
    removeD(head, 10);
    printD(head);
    cout << "Barame 15: ";
    cout << (searchD(head, 15) ? "Postoi" : "Ne postoi") << endl;
}

int main(){
    cout << "1. Zadacha 1\n2. Zadacha 2 i 3\n3. Zadacha 4\nIzbor: ";
    int izbor;
    cin >> izbor;

    if(izbor == 1){
        zadacha1();
    }
    else if(izbor == 2){
        zadacha23();
    }
    else if(izbor == 3){
        zadacha4();
    }

    return 0;
}
