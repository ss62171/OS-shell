#include "headers.h"

void writ()
{
    int i; 
    for (i=1; i<=proc_count; i++) 
        if (process[i].is_active == 0)
        {
            if (i <= proc_count) 
            { 
                proc_count -= 1; 
                for (int j=i; j<=proc_count; j++) 
                {
                    process[j].id = process[j+1].id;
                    process[j].is_active = process[j+1].is_active;
                	strcpy(process[j].name,process[j+1].name);
                	strcpy(process[j].state,process[j+1].state);
                } 
            }
        }
 
}

void kill_all()
{
    int i=1;
    while(i<= proc_count)
    {
        if(process[i].is_active)
        {
			process[i].is_active=0;
            int e = kill(process[i].id, SIGKILL);
			if(e < 0)
				perror("Some error occured\n");
		}
        i++;
    }
    proc_count = 0;
}

void jobs()
{   
    writ();
	for(int i = 1; i <= proc_count ; i++)
	{
        if(process[i].is_active)
			printf("[%d] ",i);
            printf("%s ",process[i].state);
            printf("%s ",process[i].name);
            printf("[%d]\n",process[i].id);
    }
        
}


void fg(int tokens, char** command_parts)
{
	int i, status, j = atoi(command_parts[1]);

    if(tokens != 2) {
		fprintf(stderr, "Invalid usage of fg\n");
		return;
	}
    	
	if(!process[j].is_active)
    {
		printf("No such job exists\n");
		return;
	}

    is_bg =0 ;
    if(!process[j].is_active)
        fprintf(stderr, "No job found\n");
	else
    {
        int pid;
		pid = process[j].id;
		kill(pid,SIGCONT);
		waitpid(pid, &status, WUNTRACED);
		if(WIFSTOPPED(status)==0)
			process[j].is_active = 0;

		else
		{
            // printf(" Ctrl Z\n");
			fprintf(stderr, "\n%s with pid %d has stopped!\n", command_parts[0], pid);
			char state[10];
			strcpy(state,get_state(pid));
            int i=1;
            while(i<=proc_count)
            {
                if(process[i].id==pid)
				{
					strcpy(process[i].state,state);
				}
                i++;
            }
		}
	}

}

void kjob(int tokens, char** command_parts)
{
	int jno = atoi(command_parts[1]);
    int kno = atoi(command_parts[2]);
	if(tokens != 3)
    {
		fprintf(stderr, "Invalid usage!!!\n");
		return;
	}

	if(process[jno].is_active)
	{
        int pid = process[jno].id;
        char state[10];
		strcpy(state,get_state(pid));
        
        if(kno == 9)
		    process[jno].is_active=0;

        int e = kill(process[jno].id, kno);
        strcpy(process[jno].state,state);
		
        if(e < 0)
			fprintf(stderr, "Signal not sent!\n");
	}

	else
        fprintf(stderr, "Job not found\n");
}

void bg(int tokens, char** command_parts)
{

	int i,status,j = atoi(command_parts[1]);
	int pid;
	if(tokens != 2)
    {
		fprintf(stderr, "Invalid usage of bg");
		return;
	}

	if(process[j].is_active)
    {
		pid = process[j].id;
		kill(pid,SIGCONT);
		strcpy(process[j].state,"R");
	}

	else if(!process[j].is_active)
    {
		printf("Job does not exists\n");
		return;
	}

	else
        fprintf(stderr, "Job not found\n");
}