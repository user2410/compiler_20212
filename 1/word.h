#ifndef WORD_H
#define WORD_H

#define LINE_LEN        100
#define WORD_MAX_LEN	100
#define MAX_W           100
#define MAX_STOP_W      100
#define MAX_LINE_CNT	100

char buf[LINE_LEN];
#define readLine(fstream) ({\
    fgets(buf, LINE_LEN, fstream);\
    ui len = strlen(buf);\
    if(buf[len-1] == '\n') buf[len-1] = '\0';\
    if(buf[len-2] == '\r') buf[len-2] = '\0';\
})

typedef unsigned int ui;
typedef struct{
	char* word;
	ui count;
	int lines[MAX_LINE_CNT];
}mWord;

typedef struct{
	mWord* arr[MAX_W];
	ui count;
}mContainer;

mContainer* WInit();
mWord* WFindWord(mContainer* container, const char* word, long int* wleft);
mWord* WInsertNewWord(mContainer* container, char* word, ui line);
void WClean(mContainer* container);

#endif