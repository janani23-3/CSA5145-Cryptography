#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define STATE_WIDTH 5
#define LANE_SIZE 64
#define CAPACITY_WIDTH 9 

typedef struct {
    uint64_t lanes[STATE_WIDTH][STATE_WIDTH];
} StateMatrix;

int allCapacityLanesNonzero(StateMatrix *state) {
    int i, j;
    for (i = 0; i < STATE_WIDTH; i++) {
        for (j = 0; j < CAPACITY_WIDTH; j++) {
            if (state->lanes[i][j] == 0) {
                return 0; 
            }
        }
    }
    return 1; 
}

void simulateFilling(StateMatrix *state) {
    int i, j;
    for (i = 0; i < STATE_WIDTH; i++) {
        for (j = 0; j < CAPACITY_WIDTH; j++) {
            state->lanes[i][j] = 0xFFFFFFFFFFFFFFFFULL; 
        }
    }
}

int main() {
    StateMatrix state = {0}; 

    simulateFilling(&state);

    int steps = 0;
    while (!allCapacityLanesNonzero(&state)) {
        steps++;
    }

    printf("Number of steps taken to fill all capacity lanes: %d\n", steps);

    return 0;
}

