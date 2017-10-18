#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	//string filled with random chars tested for in the function
	char * charOptions = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ{}[]() ";
	
	//selecting a random char from the charOptions string
	char randomChar = charOptions[random() % strlen(charOptions)];
	
    return randomChar;
}

char *inputString()
{
	//random string with 6 characters as the test only looks at index 0 - 5
	int stringLength = 6;
	
	//string with lower case alphabet for string creation
	//char * charOptions = "abcdefghijklmnopqrstuvwxyz";
	char * charOptions = "rest";
    char * randomString = (char*) malloc(sizeof(char) * stringLength);
	
	//looping through each char in string to fill it with a random lower case char
	int i;
	for(i = 0; i < stringLength - 1; i++){
		randomString[i] = charOptions[random() % strlen(charOptions)];
	}
	
	//setting last char to null
	randomString[5] = '\0';
	//randomString = "reset\0";
	
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
	
	//this print must be removed to speed up the program
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
		&& state == 9){
      printf("error ");
	  //adding print here to state iteration c, s and state value after test completes
	  //printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
      exit(200);
    }
	free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
