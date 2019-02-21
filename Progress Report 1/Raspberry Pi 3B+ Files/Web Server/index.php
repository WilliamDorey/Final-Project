<!DOCTYPE html>
<head>
  <link rel="stylesheet" type="text/css" href="resources/basic.css">
</head>
<h1>Monitoring</h1>
<p>     Welcome to the monitoring screen. From here you can obtain the current weight of any objects in the container, the most upto date activity at the container, and even obtain a live image.</p>
<div>
  <h2>Last Movement Update</h2>
  <img src="archive/live.jpg" width="1280" height="720" class="center">
  <br></br>
</div>

<?php
  $date = `date`;
  echo $date;
  `cat /var/www/html/scripts/live.py | sudo ssh pi@pizero python -`;
  `sudo scp pi@pizero:/home/pi/live.jpg /var/www/html/archive/live.jpg`;
?>
