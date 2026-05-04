#include <iostream>
#include <fstream>
#include <cstring>

class StockStore {
    int quantity;
    int discount;
    double price;
    char name[30];
    char brand[30];
    char release[9];

    void addItem(){
        quantity=0;
        std::ofstream Stock("Stock.dat", std::ios::binary | std::ios::app);
        std::cout<<"\n\n\n========== AGGIUNTA ARTICOLO ==========";
        while (true) {
            std::cout<<"\nInserisci il nome dell'articolo: ";
            std::cin.getline(name, 30);
            if (std::strlen(name)>0) break;
            else std::cout<<"\nNome non valido";
        }
        while (true) {
            std::cout<<"\nInserisci il marchio dell'articolo: ";
            std::cin.getline(brand, 30);
            if (std::strlen(brand)>0) break;
            else std::cout<<"\nMarchio non valido";
        }
        while (true) {
            std::cout<<"\nInserisci la data di rilascio dell'articolo nel formato ggmmaaaa: ";
            std::cin.getline(release, 9);
            if (std::strlen(release)>0) break;
            else std::cout<<"\nData non valido";
        }
        while (true) {
            std::cout<<"\nInserisci il prezzo dell'articolo in euro: ";
            std::cin>>price;
            std::cin.ignore();
            if (price>=0) break;
            else std::cout<<"\nPrezzo non valido";
        }
        while (true) {
            std::cout<<"\nInserisci la quantità disponibile: ";
            std::cin>>quantity;
            std::cin.ignore();
            if (quantity>=0) break;
            else std::cout<<"\nQuantità non valida";
        }
        while (true) {
            std::cout<<"\nInserisci lo sconto se disponibile (in caso contrario non inserire 0): ";
            discount = 0;
            std::cin>>discount;
            std::cin.ignore();
            if (discount>=0 && discount<=100) break;
            else std::cout<<"\nSconto non valido";
        }
        Stock.write((char*)this, sizeof(*this));
        Stock.close();
    }

    bool ShowItems() {
        std::ifstream Stock("Stock.dat", std::ios::binary);
        Stock.seekg(0, std::ios::end);
        std::streamsize size = Stock.tellg();
        if (size == 0) {
            std::cout<<"\n=====================\n";
            std::cout<<"|L'archivio è vuoto!|\n";
            std::cout<<"=====================\n";
            return false;
        }
        Stock.seekg(0, std::ios::beg);

        int show= 0;
        
        std::cout<<"\n\n\n========== CATALOGO ARTICOLI ==========";

        while(Stock.read((char*)this, sizeof(*this))) {
            int discounted_price=price*(discount/100.0);
            
            std::cout<<"\n\n\n========== Articolo #"<<show+1<<" ==========";
            if (discount>0) std::cout<<"\n\n\nNome: "<<name<<"\nMarca: "<<brand<<"\nRilascio: "<<release[0]<<release[1]<<"/"<<release[2]<<release[3]<<"/"<<release[4]<<release[5]<<release[6]<<release[7]<<"\nQuantità disponibile: "<<quantity<<"\nMSRP: "<<price<<"€"<<"\nPrezzo: "<<discounted_price<<"€"<<"\nSconto: "<<discount<<"%";
            else std::cout<<"\n\n\nNome: "<<name<<"\nMarca: "<<brand<<"\nRilascio: "<<release[0]<<release[1]<<"/"<<release[2]<<release[3]<<"/"<<release[4]<<release[5]<<release[6]<<release[7]<<"\nQuantità disponibile: "<<quantity<<"\nMSRP: "<<price<<"€"<<"\nPrezzo: "<<discounted_price<<"€"<<"\nSconto: No";
            show++;
        }
        Stock.close();
        return true;
    }

    void CercaPerMarca(char ricerca[30]) {
        std::ifstream Stock("Stock.dat", std::ios::binary);
        int cerca=0;
        std::cout<<"\n\n\n========== RICERCA ARTICOLI ==========";

        while (Stock.read((char*)this, sizeof(*this))) {
            if (strcmp(ricerca, brand) == 0) {
                
                int discounted_price=price*(discount/100);
                if (discount>0) std::cout<<"\n\n\nNome: "<<name<<"\nMarca: "<<brand<<"\nRilascio: "<<release[0]<<release[1]<<"/"<<release[2]<<release[3]<<"/"<<release[4]<<release[5]<<release[6]<<release[7]<<"\nQuantità disponibile: "<<quantity<<"\nMSRP: "<<price<<"€"<<"\nPrezzo: "<<discounted_price<<"€"<<"\nSconto: "<<discount<<"%";
                else std::cout<<"\n\n\nNome: "<<name<<"\nMarca: "<<brand<<"\nRilascio: "<<release[0]<<release[1]<<"/"<<release[2]<<release[3]<<"/"<<release[4]<<release[5]<<release[6]<<release[7]<<"\nQuantità disponibile: "<<quantity<<"\nMSRP: "<<price<<"€"<<"\nPrezzo: "<<discounted_price<<"€"<<"\nSconto: No";
                cerca++;
            }
        }
        if (cerca==0) std::cout<<"Marca non presente nell'archivio"<<std::endl;
        Stock.close();
    }

    void RemoveItem() {
        if (ShowItems()==false) return;
        int ItemNumber;

        std::cout<<"\nInserisci numero dell'oggetto da rimuovere: ";
        std::cin>>ItemNumber;
        std::cin.ignore();
        ItemNumber--;

        std::ifstream Stock("Stock.dat", std::ios::binary);
        std::ofstream temp("temp.dat", std::ios::binary);

        bool found=false;

        int showDel= 0;
        while (Stock.read((char*)this, sizeof(*this))) {
            if (showDel==ItemNumber) {
                found=true;
                continue;
            }
            else temp.write((char*)this, sizeof(*this));
            showDel++;
        }

        Stock.close();
        temp.close();

        std::remove("Stock.dat");
        std::rename("temp.dat", "Stock.dat");

        if (!found) std::cout<<"Articolo non trovato!"<<std::endl;
        else std::cout<<"Articolo rimosso dall'archivio"<<std::endl;

    }

