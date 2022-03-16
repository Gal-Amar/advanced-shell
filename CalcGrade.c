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

void calcGrade(char* ExamName, char* studentName);

int main(int argc, char* argv[]) {
	calcGrade(argv[1], argv[2]); 
	return 0;
}

// calaculates the grade of the student in the exem and adds it to the answers file
void calcGrade(char* ExamName, char* studentName) {
	double grade;
	int fdChecked, numOfQuestion, studentCorrectAnswers;

	char* input = (char*)malloc(MAX * sizeof(char));
	if (input == NULL){
		Error("Memory allocation failed");
	}
	
	sprintf(input, "Grade_%s_%s.txt", studentName, ExamName);

	//opens the check file
	if((fdChecked = open(input, O_RDWR)) == -1){
		printf("%s Not Found!\n", ExamName);
		return;
	}

	if(read(fdChecked, input, MAX) == -1)
		Error("Reading");

	sscanf(input, "%d %*c %d", &numOfQuestion, &studentCorrectAnswers); //extracting the relevant variables
	grade = (((float)numOfQuestion)/studentCorrectAnswers); // calculating grade
	sprintf(input,"\n\nFinal Grade %.f/100", grade*100);

	//writes the grade to the check file
	if(write(fdChecked, input, strlen(input)) == -1)
		Error("Writing");
	printf("%s\n%s\nFinal Grade: %.f\n",studentName, ExamName, grade*100); 
}
