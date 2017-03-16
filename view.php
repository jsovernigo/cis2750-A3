<html>

<head>
	<title>Viewing Streams</title>
	<link href="style.css" type="text/css" rel="stylesheet">
</head>

<body>

<?php

exec("./create view.wpml", $output, $result);
include "interpret.php";

?>

</body>

</html>
