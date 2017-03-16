<?php

$files = scandir("./messages");
$streams = array();
$username = $_POST["username"];

foreach($files as $fn)
{
	if(strpos($fn, "StreamUsers") !== false)
	{
		$lines = file("messages/".$fn);
		foreach($lines as $line)
		{
			if(strpos($line, $username) !== false)
			{
				$streams[] = substr($fn, 0, strlen($fn) - 11);
			}
		}
		
	}
}

echo "<form id=\"post\" method=\"post\" action=\"post.php\">\n";
echo "<textarea name=\"post\" rows=\"20\" cols=\"70\">\n</textarea><br>\n";

echo "<select name=\"stream\">\n";
foreach($streams as $stream)
{
	echo "<option value = $stream>$stream</option>\n";
}

echo "</select><br>\n";

echo "<input type=\"submit\" value=\"submit\">\n</form>\n";

?>
