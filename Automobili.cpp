#include <iostream>
#include <fstream>
#include <cstring>

class Automobile {
    char marca[20];
    char modello[20];
    int nporte;
    double consumo;
    int cilindrata;
    int velocitamax;
    int anno;
    double prezzo;
    double da0a100;

    void imposta() {
        std::ofstream cars("cars.dat", std::ios::binary | std::ios::app);
        std::cout<<std::endl;
        std::cout<<"========== AUTOMOBILE =========="<<std::endl;
        std::cout<<"Inserisci la marca dell'automobile: "<<std::endl;
        std::cin.getline(marca, 20);
        std::cout<<"Inserisci il modello dell'automobile: "<<std::endl;
        std::cin.getline(modello, 20);
        std::cout<<"Inserisci l'anno di commercializzazione dell'automobile: "<<std::endl;
        std::cin>>anno;
        std::cin.ignore();
        while (true) {
            std::cout<<"Inserisci la cilindrata in cm^3 dell'automobile: "<<std::endl;
            std::cin>>cilindrata;
            std::cin.ignore();
            if (cilindrata > 0) break;
            else std::cout<<"Cilindrata non valida\n";
        }
        while (true) {
            std::cout<<"Inserisci il numero di porte dell'automobile: "<<std::endl;
            std::cin>>nporte;
            std::cin.ignore();
            if (nporte > 0) break;
            else std::cout<<"Numero di porte non valido\n";
        }
        while (true) {
            std::cout<<"Inserisci il consumo in km/l dell'automobile: "<<std::endl;
            std::cin>>consumo;
            std::cin.ignore();
            if (consumo > 0) break;
            else std::cout<<"Consumo non valido\n";
        }
        while (true) {
            std::cout<<"Inserisci la velocità massima dell'automobile: "<<std::endl;
            std::cin>>velocitamax;
            std::cin.ignore();
            if (velocitamax > 0) break;
            else std::cout<<"Velocità non valida\n";
        }
        while (true) {
            std::cout<<"Inserisci il tempo d'accelerazione  0-100 km/h: "<<std::endl;
            std::cin>>da0a100;
            std::cin.ignore();
            if (da0a100 > 0) break;
            else std::cout<<"Tempo non valido\n";
        }
        while (true) {
            std::cout<<"Inserisci il prezzo dell'automobile: "<<std::endl;
            std::cin>>prezzo;
            std::cin.ignore();
            if (prezzo > 0) break;
            else std::cout<<"Prezzo non valido\n";
        }
        cars.write((char*)this, sizeof(Automobile));
        cars.close();
    }
    void mostra() {
        std::ifstream cars("cars.dat", std::ios::binary);
        cars.seekg(0, std::ios::end); //seekg servere a spostarsi nel file, il primo numero è l'offset
        std::streamsize size = cars.tellg();
        if (size == 0) {
            std::cout<<"\n=====================\n";
            std::cout<<"|L'archivio è vuoto!|\n";
            std::cout<<"=====================\n";
            return;
        }

        cars.seekg(0, std::ios::beg);
        
        int mostra=0;
        while (cars.read((char*)this, sizeof(Automobile))) {
            std::cout<<std::endl;
            std::cout<<"========== AUTOMOBILE #"<<mostra+1<<" =========="<<std::endl;
            std::cout<<"Marca automobile: "<<marca<<"\nModello automobile: "<<modello<<"\nAnno automobile: "<<anno<<"\nPrezzo automobile: "<<prezzo<<"€"<<"\nNumero di porte: "<<nporte<<"\nTempo d'accelerazione 0-100km/h: "<<da0a100<<" secondi"<<"\nVelocità massima: "<<velocitamax<<" km/h"<<"\nCilindrata: "<<cilindrata<<" cm^3"<<"\nConsumo: "<<consumo<<" km/L"<<std::endl;
            mostra++;
        }
        cars.close();
    }

    void cercaPerMarca(char ricerca[20]) {
        std::ifstream cars("cars.dat", std::ios::binary);
        int cerca=0;
        while (cars.read((char*)this, sizeof(Automobile))) {
            if (strcmp(ricerca, marca) == 0) {
                std::cout<<std::endl;
                std::cout<<"========== AUTOMOBILE #"<<cerca+1<<" =========="<<std::endl;
                std::cout<<"Marca automobile: "<<marca<<"\nModello automobile: "<<modello<<"\nAnno automobile: "<<"\nPrezzo automobile: "<<anno<<std::endl;;
                cerca++;
            } else if (cerca==0) std::cout<<"Marca non presente nell'archivio"<<std::endl;
        }
        cars.close();
    }

    void rimuovi() {
        mostra();
        char MarcaDaCancellare[20];
        char ModelloDaCancellare[20];
        int AnnoDaCancellare;

        std::cout<<"\n========== RIMOZIONE =========="<<std::endl;
        std::cout<<"\nInserisci la marca dell'auto da rimuovere: ";
        std::cin.getline(MarcaDaCancellare, 20);
        std::cout<<"\nInserisci il modello dell'auto da rimuovere: ";
        std::cin.getline(ModelloDaCancellare, 20);
        std::cout<<"\nInserisci l'anno dell'auto da rimuovere: ";
        std::cin>>AnnoDaCancellare;
        std::cin.ignore();

        std::ifstream cars("cars.dat", std::ios::binary);
        std::ofstream temp("temp.dat", std::ios::binary);

        bool found = false;

        while (cars.read((char*)this, sizeof(Automobile))) {
            if (strcmp(MarcaDaCancellare, marca) == 0 && strcmp(ModelloDaCancellare, modello) == 0 && AnnoDaCancellare == anno) {
                found = true;
                continue;
            }
            else temp.write((char*)this, sizeof(Automobile));
        }

        cars.close();
        temp.close();

        std::remove("cars.dat");
        std::rename("temp.dat", "cars.dat");

        if (!found) std::cout<<"Auto non trovata!"<<std::endl;
        else std::cout<<"Auto rimossa dall'archivio"<<std::endl;

    }

    public:
    void callImposta() {
        imposta();
    }

    void callMostra() {
        mostra();
    }

    void callcercaPerMarca() {
        char ricerca[20];
        std::cout<<std::endl;
        std::cout<<"========== RICERCA AUTOMOBILE =========="<<std::endl;;
        std::cout<<std::endl;
        std::cout<<"Inserisci la marca dell'auto da cercare"<<std::endl;
        std::cin.getline(ricerca, 20);
        cercaPerMarca(ricerca);
    }

    void callRimuovi() {
        rimuovi();
    }

};

int main() {
    Automobile A;
    int sel;
            while (true) {
                std::cout<<std::endl;
                std::cout<<"========== MENU CONCESSIONARIO =========="<<std::endl;
                std::cout<<std::endl;
                std::cout<<"[1] Inserisci auto"<<std::endl;
                std::cout<<"[2] Mostra archivio auto"<<std::endl;
                std::cout<<"[3] Ricerca per marca"<<std::endl;
                std::cout<<"[4] Elimina auto"<<std::endl;
                std::cout<<"[5] Esci"<<std::endl;
                std::cout<<"Selezione: ";
                std::cin>>sel;
                std::cin.ignore();
                switch(sel) {
                    case(1):
                    A.callImposta();
                    break;
                    case(2):
                    A.callMostra();
                    break;
                    case(3):
                    A.callcercaPerMarca();
                    break;
                    case(4):
                    A.callRimuovi();
                    break;
                    case(5):
                    return 0;
                    break;
                }
            }

    
}