#include "headers.h"
int hide(const struct dirent *namelist)
{
    if(namelist->d_name[0] == '.') return 0;
    else return 1;
}

void ls(char *dir, char flag, char * temp)
{
    struct dirent **namelist;
    int n,i=0;
    char datestring[256];
    struct tm *time;

    if(flag == 'a' || flag == 'b')
        n = scandir(dir, &namelist, NULL, alphasort);
    else if(flag == '.' || flag == 'l')
        n = scandir(dir, &namelist, hide, alphasort);
    else if(flag == 'd')
    {
        int z=0;
        char* temp_path = (char*)malloc(sizeof(char)*buffer_size);
        char* temp_path2 = (char*)malloc(sizeof(char)*buffer_size);
        temp_path2[0] = '/';
        z++;
        for(int k=0;k<strlen(temp);k++)
        {
            if(temp[k]!='~')
            {
                temp_path2[z] = temp[k];
                z++; 
            }
        }

        strcpy(temp_path, main_dir);
        strcat(temp_path, temp_path2);
        n = scandir(temp_path, &namelist, hide, alphasort);
    }

    if (n == -1) 
    {
        perror("scandir");
    }
    
    if(flag == 'a' || flag == '.' || flag == 'd')
    {
        while (i<n) {
            printf("%s\n", namelist[i]->d_name);
            free(namelist[i]);
            i++;
        }
        free(namelist);
    }   
}

