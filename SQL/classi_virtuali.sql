CREATE TABLE Studenti (
    CodiceFiscale varchar(16) PRIMARY KEY,
    Nome varchar(20) NOT NULL,
    Cognome varchar(20) NOT NULL,
    Classe tinyint UNSIGNED NOT NULL,
    Sezione varchar(3) NOT NULL
);

CREATE TABLE Classi (
    CodiceIscrizione int UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    Nome varchar(30) NOT NULL,
    Materia varchar(30) NOT NULL,
    Classe tinyint UNSIGNED NOT NULL,
    Sezione varchar(3) NOT NULL
);

CREATE TABLE Iscrizioni (
    CodiceFiscale varchar(16) NOT NULL,
    CodiceIscrizione int UNSIGNED NOT NULL,
    FOREIGN KEY (CodiceFiscale) REFERENCES Studenti(CodiceFiscale),
    FOREIGN KEY (CodiceIscrizione) REFERENCES Classi(CodiceIscrizione)
);

CREATE TABLE Videogiochi (
    ID int UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    Nome varchar(30) NOT NULL,
    Argomento varchar(50) NOT NULL,
    Durata time NOT NULL,
    MoneteOttenibili tinyint UNSIGNED NOT NULL,
    DescrizioneBreve varchar(160),
    DescrizioneEstesa varchar(500)
);

CREATE TABLE Monete (
    CodiceFiscale varchar(16) NOT NULL,
    ID int UNSIGNED NOT NULL,
    MoneteOttenute tinyint UNSIGNED NOT NULL,
    FOREIGN KEY (CodiceFiscale) REFERENCES Studenti(CodiceFiscale),
    FOREIGN KEY (ID) REFERENCES Videogiochiclasse(ID)
);

CREATE TABLE Videogiochiclasse (
    CodiceIscrizione int UNSIGNED NOT NULL,
    ID int UNSIGNED NOT NULL,
    FOREIGN KEY (CodiceIscrizione) REFERENCES Classi(CodiceIscrizione),
    FOREIGN KEY (ID) REFERENCES Videogiochi(ID)
);

CREATE TABLE Docenti (
    CodiceFiscale varchar(16) PRIMARY KEY,
    Nome varchar(20) NOT NULL,
    Cognome varchar(20) NOT NULL
);

CREATE TABLE Insegnanti (
    CodiceFiscale varchar(16) NOT NULL,
    CodiceIscrizione int UNSIGNED NOT NULL,
    FOREIGN KEY (CodiceIscrizione) REFERENCES Classi(CodiceIscrizione),
    FOREIGN KEY (CodiceFiscale) REFERENCES Docenti(CodiceFiscale)
);

SELECT * --Seleziono tutte le colonne della tabella
FROM Videogiochi
WHERE Argomento = 'Integrali' --Dico alla query di prendere solo i dati dei videogiochi con come valore "Integrali"
ORDER BY Nome ASC; --Ordino in modo ascendente in base al nome

SELECT 
    Studenti.nome,
    Studenti.cognome,
    Videogiochi.nome,
    Monete.MoneteOttenute
FROM Studenti
JOIN Monete ON Studenti.CodiceFiscale = Monete.CodiceFiscale --JOIN aggiunge una tabella che non abbiamo già alla query mentre ON gli dice di collegare ogni riga di una tabella alle righe di un altra se quei valori combaciano
JOIN Videogiochi ON Monete.ID = Videogiochi.ID
JOIN Videogiochiclasse ON Videogiochi.ID = Videogiochiclasse.ID
WHERE Videogiochiclasse.CodiceIscrizione = 1
AND Videogiochi.ID = 1
ORDER BY Monete.MoneteOttenute DESC;

SELECT
    Videogiochi.Nome,
    COUNT(Videogiochiclasse.CodiceIscrizione) AS NumeroClassi
FROM Videogiochi
JOIN Videogiochiclasse ON Videogiochi.ID = Videogiochiclasse.ID
GROUP BY Videogiochi.ID, Videogiochi.Nome
ORDER BY Videogiochi.ID ASC;

