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
#include "car.h"

extern pthread_mutex_t fillSeat[NUM_CARS];   // (signal) seat ready to fill
extern pthread_mutex_t seatFilled[NUM_CARS]; // (wait) passenger seated
extern pthread_mutex_t rideOver[NUM_CARS];   // (signal) ride over

extern sem_t driverEmptied[NUM_CARS]; // (wait) passenger seated
extern sem_t seatEmptied[NUM_CARS]; // (wait) passenger seated
extern sem_t needCar;
extern sem_t needCarDriver;
extern sem_t wakeUpDriver;

extern pthread_mutex_t parkMutex;
extern JPARK myPark;

extern sem_t getPassenger;
extern sem_t seatTaken;
extern sem_t driverReady;
extern sem_t driverLeft;

volatile int loadingCarID;

void *carTask(void *args)
{
    int carID = ((int*) args)[0];
    int numPassengers = 0;

    do{
        if(!pthread_mutex_trylock(&fillSeat[carID])){
            // say what car is being loaded?
            loadingCarID = carID;
            // get a passenger
            sem_post(&getPassenger);
            // wait for them to fill a seat!
            sem_wait(&seatTaken);

            if(++numPassengers == NUM_SEATS){
                // need a driver!
                sem_post(&needCarDriver);
                // need driver to wakeup!
                sem_post(&wakeUpDriver);
                // did driver get message?
                sem_wait(&driverReady);
            }
            // say we've acquired a new passenger!
            pthread_mutex_unlock(&seatFilled[carID]);
        }
        if(!pthread_mutex_trylock(&rideOver[carID])){
            // the ride is over!
            // release the driver
            sem_post(&driverEmptied[carID]);
            sem_wait(&driverLeft);

            // release a passenger
            while(numPassengers--){
                sem_post(&seatEmptied[carID]);
            }
            numPassengers++;
        }
    } while (myPark.numExitedPark < NUM_VISITORS);
    return NULL;
}
