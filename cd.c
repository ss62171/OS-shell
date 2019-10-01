#include "headers.h"

void cd(char ** command_parts,char *cwd,char *main_dir)
{
    if(command_parts[1]==NULL || strcmp(command_parts[1],"~\0")==0 || strcmp(command_parts[1],"~/\0")==0)
	{
		chdir(main_dir);
		strcpy(cwd,main_dir);
        set_directory();
	}
	else if(chdir(command_parts[1])==0)
	{   
		getcwd(cwd,buffer_size);
        set_directory();
	}
	else
	{
		perror("Error executing cd command...");
	}
}

void pwd()
{
    set_directory();
    printf("%s\n",disp_dir);
}

void echo(char * command)
{
    printf("%s\n",command);
}