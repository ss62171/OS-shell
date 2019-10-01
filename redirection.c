#include "headers.h"
extern int p_no;
int open_infile() {

        int fd;
        if ((fd = open(infile, O_RDONLY))< 0)
            perror(infile);
        else
        {
            dup2(fd, 0);
            close(fd);
            return fd;
        }
        
}

int open_outfile(){
        int f;
        if(c_cat == 1){
            f = open(outfile,O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            if(f < 0)
                perror(outfile);
        }

        else if(c_cat == 2){
            f = open(outfile, O_CREAT |O_APPEND | O_WRONLY);
            if(f < 0)
                perror(outfile);
        }   
        dup2(f,1);
        close(f);
        return f;
}

void p_and_r(char* cmd){
	piping_parse(cmd);
    int temp = 2*p_no-2;
	int fd1[2];
	int fd2[2];
	int* pipes = (int* )malloc(sizeof(int)*(temp));

	int pid, in, out,i,status,j;
	char** commands_parts = malloc((sizeof(char)*buffer_size)*buffer_size);
	for(i=0;i<temp-1;i+=2) {
	    if(pipe(pipes)< 0) {
	        perror("pipe is not opened!\n");
	        return;
	        }
	    }
	    i=0;
		int flag=0;
        while(i<p_no)
        {
			(flag==0)?(pipe(fd2)):(pipe(fd1));
            pid = fork();
	        is_bg = 0;
			int tokens =red_parsing(strdup(p_cmds[i]), commands_parts);
            
	        if(pid < 0)
	            perror("forking Error!\n");
	        
			else if(!pid)
            {
				if(flag==0)
				{
					if(i!=p_no-1)
					{
						dup2(fd2[1],1);
					} 
					else if(out_r==1) out = open_outfile();
					if(i!=0) dup2(fd1[0],0);
					else if(in_r==1)
					 in = open_infile();
				}
			
				else
				{
					if(i!=p_no-1)
					{
						dup2(fd1[1],1);
						dup2(fd2[0],0);
					}
					else if(out_r==1)
					 out = open_outfile();
					if(i!=0)
						dup2(fd2[0],0);
					else if(in_r==1)
					 in = open_infile();
				}
				if(execvp(commands_parts[0],commands_parts)<0)
					kill(getpid(),SIGTERM);   
	        }
			if(flag!=0)
			{
				if(i!=p_no-1)
				{
					close(fd2[0]);
					close(fd1[1]);
				}
				else
					close(fd2[0]);		
			}
			else
			{
				if(i!=0)
					close(fd1[0]);
				if(i!=p_no-1)
					close(fd2[1]);
			}
			flag=!flag;
			waitpid(pid,NULL,0);
            i++;
		}
}