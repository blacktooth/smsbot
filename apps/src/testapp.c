#include<stdio.h>
#include<stdlib.h>
int main(int argc, char ** argv)
{
	char * JSON_string = (char *) malloc(sizeof(char) * 1024);

	sprintf(JSON_string,"{	\"sendto\": \"%s\",	\"sendwhat\": \"%s\" }", getenv("SENTFROM"), getenv("TEXTSENT")) ;
	printf("%s", JSON_string);
	return 0;
}
