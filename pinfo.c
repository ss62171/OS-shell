#include"headers.h"

void pinfo(char ** command_parts)
{
	int num=0,size,len=-1;
    pid_t pid = (command_parts[1]==NULL) ? getpid() : atoi(command_parts[1]);

	char* path= malloc(sizeof(char)*1000);
	
	sprintf(path,"/proc/%d/stat",pid);

	int fd=open(path,O_RDONLY);

    char* data=malloc(sizeof(char)*100000);
	char buffer;
	char * token=malloc(sizeof(char)*1024);
    
	int i=0;
	while(size>=0)
    {
		size=lseek(fd,i,SEEK_SET);
		read(fd,&buffer,1);
		data[i]=buffer;
		if(buffer=='\n' || buffer=='\0')
			break;
        i++;
	}
	token=strtok(data," ");
	char** pinf=malloc((sizeof(char)*1000)*1000);
	char* buf=malloc(sizeof(char)*buffer_size);
	while(token!=NULL)
	{
		pinf[num]=token;
		num+=1;
		token=strtok(NULL," ");
	}
	printf("pid -- %d\n", pid);
	printf("State -- %s\n",pinf[2]);
	printf("Memory -- %s\n",pinf[22]);
	sprintf(path, "/proc/%d/exe", pid);
	len = readlink(path,buf, buffer_size - 1);
	 if(len==-1)
	    perror("Error while opening the proc/pid/exe file\n");
	else
	{
        char temporary[1024];
	    buf[len] = '\0';
        int temp=1;
        int i = strlen(buf)-strlen(main_dir);
        printf("%s\n",buf);
        for(int j=0;j<buffer_size;j++)
            temporary[j] = '\0';
    
        temporary[0] = '~';
        for(int j=strlen(main_dir);j<strlen(buf);j++)
        {
            temporary[temp] = buf[j];
            temp++;
        }
	    printf("Executable Path -- %s\n", temporary);
	}
	
close(fd);
}
