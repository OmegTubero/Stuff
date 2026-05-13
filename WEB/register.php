<?php
$uname = "";
$email = "";
$password = "";
// Creo una variabile per la connessione al Database
$conn = mysqli_connect("localhost","root","","form");
// Controllo se la connessione va a buon fine
if (!$conn) {
    die ("Impossibile connettersi al database");
}
// Dico al php di eseguire questa parte di codice solamente se richiesta tramite POST, così in caso qualcuno copiasse e incollasse il link non farebbe niente SUCA!
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $uname = $_POST["uname"];
    $email = $_POST["email"];
    $password_plain = $_POST["passwrd"];
    $password = password_hash($password_plain, PASSWORD_DEFAULT); // Converto la password in chiaro in una password codificata, NOTA COGLIONE la lunghezza è di 60 quindi il campo nel db deve eessere lungo almeno 60

    $register_user_query = $conn->prepare("INSERT INTO utenti (Username, Email, Passwrd) VALUES (?, ?, ?)"); // Definisco un prepared statement fondamentale per prevenire la SQL injection ( if hacker = plz stop him ), l'operatore -> permette di accedere a membri emetodi di un oggetto

    $register_user_query->bind_param("sss", $uname, $email, $password); // Binding dei dati, ss indica che stiamo inviando due string, i per int, d per double, b per dati binari

    if ($register_user_query->execute()) { // Controllo se l'execute va a buon fine
        header("refresh:2;url=login.php"); // Reindirizzo l'utente al login, refresh 2 è il tempo di attesa priam del reindirizzamento
        echo "<br/> Registrazione effettuata! Reindirizzamento al login in corso...<br/>";
    } else {
        echo "<br/> Errore durante la registrazione: ".$register_user_query->error; // Stampo l'errore con l'operatore
    }

    $register_user_query->close();
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