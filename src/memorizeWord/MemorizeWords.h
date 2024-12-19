#ifndef MEMORIZEWORDS_H
#define MEMORIZEWORDS_H
#include "../entity/struct.h"
void ViewWords();
int ReadWordBook(char* fname,Word wordbook[]);
void StartLearning();
void FourQuestions();
void SpellWords();
void ViewWrongWords();
void ScoreManagement();
void ReLearnWrongWords();
#endif
