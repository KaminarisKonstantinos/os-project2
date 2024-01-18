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

#define NAMESIZE 250
#define N_PROCESSES 50
#define NEW 1
#define RUNNING 2
#define STOPPED 3
#define EXITED 4

// A linked list node to store a process
struct processNode {
    char name[NAMESIZE];
    struct processNode* next;
    pid_t pid;
    int status;
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
    temp->status = NEW;
    temp->prev = NULL;
    return temp;
}

// Initialize the queue
struct queue* createQueue() {
    struct queue* q 
        = (struct queue*)malloc(sizeof(struct queue*));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

// Enqueue a process
void enqueue(struct queue* q, char *name){

    // Create new process node
    struct processNode* temp = newProcess(name);

    // If queue is empty initialize head and tail
    if (q->tail == NULL) {
        q->head = temp;
        q->tail = temp;
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

void execute(struct processNode* process) {
    if (process->status == NEW) {
        printf("I'm new!\n");
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            execlp(process->name, process->name, NULL);
        }
        else {
            process->pid = pid;
            wait(NULL);
        }
    }
}

int main(int argc, char **argv) {
    printf("Implement the scheduler here!\n");
    printf("input: %s\n", argv[argc-1]); 

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t readline;
    int i, lines = 0;
    char ch;

    // Check input
    if (argc < 2)
        exit(EXIT_FAILURE);

    // handle input
    fp = fopen(argv[argc-1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    // count number of lines in FILE
    while(!feof(fp))
    {
        ch = fgetc(fp);
        if(ch == '\n')
        {
            lines++;
        }
    }
    printf("Number of lines in file: %i\n", lines);

    // reset pointer to start of FILE
    rewind(fp);

    // Initiate queue
    struct queue* q = createQueue();

    i = -1;
    while ((readline = getline(&line, &len, fp)) != -1) {
        i++;
        //remove trailing newline
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        enqueue(q, line);
    }

    for (int i=0; i<lines; i++){
        wait(NULL);
    }
    //free(line);
    fclose(fp);

    struct processNode* k = q->head;

    // TODO: Schedule

    // Print entire queue
    while (k != q->tail) {
        execute(k);
        printf("%s\n", k->name);
        printf("%d\n", k->pid);
        printf("%d\n", k->status);
        k = k->next;
    }; 

    execute(k);
    printf("%s\n", q->tail->name);
    printf("%d\n", q->tail->pid);
    printf("%d\n", q->tail->status);

    return 0;
}
