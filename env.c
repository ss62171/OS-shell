#include"headers.h"
void sett(int n2,char **command_parts)
{
  if(n2==1)
    printf("Invalid no. of arguments\n");
  else if(n2>3)
    printf("Invalid no. of arguments\n");
  else
  {
    if(n2==2)
        setenv(command_parts[1] , " " , 1);
    else
        setenv(command_parts[1] , command_parts[2] , 1);
  }
  return;
}

void unsett(int n2,char **command_parts)
{
    if(n2!=1)
        unsetenv(command_parts[1]);
    else
        printf("Invalid no. of arguments\n");
}

