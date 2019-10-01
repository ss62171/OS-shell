#include "headers.h"

char* read_from_terminal()
{
	int i=0;
	char* command = (char*)malloc(sizeof(char)*buffer_size);

	while(1)
	{
	    char c;
		c=getchar();
		if(c!='\n')
			command[i++]=c;
		else
		{
			command[i++]='\0';
			break;
		}
	}
	return command;
}
