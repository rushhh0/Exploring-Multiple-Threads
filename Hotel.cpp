#include <iostream>
#include <queue>
#include <cstdlib>
#include <pthread.h>
#include <semaphore.h>
#include <mutex>

using namespace std;

class Guest;
class FrontDesk;
class Bellhop;

// Queues to manage guests and bellhop requests
queue<Guest*> guestRequestQueue;
queue<Guest*> bellhopRequestQueue;

// Semaphores to control access to shared resources
sem_t guestMutex, frontDeskMutex, bellhopMutex;
sem_t guestsReady, bellhopRequested;
sem_t frontDeskEmployee, bellhopEmployee;
sem_t guestLeaves;
sem_t roomRegistration;
sem_t bagsDelivered, bagsReceived;
sem_t printSemaphore;

// Arrays to track guest-specific data
int* frontDeskEmployeeID;
int* bellhopEmployeeID;
sem_t* checkedIntoRoom; // Array of semaphores to track if guests have retired
sem_t* guestsRetired; // Array of semaphores to track if guests have reached their room
int guestJoined = 0; // Variable to keep track of the number of guests that have joined

// Variable to keep track of the current room number
int currentRoomNumber = 0;

// Static method for thread-safe printing
void print(const string& message) {
    sem_wait(&printSemaphore); // Wait for access
    cout << message << endl;
    sem_post(&printSemaphore); // Release access
}

// Guest class
class Guest {
public:
    int id;
    int currentRoomNumber;
    int bagCount;
    pthread_t guest;

    // Constructor for Guest class
    Guest(int ID) {
        id = ID;
        bagCount = rand() % 6;

        print("Guest " + to_string(id) + " created");
        
        pthread_create(&guest, NULL, &Guest::guestRun, this);
    }
    
    // Static method representing the guest's thread
    static void* guestRun(void* arg) {
        Guest* guest = (Guest*)arg;

        print("Guest " + to_string(guest->id) + 
        " enters the hotel with " + to_string(guest->bagCount) + 
        " bags");

        sem_wait(&guestMutex);
        guestRequestQueue.push(guest);
        sem_post(&guestMutex);

        sem_wait(&frontDeskEmployee);
        sem_post(&guestsReady);
        sem_wait(&guestsRetired[guest->id]);
        sem_wait(&roomRegistration);
        print("Guest " + to_string(guest->id) + 
        " receives room key for room " + to_string(guest->currentRoomNumber) + 
        " from front desk employee " + to_string(frontDeskEmployeeID[guest->id]));

        sem_post(&guestLeaves);

        if (guest->bagCount > 2) {
            sem_wait(&bellhopEmployee);
            print("Guest " + to_string(guest->id) + " requests help with bags");
            sem_wait(&bellhopMutex);
            bellhopRequestQueue.push(guest);
            sem_post(&bellhopRequested);
            sem_post(&bellhopMutex);

            sem_wait(&bagsReceived);
            print("Guest " + to_string(guest->id) + 
            " enters room " + to_string(guest->currentRoomNumber));
            sem_post(&checkedIntoRoom[guest->id]);

            sem_wait(&bagsDelivered);
            print("Guest " + to_string(guest->id) + 
            " receives bags from bellhop " + to_string(bellhopEmployeeID[guest->id]) + 
            " and gives tip");
        } else {
            sem_post(&checkedIntoRoom[guest->id]);
            print("Guest " + to_string(guest->id) + 
            " enters room " + to_string(guest->currentRoomNumber));
        }

        print("Guest " + to_string(guest->id) + " retires for the evening");
        
        print("Guest " + to_string(guest->id) + " joined");

        return NULL;
    }
};

// FrontDesk class
class FrontDesk {
public:
    int id;

    // Constructor for FrontDesk class
    FrontDesk(int num) {
        id = num;
        print("Front desk employee " + to_string(id) + " created");
        pthread_t frontDesk;
        pthread_create(&frontDesk, NULL, &FrontDesk::frontDeskRun, this);
    }
    
    // Static method representing the front desk's thread
    static void* frontDeskRun(void* arg) {
        FrontDesk* frontDesk = (FrontDesk*)arg;

        while (true) {
            sem_wait(&guestsReady);

            sem_wait(&frontDeskMutex);
            Guest* guest = guestRequestQueue.front();
            guestRequestQueue.pop();
            currentRoomNumber++;
            guest->currentRoomNumber = currentRoomNumber;
            sem_post(&frontDeskMutex);

            frontDeskEmployeeID[guest->id] = frontDesk->id;
            sem_post(&roomRegistration);
            print("Front desk employee " + to_string(frontDesk->id) + 
            " registers guest " + to_string(guest->id) + 
            " and assigns room " + to_string(guest->currentRoomNumber));

            sem_post(&guestsRetired[guest->id]);
            sem_wait(&guestLeaves);
            sem_post(&frontDeskEmployee);
        }

        return NULL;
    }
};

