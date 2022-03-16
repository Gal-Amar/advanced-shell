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
void createExam(char* examName, char* examSubject, char* examWriter);

int main(int argc, char* argv[]) {
	createExam(argv[1], argv[2], argv[3]);
	return 0;
}

// creates a copy of entered exam, in the exam ther's questions with 4 answer to each
void createExam(char* examName, char* examSubject, char* examWriter) {
	int i, j;
	int numOfQuestions;
	int fdExam;

	char* input = (char*) malloc(MAX * sizeof(char));
	if (input == NULL)
		Error("Memory allocation");

	sprintf(input, "%s.txt", examName); // prints to the input and append .txt to the name of the exam

	// opening exam file
	if ((fdExam = open(input, O_WRONLY | O_CREAT | O_TRUNC, 0664)) == -1)
		Error("Open File");

	// prepers the exam file
	sprintf(input, "%s", examSubject);
	if (write(fdExam, input, strlen(examSubject)) == -1)
		Error("writing to File");
	if (write(fdExam, "\n\n", 2) == -1)
		Error("writing to File");

	//receives the number of questions there's in the exam
	printf("Insert Number of Question: \n");
	fgets(input, MAX, stdin);
	if((numOfQuestions = atoi(input)) == 0){
		printf("Invalid number of Questions");
		return;
	}
	if (write(fdExam, input, strlen(input)) == -1)
		Error("writing to File");
	

//Receives a question and writes it to the file
	for (i = 0; i < numOfQuestions; i++) {
		printf("Insert question %d:\n", i+1);
		sprintf(input, "\nQuestion %d:\n\n", i + 1);
		if (write(fdExam, input, strlen(input)) == -1)
			Error("writing to File");
		fgets(input, MAX, stdin);
		if (write(fdExam, input, strlen(input)) == -1)
			Error("writing to File");

//Receives the 4 answers and writes them to the file
		printf("Insert 4 answers:\n");
		for (j = 0; j < 4; j++) {
			printf(" %d. ",j+1);
			sprintf(input, " %d. ", j + 1);
			if (write(fdExam, input, strlen(input)) == -1)
				Error("writing to File");
			fgets(input, MAX, stdin);
			if (write(fdExam, input, strlen(input)) == -1)
				Error("writing to File");
		}
	}
	sprintf(input, "\nSuccessfully \n%s",examWriter);
	if (write(fdExam, input, strlen(input)) == -1)
		Error("writing to File");

	close(fdExam);
	free(input);
}

