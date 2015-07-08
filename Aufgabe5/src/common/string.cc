#include <common/string.h>

int strcmp(const char* a, const char* b){//vergleiche strings
  while(*a && *b){
    if(*a<*b)		//ist erstes unterschiedliches Zeichen von
      return -1;	//string 1 kleiner als von string 2 gib -1 zurück
    if(*a>*b)
      return 1;
    a++;
    b++;
  }
  return 0;
}

int strncmp(const char* a, const char* b, size_t n){
  while(*a && *b && n--){//vergleiche n zeichen von string 1 und 2
    if(*a<*b)
      return -1;
    if(*a>*b)
      return 1;
    a++;
    b++;
  }
  return 0;
}
