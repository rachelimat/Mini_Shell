/*racheli mathliach 208179267*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>


char** stringTowords(char *setOfWords) {  //פונקציה שמקבלת מערך של מילים עם רווחים בינהם  
	if (setOfWords == NULL){
		printf("no input");
		return NULL;}
	int counterWords = 0, w = 0;
	char* copy = (char*)malloc(sizeof(char)*strlen(setOfWords + 1));//הקצאת זיכרון לצורך העתקת המחרוזת המקורית
	strcpy(copy, setOfWords);
	char *cWords = strtok(setOfWords, " ");

	while (cWords != NULL) {
		
		counterWords++;
		cWords = strtok(NULL, " ");
	}

	char**array = (char**)malloc((counterWords + 1)*(sizeof(char*)));
	if (array == NULL) {
		printf("memory allocation failed!");
		exit(0);
	}
	char*word = strtok(copy, " ");//מוציא את המילה הראשונה 

	for (int w = 0; word != NULL; w++) {	//עובר על כל המילים אחת אחרי השניה

		array[w] = (char*)malloc((strlen(word) + 1) * sizeof(char));
		if (array[w] == NULL)
		{
			printf("memory allocation failed!");
			exit(0);
		}
		strcpy(array[w], word);
		word = strtok(NULL, " ");
	}
	array[counterWords] = NULL;
	//free(copy);
	return array;
}

void print(char** array) {

	for (int i = 0; array[i] != NULL; i++) {
		printf("%s\n", array[i]);
	}
}
void freeAllAllocation(char** array) {
	int i;
	for (i = 0; array[i] != NULL; i++) {
		
		free(array[i]);
	}
	free(array);
}
/**************************************************/
int main() {
	char array[510]="";
	char** newWords;
	char hostName[128];
	gethostname(hostName, 128);  
	while(1)
	{
		printf("%s@%s$",getlogin(),hostName); //the line of mini_shell model

		if(fgets(array, 510, stdin)!=NULL){
			array[strlen(array)-1]='\0';
			newWords=stringTowords(array);
			
		if(strcmp("exit",array)==0){//if the input is  exit, free  all  the allocations and exits
			freeAllAllocation(newWords);//send to free func 
				return 0;
		}

		pid_t x =fork();
		
		if(x<0){// if the fork failed
			printf("the fork failed");
			freeAllAllocation(newWords);
			return 0;
		}
		if(x==0){
			if(execvp(newWords[0],newWords)==-1){
				print(newWords);
				printf(": command not found \n");
				}
				freeAllAllocation(newWords);
				exit(0);
		}
		wait(NULL);//the father
		
		freeAllAllocation(newWords);
		//free and exit  inside the loop
		}
	}
		
	return(0);
	
}/*****************************************************************************/
