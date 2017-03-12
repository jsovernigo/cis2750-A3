/**
 *	Julian Sovernigo
 *	0948924
 *	CIS*2750_W17
 *	gsoverni
 *	gsoverni@mail.uoguelph.ca
 *
 *	This file contains the main function for the addauthor program.
 *	Utilizes stream.h to update stream files located in messages/
 */
#include "stream.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	int i;
	int remove;
	char list[1024];
	char userName[512];

	/* checks the number of args present, makes sure we actually get a file name */
	if(argc < 2)
	{
		fputs("Too few arguments to execute.\n\tUsage: ./addAuthor [-r] <username>\n", stdout);
		return 1;
	}

	remove = 0;
	userName[0] = '\0';

	for(i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-r") == 0)
		{
			remove = 1;
		}
		else
		{
			strcat(userName, argv[i]);
			strcat(userName, " ");
		}
	}

	/* eliminates the space that follows the username. */
	if(userName[strlen(userName) - 1] == ' ')
	{
		userName[strlen(userName) - 1] = '\0';
	}
	

	/* prints the prompt, then gets the list from the user. */
	fputs("List Streams: ", stdout);
	fgets(list, 1024, stdin);

	if(!remove)
	{
		addUser(userName, list);
	}
	else
	{
		removeUser(userName, list);
	}
	
	return 0;
}
