//###############################################################
// 236064 1041756 Kaminaris Konstantinos
//###############################################################
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <time.h>

#define NAMESIZE 50
#define N_PROCESSES 50

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
struct processNode* newProcess(char *name, pid_t pid){
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
void enqueue(struct queue* q, char *name, pid_t pid){

    // Create new process node
    struct processNode* temp = newProcess(name, pid);

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

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t readline;
    pid_t pid[N_PROCESSES];
    int i;

    // Check input
    if (argc < 2)
        exit(EXIT_FAILURE);

    // handle input
    fp = fopen(argv[argc-1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    // Initiate queue
    struct queue* q = createQueue();

    i = -1;
    while ((readline = getline(&line, &len, fp)) != -1) {
        i++;
        //remove trailing newline
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        pid[i] = fork();
        // fork gone wrong
        if (pid[i] == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        // child
        else if (pid[i] == 0) {
            enqueue(q, line, getpid());
            break;
        }
        // parent
        else {
        }
    }

    free(line);
    fclose(fp);

    struct processNode* k = q->head;

    // Print entire queue
    while (k != q->tail) {
        printf("\n%s", k->name);
        k = k->next;
    }; 

    printf("\n%s", q->tail->name);

    free(q);

    // TODO: Schedule

    return 0;
}
