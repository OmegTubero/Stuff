CREATE DATABASE Magazzino;
USE Magazzino;

CREATE TABLE prodotti (
    ID int UNSIGNED PRIMARY KEY AUTO_INCREMENT,
    Nome varchar(30) NOT NULL,
    Prezzo Decimal(5,2)
);