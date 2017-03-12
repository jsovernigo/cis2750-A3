<html>

<head>
	<title>Message Login</title>
	<link href="style.css" type="text/css" rel="stylesheet">
</head>

<body>

<?php
exec("./create login.wpml", $output, $result);
foreach($output as $line)
{
	echo $line;
}
?>

</body>
</html>
