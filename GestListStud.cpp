/********************************************************************************************
 *  Questo programma gestisce una lista di studenti memorizzati in vettore con una struct   *
 ********************************************************************************************/

#include <iostream>
#include <string.h>
#include <vector>

struct studente { //Creazione struct
    std::string nome = " "; //Definizioni
    std::string cognome = " ";
    float media = 0;
};

void InserisciStud(std::vector<studente> &studenti) { //Riferimento al vettore originale
    int ns = 0; //Definisco numero studenti
    std::string nome = " ";
    std::string cognome = " ";
    float media = 0;
    while (true) { //Ciclo per l'inserimento del numero degli studenti
        std::cout<<"Quanti studenti si desidera aggiungere?\n";
        if (!(std::cin>>ns) || ns <= 0) { //Controllo della validità del cin
            std::cout<<"Inserire un numero valido!\n";
            std::cin.clear(); //Reset errore
            std::cin.ignore(1000, '\n'); //Pulisco il buffer per 1000 caratteri o fin quando non trovo \n
        }
        else break;
    }
    for (int i = 0; i<ns; ++i) { //Ciclo per l'inserimento degli studenti basato sul numer o di studenti
        while (true) {
            std::cout<<"Nome studente: ";
            std::cin>>nome;
            if (nome.length()<=0) { //Controllo che la string non sia vuota
                std::cout<<"Inserire un nome valido!\n";
                std::cin.clear(); //Reset errore
                std::cin.ignore(1000, '\n'); //Pulisco il buffer per 1000 caratteri o fin quando non trovo \n
            }
            else break;
        }
        while (true) {
            std::cout<<"Cognome studente: ";
            std::cin>>cognome;
            if (cognome.length()<=0) { //Controllo che la string non sia vuota
                std::cout<<"Inserire un cognome valido!\n";
                std::cin.clear(); ///Reset errore
                std::cin.ignore(1000, '\n'); //Pulisco il buffer per 1000 caratteri o fin quando non trovo \n
            }
            else break;
        }
        while (true) { //Ciclo d'inserimento per la media
            std::cout<<"Media studente: ";
            if (!(std::cin>>media) || media<=0) { //Controllo che la media sia valida
                std::cout<<"Inserire una media valida!\n";
                std::cin.clear(); //Reset errore
                std::cin.ignore(1000, '\n'); //Pulisco il buffer per 1000 caratteri o fin quando non trovo \n
            }
            else break;
        }
        studenti.push_back({nome, cognome, media}); //Inserisco alal fine del vettore i dati
        std::cout<<studenti[i].nome<<"\n";
        std::cout<<studenti[i].cognome<<"\n";
        std::cout<<studenti[i].media<<"\n";
    }
}

void StampStud(std::vector<studente> &studenti) { //Funzione per la stampa degli studenti
    for (int i = 0; i<studenti.size(); ++i) { //Ciclo for per lo scorrimento del vettore
        std::cout<<"Studente #"<<i+1<<"\n";
        std::cout<<"Nome: "<<studenti[i].nome<<"\n";
        std::cout<<"Cognome: "<<studenti[i].cognome<<"\n";
        std::cout<<"Media: "<<studenti[i].media<<"\n";
    }
}

void MigliorStud(std::vector<studente> &studenti) { //Stampo lo studente con la media più alta
    int ms = 0;
    for (int i = 1; i<studenti.size(); ++i) {
        if (studenti[i].media>studenti[i-1].media) {
            ms = i;
        }
    }
    std::cout<<"Lo studente con la media più alta è "<<studenti[ms].nome<<" "<<studenti[ms].cognome<<" con una media di "<<studenti[ms].media<<"\n";
}

int main() {
    std::vector<studente> studenti = {}; //Definisco un vettore di tipo studente
    int short s;
    while (true) { //Menu per l'utilizzo del programma
        std::cout<<"Benvenuto nel programma di gestione degli studenti!\n";
        std::cout<<"[1] Inserimento\n";
        std::cout<<"[2] Stampa\n";
        std::cout<<"[3] Migliorstudente\n";
        std::cout<<"Selezione: ";
        std::cin>>s;

        switch (s) {
            case 1: //Inserimento studenti
                InserisciStud(studenti);
                break;
            case 2: //Stampa studenti
                if (studenti.size() <= 0) {
                    std::cout<<"Impossibile continuare, il vettore è vuoto\n";
                    break;
                }
                StampStud(studenti);
                break;
            case 3: //Stampa miglior studente
                if (studenti.size() <= 0) {
                    std::cout<<"Impossibile continuare, il vettore è vuoto\n";
                    break;
                }
                MigliorStud(studenti);
                break;
            default: //Selezione invalida
                std::cout<<"Selezione non valida!\n";
                break;
        }
    }
}