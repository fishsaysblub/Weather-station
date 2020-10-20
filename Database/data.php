<?php
  include ('connection.php');

  echo "data: \n";
  echo file_get_contents("php://input");
  echo "\n";
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
  return;
  /*$temp = "temp";
  $value = $_POST['temp'];

  $sql_insert = "INSERT INTO data (Reading, Value) VALUES ('$temp', $value)";
  if(mysqli_query($con,$sql_insert))
  {
  echo "Done";
  mysqli_close($con);
  }
  else
  {
  echo "error is ".mysqli_error($con );
}*/
?>
