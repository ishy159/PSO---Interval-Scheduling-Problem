#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TIME 1000
#define NUM_INTERVAL 10

typedef struct {
  int start;
  int end;
} Interval;

typedef struct Node {
  Interval *current;
  struct Node *parent;
  int evalValue;
} Node;

int getRand(int lower, int upper) {
  int x = rand() % (upper - lower);
  x += lower;
  return x;
}

Interval *generateListInterval() {
  int i;
  Interval *lst = malloc(NUM_INTERVAL * sizeof(Interval));
  for (i = 0; i < NUM_INTERVAL; i++) {
    lst[i].start = getRand(0, MAX_TIME - 1);
    lst[i].end = getRand(lst[i].start + 1, MAX_TIME);
  }

  // test data
  // lst[0].start = 0;
  // lst[0].end = 2;
  // lst[1].start = 2;
  // lst[1].end = 5;
  // lst[2].start = 7;
  // lst[2].end = 8;
  return lst;
}

// check Interval i is overlaped by current and parent of current
int isOverlap(Node *node, Interval i) {
  if (node != NULL) {
    if (node->current->start == i.start) {
      return 1;
    }
    if (node->current->start < i.start) {
      if (node->current->end - i.start > 0) {
        return 1;
      } else {
        return isOverlap(node->parent, i);
      }
    } else {
      if (i.end - node->current->start > 0) {
        return 1;
      } else {
        return isOverlap(node->parent, i);
      }
    }
  } else {
    return 0;
  }
}

int calCoverTime(Node *node) {
  if (node != NULL) {
    int time = node->current->end - node->current->start;
    return time + calCoverTime(node->parent);
  } else {
    return 0;
  }
}

// remain space
// small value is better
int evaluateNode(Node *node) {
  return MAX_TIME - calCoverTime(node);
}

// generate children of current node
Node *generateNode(Node *node, Interval *list, int numberOfInterval) {
  int i, count = 0;
  Node *child = malloc(sizeof(Node));
  child->parent = node;
  child->evalValue = MAX_TIME;

  Node *temp = malloc(sizeof(Node));
  for (i = 0; i < numberOfInterval; i++) {
    if (!isOverlap(node, list[i])) {
      temp->current = &list[i];
      temp->parent = node;
      temp->evalValue = evaluateNode(temp);
      if (temp->evalValue < child->evalValue) {
        child->current = temp->current;
        child->evalValue = temp->evalValue;
      }
      count++;
    }
  }

  if (count == 0) {
    child = NULL;
  }

  return child;
}

void main(int argc, char** argv) {
  srand(time(NULL)); // for random
  int i;

  Interval *lstInterval = generateListInterval();

  Node *first = malloc(sizeof(Node)); // store HEAD pointer
  first->evalValue = MAX_TIME;
  first->parent = NULL;

  // find the best first Node for Greedy
  Node *temp = malloc(sizeof(Node));
  for (i = 0; i < NUM_INTERVAL; i++) {
    temp->current = &lstInterval[i];
    temp->parent = NULL;
    temp->evalValue = evaluateNode(temp);
    if (temp->evalValue < first->evalValue) {
      first->current = temp->current;
      first->evalValue = temp->evalValue;
    }
  }
  printf("Best first value: %d\n", first->evalValue);
  printf("Best first time: %d:%d\n", first->current->start, first->current->end);

  Node *crr = generateNode(first, lstInterval, NUM_INTERVAL);
  Node *prev;
  while (crr != NULL) {
    prev = crr;
    crr = generateNode(crr, lstInterval, NUM_INTERVAL);
  }

  // prev pointer is our result
  printf("%d\n", prev->evalValue);
  while (prev != NULL) {
    printf("Time: %d - %d\n", prev->current->start,  prev->current->end);
    printf("Evaluate: %d\n", prev->evalValue);
    prev = prev->parent;
  }



  // test case isOverlap
  // check i3 is overlap with i1 and i2
  Interval i1, i2, i3;
  i1.start = 0;
  i1.end = 2;
  i2.start = 4;
  i2.end = 9;
  i3.start = 8;
  i3.end = 10;
  Node *hehe = malloc(sizeof(Node));
  hehe->current = &i1;
  hehe->parent = NULL;

  Node *hihi = malloc(sizeof(Node));
  hihi->current = &i2;
  hihi->parent = hehe;

  int x = isOverlap(hihi, i3);
  // printf("%d\n", x);
  // end testcase isOverlap

  // test case evaluateNode
  int eval = evaluateNode(hehe);
  // printf("%d\n", eval);
}
