#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define N 1000000 // number of Particle
#define RANGE 100

typedef struct {
  double x;
  double y;
  double value;
} Position;

typedef struct {
  Position current;
  Position velocity;
  Position pBest;
} Particle;

typedef struct {
  Particle *first;
  Position gBest;
} Swarm;

double calFunc(double x, double y) {
  return x * x + y * y;
}

// random from -range / 2 -> range / 2
int getRand(int lower, int upper) {
  int x = rand() % (upper - lower);
  x += lower;
  return x;
}

void main(int argc, char** argv) {
  srand(time(NULL)); // for random
  int i, j, k = 0;
  Particle *particle = malloc(N * sizeof(Particle));
  Swarm *swarm = malloc(sizeof(Swarm));
  swarm->first = particle;

  // initialize gBest
  Position temp;
  temp.value = INT_MAX;
  swarm->gBest = temp;

  // initialize value for each Particle in swarm
  for (i = 0; i < N; i++) {
    // randomize position
    Position pos;
    pos.x = getRand(-RANGE, RANGE);
    pos.y = getRand(-RANGE, RANGE);
    pos.value = calFunc(pos.x, pos.y);

    // randomize velocity
    Position velocity;
    velocity.x = getRand(-2 * RANGE, 2 * RANGE);
    velocity.y = getRand(-2 * RANGE, 2 * RANGE);

    // set particle
    particle[i].current = pos;
    particle[i].velocity = velocity;
    particle[i].pBest = pos;

    // update gBest
    if (particle[i].pBest.value < swarm->gBest.value) {
      swarm->gBest = particle[i].pBest;
    }

    // printf("x = %f\n", particle[i].current.x);
    // printf("y = %f\n", particle[i].current.y);
    // printf("value = %f\n", particle[i].current.value);
  }

  // printf("%s\n", "GBEST************************");
  // printf("x = %f\n", swarm->gBest.x);
  // printf("y = %f\n", swarm->gBest.y);
  // printf("value = %f\n", swarm->gBest.value);

  while (1) {
    for (i = 0; i < N; i++) { // each particle
      for (j = 0; j < 2; j++) {
        if (j == 0) {
          int r_p = rand() % 2;
          int r_g = rand() % 2;

          // calculate new veclocity
          particle[i].velocity.x = particle[i].velocity.x
            + 1.9 * r_p * (particle[i].pBest.x - particle[i].current.x)
            + 1.9 * r_g * (swarm->gBest.x - particle[i].current.x);

          // calculate new position
          particle[i].current.x += particle[i].velocity.x;
        } else {
          int r_p = rand() % 2;
          int r_g = rand() % 2;

          // calculate new vector
          particle[i].velocity.y = particle[i].velocity.y
            + 1.9 * r_p * (particle[i].pBest.y - particle[i].current.y)
            + 1.9 * r_g * (swarm->gBest.y - particle[i].current.y);

          // calculate new position
          particle[i].current.y += particle[i].velocity.y;
        }
        if (i == 1)
        // printf("Veloccity: %f, %f\n", particle[i].velocity.x, particle[i].velocity.y);

        // recalculate value of current value
        particle[i].current.value = calFunc(particle[i].current.x,
            particle[i].current.y);

        if (particle[i].current.value < particle[i].pBest.value) {
          particle[i].pBest = particle[i].current;
          if (particle[i].pBest.value < swarm->gBest.value) {
            swarm->gBest = particle[i].pBest;
          }
        }
      }
    }

    if (swarm->gBest.value < 0.1) { // critical to end
      break;
    }

    k++;
  }
  printf("%s\n", "GBEST************************");
  printf("x = %f\n", swarm->gBest.x);
  printf("y = %f\n", swarm->gBest.y);
  printf("value = %f\n", swarm->gBest.value);
}
