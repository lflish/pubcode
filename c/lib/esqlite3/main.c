#include <stdio.h>

int main(int a, char *b[]){
  int i = 0;

  for(; b[i] != NULL; i++)
    printf("%s\n", b[i]);

}
