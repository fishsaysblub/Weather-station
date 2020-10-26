<?php
  include ('connection.php');
  $_POST = json_decode(file_get_contents("php://input"), true);

  $temperature = $_POST["Temperature"];
  $humidity = $_POST["Humidity"];

  $sql_insert = "INSERT INTO reading (Temperature, Humidity, Light) VALUES ('$temperature', '$humidity', -1)";
  if(mysqli_query($con,$sql_insert))
  {
    echo "Done\n";
  }
  else
  {
    echo "error is ".mysqli_error($con );
  }
  return;

  $_POST = json_decode(file_get_contents("php://input"), true);

  //var_dump($_POST);

  foreach ($_POST as $key => $value)
  {
    print "$key => $value\n";
    $sql_insert = "INSERT INTO reading ('$key') VALUES ($value)";
    if(mysqli_query($con,$sql_insert))
    {
      echo "Done\n";
    }
    else
    {
      echo "error is ".mysqli_error($con );
    }
  }
  mysqli_close($con);
?>
