#include "dpsim.h"
#include <signal.h> //I had to add in this library in order to pthread_kill

static const unsigned int NUM_PHILOSPHERS = 5;
static const unsigned int NUM_CHOPSTICKS = 5;

static int chopsticks[5];
static pthread_mutex_t mutex[5];
static pthread_t philosphers[5];
int tempCounter[5];

void* th_main( void* th_main_args ) 
{
	int i;
	
	for(i = 0; i < NUM_CHOPSTICKS; i++)
	{
		chopsticks[i] = -1;
	}

	for(i = 0; i < NUM_PHILOSPHERS; i++)
	{
		tempCounter[i] = i;
		if(pthread_create(&philosphers[i], NULL, th_phil, (void*)&tempCounter[i]))		//Thread creation
		{
			perror("Error\n");
			exit(1);
		}
		
	}

	int deadlock = 0;
	while(deadlock == 0)
	{
		int temp[5];
		memcpy(temp, chopsticks, sizeof(chopsticks));		//Copy of the chopstick array
		/*
		printf("temp[0] %d\n", temp[0] );
		printf("temp[1] %d\n", temp[1] );
		printf("temp[2] %d\n", temp[2] );
		printf("temp[3] %d\n", temp[3] );
		printf("temp[4] %d\n", temp[4] );*/

		
		if(temp[0] == 0 && temp[1] == 1 && temp[2] == 2 && temp[3] == 3 && temp[4] == 4) //Dead lock condition, everyone has their own chopstick
		{
			printf("Deadlock condition (0,1,2,3,4) ... terminating\n");
			deadlock = 1;
		}


		else //if (!(chopsticks[0] == -1 && chopsticks[1] == -1 && chopsticks[2] == -1 && chopsticks[3] == -1 && chopsticks[4] == -1))
		{
			
			
				printf("Philosophers ");
				/*for(i = 0; i < NUM_CHOPSTICKS; i++)
				{
					if (temp[i] == temp[(i + 1) % 5])
					{
						printf("%d ", i);
					}
				}*/
				if(temp[0] == 0 && temp[1] == 0)	//Philsopher 0
				{
					printf("%d ", 0);
				}
				if(temp[1] == 1 && temp[2] == 1)	//Philospher 1
				{
					printf("%d ", 1);
				}
				if(temp[2] == 2 && temp[3] == 2)	//Philospher 2
				{
					printf("%d ", 2);
				}
				if(temp[3] == 3 && temp[4] == 3)	//Philospher 3
				{
					printf("%d ", 3);
				}
				if(temp[4] == 4 && temp[0] == 4) //Philospher 4
				{
					printf("%d ", 4);
				}
				printf("are eating...\n");
				
		
		}
		delay(1000);

	}


	for(i = 0; i < NUM_PHILOSPHERS; i++)
	{
		pthread_kill(philosphers[i], 0);
	}
	pthread_exit(0);

} // end th_main function


void* th_phil( void* th_phil_args ) {
	int id = *(int*) th_phil_args;
	while (TRUE)
	{
		delay(1000);
		eat(id);
	}
} // end th_phil function


void delay( long nanosec ) {

	struct timespec t_spec;

	t_spec.tv_sec = 0;
	t_spec.tv_nsec = nanosec;

	nanosleep( &t_spec, NULL );

} // end think function


void eat( int phil_id ) 
{
	//printf("PHIL ID = %d\n", phil_id);
	//delay(10000);
	pthread_mutex_lock(&mutex[phil_id]); //Picks up right chopstick
	chopsticks[phil_id] = phil_id;

	//delay(10000);
	pthread_mutex_lock(&mutex[(phil_id+1) % 5]); //Picks up left chopstick
	chopsticks[(phil_id+1) % 5] = phil_id;

	delay(10000);
	pthread_mutex_unlock(&mutex[(phil_id+1) % 5]); //Sets down left chopstick
	chopsticks[(phil_id+1) % 5] = -1;
	pthread_mutex_unlock(&mutex[phil_id]);  //Sets down right chopstick
	chopsticks[phil_id] = -1;
	delay(10000);
} // end eat function
