#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

void error(const std::string &s) {
    throw std::runtime_error(s);
}

class Enemy {
    public:
    int health;
    int attack;
    int energy;
    std::string name;

    Enemy() {
        health = 100;
        attack = 2;
        energy = 20;
        name = "Job";
    }

    void atk(int &p_energy, int &p_health) {
        std::cout<<name<<" attacks!\n";
        int rng[3] = {rand() % 7, rand() % 7, rand() % 7};
        if (rng[0] == rng[1] || rng[0] == rng[2]) {
            std::cout<<name<<" missed his attack, what a moron\n";
        }
        else {
            std::cout<<name<<" attack hits you dealing "<<attack*10<<" of damage\n";
            p_health -= attack*10;
        }
    }

    void datk(int &p_energy, int &p_health) {
        std::cout<<name<<" attacks!\n";
        int rng[3] = {rand() % 7, rand() % 7, rand() % 7};
        if (rng[0] == rng[1] || rng[0] == rng[2]) {
            std::cout<<name<<" missed his attack, what a moron\n";
        }
        else {
            std::cout<<name<<" attack hits you dealing "<<attack*10<<" of damage\n";
            p_health -= ((attack * 10) / 100) * 25;
        }
    }
    void savegame(std::ofstream &save) {
        save.write((char*)this, sizeof(Enemy));
    }
};

class Characters {
    int health;
    int attack;
    int energy;
    std::string name;
    int issave;

    public:
    Characters() {
        health = 100;
        attack = 2;
        energy = 20;
        name = "";
        issave = 0;
    }

    bool isAsave() {
        if (issave == 67) {
            return true;
        } else return false;
    }

    void setname() {
        std::cout<<"What's your name mighty knight?\nMy name is: ";
        std::cin>>name;
        std::cout<<"\nPlease sir "<<name<<" kill the monster that's destroying our town!\n";
    }

    void atk(Enemy &enemy) {
        bool valid = false;
        while(true) {
            if (valid) break;
            int s = 0;
            std::cout<<"\nWhich attack do you want to use?\n1. Slash(-5 energy)    2. Pierce(-10 energy)\n3. Parry(+5 energy)    4. Back\nSelection: ";
            std::cin>>s;
            switch(s) {
                case 1:
                    std::cout<<"\nYou land a powerfull slash against "<<enemy.name<<" dealing "<<attack*10<<" of damage\n";
                    enemy.health -= attack*10;
                    enemy.atk(energy, health);
                    energy -= 5;
                    valid = true;
                    break;
                case 2: { // Metto le graffe perchè inizzializzo una variabile nel case
                    int rng[3] = {rand() % 10, rand() % 10, rand() % 10};
                    if (rng[0] == rng[1] || rng[0] == rng[2]) {
                        std::cout<<"\nYou pierce with your sword through "<<enemy.name<<" body dealing "<<attack*30<<" of damage\n";
                        enemy.health -= attack*30;
                    }
                    else std::cout<<"You missed your attack\n";
                    enemy.atk(energy, health);
                    energy -= 10;
                    valid = true;
                    break;
                } // Qui la variabile decade
                    
                case 3: {
                    std::cout<<enemy.name<<" attacks!\n";
                    int rng[3] = {rand() % 7, rand() % 7, rand() % 7};
                    if (rng[0] == rng[1] || rng[0] == rng[2]) {
                        std::cout<<"\nYou parried "<<enemy.name<<" attack restoring 5 of your energy \n";
                        energy += 5;
                    }
                    else {
                        std::cout<<enemy.name<<" attack hits you dealing "<<enemy.attack*10<<" of damage\n";
                        health -= enemy.attack*10;
                    }
                    valid = true;
                    break;
                }
                    
                case 4:
                    return;
                    break;

                default:
                    std::cout<<"\nSelection not valid!\n";
                    continue;
            }
        }
    }

    void rest(int &energy) {
        std::cout<<"\nYou decided to catch your breath for a moment, you restore 10 of your energy\n";
        energy += 10;
    }

    void doSMT(Enemy &enemy) {
        bool valid = false;
        while(true) {
            if (enemy.health <= 0) {
                std::cout<<"\nYou defeated "<<enemy.name<<"!\n";
                return;
            } else if (health <= 0) {
                std::cout<<"\nYou got defeated by"<<enemy.name<<"!\n";
                return;
            }
            if (valid) break;
            int s = 0;
            std::cout<<"Health: "<<health<<"    Energy: "<<energy<<"\n";
            std::cout<<"What you want to do?\n1. Attack    2. Shield yourself\n3. Rest    4. Save\n5. Quit\nSelection: ";
            std::cin>>s;
            switch(s) {
                case 1:
                    atk(enemy);
                    break;

                case 2:
                    enemy.datk(energy, health);
                    break;
                    
                case 3:
                    rest(energy);
                    break;
                
                case 4: {
                    issave = 67;
                    std::ofstream save{"save.dat", std::ios::binary};
                    save.write((char*)this, sizeof(Characters));
                    enemy.savegame(save);
                    std::cout<<"Game saved\n";
                    break;
                }

                case 5:
                    return;
                    break;

                default:
                    std::cout<<"\nSelection not valid!\n";
                    continue;
            }
        }
    }
};

main() {
    Characters Campo;
    Enemy Job;
    std::cout<<"Do you want to start a new game or load one?\n1. New Game\n2. Load Game\nSelection: ";
    int selection;
    std::cin>>selection;
    switch(selection) {
        case 1:
            Campo.setname();
            Campo.doSMT(Job);
            break;
        case 2:
            std::ifstream load{"save.dat", std::ios::binary};
            load.read(reinterpret_cast<char*>(&Campo), sizeof(Characters));
            if (!Campo.isAsave() || load.bad()) { // bad indica se la lettura è fallita per un motivo grave
                error("An error has occurred when loading the savefile");
                return 1;
            }
            load.read(reinterpret_cast<char*>(&Job), sizeof(Characters));
            if (load.eof()) { //Vero se ha raggiunto la fine del file
                std::cout<<"Save file loaded\n";
            }
            Campo.doSMT(Job);
            break;
    }
}
