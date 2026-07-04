#include <wx/wx.h>
#include "chill.hpp"

// Definisco l'app
class AppChill : public wxApp {
    public:
        // OnInit viene chiamato all'avvio, è tipo il main() dei programmi classici
        virtual bool OnInit() {
            // Metto la finestra sul Heap con new così campa anche fuori da OnInit()
            FinestraChill* finestra = new FinestraChill();
            
            finestra->Center();
            // Di base sta tutta sneaky nascosta nelle backrooms quindi bisogna dirgli di mostrarsi
            finestra->Show(true);
            // Diciamo a quel menomato di wxWidgets che tutto è apposto
            return true;
        }
};
// Diciamo a wxWidgets di usare AppChill come motore principale
wxIMPLEMENT_APP(AppChill);