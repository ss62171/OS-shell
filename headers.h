#include <string.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include<fcntl.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/stat.h>
#include<signal.h>

#define buffer_size 1024

int is_bg;
char user[buffer_size];
char hostname[buffer_size];
char cwd[buffer_size];
char disp_dir[buffer_size];
char main_dir[buffer_size];
char* read_from_terminal();
void set_directory();
int hide(const struct dirent *namelist);
int open_infile();
int open_outfile();
int p_no;

char * infile;
char * outfile;
void get_screen();
void jobs();
void unsett(int tokens,char **command_parts);
void sett(int tokens,char **command_parts);

void kill_all();
void kjob(int tokens, char** command_parts);
void background(char ** command_parts,int n2);
void set_screen();
int parse(char *command,char ** command_parts,char sep);
long long int parse_single_command(char *command,char ** command_parts,char sep);
void cd(char ** command_parts,char *cwd,char *main_dir);
void pwd();
void parse_echo(char ** command_parts);
int echo_check(char *command);
void ls(char *dir, char flag, char * temp);
struct stat buf;
// void exit_process();
void pinfo(char ** command_parts);
void history(char **command_parts,char * fullpath);
void write_to(char* command_line_arg, char* fullpath);
void addjob(char ** command_parts,int wpid);
void rem_job(int wpid);
char* get_state(int wpid);
void childhandler(int sig);
void bg(int tokens, char** command_parts);
void fg(int tokens, char** command_parts);
void writ();
void piping_parse(char* cmd);
int check(char* command);
int red_parsing(char *command,char** command_parts);
int open_infile();
int open_outfile();
void p_and_r(char* cmd);
int c_in,c_out,i,in_r,out_r,c_cat,piping;
char* p_cmds[buffer_size];

pid_t kidpid;

typedef struct
{
  int id;
  char name[100];
  char state[100];
  int is_active;
} Process;
Process process[100];

int proc_count;
extern int is_bg;

