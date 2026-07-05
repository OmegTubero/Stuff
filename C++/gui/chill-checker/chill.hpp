#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

#include <wx/wx.h>

// Definisco la finestra
class FinestraChill : public wxFrame {
    public: // Creazione del costruttore della classe FinestraChill che utilizza il framework grafico wxWidgets, Il primo parametro indica il padre, il secondo indica che ID assegnargli in qeusto caso lo fa automaticamente, il terzo è il titolo della finestra, il quarto indica dove far apparire la finestra, il quinto la dimensone 
            FinestraChill() : wxFrame(NULL, wxID_ANY,"Chill checker",wxDefaultPosition,wxSize(400, 300)) {   
                // Creo un pannello necessario per il testo
                wxPanel* PannelloChill = new wxPanel(this,wxID_ANY);

                wxStaticText* TestoChill = new wxStaticText(PannelloChill,wxID_ANY,"Stai chillando twin?",wxPoint(0,0),wxDefaultSize);
                // È l'equivalente del display: flex del CSS, il contenuto nelle parentesi è l'equivalente del flex-direction del CSS
                wxBoxSizer* SizerChill = new wxBoxSizer(wxVERTICAL);
                // Creo una casella di testo
                CasellaTestoChill = new wxTextCtrl(PannelloChill,wxID_ANY,"");
                // Creo un tasto
                TastoChill = new wxButton(PannelloChill,wxID_ANY,"Chill check",wxPoint(0,0),wxSize(150,50));
                // Aggiungiamo uno spazio vuoto elastico in alto (spinge verso il basso)
                SizerChill->AddStretchSpacer(1);
                // 0 è la proporzione 0(Il testo occuperà solo lo stretto necessario per contenere le lettere.) mentre 1(Il testo tutto lo spazio possibile.), 10 è il padding, wxALL gli dice di applicare il padding a tutti i lati del componente ci sono anche (wxTOP, wxBOTTOM, wxLEFT, wxRIGHT) per combinarli si usa |
                SizerChill->Add(TestoChill,0,wxALIGN_CENTER | wxALL,5);

                SizerChill->Add(CasellaTestoChill,0,wxALIGN_CENTER | wxALL,5);

                SizerChill->Add(TastoChill,0,wxALIGN_CENTER | wxALL,5);
                // Tipo evento, puntatore alla funzione membro da eseguire, Dice a wxWidgets che deve essere chiamato sull'istanza corrente  del frame
                TastoChill->Bind(wxEVT_BUTTON, &FinestraChill::ControlloDelChilling, this);
                // Aggiungiamo uno spazio vuoto elastico in basso (spinge verso l'alto)
                SizerChill->AddStretchSpacer(1);
                // Assegno il sizer al pannello
                PannelloChill->SetSizer(SizerChill);
                
            }
    private:
            wxButton* TastoChill;
            wxTextCtrl* CasellaTestoChill;
            // Creo l'event handler
            void ControlloDelChilling(wxCommandEvent &event) {
                // Prendiamo il contenuto della text box
                wxString InputUtente = CasellaTestoChill->GetValue();
                // Puliamo eventuali spazi vuoti prima e dopo
                InputUtente.Trim(true).Trim(false);
                // Eseguiamo il controllo (ignorando maiuscole/minuscole con CmpNoCase), se restituiscono 0, significa che la differenza è zero, quindi le stringhe sono identiche
                if (InputUtente.CmpNoCase("si") == 0) {
                    wxMessageBox("Stai tutto chill twin","Bravo",wxOK | wxICON_INFORMATION);
                } else if (InputUtente.CmpNoCase("no") == 0) {
                    wxMessageBox("Datti una reffata e chilla twin","Male male",wxOK | wxICON_INFORMATION);
                } else wxMessageBox("Che stai a di' twin?","Uh?",wxOK | wxICON_INFORMATION);
            }
};

#endif
