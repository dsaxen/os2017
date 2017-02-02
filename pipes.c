/* pipes.c
* compile using: gcc -o pipes pipes.c
* run using ./pipes
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define BUFFERSIZE 100
int main() {
	int pid;
	int pid2;
	char buffer[BUFFERSIZE]; /* Allocate buffer for temporary data */
	int files[2]; /* File descriptor in unix is a integer, used
	together with operation read, write */
	/* Create the pipe, files[0] and files[1] will contain
	the file descriptors of both ends, note, writing will happen
	to files[1], reads from files[0] */
	int files2[2];
	pipe(files);
	pipe(files2);

	/* Create the child process */
	if ((pid = fork())) {
	/* OK, I'm the parent */
		while (1) {
			printf("Parent; Enter string to put into the pipe: ");
			/* Read from the standard input (=keyboard...) */
			gets(buffer);

			/* Write the complete buffer to the pipe */
			write(files[1], buffer, BUFFERSIZE);
			sleep(1);
		}
	}
	else {
		if(pid2 = fork ()){
			/* Ok, I'm the parent child */
			while(1) {
				/* Read from the pipe, read the complete buffer */
				read(files[0], buffer, BUFFERSIZE);
				write(files2[1], buffer, BUFFERSIZE);
				/* Output what was read ... */
				printf("Child: From pipe; '%s'\n", buffer);
			}
		}
		else{
			/* I'm the child child*/
			while(1){
				read(files2[0], buffer, BUFFERSIZE);
				int n = strlen(buffer) -1;
				int i;
				char tmp;
			 
				for(i=0 ; i<=n ; i++){
					tmp = buffer[i];
					buffer[i] = buffer[n];
					buffer[n] = tmp;
					n--;
				}
				//write(files2[1], buffer, BUFFERSIZE);
				printf("Childs child (the third process from pipe): '%s'\n", buffer);
				
	 
 
			}
		}
	}
}
