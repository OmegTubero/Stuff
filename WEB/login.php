<?php
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
    $email = $_POST["email"];
    $password_plain = $_POST["passwrd"];

    $login_user_query = "SELECT * FROM utenti WHERE Email = '$email'"; // Creo una query e la assegno a login_user_query

    $login = mysqli_query($conn, $login_user_query); // Metto la query sqli in una variaible per comodità

    // Controllo se la query ha restituito alemno una riga
    if (mysqli_num_rows($login) > 0){
        // Uso un array associativo per scorrere riga per riga i risultati della query
        while($row = mysqli_fetch_assoc($login)) {
            // Verifica della password
            if (password_verify($password_plain, $row['passwrd'])){
                echo "ID: ".$row['ID']."<br/>Username: ".$row['Username']."<br/>Email: ".$row['Email'];
            } else {
                echo "Password Errata!";
            }
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
    <link rel="icon" type="image/icon" href="">
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