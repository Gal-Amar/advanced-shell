#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAX 1024

//prints suitable error massage
void Error(char* msg) {
	fprintf(stderr, "%s failed\n", msg);
	exit(1);
}

void checkExam(char* name, char* stdName);

int main(int argc, char* argv[]) {
	checkExam(argv[1], argv[2]);
	return 0;
}

// checks if the student was correct in his answers 
void checkExam(char* name, char* stdName) {
	int studentCorrectCnt = 0, questionsCnt = 0, flag;
	int fdSol, fdAttempt, fdChecked;
	char correctAnswer, stdAttempt;
	char* input = (char*)malloc(MAX * sizeof(char));
	if (input == NULL)
		Error("Memory allocation");

	// opening solution file
	sprintf(input, "Sol_%s.txt", name); 
	if((fdSol = open(input, O_RDONLY)) == -1){
		printf("%s Not Found!\n", name);
			return;
	}

	//Opening student attempt file
	sprintf(input, "%s_%s.txt", stdName, name);
	if((fdAttempt = open(input, O_RDONLY)) == -1){
		printf("%s Not Found!\n",name);
		return;
	}
	//Opening check file
	sprintf(input, "Grade_%s_%s.txt", stdName, name);
	fdChecked = open(input, O_WRONLY | O_CREAT , 0664);
	if ( fdChecked == -1) 
		Error("Opening file\n");

	while ((flag = read(fdSol, &correctAnswer, 1))) {
		if (flag == -1 || read(fdAttempt, &stdAttempt, 1) == -1) { //if reading failed or answer is not correct
			Error("Reading");
		}
		if (correctAnswer != '\n') {	
			questionsCnt++;		//Counting questions
			if (correctAnswer == stdAttempt)
				studentCorrectCnt++;	//Counting correct answers
		}
	}
	//writes the results to the check file
	sprintf(input, "%d/%d", studentCorrectCnt, questionsCnt);
	if (write(fdChecked, input, strlen(input)) == -1)
		Error("Writing");

	close(fdSol);
	close(fdAttempt);
	close(fdChecked);
	free(input);

}
