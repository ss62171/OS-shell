#include "headers.h"
#define command_delms " \t\n"

int parse(char *command, char **all_commands,char sep)
{
    char * seperate=strtok(command,";");
    int count = 0;
	while(seperate!=NULL)
	{
		all_commands[count++]=seperate;
		seperate=strtok(NULL,";");
	}
	return count;
}

long long int parse_single_command(char *command,char **command_parts, char sep)
{
	char * seperate=strtok(command,command_delms);
    long long int num=0;

	while(seperate!=NULL)
	{
		command_parts[num]=seperate;
		num+=1;
		seperate=strtok(NULL,command_delms);
	}
	return num;
}

void parse_echo(char ** command_parts)
{
    for(int i=1;command_parts[i]!='\0';i++)
        printf("%s ",command_parts[i]);
    printf("\n");
}

int echo_check(char *command)
{
	char * seperate=strtok(command,"\"");
    int count = 0;
	while(seperate!=NULL)
    {
        if(count == 1)
        printf("%s\n",seperate);
		seperate=strtok(NULL,"\"");
        count++;
    }
    return count;
}
