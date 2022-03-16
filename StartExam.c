#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAX 256

//prints suitable error massage
void Error(char* msg) {
	fprintf(stderr, "%s failed\n",msg);
	exit(1);
}

void startExam(char* examName, char* studentName);

int main(int argc, char* argv[]) {
	startExam(argv[1], argv[2]);
	return 0;
}

// performs the exam an saves an answer file for each sudent
void startExam(char* examName, char* studentName) {

	int i, numOfQ, fdStdExam, fdExam, stdNumQ;
	int bytesRead; // stores the number of bytes read when reading a file
	char* answerArr; // stores the answer numbers in a proper order
	char* input, stdAns;

	if ((input = (char*) malloc(MAX * sizeof(char))) == NULL)
		Error("Memory allocation");
	sprintf(input, "%s_%s.txt", studentName, examName); // prepare the answers file's examName

	//opening student attempt file
	if((fdStdExam = open(input, O_WRONLY | O_CREAT, 0664)) == -1){
		printf("%s Not Found!\n", examName);
		return;
	}
	//opening exam file
	sprintf(input, "%s.txt", examName);
	if((fdExam = open(input, O_RDONLY)) == -1){
		printf("%s Not Found!\n",examName);
		return;
	}

	// extracting the number of questions
	if((bytesRead = (read(fdExam, input, MAX))) == -1)
		Error("Reading");
	sscanf(input, "%*s\n%d\n%*s", &numOfQ);

	// receving the ansewers from the student
	do {
		if (bytesRead == -1)
			Error("Reading");
		printf("%s", input);
	}while((bytesRead = (read(fdExam, input, MAX))) != 0);

	if ((answerArr = (char*)malloc(numOfQ * sizeof(char))) == NULL)
		Error("Memory allocation");

	//Receives the answers for the questions in the test
	printf("\nInsert number of question and sol:\n");
	for (i = 0; i < numOfQ; ++i) {
		scanf("%d %c",&stdNumQ, &stdAns);
		answerArr[stdNumQ-1] = stdAns; //writes the answer number in the correct order in the array
	}
	//Writes the answers to the answers file
	for (i = 0; i < numOfQ; ++i) {
		if(write(fdStdExam, &answerArr[i], 1 ) == -1)
			Error("Writing");
		if(write(fdStdExam, "\n\n", 2 ) == -1)
			Error("Writing");
	}
	free(input);
	close(fdStdExam);
	close(fdExam);
}
