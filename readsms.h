#ifndef readsms_H_
#define readsms_H_
#define MAX_NUMBERS 256
#define COMMAND_MAX 1024
#define MAX_BUFFER_SIZE 2048
#define MAX_MOBILE_SIZE 15
#define MAX_KWD_SIZE 10
#define MAX_APPNAME_SIZE 10
#define MAX_SMS 1024
const char * DELIM_NUMBERS = ",";
const char * GAMMU_SMSD_PATH = "/usr/local/bin/gammu-smsd-inject";
const char * SMS_FOLDER_PATH = "/home/blacktooth/sms-gateway/";
const char * KWD_FILE_PATH = "/home/blacktooth/code/smsbot/apps/applist.db";
const char * APPS_PATH = "/home/blacktooth/code/smsbot/apps/";
const char * parse_KWD(char *);
const char * check_KWD(char *);
void setenvironment(char *, char *);
const char * pipe_output(const char *);
void parse_JSON(const char *);
/*
 * Dicitonary of keywords and corresponding apps.
 */
typedef struct KWD_APPDICT {
	const char *kwd;
	const char *app;
} KWD_APPDICT;
#endif
