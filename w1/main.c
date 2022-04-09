#include <stdio.h>
#include <string.h>

#include "word.h"

ui lineCount = 1;
#define isEndingChar(c) (c=='.' || c=='?' || c=='!' || c=='\r' ||\
			((!(c>='a'&& c<='z')) && (!(c>='A'&& c<='Z'))))

int main (int argc, char** argv)
{
    if(argc != 2)
    {
        perror("Usage: [./main] [filename] ");
        return 1;
    }

    FILE* fd = fopen(argv[1], "r");
    
    if(!fd){
        perror("Failed to open file");
        return 1;
    }
    
    mContainer* con = WInit();
    while(!feof(fd))
    {
        readLine(fd);
        char* token;
        char* rest = buf;
        while(token = strtok_r(rest, " !@^#$*(),.?0123456789", &rest)){
            //puts(token);
            if(token[0] >= 'A' && token[0] <= 'Z')
                continue;
            WInsertNewWord(con, token, lineCount);
        }
        lineCount++;
    }
    
    printf("Total word counts: %u\n", con->count);
    puts("\nWord\t\t|Counts\t|Lines");
    for(ui i=0; i<con->count; i++){
        mWord* word = con->arr[i];
        printf("%s\t\t|%u\t|", word->word, word->count);
        for(ui j=0; j<word->count; j++){
            printf("%d ", word->lines[j]);
        }
        puts("");
    }
    
    fclose(fd);
    WClean(con);
}