#include <iostream>

using namespace std;

class Animal {
protected:
    string nume;
    int varsta;

public:
    Animal(string n, int v) : nume(n), varsta(v) {}

    virtual void afisare() const {
        cout << "Animal: " << nume << ", Varsta: " << varsta << " ani\n";
    }

    string getNume() const { return nume; }

    virtual ~Animal() {}
};

class Pasare : public Animal {
private:
    double lungime_aripi;
    int durata_viata;

public:
    Pasare(string n, int v, double l, int d) : Animal(n, v), lungime_aripi(l), durata_viata(d) {}

    void afisare() const override {
        cout << "Pasare: " << nume << ", Varsta: " << varsta
            << " ani, Lungime aripi: " << lungime_aripi
            << " cm, Durata de viata: " << durata_viata << " ani\n";
    }
};

class Caine : public Animal {
private:
    string rasa, tip;

public:
    Caine(string n, int v, string r, string t) : Animal(n, v), rasa(r), tip(t) {}

    void afisare() const override {
        cout << "Caine: " << nume << ", Varsta: " << varsta
            << " ani, Rasa: " << rasa << ", Tip: " << tip << "\n";
    }
};

struct Nod {
    Animal* animal;
    Nod* anterior;
    Nod* urmator;

    Nod(Animal* a) : animal(a), anterior(nullptr), urmator(nullptr) {}
};

class Zoo {
private:
    Nod* cap; 
    Nod* coada;

public:
    Zoo() : cap(nullptr), coada(nullptr) {}

    ~Zoo() {
        Nod* temp = cap;
        while (temp) {
            Nod* urm = temp->urmator;
            delete temp->animal;
            delete temp;
            temp = urm;
        }
    }

    void adaugaAnimal(Animal* a) {
        Nod* nou = new Nod(a);
        if (!cap) { 
            cap = coada = nou;
        }
        else {
            coada->urmator = nou;
            nou->anterior = coada;
            coada = nou;
        }
        cout << "Animal adaugat!\n";
    }

    void afiseazaAnimale() const {
        if (!cap) {
            cout << "Gradina zoologica este goala.\n";
            return;
        }
        Nod* temp = cap;
        while (temp) {
            temp->animal->afisare();
            temp = temp->urmator;
        }
    }

    void stergeAnimal(string nume) {
        Nod* temp = cap;
        while (temp) {
            if (temp->animal->getNume() == nume) {
                if (temp == cap) cap = cap->urmator;
                if (temp == coada) coada = coada->anterior;
                if (temp->anterior) temp->anterior->urmator = temp->urmator;
                if (temp->urmator) temp->urmator->anterior = temp->anterior;

                delete temp->animal;
                delete temp;
                cout << "Animal sters!\n";
                return;
            }
            temp = temp->urmator;
        }
        cout << "Animalul nu a fost gasit!\n";
    }
};

int main() {
    Zoo gradina;
    int optiune;

    do {
        cout << "\n--- Meniu Zoo ---\n"
            << "1. Adauga Pasare\n"
            << "2. Adauga Caine\n"
            << "3. Afiseaza Animale\n"
            << "4. Sterge Animal\n"
            << "5. Iesire\n"
            << "Alege o optiune: ";
        cin >> optiune;
        cin.ignore();

        if (optiune == 1) {
            string nume;
            int varsta, durata;
            double aripi;
            cout << "Nume: "; getline(cin, nume);
            cout << "Varsta: "; cin >> varsta;
            cout << "Lungimea aripilor (cm): "; cin >> aripi;
            cout << "Durata de viata (ani): "; cin >> durata;
            gradina.adaugaAnimal(new Pasare(nume, varsta, aripi, durata));
        }
        else if (optiune == 2) {
            string nume, rasa, tip;
            int varsta;
            cout << "Nume: "; getline(cin, nume);
            cout << "Varsta: "; cin >> varsta;
            cin.ignore();
            cout << "Rasa: "; getline(cin, rasa);
            cout << "Tip: "; getline(cin, tip);
            gradina.adaugaAnimal(new Caine(nume, varsta, rasa, tip));
        }
        else if (optiune == 3) {
            gradina.afiseazaAnimale();
        }
        else if (optiune == 4) {
            string nume;
            cout << "Nume animal de sters: ";
            getline(cin, nume);
            gradina.stergeAnimal(nume);
        }
        else if (optiune == 5) {
            cout << "Iesire...\n";
        }
        else {
            cout << "Optiune invalida!\n";
        }

    } while (optiune != 5);

    return 0;
}
