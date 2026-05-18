<?php

session_start(); // Apro una sessione

include "connect.php";

$email = "";
$password = "";
// Dico al php di eseguire questa parte di codice solamente se richiesta tramite POST, così in caso qualcuno copiasse e incollasse il link non farebbe niente SUCA!
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $email = $_POST["email"];
    $password_plain = $_POST["passwrd"];

    $login_user_query = $conn->prepare("SELECT * FROM utenti WHERE Email = ?"); // Creo una query e la assegno a login_user_query

    $login_user_query->bind_param("s", $email);

    $login_user_query->execute();

    $login = $login_user_query->get_result();

    // Controllo se la query ha restituito alemno una riga
    if (mysqli_num_rows($login) > 0){
        // Uso un array associativo per scorrere riga per riga i risultati della query
        $row = mysqli_fetch_assoc($login);
            // Verifica della password
            if (password_verify($password_plain, $row['passwrd'])){
                $_SESSION['uid'] = $row['ID']; // Creo della variabili super globali
                $_SESSION['uname'] = $row['Username'];
                $_SESSION['uemail'] = $row['Email'];
                $_SESSION['password'] = $password_plain;
                header("refresh:1;url=personal_area.php");
                echo "<br> Accesso all'area personale...";
            } else {
                echo "Password Errata!";
            }
    } else {
        echo "Utente non trovato!"; // Coglione fatti l'account che vendo i tuoi dati su Vinted
    }
}

?>
<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
    <link rel="stylesheet" type="text/css" href="form.css">
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
        height: fit-content;
        width: fit-content;
        padding: 30px;
        border: 4px solid black;
        border-radius: 15px;
    }
    .RegisterNow {
        align-self: center;
    }
</style>
<body>
    <div>
        <h1>Log In</h1><br>
    </div>
    <div class="formbox">
        <form method="post">
            <label for="email">Email</label>
            <input type="email" name="email" id="emailaddress" required><br>
            <label for="passwrd">Password</label>
            <input type="password" name="passwrd" id="password" required><br>
            <input type="submit" value="Log In" id="LogInBtn"><br>
            <a class="RegisterNow" href="register.php">Registrati</a>
        </form>
    </div>
</body>
</html> 