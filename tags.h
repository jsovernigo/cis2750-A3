
#ifndef __GSOVERNIGO_TAGS_H__
#define __GSOVERNIGO_TAGS_H__

#define START_TAGS "<html><body>"
#define END_TAGS "</body></html>"
#define LINE_BREAK "<br>"

/**
 *
 */
char* createText(char* textTag);

/**
 *
 */
char* createHeader(char* headTag);

/**
 *
 */
char* createLink(char* linkTag);

/**
 *
 */
char* createButton(char* buttonTag);

/**
 *
 */
char* createInput(char* inputTag);

/**
 *
 */
char* createRadio(char* radioTag);

/**
 *
 */
char* createPicture(char* pictureTag);

/**
 *
 */
char* createExec(char* execTag);


/*-------------------------- start of user-made tags ---------------------------*/

/**
 *
 */
char* createDiv(char* divTag);

/**
 *
 */
char* createDependency(char* depTag);

/**
 *
 */
char* createAdd(char* addTag);

/**
 *
 */
char* createView(char* viewTag);

/**
 *
 */
char* createPost(char* postTag);

#endif
