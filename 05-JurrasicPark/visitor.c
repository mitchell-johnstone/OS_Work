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
#include "visitor.h"

extern pthread_mutex_t getTicketMutex;
extern pthread_mutex_t enterParkMutex;
extern pthread_mutex_t enterMuseumMutex;
extern pthread_mutex_t enterCarMutex;
extern pthread_mutex_t enterGiftShopMutex;

extern sem_t seatEmptied[NUM_CARS]; // (wait) passenger seated

extern sem_t availableTickets;
extern sem_t spaceInPark;
extern sem_t spaceInMuseum;
extern sem_t spaceInGiftShop;

extern sem_t needCar;
extern sem_t needTicket;
extern sem_t givingTicketBooth;
extern sem_t boughtTicketBooth;
extern sem_t getPassenger;
extern sem_t seatTaken;

volatile int loadingCarID;
volatile int unloadingCarID;

extern sem_t wakeUpDriver;

extern pthread_mutex_t parkMutex;
extern JPARK myPark;

void waitRandom(int maxWait) {
    sleep((rand()%maxWait)+1);
}

void *visitorTask(void *args)
{
    // stand outside park!
    pthread_mutex_lock(&parkMutex);
    myPark.numOutsidePark++;
    pthread_mutex_unlock(&parkMutex);

    // wait to enter the park
    pthread_mutex_lock(&enterParkMutex);
    waitRandom(MAX_TIME_IN_LINE);
    pthread_mutex_unlock(&enterParkMutex);

    // enter park
    sem_wait(&spaceInPark);
    {
        // Modify the park to say we entered!
        // Also, get in ticket line!
        pthread_mutex_lock(&parkMutex);
        myPark.numOutsidePark--;
        myPark.numInPark++;
        myPark.numInTicketLine++;
        pthread_mutex_unlock(&parkMutex);

        // buy ticket
        // one ticket sold at a time
        pthread_mutex_lock(&getTicketMutex);
        {
            waitRandom(MAX_TIME_IN_LINE);
            // Hey, we need a ticket!
            sem_post(&needTicket);
            // Hey, I need an employee! 
            sem_post(&wakeUpDriver);
            // wait until they can give me a ticket
            sem_wait(&givingTicketBooth);
            // bought ticket
            sem_post(&boughtTicketBooth);
        }
        pthread_mutex_unlock(&getTicketMutex);

        // get out of line!
        // wait in line for museum!
        pthread_mutex_lock(&parkMutex);
        myPark.numInTicketLine--;
        myPark.numInMuseumLine++;
        pthread_mutex_unlock(&parkMutex);

        pthread_mutex_lock(&enterMuseumMutex);
        {
            waitRandom(MAX_TIME_IN_LINE);
            // I wanna go in!
            // wait for space
            sem_wait(&spaceInMuseum);
        }
        pthread_mutex_unlock(&enterMuseumMutex);

        // go to museum
        pthread_mutex_lock(&parkMutex);
        myPark.numInMuseumLine--;
        myPark.numInMuseum++;
        pthread_mutex_unlock(&parkMutex);

        // spend time in museum
        waitRandom(MAX_TIME_IN_MUSEUM);

        // go to car line
        pthread_mutex_lock(&parkMutex);
        sem_post(&spaceInMuseum);
        myPark.numInMuseum--;
        myPark.numInCarLine++;
        pthread_mutex_unlock(&parkMutex);

        int carID = -1;
        // car time! I'm entering!
        pthread_mutex_lock(&enterCarMutex);
        {
            // wait for car to respond
            sem_wait(&getPassenger);
            // Get the car id!
            carID = loadingCarID;
            // say that I'm sitting down!
            sem_post(&seatTaken);
        }
        pthread_mutex_unlock(&enterCarMutex);

        // go through car ride
        pthread_mutex_lock(&parkMutex);
        myPark.numInCarLine--;
        sem_post(&availableTickets);
        myPark.numInCars++;
        pthread_mutex_unlock(&parkMutex);

        // wait for car ride to be over!
        sem_wait(&seatEmptied[carID]);

        // go to gift shop line
        pthread_mutex_lock(&parkMutex);
        myPark.numInCars--;
        myPark.numInGiftLine++;
        pthread_mutex_unlock(&parkMutex);

        // my turn in the gift shop line
        pthread_mutex_lock(&enterGiftShopMutex);
        {
            waitRandom(MAX_TIME_IN_LINE);
            // I wanna go in!
            // wait for space
            sem_wait(&spaceInGiftShop);
        }
        pthread_mutex_unlock(&enterGiftShopMutex);
        
        // go to gift shop
        pthread_mutex_lock(&parkMutex);
        myPark.numInGiftLine--;
        myPark.numInGiftShop++;
        pthread_mutex_unlock(&parkMutex);

        // spend time in the gift shop
        waitRandom(MAX_TIME_IN_GIFTSHOP);

        // Modify the park to say we exited!
        pthread_mutex_lock(&parkMutex);
        myPark.numInGiftShop--;
        sem_post(&spaceInGiftShop);
        myPark.numInPark--;
        myPark.numExitedPark++;
        pthread_mutex_unlock(&parkMutex);
    }

    // exit park
    sem_post(&spaceInPark);

    return NULL;
}
