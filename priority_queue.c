#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

struct node {
    int data;
    int priority;
};

struct priority_queue {
    int size;
    int capacity;
    struct node* data;
};

typedef struct priority_queue Priority_queue;

void fix_up(PRIORITY_QUEUE hQueue, int index);
void fix_down(PRIORITY_QUEUE hQueue, int index);

PRIORITY_QUEUE priority_queue_init_default(void) {
    Priority_queue* pQueue = (Priority_queue*)malloc(sizeof(Priority_queue));
    if (pQueue != NULL) {
        pQueue->size = 0;
        pQueue->capacity = 1;
        pQueue->data = (struct node*)malloc(sizeof(struct node) * pQueue->capacity);
        if (pQueue->data == NULL) {
            free(pQueue);
            return NULL;
        }
    }
    return (PRIORITY_QUEUE)pQueue;
}

Status priority_queue_insert(PRIORITY_QUEUE hQueue, int priority_level, int data_item) {
    Priority_queue* pQueue = (Priority_queue*)hQueue;
    struct node* temp;
    int i;
    if (pQueue->size >= pQueue->capacity) {
        pQueue->capacity *= 2;
        temp = (struct node*)malloc(sizeof(struct node) * pQueue->capacity);
        for (i = 0; i < pQueue->size; i++)
        {
            temp[i] = pQueue->data[i];
        }
        free(pQueue->data);
        pQueue->data = temp;
        if (pQueue->data == NULL) {
            return FAILURE;
        }
    }

    //dyanically allcoate a bigger array using temp not data
    //copy all the information from data to temp
    //free data
    //make data equal to temp.
    pQueue->data[pQueue->size].data = data_item;
    pQueue->data[pQueue->size].priority = priority_level;
    pQueue->size++;
    
    fix_up(hQueue, pQueue->size - 1);
    
    return SUCCESS;
}

Status priority_queue_service(PRIORITY_QUEUE hQueue) {
    if (priority_queue_is_empty(hQueue) == TRUE) {
        return FAILURE;
    }

    Priority_queue* pQueue = (Priority_queue*)hQueue;

    pQueue->data[0] = pQueue->data[pQueue->size - 1];
    pQueue->size--;

    fix_down(hQueue, 0);

    return SUCCESS;
}

int priority_queue_front(PRIORITY_QUEUE hQueue, Status* pStatus) {
    Priority_queue* pQueue = (Priority_queue*)hQueue;

    if (pQueue->size > 0) {
        *pStatus = SUCCESS;
        return pQueue->data[0].data;
    } else {
        *pStatus = FAILURE;
        return -1;
    }
}

Boolean priority_queue_is_empty(PRIORITY_QUEUE hQueue) {
    Priority_queue* pQueue = (Priority_queue*)hQueue;

    return (pQueue->size == 0) ? TRUE : FALSE;
}

void priority_queue_destroy(PRIORITY_QUEUE* phQueue) {
    Priority_queue* pQueue = (Priority_queue*)*phQueue;
    free(pQueue->data);
    free(pQueue);
    *phQueue = NULL;
}

void fix_up(PRIORITY_QUEUE hQueue, int index) {
    Priority_queue* pQueue = (Priority_queue*)hQueue;

    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pQueue->data[parent].priority < pQueue->data[index].priority) {
            struct node temp = pQueue->data[parent];
            pQueue->data[parent] = pQueue->data[index];
            pQueue->data[index] = temp;
            index = parent;
        } else {
            break;
        }
    }
}

void fix_down(PRIORITY_QUEUE hQueue, int index) {
    Priority_queue* pQueue = (Priority_queue*)hQueue;
    printf("The size is: %d\n", pQueue->size);
    while (index * 2 + 1 < pQueue->size) {
        int left = index * 2 + 1;
        int right = left + 1;
        int largest = left;

        if (right < pQueue->size && pQueue->data[right].priority > pQueue->data[left].priority) {
            largest = right;
        }

        if (pQueue->data[index].priority < pQueue->data[largest].priority) {
            printf("The value of the index of the largest: %d\n", pQueue->data[index].data);
            struct node temp = pQueue->data[index];
            pQueue->data[index] = pQueue->data[largest];
            pQueue->data[largest] = temp;
            index = largest;
        } else {
            break;
        }
    }
}
