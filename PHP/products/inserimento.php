<?php

include "connessione.php";

$nome = "";
$prezzo = "";

if($_SERVER["REQUEST_METHOD"] == "POST") {
    $nome = $_POST["nome"];
    $prezzo = $_POST["prezzo"];

    $inserimento = $conn->prepare("INSERT INTO prodotti(Nome, Prezzo) VALUES(?,?)");

    $inserimento->bind_param("sd", $nome, $prezzo);

    if($inserimento->execute()) {
        header("refresh:2;url=/inserimento.php");
        echo "Prodotto inserito con successo!";
    } else echo "Errore durante l'inserimento del prodotto ( ".$inserimento->error." )";
}

?>
<!DOCTYPE html>
<html>
<head>
    <title>Inserimento prodotto</title>
    <link rel="stylesheet" href="/form.css">
</head>
<body>
    <div>
        <h1>Inserimento prodotto</h1>
    </div>
    <div class="form-box">
        <form method="POST">
            <label for="nome">Nome prodotto:</label>
            <input type="text" id="nome" name="nome" placeholder="es Cubo di amianto" required><br>
            <label for="prezzo">Prezzo prodotto:</label>
            <input type="number" id="prezzo" name="prezzo" step=".01" placeholder="in EURO" required><br>
            <input type="submit" id="submitBTN" value="Inserisci"><br>
            <input type="reset" id="resetBTN" value="Pulisci"><br>
            <a href="/eliminazione.php" style="align-self: center">Elimina prodotto</a>
        </form>
    </div>
</body>
</html>