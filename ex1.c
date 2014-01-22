#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 60
#define MAX_WORDS 100

typedef struct Index{
  char* word;
  int numberOfWords;
  char * line;
}Index;

typedef struct StopWordsTable{
  char* words[MAX];
  int size;
}StopWordsTable;

typedef struct IndexTable{
  Index table[MAX_WORDS];
  int size;
}IndexTable;

StopWordsTable stop;
IndexTable table;

void initTable();
int checkWord(char* str, int isStartSentence);
int findInStop(char* str);
void addWord(char *str, int line);

int main(){
  FILE *fin,*fout;
  int i_line,startSentence; // use i_line to index line when read text
  int i,j;
  char c;
  char str[80];

  initTable();
  // read stop words from stopw.txt file
  if((fin = fopen("stopw.txt","r")) == NULL){
    printf("Cant read file stopw.txt\n");exit(1);
  }
  while(fscanf(fin,"%s",str) == 1){
    char* buff = (char*)malloc((strlen(str)+1)*sizeof(char));
    strcpy(buff,str);
    toLower(buff);
    stop.words[(stop.size)++] = buff;
  }
  fclose(fin);
  qsort(stop.words,stop.size,sizeof(char*),compare_str);
      
  // read text from vanban.txt file
  if((fin = fopen("vanban.txt","r")) == NULL){
    printf("Cant read file vanban.txt\n");exit(1);
  }

  i=0;
  i_line = 1;
  startSentence = 1;
  while(!feof(fin)){
    if ((c=fgetc(fin)) != EOF){
      // if a word is alphabet add it to str string
      if(isAlphabet(c)){
        str[i++] = c;
      } else {
        str[i] = '\0';
        if(checkWord(str,startSentence)){
          char* buff = (char*)malloc(sizeof(char)*(strlen(str)+1));
          strcpy(buff,str);
          addWord(buff,i_line);
        }

        if (c == '\r'){
          i_line++;
        }
        startSentence = isEndSentenceCharacter(c);
        i = 0;
      }
    }
  }
  fclose(fin);

  for(i = 0; i < table.size; i++){
    Index index = table.table[i];
    printf("%s %d %s\n",index.word,index.numberOfWords,index.line);
  }

  return 0;
}

void initTable(){
  stop.size = 0;
  table.size = 0;
}

int checkWord(char* str, int isStartSentence){
  // str contains no space or numberic or ending-word character.
  int i;
  // check string's len
  if (strlen(str) < 1){
    return 0;
  }

  // check the first letter
  if (('A' <= str[0] && 'Z'>= str[0]) && !isStartSentence){
    return 0;
  }

  toLower(str);


  return findInStop(str);
}

int findInStop(char *str){
  int i;
  for(i = 0; i < stop.size; i++){
    int k = strcmp(str,stop.words[i]);
    if(k == 0){
      return 0;
    } else if (k < 0){
      return 1;
    }
  }
  return 1;
}
      
void addWord(char* str,int line){
  int i, j;
  for(i=0; i < table.size; i++){
    int k = strcmp(str,table.table[i].word);
    if (k == 0){
      // update values
      table.table[i].numberOfWords++;
      char* buf = catStr(table.table[i].line,catStr(",",intToStr(line)));
      table.table[i].line = buf;
      return;
    } else if (k < 0){
      // insert new
      for (j = table.size; j > i ; j--){
        table.table[j] = table.table[j-1];
      }

      Index index;
      index.word = str;
      index.numberOfWords = 1;
      index.line = intToStr(line);
      table.table[i] = index;
      table.size++;
      return;
    }
  }

  Index index;
  index.word = str;
  index.numberOfWords = 1;
  index.line = intToStr(line);
  table.table[(table.size)++] = index;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define EndSentenceCharacters ".?!"

// to lower a string
void toLower(char* str){
  int i;
  for (i = 0; i < strlen(str); i++){
    if ('A' <= str[i] && 'Z' >= str[i]){
      str[i] = str[i] - 'A' + 'a';
    }
  }
}

// check a character is an alphabetic or not
int isAlphabet(char c){
  return (c<= 'z' && c >='a')||(c<='Z' && c >= 'A');
}

// check a character is a character that end of sentence or not
int isEndSentenceCharacter(char c){
  int i;
  for(i=0;i<strlen(EndSentenceCharacters);i++){
    if(c == EndSentenceCharacters[i])
      return 1;
  }
  return 0;
}

char* intToStr(int num){
  char buf[10];
  sprintf(buf,"%d",num);
  char* buff = (char*)malloc((strlen(buf)+1)*sizeof(char));
  strcpy(buff,buf);
  return buff;
}

char* catStr(char* s1, char* s2){
  char* s = (char*)malloc((strlen(s1)+strlen(s2)+1)*sizeof(char));
  strcpy(s,s1);
  strcpy(&s[strlen(s1)],s2);
  return s;
}

int compare_str(const void * a, const void * b){
  const char *pa = *(const char**)a;
  const char *pb = *(const char**)b;

  return strcmp(pa,pb);
}