SELECT
    Studenti.Nome,
    Studenti.Cognome,
    Studenti.Classe,
    Studenti.Sezione,
    IFNULL(SUM(MoneteOttenute), 0) AS MoneteTotali --Se il valore è nullo lo imposto a 0
FROM Studenti
LEFT JOIN Monete ON Studenti.CodiceFiscale = Monete.CodiceFiscale
GROUP BY Studenti.Nome, Studenti.Cognome, Studenti.Classe, Studenti.Sezione
ORDER BY MoneteTotali DESC;

INSERT INTO Studenti
VALUES ('RSSMRA80A01H501W', 'Mario', 'Rossi', 3, 'A'); --Inserisco i dati nella tabella, in questo modo vengono messi seguendo l'ordine della struttura

INSERT INTO Docenti
VALUES ('BNCLRA85B02L219Z', 'Laura', 'Bianchi');

INSERT INTO Classi (Nome, Materia, Classe, Sezione)
VALUES ('Matematica Avanzata', 'Matematica', 3, 'A'); --Inserisco i dati nella tabella, in questo modo vengono messi seguendo l'ordine in parentesi

INSERT INTO Iscrizioni
VALUES ('RSSMRA80A01H501W', 1);

--Comando CREATE

CREATE TABLE Studenti ( --Creo una tabella
    colonna datatype constraint
);

CREATE TABLE Primini AS --Creo una tabella basata su un altra prendendone i dati, è anche possibile filtrare con WHERE
SELECT * FROM Studenti
WHERE Classe = 1;

--Comando ALTER

ALTER TABLE Studenti
ADD email varchar(255) NOT NULL; --Aggiunge una colonna

ALTER TABLE Studenti
DROP COLUMN email; --Rimuove una colonna

ALTER TABLE Studenti
RENAME COLUMN email to Email; --Rinomina una colonna

ALTER TABLE Studenti
MODIFY Email varchar(100) NOT NULL; --Modifica i parametri di una colonna

ALTER TABLE Studenti
ADD CONSTRAINT CHK_Classe CHECK (Classe >= 1 AND Classe <=5); --Anche (Classe BETWEEN 1 AND 5) va bene come comando

ALTER TABLE Studenti
RENAME TO Capre; --Rinomina una tabella

--Comando DROP

DROP TABLE Studenti; --Elimina una tabella

DROP TABLE IF EXISTS Studenti; --Elimina una tabella se esiste (è buona pratica farlo così)

TRUNCATE TABLE Studenti; --Elimina tutti i dati della tabella mantenendone la struttura

--Comando UPDATE

UPDATE Studenti
SET Nome = 'Davide', Cognome = 'Camposeo', Classe = 5 --Aggiorno i dati presenti in una tabella filtrando con WHERE
WHERE CodiceFiscale = 'RSSMRA80A01H501W';

--Comando DELETE

DELETE FROM Studenti WHERE CodiceFiscale = 'RSSMRA80A01H501W'; --Cancello i dati presenti in una tabella filtrando con WHERE

DELETE FROM Studenti --Cancello tutti i dati presenti in una tabella, la struttura non viene intaccata

--Comandi TCL

START TRANSACTION; --Attivo la modalità di transazione

COMMIT; --Salvo le modifiche effettuate

SAVEPOINT Salvataggio; --Creo un punto di salvataggio

ROLLBACK; --Faccio un undo dei cambiamenti effettuati riportandoli allo stato salvato nel SAVEPOINT

------------------------------------------------------------------------------------------------------------

ALTER TABLE Studenti
ADD Email varchar(100)  UNIQUE NOT NULL; --Aggiungi una colonna Email alla tabella Studenti. Deve essere unica e non nulla.

ALTER TABLE Videogiochi
MODIFY MoneteOttenibili tinyint UNSIGNED DEFAULT 10; --Modifica la tabella Videogiochi affinché il valore di default per MoneteOttenibili sia 10.

