
#include "generation.h"
#include "tags.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	int i;
	/*
	char* argLine = ".h(text=\"hello\",size=6).d().t(text=\"This is your main webpage.\").b(name=\"press me, please.\",link=\"funStart.html\")\n";
	*/

	char* returnedTag;

	i = 0;

	returnedTag = createLink(".l(text=\"Welcome to our world.\",link=\"greeting.html\",align=\"center\")");

	puts(returnedTag);
	free(returnedTag);

	return 0;
}