    void EditItem() {
        if (ShowItems()==false) return;
        int ItemNumber;

        std::cout<<"\n\nInserisci numero dell'oggetto da modificare: ";
        std::cin>>ItemNumber;
        std::cin.ignore();
        ItemNumber--;

        std::ifstream Stock("Stock.dat", std::ios::binary);
        std::ofstream temp("temp.dat", std::ios::binary);

        bool found=false;
        int showEd= 0;
        while (Stock.read((char*)this, sizeof(*this))) {
            if (showEd==ItemNumber) {
                found=true;
                bool cicle=true;
                int sel;
                while (cicle) {
                    std::cout<<std::endl;
                    std::cout<<"========== MENU MODIFICA =========="<<std::endl;
                    std::cout<<std::endl;
                    std::cout<<"[1] Modifica nome"<<std::endl;
                    std::cout<<"[2] Modifica marca"<<std::endl;
                    std::cout<<"[3] Modifica data di commercializzazione"<<std::endl;
                    std::cout<<"[4] Modifica prezzo"<<std::endl;
                    std::cout<<"[5] Modifica quantità"<<std::endl;
                    std::cout<<"[6] Modifica sconto"<<std::endl;
                    std::cout<<"[7] Esci"<<std::endl;
                    std::cout<<"Selezione: ";
                    std::cin>>sel;
                    std::cin.ignore();
                    switch(sel) {
                        case(1):
                        while (true) {
                            std::cout<<"\nInserisci il nome dell'articolo: ";
                            std::cin.getline(name, 30);
                            if (std::strlen(name)>0) break;
                            else std::cout<<"\nNome non valido";
                        }
                        break;
                        case(2):
                        while (true) {
                            std::cout<<"\nInserisci il marchio dell'articolo: ";
                            std::cin.getline(brand, 30);
                            if (std::strlen(brand)>0) break;
                            else std::cout<<"\nMarchio non valido";
                        }
                        break;
                        case(3):
                        while (true) {
                            std::cout<<"\nInserisci la data di rilascio dell'articolo nel formato ggmmaaaa: ";
                            std::cin.getline(release, 9);
                            if (std::strlen(release)>0) break;
                            else std::cout<<"\nData non valido";
                        }
                        break;
                        case(4):
                        while (true) {
                            std::cout<<"\nInserisci il prezzo dell'articolo in euro: ";
                            std::cin>>price;
                            std::cin.ignore();
                            if (price>=0) break;
                            else std::cout<<"\nPrezzo non valido";
                        }
                        break;
                        case(5):
                        while (true) {
                            std::cout<<"\nInserisci la quantità disponibile: ";
                            std::cin>>quantity;
                            std::cin.ignore();
                            if (quantity>=0) break;
                            else std::cout<<"\nQuantità non valida";
                        }
                        break;
                        case(6):
                        while (true) {
                            std::cout<<"\nInserisci lo sconto se disponibile (in caso contrario non inserire 0): ";
                            discount = 0;
                            std::cin>>discount;
                            std::cin.ignore();
                            if (discount>=0 && discount<=100) break;
                            else std::cout<<"\nSconto non valido";
                        }
                        break;
                        case(7):
                        cicle=false;
                        temp.write((char*)this, sizeof(*this));
                        break;
                    }
                }
            }
            else temp.write((char*)this, sizeof(*this));
            showEd++;
        }

        Stock.close();
        temp.close();

        std::remove("Stock.dat");
        std::rename("temp.dat", "Stock.dat");

        if (!found) std::cout<<"Articolo non trovato!"<<std::endl;
        else std::cout<<"Articolo modificato con successo"<<std::endl;

    }

    public:
        void CallAddItem() {
            addItem();
        }

        void CallShowItems() {
            ShowItems();
        }

        void CallCercaPerMarca() {
            char search[30];
            std::cout<<"\nInserisci il nome della marca da cercare: ";
            std::cin.getline(search, 30);
            CercaPerMarca(search);
        }

        void CallRemoveItem() {
            RemoveItem();
        }

        void CallEditItem() {
            EditItem();
        }

};

int main() {
    StockStore Store;
    int s;
            while (true) {
                std::cout<<std::endl;
                std::cout<<"========== MENU NEGOZIO =========="<<std::endl;
                std::cout<<std::endl;
                std::cout<<"[1] Inserisci articolo"<<std::endl;
                std::cout<<"[2] Mostra articoli"<<std::endl;
                std::cout<<"[3] Ricerca per marca"<<std::endl;
                std::cout<<"[4] Elimina articolo"<<std::endl;
                std::cout<<"[5] Modifica articolo"<<std::endl;
                std::cout<<"[6] Esci"<<std::endl;
                std::cout<<"Selezione: ";
                std::cin>>s;
                std::cin.ignore();
                switch(s) {
                    case(1):
                    Store.CallAddItem();
                    break;
                    case(2):
                    Store.CallShowItems();
                    break;
                    case(3):
                    Store.CallCercaPerMarca();
                    break;
                    case(4):
                    Store.CallRemoveItem();
                    break;
                    case(5):
                    Store.CallEditItem();
                    break;
                    case(6):
                    return 0;
                    break;
                }
            }
    
    return 0;
}