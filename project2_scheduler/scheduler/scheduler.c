//###############################################################
// 236064 1041756 Kaminaris Konstantinos
//###############################################################
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMESIZE 50

FILE *fp;
char *line = NULL;
size_t len = 0;
ssize_t read;

// A linked list node to store a process
struct processNode {
    char name[NAMESIZE];
    struct processNode* next;
    struct processNode* prev;
};

// The queue, head is the first and tail is the last element
struct queue {
    struct processNode *head, *tail;
};

// Create a new linked list node
struct processNode* newProcess(char *name){
    struct processNode* temp 
        = (struct processNode*)malloc(sizeof(struct processNode));
    strcpy(temp->name, name);
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

// Initialize the queue
struct queue* createQueue() {
    struct queue* q =
        (struct queue*)malloc(sizeof(struct queue*));
    q->head = q->tail = NULL;
    return q;
}

// Enqueue a process
void enqueue(struct queue* q, char *name){

    // Create new process node
    struct processNode* temp = newProcess(name);

    // If queue is empty initialize head and tail
    if (q->tail == NULL) {
        q->head = q->tail = temp;
        return;
    }

    // Add new node at the end of the queue
    q->tail->next = temp;
    temp->prev = q->tail;
    q->tail = temp;
    return;
}

// Dequeue a process
void dequeue(struct queue* q){

    // If queue is empty return NULL
    if (q->head == NULL)
        return; 

    // Store previous head and move head one node ahead
    struct processNode* temp = q->head;
    q->head = q->head->next;

    // If head becomes NULL, tail also becomes NULL
    if (q->head == NULL)
        q->tail = NULL;

    // Free memory
    free(temp);
    return;
}

int main(int argc, char **argv) {
    printf("Implement the scheduler here!\n");
    printf("input: %s\n", argv[argc-1]); 

    // Check input
    if (argc < 2)
        exit(EXIT_FAILURE);

    // handle input
    fp = fopen(argv[argc-1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    // Initiate queue
    struct queue* q = createQueue();

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("%s", line);
        enqueue(q, line);
    }

    free(line);

    struct processNode* i = q->head;

    // Print entire queue
    while (i != q->tail) {
        printf("\n%s", i->name);
        i = i->next;
    }; 

    printf("\n%s", q->tail->name);

    // TODO: Schedule

    return 0;
}
