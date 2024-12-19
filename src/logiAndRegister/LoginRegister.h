#ifndef LOGINANDREGISTER_H
#define LOGINANDREGISTER_H
#include "../entity/struct.h"
int ReadUsersInf(char* filename,User users[]);
int Login();
int RegisterUser();
int WordBook();
void DayPlusOne();
int ReadTime(char* fname,Time time[]);
void Encourgement();
#endif
