#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"


int main(int argc, char* argv[]){

	// command to execute
	char *cmd = argv[1];
	
	// command args
	char *cmdExecute[MAXARG];
	
	char buffer[512];
	char *cmdExecuteTmp = buffer;
	int index = 0, argvNum = 0;
	
	// char read_block_data[32], buf[32];
	// char *cmdSplit = buf;
	// int read_data_size, cmdSplitPos = 0, cmdNum = 0;
	
	for(int i=1;i<argc;i++){
		cmdExecute[argvNum++] = argv[i];
	}
	
	while(read(0, &buffer[index], sizeof(char)) == sizeof(char)){
		if(buffer[index] == '\n'){
			buffer[index] = '\0';
			cmdExecute[argvNum++] = cmdExecuteTmp;
			cmdExecute[argvNum] = 0; // assign pointer to NULL
			
			// Reset
			index = 0;
			argvNum = argc - 1;
			
			// Exec
			if (fork() == 0){
				exec(cmd, cmdExecute);
			}
			else{
				wait();
			}
			
		}
		else if (buffer[index] == ' '){
			buffer[index++] = '\0';
			cmdExecute[argvNum++] = cmdExecuteTmp;
			
			// Reset
			cmdExecuteTmp = &buffer[index];
			// index = 0;
		}
		else{
			index++;
		}
	}
	
	/*
	while((read_data_size = read(0, read_block_data, sizeof(read_block_data))) > 0){
		for(int pos = 0; pos<read_data_size; pos++){
			if(read_block_data[pos] == '\n'){
				buf[cmdSplitPos] = '\0';
				cmdExecute[cmdNum++] = cmdSplit;
				cmdSplit = buf;
				
				cmdExecute[cmdNum] = '\0';
				cmdSplitPos = 0;
				cmdNum = argc - 1;
				if (fork() == 0){
					exec(cmd, cmdExecute);
				}
				wait();
			}
			else if(read_block_data[pos] == ' '){
				buf[cmdSplitPos++] = '\0';
				cmdExecute[cmdNum++] = cmdSplit;
				cmdSplit = &buf[cmdSplitPos];
			}
			else{
				buf[cmdSplitPos++] = read_block_data[pos];
			}
		}
	}
	*/
	
	exit();
}
