#include <stdlib.h>
#include <stdio.h>
#include "utils.h"   

typedef struct{
    Node* next;
    position* position;
}Node;

typedef struct{
    Node* head;
    int size;
}list;

//List methods