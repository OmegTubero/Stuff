<?php
$email = "";
$password_plain = "";

include "connect.php";

session_start(); // Apro una sessione

if (!isset($_SESSION['uid'])) { // In caso l'ID non sia presente chiudo la sessione e reindirizzo al LogIn
    header("Location: login.php");
    exit(); // Esco dalla sessione
}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $email = $_POST["uemail"];
    $password_plain = $_POST["upassword"];
    $password = password_hash($password_plain, PASSWORD_DEFAULT);

    $new_cred = $conn->prepare("UPDATE utenti SET Email=?, passwrd=? WHERE ID=?");

    $new_cred->bind_param("ssi", $email, $password, $_SESSION['uid']);

    if ($new_cred->execute()) {
        header("refresh:2;url=login.php");
        echo "Reindirizzamento al Log In...";
        exit();
    }
}

?>
<!DOCTYPE html>
<html>
<head>
    <title>Area Personale</title>
    <link rel="stylesheet" href="form.css" type="text/css">
</head>
<style>
    .form-box {
        display: flex;
        flex-direction: column;
        width: fit-content;
        height: fit-content;
        padding: 30px;
        border: 4px solid black;
        border-radius: 15px;
    }
    form {
        display: flex;
        flex-direction: column;
    }
</style>
<body> 
    <div class="form-box">
        <h1> Benvenuto <?php if($_SESSION['uname'] == "Campozeus") {  echo "RE DEL DIVANO"; } ?> <?= htmlspecialchars($_SESSION['uname']) ?></h1><br> <!-- con < ? php dico al php di eseguire il codice direttamente -->
        <form method="post">
            <h3>Pannello di controllo</h3><br>
            <label for="email">Email:</label> 
            <input type="email" id="email" name="uemail" value="<?= htmlspecialchars($_SESSION['uemail']) ?>" required><br> <!-- con uso il php, con htmlspecialchars() prevengo il cross site scripting -->
            <label for="password">Password:</label>
            <input type="password" id="password" name="upassword" value="<?= htmlspecialchars($_SESSION['password']) ?>" required><br>
            <input type="submit" id="submitbtn" value="Applica modifiche"><br>
            <a href="logout.php" style="align-self: center">Logout</a>
        </form>
    </div>
</body>
</html>
