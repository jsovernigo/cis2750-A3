<html>
<body>

<head>
	<title>User Added</title>
	<link href="style.css" type"text/css" rel="stylesheet">
</head>

<?php

exec("./create addedScreen.wpml", $output, $result);
include "interpret.php";

$sstring = "";

if($_POST["newstreams"] != "")
{
	$sstring = $sstrings.$_POST["newstreams"].",";
}

foreach($_POST["streams"] as $stream)
{
	$sstring = $sstring.$stream.",";
}

$sstring = substr($sstring, 0, -1);

$streamslist = explode(",", $sstring);

echo "<div id=\"card\"><p>";
echo "You were added to the following streams:<br>";
foreach($streamslist as $strm)
{
	echo "$strm<br>";
}

echo "<form method=\"post\" action=\"chooseStream.php\">";
include "brand.php";
echo "<input type=\"submit\" value=\"back\"></form>";

echo "</div></p>";

$username = $_POST["username"];
if($_POST["remove"] === "true")
{
	exec("./addauthor $username $sstring -r", $aout, $ares);
}
else
{
	exec("./addauthor $username $sstring", $aout, $ares);
}

?>

</body>
</html>
