#include "headers.h"

void get_screen()
{ 
    gethostname(hostname,buffer_size-1);
    getcwd(main_dir,buffer_size-1);
	strcpy(cwd,main_dir);
}   


void set_screen()
{
    char *name;
    name=getenv("USER");
    printf("%s@%s:%s$",name,hostname,disp_dir);
}

void set_directory()
{
    int temp=1;
    int flagg = 1;
    int i = strlen(cwd)-strlen(main_dir);

    for(int j=0;j<buffer_size;j++)
        disp_dir[j] = '\0';


    for(int j=0;j<strlen(main_dir);j++)
    {
        if(main_dir[j]!=cwd[j])
        {
            flagg = 0;
            break;
        }
    }

    if(flagg == 1)
    {
        disp_dir[0] = '~';
        for(int j=strlen(main_dir);j<strlen(cwd);j++)
        {
            disp_dir[temp] = cwd[j];
            temp++;
        }
    }
    else
    {
        for(int j=0;j<strlen(cwd);j++)
            disp_dir[j] = cwd[j];
    }
    
}