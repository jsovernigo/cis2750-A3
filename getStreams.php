<?php

$files = scandir("./messages");

$streams = array();
$streams[] = 'all';

$uname = $_POST["username"];

foreach ($files as $fn)
{
	/* if we are looking at a streamUsers file */
	if(strpos($fn, "StreamUsers") !== false)
	{
		$lines = file("messages/".$fn);
		foreach($lines as $buffer)
		{
			if(strpos($buffer, $uname) !== false)
			{
				$sbuff = substr($fn, 0, strlen($fn) - 11);
				$streams[] = $sbuff;
				break;
			}
		}
	}
}

echo "<form method=\"post\" action=\"viewPost.php\"><select>";

foreach($streams as $cstream)
{
	echo "<option value = $cstream>$cstream</option>";
}

echo "</select><input type=\"submit\" value=\"View Stream\"></form>";

?>
