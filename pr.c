#include "headers.h"
#define command_delms " \t\n"
extern int p_no;
int check(char* command)
{
    int i=0;
	c_cat=piping=in_r=out_r=c_in=c_out=0;

	while(command[i])
	{
		if(command[i] == '>')
		{
            out_r = 1;
            if(!c_cat)c_cat = 1;
            if(!c_out)c_out = i;
        }

		if(command[i] == '>')
			if(command[i+1] == '>')
            	c_cat = 2;

        if(command[i] == '<')
        {
            in_r = 1;
            if(!c_in)
                c_in = i;
        }
		
        if(command[i] == '|')
            piping = 1;

		i++;
	}
    
        if(piping) return 1;
        else return -1;
}

int red_parsing(char *command,char** command_parts)
{
	int n=0;
	char * cmd_dup=strdup(command);
	c_in=c_out=i=in_r=out_r=c_cat=0;
	infile=NULL;
	outfile=NULL;

	while(command[i])
	{
		if(command[i]=='>')
		{
			out_r=1;
			if(!c_cat)
				c_cat=1;
			if(!c_out)
				c_out=i;
		}

		if(command[i]=='>')
			if(command[i+1]=='>')
				c_cat=2;

		if(command[i]=='<')
		{
			in_r=1;
			if(!c_in)c_in=i;
		}
		i++;
	}

	if(in_r && out_r)
	{
		char* parts;
		parts=strtok(cmd_dup," <>\t\n");
		for(n=0;parts!=NULL;n++)
		{
			command_parts[n]=strdup(parts);
			parts=strtok(NULL,"<> \t\n");
		}

		if(c_in <= c_out)
		{
			outfile=strdup(command_parts[n-1]);
			infile=strdup(command_parts[n-2]);
		}
		if(c_in>c_out)
        {
			infile=strdup(command_parts[n-1]);
			outfile=strdup(command_parts[n-2]);
		}

		command_parts[n- 2]=command_parts[n-1]=NULL;
		return n-2;
	}

	if(out_r)
	{
		char *parts;
		char ** c_out_command=malloc((sizeof(char)*buffer_size)*buffer_size);
		char * cmd_dup=strdup(command);
		
		if(c_cat==1)
		    parts=strtok(cmd_dup, ">");

		else if(c_cat==2)
		    parts=strtok(cmd_dup, ">>");
		
		for(n=n;parts!=NULL;n++)
		{
		    c_out_command[n]=parts;
		    if(c_cat>=2)
		        parts=strtok(NULL, ">>");
			else if(c_cat==1)
		        parts=strtok(NULL, ">");
	    }

	    cmd_dup=strdup(c_out_command[n-1]);

	    outfile=strdup(strtok(cmd_dup,"< |\t\n"));
		if(outfile[0]=='~' && outfile[1]=='/'){
			char new_outfile[200];
			sprintf(new_outfile,"%s%s",main_dir,&outfile[1]);
			outfile = strdup(new_outfile);
		}
	    parts=strtok(c_out_command[0]," \t\n");
	    
		for(n=0;parts!=NULL;n++)
	    {
		    command_parts[n]=strdup(parts);
		    parts=strtok(NULL,command_delms);
	    }
	}

    if(in_r)
    {
	    char ** c_in_command=malloc((sizeof(char)*buffer_size)*buffer_size);
	    char *parts;
	    char * cmd_dup=strdup(command);

	    parts=strtok(cmd_dup, "<");

		for(n=n;parts!=NULL;n++)
	    {
	        c_in_command[n]=parts;
	        parts=strtok(NULL,"<");
        }
            
        cmd_dup=strdup(c_in_command[n-1]);
        infile=strdup(strtok(cmd_dup,"> |\t\n"));
		if(infile[0]=='~' && infile[1]=='/'){
			char new_infile[200];
			sprintf(new_infile,"%s%s",main_dir,&infile[1]);
			infile = strdup(new_infile);
		}
        n=0;
        parts=strtok(c_in_command[0],command_delms);
        
		for(n=0;parts!=NULL;n++)
        {
	        command_parts[n]=strdup(parts);
	        parts=strtok(NULL,command_delms);
        }
        
        command_parts[n]=NULL;

    }

    if(!out_r)
		if(!in_r)
    	{
        	char te = ';';
        	return parse_single_command(command,command_parts,te);
    	}
    else
        return n;
}

void piping_parse(char* cmd)
{
    int i=0;
	char* cmd_dup = strdup(cmd);
    char* part;
    part = strtok(cmd_dup, "|");
	for(i=0;part!=NULL;i++)
    {
        p_cmds[i] = part;
        part = strtok(NULL, "|");
    }
    p_no = i;
}