CREATE TABLE LogAccessi( 
    CodiceFiscale varchar(16) PRIMARY KEY,
    OraAccesso timestamp 
); --Crea una tabella LogAccessi che memorizzi il CodiceFiscale dello studente e l'ora di accesso (timestamp).

DROP TABLE IF EXISTS LogAccessi; --Elimina la tabella LogAccessi appena creata.

INSERT INTO Studenti
VALUES ('RSSMRA80A01H501W','Campo', 'Grasso', 5, 'A'); --Inserisci un nuovo studente (inventa i dati) e iscrivilo alla classe con CodiceIscrizione = 1.

INSERT INTO Iscrizioni
VALUES ('RSSMRA80A01H501W',1); --Inserisci un nuovo studente (inventa i dati) e iscrivilo alla classe con CodiceIscrizione = 1.

UPDATE Videogiochi
SET Durata = SEC_TO_TIME(TIME_TO_SEC(Durata) * 1.20)
WHERE Argomento = 'Storia'; --Aumenta del 20% la Durata di tutti i videogiochi che hanno come argomento "Storia".

DELETE FROM Monete WHERE MoneteOttenute = 0; --Elimina tutte le righe dalla tabella Monete dove MoneteOttenute è pari a 0.

UPDATE Studenti
SET Sezione = 'B'
WHERE CodiceFiscale = 'RSSMRA80A01H501W'; --Cambia la sezione dello studente con un determinato Codice Fiscale da "A" a "B".

SELECT
    Studenti.Nome,
    Studenti.Cognome
FROM Studenti
JOIN Iscrizioni ON Studenti.CodiceFiscale = Iscrizioni.CodiceFiscale
JOIN Classi ON Iscrizioni.CodiceIscrizione = Classi.CodiceIscrizione
WHERE Classi.Materia = 'Matematica'; --Visualizza il Nome e Cognome di tutti gli studenti iscritti alla classe di "Matematica".

SELECT
    Videogiochi.Nome
FROM Videogiochi
JOIN Videogiochiclasse ON Videogiochi.ID = Videogiochiclasse.ID
JOIN Classi ON Videogiochiclasse.CodiceIscrizione = Classi.CodiceIscrizione
JOIN Insegnanti ON Classi.CodiceIscrizione = Insegnanti.CodiceIscrizione
JOIN Docenti ON Insegnanti.CodiceFiscale = Docenti.CodiceFiscale
WHERE Docenti.Nome = 'Mario' AND Docenti.Cognome = 'Rossi'; --Mostra i titoli dei videogiochi assegnati alla classe in cui insegna il docente "Mario Rossi".

SELECT
    Studenti.Nome,
    Studenti.Cognome,
    IFNULL(SUM(Monete.MoneteOttenute), 0) AS MoneteTotali
FROM Studenti
LEFT JOIN Monete ON Monete.CodiceFiscale = Studenti.CodiceFiscale
GROUP BY Studenti.Nome, Studenti.Cognome
ORDER BY MoneteTotali DESC; --Calcola il totale delle MoneteOttenute per ogni studente, visualizzando Nome, Cognome e Totale.

SELECT
    Studenti.Nome,
    Studenti.Cognome,
    SUM(Monete.MoneteOttenute) AS MoneteTotali
FROM Studenti
LEFT JOIN Monete ON Monete.CodiceFiscale = Studenti.CodiceFiscale
GROUP BY Studenti.Nome, Studenti.Cognome
HAVING MoneteTotali >= 50 --Uso HAVING per i valori calcolati
ORDER BY MoneteTotali DESC; --Trova tutti gli studenti che hanno ottenuto più di 50 monete in totale.

SELECT
    Videogiochi.Nome
FROM Videogiochi
LEFT JOIN Monete ON Videogiochi.ID = Monete.ID
WHERE Monete.CodiceFiscale IS NULL; --Seleziona i nomi dei videogiochi che non sono mai stati giocati da nessuno studente (ovvero non presenti nella tabella Monete).
