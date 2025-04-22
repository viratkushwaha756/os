#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h> 
 
#define MAX 100 
 
typedef struct { 
    char data[MAX][MAX]; 
    int front, rear; 
} Queue; 
 
void initQueue(Queue *q) { 
    q->front = 0; 
    q->rear = 0; 
} 
 
void enqueue(Queue *q, char *msg) { 
    if (q->rear < MAX) { 
        strcpy(q->data[q->rear++], msg); 
    } 
} 
 
char* dequeue(Queue *q) { 
    if (q->front < q->rear) { 
        return q->data[q->front++]; 
    } 
    return NULL; 
} 
 
int main() { 
    int pipe1[2], pipe2[2]; 
    Queue parentQueue, childQueue; 
    char msg[MAX]; 
 
    pipe(pipe1); 
    pipe(pipe2); 
    initQueue(&parentQueue); 
    initQueue(&childQueue); 
 
    if (fork() == 0) { 
        close(pipe1[1]); 
        close(pipe2[0]); 
 
        read(pipe1[0], msg, sizeof(msg)); 
        enqueue(&childQueue, msg); 
        printf("Child read: %s", dequeue(&childQueue)); 
 
        printf("Child: Enter message: "); 
        fgets(msg, sizeof(msg), stdin); 
        enqueue(&childQueue, msg); 
        write(pipe2[1], dequeue(&childQueue), strlen(msg)); 
 
        close(pipe1[0]); 
        close(pipe2[1]); 
    } else { 
        close(pipe1[0]); 
        close(pipe2[1]); 
 
        printf("Parent: Enter message: "); 
        fgets(msg, sizeof(msg), stdin); 
        enqueue(&parentQueue, msg); 
        write(pipe1[1], dequeue(&parentQueue), strlen(msg)); 
 
        read(pipe2[0], msg, sizeof(msg)); 
        enqueue(&parentQueue, msg); 
        printf("Parent read: %s", dequeue(&parentQueue)); 
 
        close(pipe1[1]); 
        close(pipe2[0]); 
    } 
    return 0; 
}