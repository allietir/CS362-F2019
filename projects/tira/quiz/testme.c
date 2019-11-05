/*
Name: Alexander Tir
ONID: tira
Sources: http://www.asciitable.com/
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//This function returns a character that I choose to be 
//between <space> and } which is the range 32 to 125 on the ASCII table.
char inputChar()
{
  char randomChar;
  // 125-32 = 93, so we will add the range 93 to the space character
  randomChar = ' ' + (rand() % 94);
  return randomChar;
}

//This function returns a random string consisting of 5 characters in the range
//e to t which is the range 101 to 116 on the ASCII table.
char *inputString()
{
  char randomString[6];
  for (int i = 0; i < 6; i++)
  {
    //116 - 101 = 15, so we will add the range 15 to the character 'e'
    randomString[i] = 'e' + (rand() % 16);
  }
    return randomString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
