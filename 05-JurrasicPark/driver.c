#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "constants.h"
#include "mutexes.h"

#include "park.h"
#include "driver.h"

extern sem_t availableTickets;

extern sem_t needTicket;
extern sem_t givingTicketBooth;
extern sem_t boughtTicketBooth;

extern sem_t needCarDriver;
volatile int loadingCarID;

extern sem_t wakeUpDriver;
extern sem_t driverReady;
extern sem_t driverLeft;

extern sem_t driverEmptied[NUM_CARS]; // (wait) passenger seated
extern pthread_mutex_t parkMutex;
extern JPARK myPark;

void *driverTask(void *args)
{
    int driverNum = ((int*) args)[0];
    do{
        // see if anyone needs any help
        if(!sem_trywait(&wakeUpDriver)){
            // someone needs help! What with?

            // does someone need a ticket?
            if(!sem_trywait(&needTicket)){
                // ticket station!
                pthread_mutex_lock(&parkMutex);
                myPark.drivers[driverNum] = -1;
                pthread_mutex_unlock(&parkMutex);
                
                sleep((rand()%MAX_TIME_IN_LINE)+1);

                // wait until we have an available ticket
                sem_wait(&availableTickets);
                // give them a ticket
                sem_post(&givingTicketBooth);
                // wait till they recieve said ticket
                sem_wait(&boughtTicketBooth);
            }

            // does a car need a driver?
            if(!sem_trywait(&needCarDriver)){
                // update car
                int carID = loadingCarID;
                pthread_mutex_lock(&parkMutex);
                myPark.drivers[driverNum] = carID+1;
                pthread_mutex_unlock(&parkMutex);

                // I'm ready to drive!
                sem_post(&driverReady);

                // wait until they release me!
                sem_wait(&driverEmptied[carID]);
                sem_post(&driverLeft);
            }

            // go back to bed
            pthread_mutex_lock(&parkMutex);
            myPark.drivers[driverNum] = 0;
            pthread_mutex_unlock(&parkMutex);
        }
    } while (myPark.numExitedPark < NUM_VISITORS);

    return NULL;
}
