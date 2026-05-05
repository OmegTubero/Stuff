#include <iostream>
#include <vector>
#include <ctime>

class Date {
    int Day;
    int Month;
    int Year;

    public:
    int day;
    int month;
    int year;

    int GetDay() {
        return Day;
    }
    int GetMonth() {
        return Month;
    }
    int GetYear() {
        return Year;
    }
    void PrintDate() const { // In questo modo la funzione può interagire con una costante
        std::cout<<Day<<"/"<<Month<<"/"<<Year;
    }
    void SetNewDate() {
        Day = day;
        Month = month;
        Year = year;
    }
        Date() {
            std::time_t t = std::time(nullptr); // Prende la data attuale (interroga il sistema operativo per farsi dare l'ora attuale passando nullptr (oppure 0), diciamo alla funzione che vogliamo solo il valore di ritorno.)
            std::tm* actualdate = std::localtime(&t); // Converte la data in una struttura locale (prende il timestamp t (tramite il suo indirizzo &t) e lo converte in una struttura tm tenendo conto del fuso orario impostato sul computer.)
            Day = actualdate->tm_mday;
            Month = actualdate->tm_mon + 1; // Perchè conta da 0
            Year = actualdate->tm_year + 1900; // Perchè conta dal 1900
            day = Day;
            month = Month;
            year = Year;
        }
};

enum class Month { // Se non viene assegnato un valore per gli enumeratori successive il compilatore gli assegnera il valore del precedente +1
    gennaio=1, febbraio, marzo, aprile, maggio, giugno, luglio, agosto, settembre, ottobre, novembre, dicembre
};

enum class Day {
    lunedi=1, martedi, mercoledi, giovedi, venerdi, sabato, domenica
};

std::vector<std::string> Months = {"gennaio", "febbraio", "marzo", "aprile", "maggio", "giugno", "luglio", "agosto", "settembre", "ottobre", "novembre", "dicembre"};

std::vector<std::string> Days = {"lunedi", "martedi", "mercoledi", "giovedi", "venerdi", "sabato", "domenica"};

Date operator ++(Date &d) {
    if (d.month==1 || d.month==3 || d.month==5 || d.month==7 || d.month==8 || d.month==10 || d.month==12) {
        std::cout<<"31d "<<d.day<<"/"<<d.month<<"/"<<d.year<<"\n";
        if (d.day==31) {
            if (d.month==12) {
                ++d.year;
                d.month=1;
            } else ++d.month;
            d.day = 1;
        } else ++d.day;
    } else if (d.month==4 || d.month==6 || d.month==9 || d.month==11) {
        std::cout<<"30d "<<d.day<<"/"<<d.month<<"/"<<d.year<<"\n";
        if (d.day==30) {
            ++d.month;
            d.day=1;
        } else ++d.day;
    } else if (d.year % 4 == 0) {
        std::cout<<"29d "<<d.day<<"/"<<d.month<<"/"<<d.year<<"\n";
        if (d.day==29) {
            ++d.month;
            d.day=1;
        } else ++d.day;
    } else {
        std::cout<<"28d "<<d.day<<"/"<<d.month<<"/"<<d.year<<"\n";
        if (d.day==28) {
            ++d.month;
            d.day=1;
        } else ++d.day;
    }
    d.SetNewDate();
    return d;
}

main() {
    Date date1;
    std::cout<<"temps "<<date1.day<<"/"<<date1.month<<"/"<<date1.year<<"\n";
    date1.PrintDate();
    std::cout<<"\n";
    ++date1;
    date1.PrintDate();
}