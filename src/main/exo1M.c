#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void sendUsr1();

pid_t sonPid = -1;

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Il faut 1 argument, au lieu de %d\n", argc - 1);
		return -1;
	}
	else
	{
		pid_t _fork = fork();
		if(sonPid = _fork)
		{
			//mere
			signal(SIGINT, sendUsr1);
			int _exit = -1;
			wait(&_exit);
			if(_exit == -1)
				printf("Mere: Erreur avec la fille\n");
			else
				printf("Mere: La fille avait encore %d secondes\n", _exit);
		}
		else
		{
			//Fille
			execv(
				"/home/tom/EXAM/bin/fille.o",
				(char *[]){"fille.o", argv[1], NULL}
			);
		}
		return 0;
	}
}

void sendUsr1()
{
	if(sonPid != -1)
		kill(sonPid, SIGUSR1);
	else
		printf("Mere: Erreur avec le PID de la fille\n");
}
