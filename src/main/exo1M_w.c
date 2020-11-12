#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

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
			//cablage du signal SIGINT
			signal(SIGINT, sendUsr1);

			//Reception du statut fille
			int _exit = -1;
			wait(&_exit);
			if(_exit == -1)
				printf("Mere: Erreur avec la fille\n");
			else
			{
				//Création d'un fichier si non existant
				int fd = open("../docs/remain.txt", O_WRONLY|O_CREAT);

				//Réécriture
				lseek(fd, 0, SEEK_SET);
				write(fd, &_exit, 5);

				//Fermeture
				close(fd);

				printf("Il restait %d secondes a la fille, fd = %d\n", _exit, fd);
			}
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
