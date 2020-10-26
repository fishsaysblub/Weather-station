<?php
$username = "root";
$password = "";
$host = "localhost";
$db_name = "weerstation";
$con = mysqli_connect ($host, $username, $password);
$db = mysqli_select_db ( $con, $db_name );
?>
