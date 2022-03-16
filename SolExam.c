#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAX 256

void Error(char* msg) {
	fprintf(stderr, "%s failed\n",msg);
	exit(1);
}
void solExam(char* examName);

int main(int argc, char* argv[]) {
	solExam(argv[1]);
	return 0;
}

// creates file for correct answers
void solExam(char* examName) {

	int i, numOfQ, fdSol, fdExam;
	char* input;

	if ((input = (char*) malloc(MAX * sizeof(char))) == NULL)
		Error("Memory allocation");

	sprintf(input, "%s.txt",examName);
//opens the exam file
	if((fdExam = open(input, O_RDONLY)) == -1){
		printf("%s Not Found!\n", examName);
		return;
	}
	sprintf(input, "Sol_%s.txt",examName);
//creates the solution file
	if((fdSol = open(input, O_WRONLY | O_CREAT | O_TRUNC, 0664)) == -1)
		Error("Opening file"); 

	
	if (read(fdExam, input, MAX) == -1)
		Error("Reading");

	sscanf(input, "%*s\n%d\n%*s", &numOfQ);
//receives the correct number for each question in the test
	for(i = 0; i < numOfQ; i++){
		printf("Insert True Sol for Question %d:\n",i+1);
		fgets(input, MAX, stdin);

		if(write(fdSol,input,strlen(input)) == -1)
			Error("Writaing");
		if(write(fdSol,"\n",1) == -1)
			Error("Writaing");
	}

	close(fdExam);
	close(fdSol);
	free(input);
}
