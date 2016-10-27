#include "dpsim.h"


static const unsigned int NUM_PHILOSPHERS = 5;
static const unsigned int NUM_CHOPSTICKS = 5;

static int chopsticks[5];
static pthread_mutex_t mutex[5];
static pthread_t philosphers[5];


void* th_main( void* th_main_args ) 
{

	int i;
	for(i = 0; i < NUM_CHOPSTICKS; i++)
	{
		chopsticks[i] = -1;
	}
	for(i = 0; i < NUM_PHILOSPHERS; i++)
	{
		if(pthread_create(&philosphers[i], NULL, th_phil, (void *)i)
		{
			exit(1);
		}
	}

	while(TRUE)
	{
		if(chopsticks[0] == 0 && chopsticks[1] == 1 && chopsticks[2] == 2 && chopsticks[3] == 3 && chopsticks[4] == 4)
		{
			printf("Deadlock condition (0,1,2,3,4) ... terminating\n");
			FALSE;
		}
		else
		{
			th_phil();
				
		}
	}

} // end th_main function


void* th_phil( void* th_phil_args ) {
	int id = (int) th_phil_args;
	while (TRUE)
	{
		delay(5000);
		eat(id);
	}
} // end th_phil function


void delay( long nanosec ) {

	struct timespec t_spec;

	t_spec.tv_sec = 0;
	t_spec.tv_nsec = nanosec;

	nanosleep( &t_spec, NULL );

} // end think function


void eat( int phil_id ) {
	chopsticks[phil_id] = phil_id; //Grabs right chopstick
	delay(5001);
	if(phil_id == 4)
	{
		pthread_mutex_t[&mutex[0]];
		chopsticks[0] = phil_id; //Grabs left chopstick
	}
	else
	{
		pthread_mutex_t[&mutex[phil_id+1]];
		chopsticks[phil_id + 1] = phil_id; //Grabs left chopstick
	}
	delay(5001); //Eating nom nom nom

	if(phil_id == 4)
	{
		pthread_mutex_unlock(&mutex[0]);
	}
	else
	{
		pthread_mutex_unlock(&mutex[phil_id]);
	}
} // end eat function
