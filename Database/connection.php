<?php
$username = "AdminWeerstation";
$password = "kz,yRmC%?r4x8D@";
$host = "localhost";
$db_name = "weerstation";
$con = mysqli_connect ($host, $username, $password);
$db = mysqli_select_db ( $con, $db_name );
?>
