#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "word.h"

#define int long int

static ui Wcnt = 0;
static ui stopWCnt = 0;
static char* stopW[MAX_STOP_W];

mContainer* WInit()
{
    FILE* fd = fopen("stopw.txt", "r");
    if(!fd)
    {
        return NULL;
    }
    while(!feof(fd))
    {
        readLine(fd);
        stopW[stopWCnt++] = strdup(buf);
    }
    fclose(fd);

    mContainer* container = (mContainer*)malloc(sizeof(mContainer));
    container->count = 0;

    return container;
}

static void Normalize(char* word)
{
    ui len = strlen(word);
    for(ui i=0; i<len; i++)
    {
        if(word[i]>='A' && word[i]<='Z')
            word[i] += 'a' - 'A';
    }
}

char isStopWord(char* word)
{
    int left = 0;
    int right = stopWCnt - 1;

    while(left <= right)
    {
        int m = (left + right) >> 1;
        int cmp = strcmp(word, stopW[m]);
        if(cmp > 0)
        {
            left = m+1;
        }
        else if(cmp < 0)
        {
            right = m-1;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

mWord* WFindWord(mContainer* container, const char* word, int* wleft)
{
    char searchWord[strlen(word)];
    strcpy(searchWord, word);

    Normalize(searchWord);
    
    int left = 0;
    int right = (int)container->count - 1;

    while(left <= right)
    {
        int m = (left + right) >> 1;
        int cmp = strcmp(searchWord, container->arr[m]->word);
        if(cmp > 0)
        {
            left = m+1;
        }
        else if(cmp < 0)
        {
            right = m-1;
        }
        else
        {
            *wleft = left;
            return container->arr[m];
        }
    }

    *wleft = left;
    return NULL;
}

mWord* WInsertNewWord(mContainer* container, char* word, ui line)
{
    if(isStopWord(word))
        return NULL;
    
    int left;
    mWord* cur = WFindWord(container, word, &left);

    if(cur)
    {
        cur->lines[cur->count++] = line;
        return cur;
    }

    char* newWord = strdup(word);
    Normalize(newWord);
    
    mWord* tmp = (mWord*)malloc(sizeof(mWord));
    if(!tmp)
    {
        return NULL;
    }

    tmp->word = newWord;
    tmp->count = 0;
    tmp->lines[tmp->count++] = line;
    
    // insert at left position
    int afterCnt = (int)container->count - left;
    // afterCnt = afterCnt >= 0 ? afterCnt : 0;
    mWord* cpy[afterCnt];
    memcpy(cpy, container->arr + left, afterCnt*sizeof(mWord*));
    container->arr[left++] = tmp;
    memcpy(container->arr + left, cpy, afterCnt*sizeof(mWord*));
    container->count++;
    
    return tmp;
}

void WClean(mContainer* container)
{
    for(ui i=0; i<container->count; i++)
    {
        mWord* word = container->arr[i];
        free(word->word);
        free(word);
    }
    free(container);
}