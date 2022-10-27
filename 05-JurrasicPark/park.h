#ifndef __park_h__
#define __park_h__

#include "constants.h"

#define ParkDebug(s) printf("\n%s: %s", "Debug", s);

volatile int begin;

typedef struct car
{
    int location;   // location of car in park
    int passengers; // # of passengers in car
} CAR;

typedef struct jpark
{
    int numOutsidePark;       // # outside of park
    int numInPark;            // # in park (P=#)
    int numTicketsAvailable;  // # left to sell (T=#)
    int numRidesTaken;        // # of tour rides taken (S=#)
    int numExitedPark;        // # who have exited the park
    int numInTicketLine;      // # in ticket line
    int numInMuseumLine;      // # in museum line
    int numInMuseum;          // # in museum
    int numInCarLine;         // # in tour car line
    int numInCars;            // # in tour cars
    int numInGiftLine;        // # in gift shop line
    int numInGiftShop;        // # in gift shop
    int drivers[NUM_DRIVERS]; // driver state (-1=T, 0=z, 1=A, 2=B, etc.)
    CAR cars[NUM_CARS];       // cars in park
} JPARK;

void *jurassicTask(void *args);
void *jurassicDisplayTask(void *args);
void *lostVisitorTask(void *args);
int makeMove(int car);
void drawPark(JPARK *park);

#endif
