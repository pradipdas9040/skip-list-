#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#define N 10000

typedef struct snode 
{
    int key;
    struct snode **forward;
} snode;

int SKIPLIST_MAX_LEVEL(int n)
{
    return log(n)/log(2);
}

typedef struct skiplist 
{
    int level;
    struct snode *header;
} skiplist;

skiplist *skiplist_init(skiplist *list) 
{
    int i;
    snode *header = (snode *) malloc(sizeof(struct snode));
    list->header = header;
    header->key = INT_MAX;
    header->forward = (snode **) malloc(sizeof(snode*) * (SKIPLIST_MAX_LEVEL(N) + 1));
    for (i = 0; i <= SKIPLIST_MAX_LEVEL(N); i++) 
    {
        header->forward[i] = list->header;
    }
    list->level = 1;
    return list;
}

int rand_level() 
{
    int level = 1;
    while (rand() < RAND_MAX / 2 && level < SKIPLIST_MAX_LEVEL(N))
        level++;
    return level;
}
 
int skiplist_insert(skiplist *list, int k) 
{
    snode *update[SKIPLIST_MAX_LEVEL(N) + 1];
    snode *x = list->header;
    int i, level;
    for (i = list->level; i >= 1; i--) 
    {
        while (x->forward[i]->key < k)
            x = x->forward[i];
        update[i] = x;
    }
    x = x->forward[1];
    if (k != x->key)
    {
        level = rand_level();
        if (level > list->level) 
        {
            for (i = list->level + 1; i <= level; i++) 
            {
                update[i] = list->header;
            }
            list->level = level;
        }
        x = (snode *) malloc(sizeof(snode));
        x->key = k;
        x->forward = (snode *) malloc(sizeof(snode) * (level + 1));
        for (i = 1; i <= level; i++) 
        {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
    }
    return 0;
}

static void Print(skiplist *list) 
{
    int i;
    snode *x; 
    for(i=1;i<=SKIPLIST_MAX_LEVEL(N);i++)
    {
        x = list->header;
        printf("Node in level %d: ",i);
        while (x && x->forward[i] != list->header) 
        {
            printf("%d->", x->forward[i]->key);
            x = x->forward[i];
        }
    printf("NIL\n");
    printf("\n");
    }
}

int main()
{
    int arr[N], i;
    skiplist list;
    skiplist_init(&list);
    srand(time(NULL));
    for(i =0; i< N; i++)
    {
        arr[i]=rand()%100000;
    }
    printf("Insert:\n");
    for (i = 0; i < N; i++)
    {
        skiplist_insert(&list, arr[i]);
    }
    Print(&list);
    return 0;
}

