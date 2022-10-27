#include <pthread.h>
#include <semaphore.h>

#include "constants.h"

// Resource Semaphores - for counting!
// - sem_init(&sem, 0, initial_value);
// - sem_wait(sem)
// - sem_post(sem)
sem_t availableTickets;
sem_t spaceInPark;
sem_t spaceInMuseum;
sem_t spaceInGiftShop;


// Mutex Semaphores  - for protecting code
// - pthread_mutex_lock(&needDriverMutex);
// - pthread_mutex_unlock(&needDriverMutex);
pthread_mutex_t parkMutex; // mutex park variable access
pthread_mutex_t moveCars;
pthread_mutex_t fillSeat[NUM_CARS];   // (signal) seat ready to fill
pthread_mutex_t seatFilled[NUM_CARS]; // (wait) passenger seated
pthread_mutex_t rideOver[NUM_CARS];   // (signal) ride over

sem_t driverEmptied[NUM_CARS]; // (wait) passenger seated
sem_t seatEmptied[NUM_CARS]; // (wait) passenger seated

pthread_mutex_t getTicketMutex;
pthread_mutex_t enterParkMutex;
pthread_mutex_t enterMuseumMutex;
pthread_mutex_t enterCarMutex;
pthread_mutex_t enterGiftShopMutex;

// Signal Semaphores - for  trading
// sem_t
// - sem_init(&sem, 0, initial_value);
// - sem_wait(sem)
// - sem_post(sem)
sem_t wakeUpDriver;

sem_t needTicket;
sem_t givingTicketBooth;
sem_t boughtTicketBooth;

sem_t needCar;
sem_t needCarDriver;
sem_t getPassenger;
sem_t seatTaken;
sem_t driverReady;
sem_t driverLeft;


// Functions
void init_mutexes(){
    sem_init(&needTicket, 0, 0);
    sem_init(&needCar, 0, 0);
    sem_init(&wakeUpDriver, 0, 0);
    sem_init(&givingTicketBooth, 0, 0);
    sem_init(&boughtTicketBooth, 0, 0);
    sem_init(&getPassenger, 0, 0);
    sem_init(&seatTaken, 0, 0);
    sem_init(&driverReady, 0, 0);
    sem_init(&driverLeft, 0, 0);

    for(int i = 0; i < NUM_CARS; i++){
        sem_init(&seatEmptied[i],0,0);
        sem_init(&driverEmptied[i],0,0);
    }
    sem_init(&availableTickets, 0, MAX_TICKETS);
    sem_init(&spaceInPark, 0, MAX_IN_PARK);
    sem_init(&spaceInMuseum, 0, MAX_IN_MUSEUM);
    sem_init(&spaceInGiftShop, 0, MAX_IN_GIFTSHOP);
}