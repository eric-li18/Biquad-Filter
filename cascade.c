#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	int n = (argc-1)/5;
	int pipefd[n-1][2];
	pid_t p[n];
	
	if (n == 1){
		if((p[0] = fork()) == -1){
			return 1;
		}
		else if(p[0] == 0){
			execlp("./biquad","./biquad",argv[1],argv[2],argv[3],argv[4],argv[5], (char *)NULL);
		}
		else{
			waitpid(p[0],NULL,0);
		}
		return 0;
	}

	for (int i=0;i<n;i++){
		if(i <n-1){
			if(pipe(pipefd[i]) == -1){		
				fprintf(stderr,"pipe failed");
				return 1;
			}
		}
		if((p[i] = fork()) == -1){
			//failed to fork
			fprintf(stderr,"fork() failed");
			return 1;
		}else if(p[i] == 0){
			//child process
			if(i == 0){
				//first biquad instance
				close(pipefd[i][0]);
				dup2(pipefd[i][1],1);
				close(pipefd[i][1]);
				execlp("./biquad","./biquad",argv[5*i+1],argv[5*i+2],argv[5*i+3],argv[5*i+4],argv[5*i+5], (char *)NULL);
			}
			else if(i == (n-1)){
				//last ./biquad instance
				dup2(pipefd[i-1][0], 0);
				close(pipefd[i-1][0]);
				execlp("./biquad","./biquad",argv[5*i+1],argv[5*i+2],argv[5*i+3],argv[5*i+4],argv[5*i+5], (char *)NULL);
			}
			else{
				//all in-between ./biquad instances
				dup2(pipefd[i-1][0],0);
				close(pipefd[i-1][0]);
				close(pipefd[i][0]);
				dup2(pipefd[i][1],1);
				close(pipefd[i][1]);
				execlp("./biquad","./biquad",argv[5*i+1],argv[5*i+2],argv[5*i+3],argv[5*i+4],argv[5*i+5], (char *)NULL);
			}
		}else{
			//parent process
			if(i == 0){
				//closing the first childs index=0, write
				close(pipefd[i][1]);

			}
			else if(i == n-1){
				//closing the in between childs index = i, write, index = i-1, read
				close(pipefd[i-1][0]);
			}
			else{
				//closing the last
				close(pipefd[i-1][0]);
				close(pipefd[i][1]);
			}
		}
	}
	for (int j=0; j<n; j++){
        	waitpid(p[j],NULL,0);
	}
	return 0;
}

