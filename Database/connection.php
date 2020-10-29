<?php
$username = "ljgastel";
$password = "Ab12345";
$host = "databases.aii.avans.nl";
$db_name = "ljgastel_db2";
$con = mysqli_connect ($host, $username, $password);
$db = mysqli_select_db ( $con, $db_name );
?>
