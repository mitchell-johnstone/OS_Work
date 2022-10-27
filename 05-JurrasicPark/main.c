// os345p3.c - Jurassic Park 07/27/2020
// ***********************************************************************
// **   DISCLAMER ** DISCLAMER ** DISCLAMER ** DISCLAMER ** DISCLAMER   **
// **                                                                   **
// ** The code given here is the basis for the CS345 projects.          **
// ** It comes "as is" and "unwarranted."  As such, when you use part   **
// ** or all of the code, it becomes "yours" and you are responsible to **
// ** understand any algorithm or method presented.  Likewise, any      **
// ** errors or problems become your responsibility to fix.             **
// **                                                                   **
// ** NOTES:                                                            **
// ** -Comments beginning with "// ??" may require some implementation. **
// ** -Tab stops are set at every 3 spaces.                             **
// ** -The function API's in "OS345.h" should not be altered.           **
// **                                                                   **
// **   DISCLAMER ** DISCLAMER ** DISCLAMER ** DISCLAMER ** DISCLAMER   **
// ***********************************************************************
#include <ctype.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "constants.h"
#include "mutexes.h"
#include "park.h"
#include "car.h"
#include "visitor.h"
#include "driver.h"

// Jurassic Park
extern volatile int begin;
extern JPARK myPark;

extern pthread_mutex_t parkMutex;            // mutex park variable access
extern pthread_mutex_t fillSeat[NUM_CARS];   // (signal) seat ready to fill
extern pthread_mutex_t seatFilled[NUM_CARS]; // (wait) passenger seated
extern pthread_mutex_t seatEmptied[NUM_CARS]; // (wait) passenger seated
extern pthread_mutex_t rideOver[NUM_CARS];   // (signal) ride over

int main(int argc, char *argv[])
{
    // initialize mutexes
    init_mutexes();

    // begin!
    begin = 0;
    // start park
    pthread_t parkTask;
    pthread_create(&parkTask, NULL, jurassicTask, NULL);

    // wait for park to get initialized...
    while (!begin)
    {
    }
    printf("\n\nWelcome to Jurassic Park\n\n");

    // create car tasks
    pthread_t carTasks[NUM_CARS];
    int carNum[NUM_CARS];
    for(int i = 0; i < NUM_CARS; i++){
        carNum[i] = i;
        pthread_create(carTasks+i, NULL, carTask, carNum + i);
    }

    // create driver tasks
    pthread_t driverTasks[NUM_DRIVERS];
    int driverNums[NUM_DRIVERS];
    for(int i = 0; i < NUM_DRIVERS; i++){
        driverNums[i] = i;
        pthread_create(driverTasks+i, NULL, driverTask, driverNums+i);
    }

    // create visitor tasks 
    pthread_t visitorTasks[NUM_VISITORS];
    for(int i = 0; i < NUM_VISITORS; i++){
        pthread_create(visitorTasks+i, NULL, visitorTask, NULL);
    }

    // close all threads
    pthread_join(parkTask, NULL);
    for(int i = 0; i < NUM_CARS; i++){
        pthread_join(carTasks[i], NULL);
    }
    for(int i = 0; i < NUM_DRIVERS; i++){
        pthread_join(driverTasks[i], NULL);
    }
    for(int i = 0; i < NUM_VISITORS; i++){
        pthread_join(visitorTasks[i], NULL);
    }
    return 0;
}
