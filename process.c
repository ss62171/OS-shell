#include "headers.h"
int is_bg;
void background(char ** command_parts,int n2)
{
	int status;
	pid_t wpid, wid;
	wpid=fork();

	if(wpid<0)
		perror("fork error\n");
	
	else if(wpid==0)
	{

        int ret,in,out;
		if(is_bg)
			setpgid(0,0);

		if(in_r){
				in = open_infile();
				if(in == -1) _exit(-1);
		}
		if(out_r){
				out = open_outfile();
				if(out == -1) _exit(-1);
		}
		
		if((ret = execvp(command_parts[0],command_parts)) < 0)
		{
			perror("Error executing command!");
			_exit(-1);
		}
	}

    else if (!is_bg) //is bg ==0
    {
		int status;
		waitpid(wpid, &status, WUNTRACED);
        if(WIFSTOPPED(status))
        {
			char state[10];
			strcpy(state,get_state(wpid));

			fprintf(stderr, "\n%s with pid %d has stopped!\n", command_parts[0], wpid);
        	
            writ();
            proc_count++;
            addjob(command_parts,wpid);
            int i=1;
            while(i<=proc_count)
            {
                if(process[i].id==wpid)
				    strcpy(process[i].state,state);
                i++;
            }
        }

        else
        {
            rem_job(wpid);
        }
    }

    else
    {
        signal(SIGCHLD,childhandler);
        writ();
    	proc_count++;
    	addjob(command_parts,wpid);
    }
}


void addjob(char ** command_parts,int wpid)
{
	char state[10];
	printf("[%d]  %d\n",proc_count,wpid);
	strcpy(process[proc_count].name,command_parts[0]);
	strcpy(state,get_state(wpid));
	strcpy(process[proc_count].state,state);
    process[proc_count].id = (int) wpid;
	process[proc_count].is_active=1;
}

void rem_job(int wpid)
{
    int i=1;
    while(i<=proc_count)
    {
        if(process[i].id == wpid)
        {
            process[i].is_active = 0;
            break;
        }
        i++;
    }
}

char* get_state(int wpid)
{
	int num=0;
	char* path= malloc(sizeof(char)*1000);
	sprintf(path,"/proc/%d/stat",wpid);
	int fd=open(path,O_RDONLY);

    if(fd>=0)
    {
    	int a=1,i=0;
        char buffer;
	    char* data=malloc(sizeof(char)*100000);
        
        while(a>=0)
        {
            a=lseek(fd,i,SEEK_SET);
			read(fd,&buffer,1);
			data[i]=buffer;
            i++;
			if(buffer=='\n' || buffer=='\0')
			    break;
        }

    	char * token=malloc(sizeof(char)*1024);
    	char** pinf=malloc((sizeof(char)*1000)*1000);

		token=strtok(data," ");
		while(token!=NULL)
		{
			pinf[num]=token;
			token=strtok(NULL," ");
			num+=1;
		}
			return pinf[2];
    }
	else
	{
		  perror("Error while opening the proc/pid/status file\n");
			_exit(-1);
	}
}

void childhandler(int sig)
{
	int status,i;
	pid_t pid;
	if(sig==SIGCHLD)
	{
		while((pid=waitpid(-1,&status,WNOHANG))>0)
		{
			
			if (WIFEXITED(status))
			{
                for(i=1;i<=proc_count; i++)
			    {   
				    if (process[i].id==pid)
				    {
					    process[i].is_active=0;
					    break;
				    }
			    }
				printf("Process with pid %d terminated with exit status: ",pid );
                printf("%d\n",WEXITSTATUS(status));
                break;
			}
			else
			{
				if (WIFSIGNALED(status));
			}

		}

    }
}