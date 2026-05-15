<?php
// Creo una variabile per la connessione al Database
$conn = mysqli_connect("localhost","root","","form");
// Controllo se la connessione va a buon fine
if (!$conn) {
    die ("Impossibile connettersi al database");
}
?>