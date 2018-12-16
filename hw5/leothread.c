//
//  main.c
//  leothread
//
//  Created by Nikki Woo on 11/26/18.
//  Copyright © 2018 Nikki Woo. All rights reserved.
//

//#include <csapp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void *thread(void *vargp);
int turnleo(int t);
void leothread(int N);

struct arg_struct {
    int nod;
    int maxnode;
    int levels;
};

int main (int argc, char *argv[])
{
    //argv[1] = 4;
    int j = (int)argv[1];
    
    leothread(j);
    return 0;
}

void leothread(int N) {
    struct arg_struct args;
    args.nod = 0;
    args.maxnode = (turnleo(N) - 1);
    args.levels = N;
    pthread_t zeromain;
    pthread_create(&zeromain, NULL, thread, (void *)&args);
    pthread_join(zeromain, NULL);
    exit(0);
}

void *thread(void *vargp) /* thread routine */ {
    struct arg_struct *args = vargp;
    int d = args->nod;
    int max = args->maxnode;
    int N = args->levels;
    //int k = turnleo(N - 1);
    //calculate children and see if d > max
    if (N - 1 <= 0) {
        printf("[%d]\n", d);
        return NULL;
    }
    int child1 = d + 1;
    int child2 = d + 1 + turnleo(N - 1);
    //printf("child2 : %d", child2);
    if (child1 > max || child2 > max) {
        //If so, print "[d]\n" and return
        printf("[%d]\n", d);
        return NULL;
    }
    
    //print "(T\n" and create children threads with values d + 1 and d + 1 + L(k - 1)
    //where k is used for L(k) - 1 which is the number of descendants for this node
    printf("(%d\n", d);
    struct arg_struct nodeargs1;
    nodeargs1.nod = child1;
    nodeargs1.maxnode = max;
    nodeargs1.levels = N - 1;
    pthread_t node1;
    //printf("child1\n");
    pthread_create(&node1, NULL, thread, (void *)&nodeargs1);
    pthread_join(node1, NULL);
    
    struct arg_struct nodeargs2;
    nodeargs2.nod = child2;
    nodeargs2.maxnode = max;
    nodeargs2.levels = N - 2;
    pthread_t node2;
    //printf("child2\n");
    pthread_create(&node2, NULL, thread, (void *)&nodeargs2);
    pthread_join(node2, NULL);

    // print "T)\n"
    printf("%d)\n",d);
    
    //printf("Hello, %d\n", *d);
    return NULL;
}

int turnleo(int t) {
    if (t == 0 || t == 1) {
        return 1;
    }
    //L(n - 1) + L(n - 2) + 1
    return (turnleo(t - 1) + turnleo(t - 2) + 1);
}
