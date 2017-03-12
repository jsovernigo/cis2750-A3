/**
 *	Julian Sovernigo
 *	0948924
 *	CIS*2750_W17
 *	gsoverni
 *	gsoverni@mail.uoguelph.ca
 *
 * 	this file contains source for an html generator. 
 */
#ifndef __GSOVERNIGO_GENERATION_H__
#define __GSOVERNIGO_GENERATION_H__

/**
 *
 */
void generatePage(char* fname);

/**
 *
 */
char* generateTag(char* configTag);

/**
 *
 */
char* getValue(char* attribute);

/**
 *
 */
char** splitTagLine(char* tagLine);

/**
 *	getArgs
 */
char** getArgs(char* wholeTag);

#endif
