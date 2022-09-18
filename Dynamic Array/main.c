#include <stdio.h>
#include <stdlib.h>

struct array{
    int * data;
    int size;
};

typedef struct array array;

void init(array * p);
void insertAtEnd(array * p, int value);
void insertAtHead(array * p, int value);
void insertIndex(array * p, int value, int index);
void deleteIndex(array * p, int index);
void deleteArray(array * p);

int main() {
    array arr;
    init(&arr);
    insertAtEnd(&arr, 10);
    insertAtEnd(&arr, 44);
    insertAtEnd(&arr, 33);
    insertAtEnd(&arr, 777);
    insertAtHead(&arr, 99);
    insertIndex(&arr, 888, 0);
    printf("Data : %d, size : %d\n", arr.data[0], arr.size);
    printf("Data : %d, size : %d\n", arr.data[1], arr.size);
    printf("Data : %d, size : %d\n", arr.data[2], arr.size);
    printf("Data : %d, size : %d ***\n", arr.data[3], arr.size);
    printf("Data : %d, size : %d\n", arr.data[4], arr.size);
    printf("Data : %d, size : %d\n", arr.data[5], arr.size);
    deleteIndex(&arr, 3);
    printf("Data : %d, size : %d ***\n", arr.data[3], arr.size);
    deleteArray(&arr); // Kill the Zombie
    return 0;
}

void init(array * p){
    p->data = (int *) malloc(sizeof (int));
    p->size = 0;
}

void insertAtEnd(array * p, int value){
    if(p->size == 0){
        p->data[0] = value;
        p->size++;
        return;
    }

    p->data = (int *)(realloc(p->data, sizeof (p->data)+1));
    p->data[p->size] = value;
    p->size++;
}

void insertAtHead(array * p, int value){
    if(p->size == 0){
        p->data[0] = value;
        p->size++;
        return;
    }

    int * tmp = (int *) malloc(sizeof (p->data)+1);
    tmp[0] = value;
    int i = 0;
    for(i = 1; i < p->size+1; i++){
        tmp[i] = p->data[i-1];
    }
    p->data = tmp;
    p->size++;
}

void insertIndex(array * p, int value, int index){
    if(index < 0 || index > p->size){
        printf("Sorry, the index must be positive and between 0 and %d.", p->size);
        return;
    }

    if(p->size == 0){
        insertAtEnd(p, value);
        return;
    }

    if(index == 0){
        insertAtHead(p, value);
        return;
    }

    if(index == p->size){
        insertAtEnd(p, value);
        return;
    }

    int i = 0;
    int * tmp = (int *)(malloc(sizeof (p->data)+1));

    for(i = 0; i < index; i++){
        tmp[i] = p->data[i];
    }
    tmp[index] = value;
    for(i = (index + 1); i < p->size+1; i++){
        tmp[i] = p->data[i-1];
    }

    p->data = tmp;
    p->size++;
}

void deleteIndex(array * p, int index){
    if(index < 0 || index > p->size){
        printf("Sorry, the index must be positive and between 0 and %d.", p->size);
        return;
    }

    int i = 0;
    int * tmp = (int *)(malloc(sizeof (p->data)-1));

    for(i = 0; i < index; i++){
        tmp[i] = p->data[i];
    }

    for(i = index + 1; i < p->size; i++){
        tmp[i-1] = p->data[i];
    }

    p->data = tmp;
    p->size--;
}

void deleteArray(array * p){
    free(p->data);
    //free(p);
}
