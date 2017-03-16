<?php

$files = scandir("./messages");

$streams = array();

foreach($files as $fn)
{
	if(strpos($fn, "StreamUsers") !== false)
	{
		$streams[] = substr($fn, 0, strlen($fn) - 11);
	}
}

echo "<form id=\"adduser\" method=\"post\" action=\"addUser.php\">\n";

echo "<input type=\"text\" name=\"newstreams\"><br>\n";

foreach($streams as $stream)
{
	echo "<input type=\"checkbox\" name=\"streams[]\" value=\"$stream\">$stream<br>\n";
}
echo  "<input type=\"submit\" value=\"submit\"><input type=\"hidden\" name=\"remove\" value=\"false\"><input type=\"checkbox\" name=\"remove\" value=\"true\">Remove?</form>";

?>
