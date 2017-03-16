
#include"stream.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int updateStream(struct userPost* st)
{
	char streamFile[256]; 
	char streamUserFile[256];
	char streamDataFile[256];

	if(st == NULL)
	{
		return -1;
	}

	strcpy(streamFile, "messages/");
	strcpy(streamUserFile, "messages/");
	strcpy(streamDataFile, "messages/");

	strcat(streamFile, st->streamname);
	strcat(streamUserFile, st->streamname);
	strcat(streamDataFile, st->streamname);

	strcat(streamFile, "Stream");
	strcat(streamUserFile, "StreamUsers");
	strcat(streamDataFile, "StreamData");

	/* if the user has permission to post to this stream */
	if(checkIfPresent(streamUserFile, st->username) == 1)
	{
		FILE* stf;

		stf = fopen(streamFile, "a+");
		if(stf == NULL)
		{
			return -1;
		}
		else
		{
			int sizebytes;
			int finalbytes;

			char line[512];

			FILE* dtf;

			finalbytes = 0;

			/* the 16 extra bytes are for the "Sender: , \nDate: ,\n" sections, added together. */
			sizebytes = strlen(st->username) + strlen(st->date) + strlen(st->text) + 16;

			fprintf(stf, "Sender: %s\nDate: %s\n%s", st->username, st->date, st->text);

			/* update data file */

			dtf = fopen(streamDataFile, "r");
			if(dtf != NULL)
			{
				while(fgets(line, 512, dtf) != NULL)
				{
					/* gets the last set of bytes from the file */
					sscanf(line, "%d", &finalbytes);
				}
				fclose(dtf);
			}

			finalbytes += sizebytes;

			dtf = fopen(streamDataFile, "a+");
			fprintf(dtf, "%d\n", finalbytes);

			fclose(dtf);

		}
		fclose(stf);
	}
	else
	{
		return 1;
	}

	return 0;
}

int addUser(char* username, char* list)
{
	int i;
	int cpos;
	char buffer[512];

	cpos = 0;

	if(username == NULL || list == NULL)
	{
		return -1;
	}

	/* find all the commas */
	for(i = 0; i < strlen(list); i++)
	{
		buffer[cpos] = list[i];
		cpos ++;

		/* if we found a comma, we *should* have a complete file name */
		if(list[i] == ',' || i == strlen(list) - 1)
		{
			FILE* streamUserFile;
			char finalFileName[512];

			buffer[cpos] = '\0';

			if(buffer[cpos - 1] == ',')
			{
				buffer[cpos - 1] = '\0';
			}
			strcpy(finalFileName, "messages/");
			strcat(finalFileName, buffer);
			strcat(finalFileName, "StreamUsers");

			/* check if present */
			if(checkIfPresent(finalFileName, username) == 0)
			{

				streamUserFile = fopen(finalFileName, "a+");

				if(streamUserFile == NULL)
				{
					return -1;
				}
				else
				{
					fputs(username, streamUserFile);
					fputs(" 0\n", streamUserFile);
				}

				/* reset the buffer for the next file name. */
				cpos = 0;
				buffer[0] = '\0';

				fclose(streamUserFile);
			}
		}
	}

	return 0;
}

int removeUser(char* username, char* list)
{
	int i;
	int cpos;
	char buffer[500000];

	cpos = 0;

	if(username == NULL || list == NULL)
	{
		return -1;
	}

	/* find all the commas */
	for(i = 0; i < strlen(list); i++)
	{
		buffer[cpos] = list[i];
		cpos ++;

		/* if we found a comma, we *should* have a complete file name */
		if(list[i] == ',' || i == strlen(list) - 1)
		{
			int j;
			FILE* streamUserFile;
			char finalFileName[512];

			buffer[cpos] = '\0';
			if(buffer[cpos - 1] == ',')
			{
				buffer[cpos - 1] = '\0';
			}
			
			strcpy(finalFileName, "messages/");
			strcat(finalFileName, buffer);
			strcat(finalFileName, "StreamUsers");
			buffer[0] = '\0';
			cpos = 0;

			/* check if present */
			if(checkIfPresent(finalFileName, username) == 1)
			{
				int nlines;
				char contents[1024][256];

				streamUserFile = fopen(finalFileName, "r");

				if(streamUserFile == NULL)
				{
					return -1;
				}
				else
				{
					char lbuff[256];
					j = 0; 

					while(fgets(lbuff, 256, streamUserFile) != NULL)
					{
						/* essentially, if the username is not present on the line */
						if(strstr(lbuff, username) == NULL)
						{
							strcpy(contents[j], lbuff);
							j++;
						}
					}
					nlines = j;
				}
				fclose(streamUserFile);

				streamUserFile = fopen(finalFileName, "w");
				if(streamUserFile == NULL)
				{
					return -1;
				}
				else
				{
					int j;
					j = 0;
					/* while we are not at the end of the list */
					while(j < nlines)
					{
						fputs(contents[j], streamUserFile);
						j++;
					}
				}

				fclose(streamUserFile);

				/* reset the buffer for the next file name. */
				cpos = 0;
				buffer[0] = '\0';

			}
		}
	}

	return 0;
}

int checkIfPresent(char* fname, char* word)
{
	char line[1024];
	FILE* checkFile;

	checkFile = fopen(fname, "r");
	if(checkFile == NULL)
	{
		return 0;
	}

	/* check all lines in the file for word */
	while(fgets(line, 1023, checkFile) != NULL)
	{
		if(strstr(line, word) != NULL)
		{
			fclose(checkFile);
			return 1;
		}
	}

	fclose(checkFile);

	return 0;
}