// Bellhop class
class Bellhop {
public:
    int id;

    // Constructor for Bellhop class
    Bellhop(int num) {
        id = num;
        print("Bellhop " + to_string(id) + " created");
        pthread_t bellhop;
        pthread_create(&bellhop, NULL, &Bellhop::bellhopRun, this);
    }

    // Static method representing the bellhop's thread
    static void* bellhopRun(void* arg) {
        Bellhop* bellhop = (Bellhop*)arg;

        while (true) {
            sem_wait(&bellhopRequested);
            sem_wait(&bellhopMutex);
            Guest* guest = bellhopRequestQueue.front();
            bellhopRequestQueue.pop();
            bellhopEmployeeID[guest->id] = bellhop->id;
            sem_post(&bellhopMutex);

            print("Bellhop " + to_string(bellhop->id) + 
            " receives bags from guest " + to_string(guest->id));
            sem_post(&bagsReceived);

            sem_wait(&checkedIntoRoom[guest->id]);
            print("Bellhop " + to_string(bellhop->id) + 
            " delivers bags to guest " + to_string(guest->id));

            sem_post(&bagsDelivered);
            sem_post(&bellhopEmployee);
        }

        return NULL;
    }
};

int main() {
    srand(time(NULL));
    
    // Initialize semaphores
    sem_init(&guestMutex, 0, 1);
    sem_init(&frontDeskMutex, 0, 1);
    sem_init(&bellhopMutex, 0, 1);
    sem_init(&guestsReady, 0, 0);
    sem_init(&bellhopRequested, 0, 0);
    sem_init(&frontDeskEmployee, 0, 2);
    sem_init(&bellhopEmployee, 0, 2);
    sem_init(&guestLeaves, 0, 0);
    sem_init(&roomRegistration, 0, 0);
    sem_init(&bagsDelivered, 0, 0);
    sem_init(&bagsReceived, 0, 0);
    sem_init(&printSemaphore, 0, 1);

    // Initialize arrays
    frontDeskEmployeeID = new int[25]; // Array to store the ID of front desk employees for each guest
    bellhopEmployeeID = new int[25]; // Array to store the ID of bellhop employees for each guest
    guestsRetired = new sem_t[25]; // Array of semaphores to track if guests have retired
    checkedIntoRoom = new sem_t[25]; // Array of semaphores to track if guests have reached their room

    for (int i = 0; i < 25; i++) {
        sem_init(&guestsRetired[i], 0, 0);
        sem_init(&checkedIntoRoom[i], 0, 0);
        frontDeskEmployeeID[i] = 0;
        bellhopEmployeeID[i] = 0;
    }

    cout << "Simulation starts" << endl;

    // Create frontDesk employees
    for (int i = 0; i < 2; i++)
        new FrontDesk(i);

    // Create bellhop employees
    for (int i = 0; i < 2; i++)
        new Bellhop(i);

    // Create guests
    Guest* guestArray[25];
    for (int i = 0; i < 25; i++) {
        guestArray[i] = new Guest(i);
    }
    
    // Join guest threads
    for (int i = 0; i < 25; i++) {
        pthread_join(guestArray[i]->guest, NULL);
        //cout << "Guest " + to_string(i) + " joined" << endl;
    }
    
    // Clean up
    for (int i = 0; i < 25; i++) {
        delete guestArray[i];
    }
    delete[] frontDeskEmployeeID;
    delete[] bellhopEmployeeID;
    delete[] checkedIntoRoom;
    delete[] guestsRetired;

    // Destroy semaphores
    sem_destroy(&guestMutex);
    sem_destroy(&frontDeskMutex);
    sem_destroy(&bellhopMutex);
    sem_destroy(&guestsReady);
    sem_destroy(&bellhopRequested);
    sem_destroy(&frontDeskEmployee);
    sem_destroy(&bellhopEmployee);
    sem_destroy(&guestLeaves);
    sem_destroy(&roomRegistration);
    sem_destroy(&bagsDelivered);
    sem_destroy(&bagsReceived);
    sem_destroy(&printSemaphore);
    
    cout << "Simulation ends" << endl;

    return 0;
}