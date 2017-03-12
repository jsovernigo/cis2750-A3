<html>
<body>

<?php

$files = scandir('./');

foreach($files as $fn)
{
	if($fn[0] != '.')
	{
		echo $fn;
	}
}

?>

</body>
</html>
