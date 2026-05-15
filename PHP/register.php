<?php

include "connect.php";

$uname = "";
$email = "";
$password = "";
// Dico al php di eseguire questa parte di codice solamente se richiesta tramite POST, così in caso qualcuno copiasse e incollasse il link non farebbe niente SUCA!
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $uname = $_POST["uname"];
    $email = $_POST["email"];
    $password_plain = $_POST["passwrd"];
    $password = password_hash($password_plain, PASSWORD_DEFAULT); // Converto la password in chiaro in una password codificata, NOTA COGLIONE la lunghezza è di 60 quindi il campo nel db deve eessere lungo almeno 60

    $register_user_query = $conn->prepare("INSERT INTO utenti (Username, Passwrd) VALUES (?, ?)"); // Definisco un prepared statement fondamentale per prevenire la SQL injection ( if hacker = plz stop him ), l'operatore -> permette di accedere a membri e metodi di un oggetto

    $register_user_query->bind_param("ss", $uname, $password); // Binding dei dati, ss indica che stiamo inviando due string, i per int, d per double, b per dati binari

    $register_useremail_query = $conn->prepare("UPDATE utenti SET Email = ? WHERE Username = ?");

    $register_useremail_query->bind_param("ss", $email, $uname);

    try {
        $conn->begin_transaction(); // Attivo la modalità di transazione per evitare modifiche automatica al DB

        $register_user_query->execute();

        try {

        if ($register_useremail_query->execute()) { // Controllo se l'execute va a buon fine
            $conn->commit(); // Applico le modifiche al DB
            header("refresh:2;url=login.php"); // Reindirizzo l'utente al login, refresh 2 è il tempo di attesa priam del reindirizzamento
            echo "<br/> Registrazione effettuata! Reindirizzamento al login in corso...<br/>";
        } else {
            echo "<br/> Errore durante la registrazione: ".$register_user_query->error; // Stampo l'errore con l'operatore
            $conn->rollback(); // Annullo le modifiche
        }

        $register_user_query->close();
        } catch (mysqli_sql_exception $e) {

            if ($e->getCode() == 1062) {
                echo "Email già in uso";
                $conn->rollback();
            }
        }         
    } catch (mysqli_sql_exception $e) {
        
        if ($e->getCode() == 1062) {
            echo "Nome utente già in uso";
            $conn->rollback(); // Annullo le modifiche
        }
    }

    
}

?>
<!DOCTYPE html>
<html>
<head>
    <title>Registrazione</title>
</head>
<style>
    * { /* Serve a rimuovere l'offset predefinito del browser, * seleziona tutti gli elementi */
        margin: 0;
        padding: 0;
        box-sizing: border-box; /* Molto utile per gestire le dimensioni correttamente */
    }
    body {
        display: flex;
        flex-direction: column;
        justify-content: center;
        align-items: center;
        height: 100vh;
    }
    form {
        display: flex;
        flex-direction: column;
    }
    .formbox {
        display: flex;
        justify-content: center;
        align-items: center;
        padding: 30px;
        border: 4px solid black;
        border-radius: 15px;
        height: fit-content;
        width: fit-content;
    }
    .LoginNow {
        align-self: center;
    }
</style>
<body>
    <div>
        <h1>Registrazione</h1><br>
    </div>
    <div class="formbox">
    <form method="post">
        <label for="uname">Nome utente</label>
        <input type="text" name="uname" id="username" placeholder="rumeno67" required><br>
        <label for="email">Email</label>
        <input type="email" name="email" id="emailaddress" placeholder="rumeno67@yahoo.com" required><br>
        <label for="passwrd">Password</label>
        <input type="password" name="passwrd" id="password" placeholder="rame67!?!" required><br>
        <input type="submit" value="Register" id="RegisterBtn"><br>
        <a class="LoginNow" href="login.php">Log In</a>
    </form>
    </div>
</body>
</html>