#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#include "sys/time.h"

pthread_t		tpid[2];
pthread_mutex_t mutex;
int				counter = 0;

void	*routine(void *arg)
{
	int	i;

	(void)arg;
	i = -1;
	while (++i < 100000)
	{
		pthread_mutex_lock(&mutex);
		counter++;
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

int	main(void)
{
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&(tpid[0]), NULL, &routine, NULL);
	pthread_create(&(tpid[1]), NULL, &routine, NULL);
	pthread_join(tpid[0], NULL);
	pthread_join(tpid[1], NULL);
	pthread_mutex_destroy(&mutex);
	printf("%d\n", counter);
	printf("Thread ends\n");
}
