#ifndef onegin
#define onegin
const int maxTextSize = 10000;

int readFromFile(const char* nameFile, char* index[]);
int checkForEmpty(char* str);
bool isAlphaOrNum(char a);

#endif