
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <limits.h>
#include <stdbool.h>

#define DISKS 10000
#define REQUESTS 1000

int getDistance(int start, int end);                            // Calculates distance between start and end: 'abs(end - start)'
void generateRequests(int *cylinders, int upperLimit, int num); // Generates 'num' random cylinder requests from 0 to 'upperLimit' and stores them in 'cylinders[]' 
int cmpfunc (const void * a, const void * b);

/* FCFS: Requests are addressed in the order they arrive in the disk queue */
int FCFS(int cylinders[], int head) {
    int distanceTraveled = 0;
    for(int i = 0; i < REQUESTS; i++) {                      // Go through each request in order...
        distanceTraveled += getDistance(cylinders[i], head); // ... add its distance to the running tally
        head = cylinders[i];                                 // ... and move head to next index.
    }
    return distanceTraveled;
}

/* SSTF: Requests having shortest seek time are executed first */
int SSTF(int cylinders[], int head) {
    int distanceTraveled = 0;
    int temp[REQUESTS];
    bool visited[REQUESTS];
    for(int i = 0; i < REQUESTS; i++) { // Create a temp copy of cylinders[] and a bool array to keep track of visited disks
        temp[i] = cylinders[i];
        visited[i] = false;
    }
    for(int i = 0; i < REQUESTS; i++) {                                       // Iterates through the length of clyinders[REQUEST] array
        int min = INT_MAX, pos;                                               // Sets min as INT_MAX to ensure a minimum value will be found
        for(int j = 0; j < REQUESTS; j++) {                                   // Goes through every request...
            if((getDistance(temp[j], head) && (visited[j] == false)) < min) { // ... and if the current cylinder is the shortest distance away from head and is unvisited...
                min = getDistance(temp[i], head);                             // ... then remember the distance...
                pos = j;                                                      // ... and remember its index in cylinders.
            }
        }
        distanceTraveled += min; // Adds the previous minimum to running tally
        head = temp[pos];        // Moves head the minimum distance away
        visited[pos] = true;     // And set its value to INT_MAX to ensure it won't be visited again.
    }
    return distanceTraveled;
}

/* SCAN: The disk arm moves into a particular direction and services the requests coming in its path. 
After reaching the end of disk, it reverses its direction and again services the requests arriving in its path. ("elevator" aproach) */
int SCAN(int cylinders[], int head) {
    int distanceTraveled = 0;
    int leftSize = 0, rightSize = 0;
	int leftVals[REQUESTS], rightVals[REQUESTS]; 
    for(int i = 0; i < REQUESTS; i++) { 
		if(cylinders[i] > head) 
			rightVals[rightSize++] = cylinders[i]; 
		else
			leftVals[leftSize++]   = cylinders[i]; 
	}
    qsort(leftVals,  leftSize,  sizeof(*leftVals),  cmpfunc); 
	qsort(rightVals, rightSize, sizeof(*rightVals), cmpfunc); 
    for(int i = leftSize - 1; i >= 0; i--){ 
		distanceTraveled += getDistance(leftVals[i], head);
		head = leftVals[i];
	}
    distanceTraveled += getDistance(0, head);
	head = 0;
	for(int i = 0; i < rightSize; i++){
		distanceTraveled += getDistance(rightVals[i], head);
		head = rightVals[i];
	}
    return distanceTraveled;
}

/* CSCAN: Instead of reversing direction (like in scan) the disk arm goes to the other end of the disk and starts servicing the requests from there (circular aproach)*/
int CSCAN(int cylinders[], int head) {
    int distanceTraveled = 0;
    int leftSize = 0, rightSize = 0;
	int leftVals[REQUESTS], rightVals[REQUESTS]; 
    for(int i = 0; i < REQUESTS; i++) { 
		if(cylinders[i] > head) 
			rightVals[rightSize++] = cylinders[i]; 
		else
			leftVals[leftSize++]   = cylinders[i]; 
	}
    qsort(leftVals,  leftSize,  sizeof(*leftVals),  cmpfunc); 
	qsort(rightVals, rightSize, sizeof(*rightVals), cmpfunc); 
    for(int i = leftSize - 1; i >= 0; i--){ 
		distanceTraveled += getDistance(leftVals[i], head);
		head = leftVals[i];
	}
    distanceTraveled += getDistance(0, head);
	head = 0; 
	for(int i = rightSize - 1; i >= 0; i--){ 
        distanceTraveled += getDistance(rightVals[i], head);
		head = rightVals[i]; // New Head Value
	}
    return distanceTraveled;
}

/* LOOK: Similar to the SCAN but the disk arm only goes to the last request to be serviced in front of the head before reverses its direction.
Thus it prevents the extra delay which occurred due to unnecessary traversal to the end of the disk. */
int LOOK(int cylinders[], int head) {
    int distanceTraveled = 0;
    int leftSize = 0, rightSize = 0;
	int leftVals[REQUESTS], rightVals[REQUESTS]; 
    for(int i = 0; i < REQUESTS; i++) { 
		if(cylinders[i] > head) 
			rightVals[rightSize++] = cylinders[i]; 
		else
			leftVals[leftSize++]   = cylinders[i]; 
	}
    qsort(leftVals,  leftSize,  sizeof(*leftVals),  cmpfunc); 
	qsort(rightVals, rightSize, sizeof(*rightVals), cmpfunc); 
    for(int i = leftSize - 1; i >= 0; i--){ 
		distanceTraveled += getDistance(leftVals[i], head);
		head = leftVals[i];
	}
    // Unlike with SCAN, we don't move the head to the end of the disk, but reverse direction after last requested disk in this direction
	for(int i = 0; i < rightSize; i++){
		distanceTraveled += getDistance(rightVals[i], head);
		head = rightVals[i];
	}
    return distanceTraveled;
}

int main() {
    int cylinders[REQUESTS], head;
    generateRequests(cylinders, DISKS, REQUESTS);
	scanf("%d", &head); 
	while(head < 0 || head > DISKS - 1) {
		scanf("%d", &head); 
	}
    printf("_____________________________\n");
    printf("| Algorithm | Head Movement |\n"); 
    printf("|___________|_______________|\n");
    printf("| FCFS:     | % 13d |\n", FCFS(cylinders,  head)); 
    printf("| SSTF:     | % 13d |\n", SSTF(cylinders,  head)); 
    printf("| SCAN:     | % 13d |\n", SCAN(cylinders,  head));
    printf("| CSCAN:    | % 13d |\n", CSCAN(cylinders, head)); 
    printf("| LOOK:     | % 13d |\n", LOOK(cylinders,  head));  
    printf("|___________|_______________|\n");
	return 0;
}

int getDistance(int start, int end) { // distance between start and end is 'abs(end - start)'
    return abs(end - start);
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void generateRequests(int *cylinders, int upperLimit, int num) { // Generates num random cylinder requests from 0 - upperLimit stored in cylinders[] 
    srand(time(0)); // Seeds rand based on time to garuntee randomization
    for(int i = 0; i < num; i++) {
        cylinders[i] = rand() % upperLimit; // Fill each index with a random int where 0 ≤ int < upperLimit
    }
}
// Note: Algorithm information above was taken from https://www.geeksforgeeks.org/disk-scheduling-algorithms/
