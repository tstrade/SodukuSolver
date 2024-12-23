#include "datastructs.h"
#include <stdlib.h>
#include <stdio.h>

#define SLOTS_TIMES_NEIGHBORS 1620

struct Queue {
  int **tuples;
  int maxSize;
  int currSize;
  int head;
  int tail;
};

Queue *initQueue(Queue *q) {
  q = malloc(sizeof(Queue));
  if (q == NULL) {
    fprintf(stderr, "Malloc failed on Queue struct!\n");
    exit(EXIT_FAILURE);
  }

  q->maxSize = SLOTS_TIMES_NEIGHBORS;
  q->currSize = 0;
  q->head = 0;
  q->tail = 0;

  q->tuples = malloc(SLOTS_TIMES_NEIGHBORS * sizeof(int *));

  if (q->tuples == NULL) {
    fprintf(stderr, "Malloc failed on tuples list!\n");
    exit(EXIT_FAILURE);
  }

  int tupleIndex;
  for (tupleIndex = 0; tupleIndex < SLOTS_TIMES_NEIGHBORS; tupleIndex++) {
    q->tuples[tupleIndex] = calloc(2, sizeof(int));

    if (q->tuples[tupleIndex] == NULL) {
      fprintf(stderr, "Calloc failed on tuple #%d!\n", tupleIndex);
      exit(EXIT_FAILURE);
    }
  }

  return q;
}

void enqueue(Queue *q, int Xi, int Xj) {
  int tail = q->tail;

  q->tuples[tail][0] = Xi;
  q->tuples[tail][1] = Xj;

  q->tail = (q->tail + 1) % q->maxSize;
  q->currSize += 1;
}

void dequeue(Queue *q, int *item) {
  item[0] = q->tuples[q->head][0];
  item[1] = q->tuples[q->head][1];

  q->head = (q->head + 1) % q->maxSize;
  q->currSize -= 1;
}

int *peek(Queue *q) {
  return q->tuples[q->head];
}

int isFull(Queue *q) {
  return (q->currSize >= SLOTS_TIMES_NEIGHBORS);
}

int isEmpty(Queue *q) {
  return (q->currSize == 0);
}

void destroyQueue(Queue *q) {
  int tuplesIndex;
  for (tuplesIndex = 0; tuplesIndex < q->maxSize; tuplesIndex++) {
    free(q->tuples[tuplesIndex]);
    q->tuples[tuplesIndex] = NULL;
  }

  free(q->tuples);
  free(q);
  q = NULL;
}