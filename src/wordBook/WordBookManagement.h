    #ifndef WORDBOOKMANAGEMENT_H
#define WORDBOOKMANAGEMENT_H
#include "../entity/struct.h"
int ReadWordBook(char* fname,Word word[]);
void AddWord();
void DeleteWord();
void ModifyWord();
void AddMeaning();
void ViewWords();
#endif
