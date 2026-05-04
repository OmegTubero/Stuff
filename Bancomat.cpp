#include <iostream>
#include <fstream>
#include <cstring>

class ATM {
    double balance;
    char pin[5];

    public:
        char cardnumb [17];
        char cardholdername[30];
        char cardholdersurname[30];

        void AddCard(bool admin){
            bool pinvalid=false;
            bool cardnumbvalid=false;
            std::cout<<"_______________________________________________________________________"<<std::endl;
            if (!admin) {
                std::cout<<"Non hai i permessi per eseguire quest'operazione"<<std::endl;
                return;
            }
            int j=0;
            std::ofstream cards("cards.dat", std::ios::binary | std::ios::app);
            std::cout<<"Inserisci il nome del proprietario della carta"<<std::endl;
            std::cin>>cardholdername;
            std::cin.ignore();
            std::cout<<"Inserisci il cognome del proprietario della carta"<<std::endl;
            std::cin>>cardholdersurname;
            std::cin.ignore();
            while (true) {
                std::cout << "Inserisci il numero di carta (16 cifre)" << std::endl;
                std::cin.getline(cardnumb, 17);
                if (strlen(cardnumb) != 16) {
                    std::cout << "Il numero deve contenere esattamente 16 cifre!" << std::endl;
                    continue;
                }
                cardnumbvalid = true;
                for (int i = 0; i < 16; i++) {
                    if (!isdigit(cardnumb[i])) {
                        cardnumbvalid = false;
                        break;
                    }
                }
                if (cardnumbvalid) break;
                else std::cout << "Il numero deve contenere solo cifre!" << std::endl;
            }
            for (int i = 0; cardnumb[i] != '\0'; i++) {
                if (cardnumb[i] != ' ') {
                    cardnumb[j] = cardnumb[i];
                    j++;
                }
            }
            cardnumb[j] = '\0';
            while (true) {
                std::cout << "Inserisci il pin della carta (4 cifre)" << std::endl;
                std::cin.getline(pin, 5);
                if (strlen(pin) != 4) {
                    std::cout << "Il pin deve contenere esattamente 4 cifre!" << std::endl;
                    continue;
                }
                pinvalid = true;
                for (int i = 0; i < 4; i++) {
                    if (!isdigit(pin[i])) {
                        pinvalid = false;
                        break;
                    }
                }
                if (pin) break;
                else std::cout << "Il pin deve contenere solo cifre!" << std::endl;
            }
            balance = 0.0;
            cards.write((char*)this, sizeof(ATM));
            std::cout<<"Carta registrata correttamente"<<std::endl;
            cards.close();
            return;
        }

        void RemoveCard(bool admin) {
            std::cout<<"_______________________________________________________________________"<<std::endl;
            if (!admin) {
                std::cout<<"Non hai i permessi per eseguire quest'operazione"<<std::endl;
                return;
            }

            ShowCards(admin);

            std::cout<<"_______________________________________________________________________"<<std::endl;

            char nomeDaCancellare[20];
            char cognomeDaCancellare[20];
            char cartaDaCancellare[17];
            std::cout<<"Inserisci il nome dell'intestatario della carta da rimuovere"<<std::endl;
            std::cin>>nomeDaCancellare;
            std::cin.ignore();
            std::cout<<"Inserisci il cognome dell'intestatario della carta da rimuovere"<<std::endl;
            std::cin>>cognomeDaCancellare;
            std::cin.ignore();

            std::ifstream cards("cards.dat", std::ios::binary);
            std::ofstream temp("temp.dat", std::ios::binary);

            bool found = false;

            while (cards.read((char*)this, sizeof(ATM))) {
                if (strcmp(cardholdername, nomeDaCancellare) == 0 && strcmp(cardholdersurname, cognomeDaCancellare) == 0 && strcmp(cardnumb, cartaDaCancellare) == 0) {
                    found = true;
                    continue;
                }
                temp.write((char*)this, sizeof(ATM));
            }

            cards.close();
            temp.close();

            
            std::remove("cards.dat");
            std::rename("temp.dat", "cards.dat");

            if (found)
                std::cout<<"Carta eliminata con successo!"<<std::endl;
            else
                std::cout<<"Carta non trovata!"<<std::endl;
        }

        void ShowCards(bool admin){
            std::cout<<"_______________________________________________________________________"<<std::endl;
            if (!admin) {
                std::cout<<"Non hai i permessi per eseguire quest'operazione"<<std::endl;
                return;
            }

            std::cout<<"Ecco le informazioni delle carte archiviate"<<std::endl;
            std::ifstream cards("cards.dat", std::ios::binary);
            while (cards.read((char*)this, sizeof (ATM))) {
                std::cout<<"_______________________________________________________________________"<<std::endl;
                std::cout<<"Nome dell'intestatario della carta: "<<cardholdername<<"\nCognome dell'intestatario della carta: "<<cardholdersurname<<"\nNumero della carta: "<<cardnumb<<"\nSaldo della carta: "<<balance<<"€"<<std::endl;
            }
            cards.close();
            return;
        }

