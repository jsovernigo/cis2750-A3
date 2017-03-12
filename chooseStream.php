<html>

<head>
	<title>Choose Stream</title>
	<link href="style.css" type="text/css" rel="stylesheet">
</head>

<body>

<?php

exec("./create chooseStream.wpml", $output, $result);

$script = "";
$inphp = 0;

include "interpret.php";

?>

</body>
</html>
