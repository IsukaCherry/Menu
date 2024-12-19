
#ifndef STRUCT_H
#define STRUCT_H
#define MAX 100
#define ALL 50
typedef struct
{
    char UsersName[MAX];
    char Password[MAX];
    int score;
    int daysStudied;
}User ;

typedef struct {
    char word[100];
    char partOfSpeech[100];
    char meaning[1000];
}Word;

typedef struct {
    int year;
    int month;
    int day;
}Time;


#endif
