CREATE TABLE Stati (
    ID tinyint UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    Nome varchar(20) NOT NULL
);

CREATE TABLE Allergeni (
    ID tinyint UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    Tipo varchar(20) NOT NULL
);

CREATE TABLE Dispensa (
    ID smallint UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    Nome varchar(30) NOT NULL,
    Disponibile boolean NOT NULL,
    QuantitaRimanente_g smallint UNSIGNED NOT NULL
);

CREATE TABLE Piatti (
    ID tinyint UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    QuantitaRichiesta_g smallint UNSIGNED NOT NULL,
    TempoDiPreparazione time NOT NULL,
    Nome varchar(30) NOT NULL,
    Descrizione varchar(200) NOT NULL,
    Prezzo decimal(4,2) NOT NULL
);

CREATE TABLE Menu (
    ID tinyint UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    PiattoID tinyint UNSIGNED NOT NULL,
    FOREIGN KEY (PiattoID) REFERENCES Piatti(ID)
);

CREATE TABLE Ordinazioni (
    ID tinyint UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    Tavolo tinyint UNSIGNED NOT NULL,
    PiattoID tinyint UNSIGNED NOT NULL,
    StatoID tinyint UNSIGNED NOT NULL,
    FOREIGN KEY (PiattoID) REFERENCES Piatti(ID),
    FOREIGN KEY (StatoID) REFERENCES Stati(ID)
);

CREATE TABLE Cucina (
    OrdinazioneID smallint UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    StatoID tinyint UNSIGNED,
    FOREIGN KEY (StatoID) REFERENCES Stati(ID)
);

CREATE TABLE Contenuto (
    AllergenoID tinyint UNSIGNED NOT NULL,
    DispensaID tinyint UNSIGNED NOT NULL,
    FOREIGN KEY (AllergenoID) REFERENCES Allergeni(ID),
    FOREIGN KEY (DispensaID) REFERENCES Dispensa(ID)
);

CREATE TABLE Ingredienti (
    PiattoID tinyint UNSIGNED NOT NULL,
    DispensaID tinyint UNSIGNED NOT NULL,
    FOREIGN KEY (PiattoID) REFERENCES Piatti(ID),
    FOREIGN KEY (DispensaID) REFERENCES Dispensa(ID)
);