#include "headers.h"
int is_bg;

void sig_handler(int signo)
 {
	 if(signo==SIGINT)
	 {
        //  printf("here\n");
		 fprintf(stderr,"\n");
	 }
}

int main()
{
    char c;
    int length = 0,i=0;
    char sep = ';';
    char* command_line_arg = (char*)malloc(sizeof(char)*buffer_size);
    char** all_commands=(char**)malloc((sizeof(char)*buffer_size)*buffer_size);
    char** command_parts=(char**)malloc((sizeof(char)*buffer_size)*buffer_size);
    
    int total;
    get_screen();
    set_directory();

    char* home = strdup(main_dir);
    if (home == NULL)
        printf("Some error occured\n");
    char* path = "/history.txt";
    size_t len = strlen(home) + strlen(path) + 1;
    char* fullpath = malloc(len);
    if (fullpath == NULL)
        printf("Some error occured\n");
    strcpy(fullpath, home);
    strcat(fullpath, path);
    
    while(1)
    {
        signal (SIGINT, sig_handler);   //new
  	    signal (SIGQUIT, sig_handler);  //new
 	    signal (SIGTSTP, sig_handler);  //new
        
        set_screen();
        int echo_flag = 0;
        command_line_arg = read_from_terminal();
        if(command_line_arg[strlen(command_line_arg)-1] != '\0')
        {
            write_to(command_line_arg,fullpath);
        }
        total = parse(command_line_arg,all_commands,sep);

        for(int i=0;i<total;i++)
		{
            is_bg = 0;
		    for(int j=0;j<buffer_size;j++)
		    	command_parts[j]='\0';

            echo_flag=echo_check(all_commands[i]);
            int n2;

            if(check(strdup(all_commands[i])) == -1) 
			{
  	  			if(in_r==1 || out_r==1)
                {
  	      			n2=red_parsing(command_line_arg,command_parts);
                }

                else
                {
                    n2=parse_single_command(all_commands[i],command_parts,sep);
                }

                if(!strcmp(command_parts[n2-1], "&\0"))
                {
                    is_bg = 1;
                    command_parts[n2-1] = NULL; 
                    background(command_parts,n2);
                }

                else if(!strcmp(command_parts[0], "pinfo\0"))
		            pinfo(command_parts);
                else if(!strcmp(command_parts[0], "history\0"))
		            history(command_parts,fullpath);
                else if(!strcmp(command_parts[0], "cd\0"))
	               cd(command_parts, cwd, main_dir);
                else if(!strcmp(command_parts[0], "pwd\0"))
	               pwd();
               
                else if(strcmp(command_parts[0], "unsetenv\0") == 0)
					unsett(n2,command_parts);
                else if(strcmp(command_parts[0], "setenv\0") == 0)
					sett(n2,command_parts);
                else if(strcmp(command_parts[0], "fg\0") == 0)
			        fg(n2,command_parts);
                else if(strcmp(command_parts[0], "bg\0") == 0)
			    	bg(n2,command_parts);
                else if(strcmp(command_parts[0], "jobs\0") == 0)
			    	jobs();
			    else if(strcmp(command_parts[0], "overkill\0") == 0)
			    	kill_all();
                else if(strcmp(command_parts[0], "kjob\0") == 0)
			    	kjob(n2,command_parts);
                else if(strcmp(command_parts[0], "quit\0") == 0)
                    _exit(0);
                else if(isalpha(command_parts[0][0]))
	            {
                	background(command_parts,n2);
	            }
        
            }
		    
            else
            {
                // printf("here_3\n");
                p_and_r(all_commands[i]);          
            }
    	}
    }
    return 0;
}

