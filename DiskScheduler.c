#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define DISKS 10000
#define REQUESTS 1000

int cylinders[REQUESTS];

int distance(int start, int end) { // distance between start and end is 'abs(end - start)'
    return abs(end - start);
}

void generateRequests(int *cylinders, int upperLimit, int num) { // Generates num random cylinder requests from 0 - upperLimit stored in cylinders[] 
    srand(time(0)); // Seeds rand based on time to garuntee randomization
    for(int i = 0; i < num; i++) {
        cylinders[i] = rand() % (upperLimit+1); // Fill each index with an int between 0 and upperLimit
    }
}

/* FCFS: Requests are addressed in the order they arrive in the disk queue */
int FCFS(int cylinders[], int head) {
    int distanceTraveled = 0;
    for(int i = 0; i < REQUESTS; i++) {
        distanceTraveled += distance(cylinders[i], head);
        head = cylinders[i];
    }
    return distanceTraveled;
}

/* SSTF: Requests having shortest seek time are executed first */
int SSTF(int cylinders[], int head) {
    int distanceTraveled = 0;
    int temp[REQUESTS];
    for(int i = 0; i < REQUESTS; i++) {
        temp[i] = cylinders[i];
    }
    for(int i = 0; i < REQUESTS; i++) {
        
    }

    return distanceTraveled;
}

// /* SCAN: The disk arm moves into a particular direction and services the requests coming in its path. 
// After reaching the end of disk, it reverses its direction and again services the requests arriving in its path. ("elevator" aproach) */
// int SCAN(int cylinders[], int head) {

// }

// /* CSCAN: Instead of reversing direction (like in scan) the disk arm goes to the other end of the disk and starts servicing the requests from there (circular aproach)*/
// int CSCAN(int cylinders[], int head) {

// }

// /* LOOK: Similar to the SCAN but the disk arm only goes to the last request to be serviced in front of the head before reverses its direction.
// Thus it prevents the extra delay which occurred due to unnecessary traversal to the end of the disk. */
// int LOOK(int cylinders[], int head) {

// }

int main() {

}

// Note: Algorithm information above was taken from https://www.geeksforgeeks.org/disk-scheduling-algorithms/
