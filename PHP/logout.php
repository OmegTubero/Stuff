<?php

include "connect.php";

session_start();


header("refresh:2;url=login.php");


?>
<html>
<head>
    <title>Logout</title>
    <link rel="stylesheet" href="form.css" type="text/css">
</head>
<style>
    * {
        margin: 0;
        padding: 0;
        box-sizing: border-box;

    }
    body {
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        height: 100vh;
    }
</style>
<body>
    <h2>Logout in corso...</h2>
</body>
</html>
<?php

exit();

?>