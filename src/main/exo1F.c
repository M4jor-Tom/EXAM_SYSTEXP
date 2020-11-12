#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void endProg();
int remain = 0;

int main(int argc, char *argv[])
{
	signal(SIGUSR1, endProg);
	if(argc != 2)
	{
		printf("Fille: Erreur, argc != 2 (%d)\n", argc);
		exit(-1);
	}
	else
	{
		int i, duration = remain = atoi(argv[1]);
		for(i = 0; i < duration; i++)
		{
			sleep(1);
			remain--;
			printf("Fille: %d secondes ecoulees\n", i + 1);
		}
		exit(0);	
	}
	return 0;
}

void endProg()
{
	exit(remain);
}
