#include "headers.h"

void history(char **command_parts, char * fullpath)
{   
    char ** hist=(char**)malloc((sizeof(char)*buffer_size)*1024);
    char * line = NULL;
    size_t length = 0;
    ssize_t read;
    FILE* fp = fopen(fullpath, "r");
    int count = 0;
    
    while ((read = getline(&line, &length, fp)) != -1) {
                    line[strlen(line)-1] = '\0';
                    hist[count] = strdup(line);
                    if(command_parts[1]== NULL)
                        printf("%s\n",hist[count]);
                
                count++;
        }

    if(command_parts[1]!=NULL)
    {
        int x = atoi(command_parts[1]);
        for(int i=count-1;i>=count-x;i--)
        {
            if(i<0)
            {
                printf("Not enough commands\n");
                break;
            }
            printf("%s\n",hist[i]);
            
        }
    }
    fclose(fp);
}

void write_to(char* command_line_arg, char* fullpath)
{
    FILE *out = fopen(fullpath, "a");
    fprintf(out, "%s", command_line_arg);  
    fprintf(out,"%c",'\n');
    fclose(out);
}