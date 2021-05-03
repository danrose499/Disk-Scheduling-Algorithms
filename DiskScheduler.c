#include <stdio.h>
#include <stdlib.h>

#define DISKS 10000
#define REQUESTS 1000

int distance(int start, int end) { // distance between start and end is 'abs(end - start)'
    return abs(end - start);
}

/* FCFS: Requests are addressed in the order they arrive in the disk queue */
int FCFS(int requests[], int head) {
    int distanceTraveled = 0;
    for(int i = 0; i < REQUESTS; i++) {
        distanceTraveled += distance(requests[i], head);
        head = requests[i];
    }
    return distanceTraveled;
}

/* SSTF: Requests having shortest seek time are executed first */
int SSTF(int requests[], int head) {

}

/* SCAN: The disk arm moves into a particular direction and services the requests coming in its path. 
After reaching the end of disk, it reverses its direction and again services the requests arriving in its path. ("elevator" aproach) */
int SCAN(int requests[], int head) {

}

/* CSCAN: Instead of reversing direction (like in scan) the disk arm goes to the other end of the disk and starts servicing the requests from there (circular aproach)*/
int CSCAN(int requests[], int head) {

}

/* Look: Similar to the SCAN but the disk arm only goes to the last request to be serviced in front of the head before reverses its direction.
Thus it prevents the extra delay which occurred due to unnecessary traversal to the end of the disk. */
int LOOK(int requests[], int head) {

}

int main() {

}

// Note: Algorithm information above was taken from https://www.geeksforgeeks.org/disk-scheduling-algorithms/
