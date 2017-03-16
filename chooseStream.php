<html>

<head>
	<title>Forum Menu</title>
	<link href="style.css" type="text/css" rel="stylesheet">
</head>

<body>

<?php

exec("./create chooseStream.wpml", $output, $result);
include "interpret.php";

echo "<input type=\"hidden\" value=\"".$_POST["username"]."\" name=\"username\" form=\"\">";
echo "<input type=\"hidden\" value=\"".$_POST["username"]."\" name=\"username\" form=\"\">";
echo "<input type=\"hidden\" value=\"".$_POST["username"]."\" name=\"username\" form=\"\">";

?>

</body>
</html>
