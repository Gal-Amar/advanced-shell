#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

//prints suitable error massage
void Error(char* msg) {
	printf("%s failed\n", msg);
	exit(1);
}

int main() {
	char path[MAX] = "./";
	char* cCmds[] = {"CreateExam","SolExam","StartExam","CheckExam","CalcGrade"};
	int i, numsOfElements;
	char* end = "GoodBye";

	char* input = (char*) malloc(MAX * sizeof(char));
	if (input == NULL)
		Error("Memory allocation");

	char* args[4];
	for (i = 0; i < 4; ++i) {
		args[i] = (char*)malloc(MAX * sizeof(char));
		if (args[i] == NULL)
			Error("Memory allocation");
	}

	printf("AdvShell>"); // new shell prompt
	fgets(input, MAX, stdin);
	numsOfElements = sscanf(input, "%s %s %s %s", args[0], args[1], args[2],
						args[3]); // receiving first command

// in args[0] we save the command's name
	while (strcmp(args[0], end)) {

		for(i=0; i < 5; i++){
			// if the command is a regular shell command than add the prefix ./ 
			if(!strcmp(args[0], cCmds[i])){
				strcat(path, args[0]); // path = ./funcName
				strcpy(args[0], path); // arg[0] = path
				strcpy(path, "./");	// initialized path string
				break;
			}
	}
	// execution of each command depends on number of elements
	switch (numsOfElements) {
		// command with no elements
		case (1): 
		//child process will execute the requested command
			if (fork() == 0) {
				char* oneArgs[2] = { args[0], NULL };
				execvp(oneArgs[0], oneArgs);
				printf("Unsupported command\n");
				exit(1);
			}
			break;
		// command with one elements
		case (2):
		//child process will execute the requested command
			if (fork() == 0) {
				char* twoArgs[3] = { args[0], args[1] ,NULL};
				execvp(twoArgs[0], twoArgs);
				printf("Unsupported command\n");
				exit(1);
			}
			break;

		// command with 2 elements
		case (3):
		//child process will execute the requested command
			if (fork() == 0) {
				char* threeArgs[4] = { args[0], args[1], args[2] ,NULL};
				execvp(threeArgs[0], threeArgs);
				printf("Unsupported command\n");
				exit(1);
			}
			break;

		// command with 2 elements
		case (4):
		//child process will execute the requested command
			if (fork() == 0) {
				char* fourArgs[5] = { args[0], args[1], args[2] ,args[3],NULL};
				execvp(fourArgs[0], fourArgs);
				printf("Unsupported command\n");
				exit(1);
			}
			break;
		}

		wait(); // the father process wait for child to terminate before continues to except the next command
		printf("AdvShell>");
		for (i = 0; i < 4; ++i) {
				free(args[i]); 
				args[i] = (char*) malloc(MAX * sizeof(char));
				if (args[i] == NULL)
					Error("Memory allocation");
		}

		fgets(input, MAX, stdin); //receiving next command
		numsOfElements = sscanf(input, "%s %s %s %s", args[0], args[1], args[2],
								args[3]);
	}
// freeing all data that has been allocated
	free(input);
	for (i = 0; i < 4; ++i) {
		free(args[i]);
	}
	return 0;
}

