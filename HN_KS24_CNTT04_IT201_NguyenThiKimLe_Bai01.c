#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Request {
    char username[30];
    char issue[100];
    char timestamp[30];
} Request;

typedef struct Stack {
    Request* requests;
    int top;
    int size;
} Stack;
typedef struct Queue {
    Request* requests;
    int front;
    int rear;
    int capacity;
} Queue;

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(capacity * sizeof(Queue));
    queue->requests = (Request*)malloc(capacity * sizeof(Request));
    queue -> front = 1;
    queue -> rear = 0;
    queue -> capacity = capacity;
    return queue;
}

int isQueueEmpty(Queue* queue) {
    if (queue -> front > queue -> rear) {
        return 1;
    }
    return 0;
}
int isQueueFull(Queue* queue) {
    if (queue -> rear >=  queue -> capacity -1) {
        return 1;
    }
    return 0;
}
void enqueue(Queue* queue, Request request) {
    if (isQueueFull(queue)) {
        printf("Queue is full\n");
        return;
    }
    queue -> requests[++queue ->rear ] = request;
}
void dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    queue -> front++;
    return;
}

void printQueue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    for (int i = queue -> front; i <= queue -> rear;i++) {
        printf("Username: %s\n", queue -> requests[i].username);
        printf("Issue: %s\n", queue -> requests[i].issue);
        printf("Timestamp: %s\n", queue -> requests[i].timestamp);
        printf("\n");
    }
}
Stack* createStack(int size) {
    Stack* stack = (Stack*)malloc(size * sizeof(Stack));
    stack->requests = (Request*)malloc(size * sizeof(Request));
    stack -> top = -1;
    stack -> size = size;
    return stack;
}

int isStackEmpty(Stack* stack) {
    if (stack ->top == -1) {
        return 1;
    }
    return 0;
}

int isStackFull(Stack* stack) {
    if (stack -> top == stack -> size - 1) {
        return 1;
    }
    return 0;
}
void push (Stack* stack, Request request) {
    if (isStackFull(stack)) {
        printf("Stack is empty\n");
        return;
    }
    stack -> requests[++stack -> top] = request;
}
void pop(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack is emptyy\n");
        return;
    }
    stack -> top --;
    return;
}

int main() {
    int choice;
    Queue* requestQueue = createQueue(100);
    Stack* requestStack = createStack(100);

    do{
        printf("===REQUEST HANDLER===\n");
        printf("1. CREATE REQUEST\n");
        printf("2. PROCESS\n");
        printf("3. UNDO\n");
        printf("4. VIEW\n");
        printf("5. HISTORY\n");
        printf("6. CLEAR HISTORY\n");
        printf("7. EXIT\n");
        printf("Enter your choice:");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                Request newRequest;
                printf("User name: ");
                scanf("%s", newRequest.username);
                printf("Issue: ");
                scanf("%s", newRequest.issue);
                printf("Timetamp: ");
                scanf("%s", newRequest.timestamp);
                enqueue(requestQueue, newRequest);
                break;
            case 2:
                if (!isQueueEmpty(requestQueue)) {
                    push(requestStack, requestQueue->requests[requestQueue->front]);
                    dequeue(requestQueue);
                }
                break;
            case 3:
                Request lastProcessed = requestStack->requests[requestStack->top];
                pop(requestStack);
                enqueue(requestQueue, lastProcessed);
                break;
            case 4:
                printQueue(requestQueue);
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                printf("EXIT\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
                break;
        }
    }while (choice != 7);
    return 0;
}
