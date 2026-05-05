#include <iostream>
#include <string>
#include <vector>
#include <ctime> //Libreria per la data

class Date {
    int Day;
    int Month;
    int Year;

    public:
    int GetDay() {
        return Day;
    }
    int GetMonth() {
        return Month;
    }
    int GetYear() {
        return Year;
    }
    void PrintBD() const { // In questo modo la funzione può interagire con una costante
        std::cout<<Day<<"/"<<Month<<"/"<<Year;
    }
    int BDday = Day;
    int BDmonth = Month;
    int BDyear = Year;
        Date() {
            std::time_t t = std::time(nullptr); // Prende la data attuale (interroga il sistema operativo per farsi dare l'ora attuale passando nullptr (oppure 0), diciamo alla funzione che vogliamo solo il valore di ritorno.)
            std::tm* actualdate = std::localtime(&t); // Converte la data in una struttura locale (prende il timestamp t (tramite il suo indirizzo &t) e lo converte in una struttura tm tenendo conto del fuso orario impostato sul computer.)
            Day = actualdate->tm_mday;
            Month = actualdate->tm_mon + 1; // Perchè conta da 0
            Year = actualdate->tm_year + 1900; // Perchè conta dal 1900
        }
};

enum class PetState{
    Chillin = 0, Bored, Mad, Sad, Happy, Hungry, Thirsty, Sleepy
};

enum class PetRace{
    Dog = 0, Cat, Rabbit, Bird, Turtle, Fish, Capybara
};

class Pet {
    public:
        std::string name;
        PetRace race;
        int age;
        const Date BirthDate;
        PetState State;
        Pet() {
            name = "";
            race = static_cast<PetRace>(0);
            std::time_t t = std::time(nullptr);
            std::tm* actualdate = std::localtime(&t);
            int day = actualdate->tm_mday;
            int month = actualdate->tm_mon;
            int year = actualdate->tm_year;
            year -= BirthDate.BDyear;
            if (month >= BirthDate.BDmonth) {
                if (day >= BirthDate.BDday) {
                    age = year;
                }
            }
            State = static_cast<PetState>(4);
        }

        void PrintPetName() {
            std::cout<<name;
        }
        void PrintPetBD() {
            BirthDate.PrintBD();
        }
        void RenamePet() {
            std::cout<<"Quale sarà il nome del tuo pet?: ";
            std::cin>>name;
            std::cout<<"Perfetto "<<name<<" sarà il suo nuovo nome\n";
        }
        void SetPetRace() {
            std::cout<<"Scegli tra le seguenti razze: \n[1] Cane\n[2] Gatto\n[3] Coniglio\n[4] Uccello\n[5] Tartaruga\n[6] PesceStrada\n[7] Capybara\nScelta: ";
            int s;
            std::cin>>s;
            switch (s) {
                default:
                std::cout<<"\nSelezione invalida, imposto come Capybara perchè stanno troppo chill\n";
                race = static_cast<PetRace>(6);
                break;
                case 1:
                race = static_cast<PetRace>(s-1);
                break;
                case 2:
                race = static_cast<PetRace>(s-1);
                break;
                case 3:
                race = static_cast<PetRace>(s-1);
                break;
                case 4:
                race = static_cast<PetRace>(s-1);
                break;
                case 5:
                race = static_cast<PetRace>(s-1);
                break;
                case 6:
                race = static_cast<PetRace>(s-1);
                break;
                case 7:
                race = static_cast<PetRace>(s-1);
                break;
            }



        }
        
};

std::vector<std::string> PetStates = {"Chillin", "Bored", "Mad", "Sad", "Happy", "Hungry", "Thirsty", "Sleepy"};

std::vector<std::string> PetRaces = {"Dog", "Cat", "Rabbit", "Bird", "Turtle", "Fish", "Capybara"};

std::ostream& operator<<(std::ostream& os, PetState state) {
    return os << PetStates[static_cast<int>(state)];
}

std::ostream& operator<<(std::ostream& os, PetRace race) {
    return os << PetRaces[static_cast<int>(race)];
}

main() {
    Pet Pet1;
    std::cout<<Pet1.name<<" "<<Pet1.race<<" "<<Pet1.age<<" ";
    Pet1.PrintPetBD();
    std::cout<<" "<<Pet1.State<<"\n";
    Pet1.RenamePet();
    Pet1.SetPetRace();
    std::cout<<"PET MONITOR\n";
    std::cout<<"Nome: ";
    Pet1.PrintPetName();
    std::cout<<"\nRazza: "<<Pet1.race<<"\nStato: "<<Pet1.State<<"\nDataDiNascita: ";
    Pet1.PrintPetBD();
    Pet Pet2 = Pet1; // Copio Pet1 in Pet2
}
