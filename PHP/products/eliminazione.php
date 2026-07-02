<html>
<head>
    <title>Eliminazione prodotto</title>
    <link rel="stylesheet" href="/form.css">
    <?php

        include "connessione.php";

        $ID = "";

        $mostra = $conn->prepare("SELECT * FROM prodottiphp");

        $mostra->execute();

        $mostra_res = $mostra->get_result();

        if(mysqli_num_rows($mostra_res) == 0) {
            header("refresh:2;url=/inserimento.php");
            echo "Nessun prodotto presente nel Database, reindirizzamento alla pagina d'inserimento...";
            exit();
        }

        if($_SERVER["REQUEST_METHOD"] == "POST") {

            $ID = $_POST["ID"];

            $elimina = $conn->prepare("DELETE FROM prodottiphp WHERE ID=?");

            $elimina->bind_param("i", $ID);

            $elimina->execute();

            if($elimina->affected_rows == 0) {
                header("refresh:1;url=/eliminazione.php");
                echo "Prodotto non trovato!";
            } else {
                header("refresh:1;url=/eliminazione.php");
            }
        }
    ?>
</head>
<body>
    <h1>Eliminazione prodotto</h1>
    <div class=form-box>
        <form method="POST">
            <label for="ID">ID prodotto:</label>
            <input type="number" id="ID" name="ID" required><br>
            <input type="submit" id="eliminaBTN" value="Elimina"><br>
            <a href="/esercizi/25-05-2026/inserimento.php" style="align-self: center">Inserisci prodotto</a>
        </form>
    </div>
</body>
</html>

<?php

while ($row = mysqli_fetch_assoc($mostra_res)) {
    echo "<br>ID: ".$row['ID']." | Nome prodotto: ".$row['Nome']." | Prezzo: ".$row['Prezzo']."€";
}

?>