        void UserMenu(bool found, char numerocarta[17], char pincarta[5]){
            int sel;
            while (true) {
            std::cout<<"_______________________________________________________________________"<<std::endl;
            std::cout<<"Menu operazioni"<<std::endl;
            std::cout<<"[1] Prelievo"<<std::endl;
            std::cout<<"[2] Deposito"<<std::endl;
            std::cout<<"[3] Mostra saldo"<<std::endl;
            std::cout<<"[4] Esci"<<std::endl;
            std::cout<<"Selezione: ";
            std::cin>>sel;
            switch(sel) {
                case(1):
                Withdraw(found, numerocarta, pincarta);
                break;
                case(2):
                Deposit(found, numerocarta, pincarta);
                break;
                case(3):
                ShowBalance(found, numerocarta, pincarta);
                break;
                case(4):
                std::cout<<"Grazie per aver usato il nostro ATM"<<std::endl;
                return;
                break;
                case(67):
                std::cout<<"Modalità admin attiva"<<std::endl;
                AdminMenu();
                return;
                break;
            }
            }

        }

        void AdminMenu(){
            bool admin=true;
            int sel;
            while (true) {
            std::cout<<"_______________________________________________________________________"<<std::endl;
            std::cout<<"Menu admin"<<std::endl;
            std::cout<<"[1] Aggiungi carta"<<std::endl;
            std::cout<<"[2] Rimuovi carta"<<std::endl;
            std::cout<<"[3] Mostra carte"<<std::endl;
            std::cout<<"[4] Esci"<<std::endl;
            std::cout<<"Selezione: ";
            std::cin>>sel;
            switch(sel) {
                case(1):
                AddCard(admin);
                break;
                case(2):
                RemoveCard(admin);
                break;
                case(3):
                ShowCards(admin);
                break;
                case(4):
                return;
                break;
            }
            }

        }

        void Withdraw(bool found, char numerocarta[17], char pincarta[5]){
            found = false;
            double withdraw=0;
            //FindCard(found, numerocarta, pincarta);
            std::cout<<"Inserire l'importo che si desidera prelevare: ";
            std::cin>>withdraw;
            std::ifstream cards("cards.dat", std::ios::binary);
            std::ofstream temp("temp.dat", std::ios::binary);

            bool foundcard = false;

            while (cards.read((char*)this, sizeof(ATM))) {
                if (strcmp(cardnumb, numerocarta) == 0 && strcmp(pin, pincarta) == 0) {
                foundcard = true;
                    if (balance < withdraw) {
                        std::cout<<"Saldo insufficiente"<<std::endl;
                    } else {
                        balance -= withdraw;
                        std::cout<<"Prelievo effettuato con successo"<<std::endl;
                    }
                 }
                temp.write((char*)this, sizeof(ATM));
            }


            cards.close();
            temp.close();

            std::remove("cards.dat");
            std::rename("temp.dat", "cards.dat");
        }
        
        void Deposit(bool found, char numerocarta[17], char pincarta[5]){
            found = false;
            double deposit=0;
            //FindCard(found, numerocarta, pincarta);
            std::cout<<"Inserire l'importo che si desidera depositare: ";
            std::cin>>deposit;
            std::ifstream cards("cards.dat", std::ios::binary);
            std::ofstream temp("temp.dat", std::ios::binary);

            bool foundcard = false;

            while (cards.read((char*)this, sizeof(ATM))) {
                if (strcmp(cardnumb, numerocarta) == 0 && strcmp(pin, pincarta) == 0) {
                    foundcard = true;
                    balance += deposit;
                    std::cout<<"Deposito effettuato con successo"<<std::endl;
                }
                temp.write((char*)this, sizeof(ATM));
            }

            cards.close();
            temp.close();

            
            std::remove("cards.dat");
            std::rename("temp.dat", "cards.dat");
        }

        void ShowBalance(bool found, char numerocarta[17], char pincarta[5]){
            found = false;
            //FindCard(found, numerocarta, pincarta);
            std::ifstream cards("cards.dat", std::ios::binary);

            bool foundcard = false;

            while (cards.read((char*)this, sizeof(ATM))) {
                if (strcmp(cardnumb, numerocarta) == 0 && strcmp(pin, pincarta) == 0) {
                    foundcard = true;
                    std::cout<<"Il saldo della carta è: "<<balance<<"€"<<std::endl;
                    continue;
                }
            }

            cards.close();
        }

        bool FindCard(bool &found, char numerocarta[17], char pincarta[5]){
        std::ifstream cards("cards.dat", std::ios::binary);
        char admin[3]="67";
        if (strcmp(admin, numerocarta) == 0 && strcmp(admin, pincarta) == 0) {
            found = true;
            cards.close();
            return found;
        }
            while (cards.read((char*)this, sizeof(ATM))) {
            if (strcmp(cardnumb, numerocarta) == 0 && strcmp(pin, pincarta) == 0) {
                found = true;
                cards.close();
                return found;
            }
        }
        cards.close();
        return found;
        }
        

};

int main() {
    ATM A;
    char numerocarta[17];
    char pincarta[5];

    while (true) {
        std::cout<<"Inserisci le credenziali richieste"<<std::endl;
        std::cout<<"Numero Carta: ";
        std::cin>>numerocarta;
        std::cout<<"Pin: ";
        std::cin>>pincarta;
        bool found = false;
        A.FindCard(found, numerocarta, pincarta);
        if (found) A.UserMenu(found, numerocarta, pincarta);
        else std::cout<<"Credenziali non valide!"<<std::endl;
    }
}