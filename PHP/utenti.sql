CREATE TABLE utenti (
  ID int UNSIGNED PRIMARY KEY AUTO_INCREMENT,
  Username varchar(30) UNIQUE NOT NULL,
  Email varchar(50) UNIQUE NOT NULL,
  passwrd varchar(60) NOT NULL
)