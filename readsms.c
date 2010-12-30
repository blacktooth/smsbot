/*
 * This is executed when a SMS is received
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "readsms.h"
#include "messages.h"
#include "cJSON.h"
char * SENDTO;
char * SENDWHAT;
unsigned int reply_SMS(char * numbers_string, const char * message)
{
	char * number = (char *) malloc(sizeof(char) * MAX_MOBILE_SIZE);
	char * buffer = (char *) malloc(sizeof(char) * MAX_BUFFER_SIZE);
	char * command = (char *) malloc(sizeof(char) * COMMAND_MAX);
	unsigned int numbers_messages_sent = 0;
	strcpy(buffer,numbers_string);
	for( number = strtok(buffer, DELIM_NUMBERS); number != NULL; number = strtok(NULL, DELIM_NUMBERS) )
	{
		sprintf(command, "%s TEXT %s -len %d -text \"%s\"", GAMMU_SMSD_PATH, number, strlen(message), message);
		if(system(command) == 0)
			numbers_messages_sent++;
	}
	return numbers_messages_sent;
}

const char * check_KWD(char * KWD)
{
	FILE * appfile = fopen(KWD_FILE_PATH,"r+");
	char * content = (char *) malloc(sizeof(char) * MAX_BUFFER_SIZE);
	char * p_tuple;
	char * temp = (char *) malloc(sizeof(char) * MAX_BUFFER_SIZE);
	fgets(content, MAX_BUFFER_SIZE, appfile);
	fclose(appfile);
	strcpy(temp, content);
	for(p_tuple = strtok(content, "|");p_tuple != NULL; p_tuple = strtok(NULL, "|"))
	{
		char * p_kwd = strtok(p_tuple, "->");
		char * p_app = strtok(NULL,">");
		if(!strcmp(p_kwd, KWD))
		{
			char * command = (char *) malloc(sizeof(char) * COMMAND_MAX);
			sprintf(command, "%s%s",APPS_PATH, p_app);
			return (const char *) command;
		}
		strcpy(content, temp);	
	}
	return NULL;
}

void setenvironment(char * SENDER, char * SMS_CONTENT)
{
	setenv("SENTFROM", SENDER, 1);
	setenv("TEXTSENT", SMS_CONTENT, 1);
}

const char * pipe_output(const char * command)
{
	FILE * CHLD_PIPE;
	char * CHLD_STDOUT = (char *) malloc(sizeof(char) * MAX_SMS);
	CHLD_PIPE = (FILE *) popen(command, "r");
	fread(CHLD_STDOUT, sizeof(char), MAX_SMS, CHLD_PIPE);
	pclose(CHLD_PIPE);
	return (const char *) CHLD_STDOUT;
}

void parse_JSON(const char * JSON_string)
{
	SENDTO = (char *) malloc(sizeof(char) * MAX_MOBILE_SIZE);
	SENDWHAT = (char *) malloc(sizeof(char) * MAX_BUFFER_SIZE);
	cJSON * root = cJSON_Parse(JSON_string);
	SENDTO = cJSON_GetObjectItem(root, "sendto")->valuestring;
	SENDWHAT = cJSON_GetObjectItem(root, "sendwhat")->valuestring;
}

int main(int argc, char **argv)
{
	int NUMBER_PARTS_SMS = atoi(getenv("SMS_MESSAGES"));
	char * SENDER = getenv("SMS_1_NUMBER");
	char * SMS_TEXT = getenv("SMS_1_TEXT");
	char * KWD = strtok(SMS_TEXT, " ");
	char * SMS_CONTENT = strtok(NULL,"");
	if(NUMBER_PARTS_SMS > 1)
		reply_SMS(SENDER, ERR_LONG_SMS);
	else
	{	
		if(check_KWD(KWD) != NULL)	
		{
			setenvironment(SENDER, SMS_CONTENT);
			parse_JSON(pipe_output(check_KWD(KWD)));
			reply_SMS(SENDTO, SENDWHAT);
		}	
		else
			reply_SMS(SENDER, ERR_INVALID_KWD);
	}
	return 0;
}
