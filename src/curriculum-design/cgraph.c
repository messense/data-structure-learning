#include <stdio.h>
#include <stdlib.h>

#define kMaxVextex 10

typedef struct qnode {
    int value; // value of node
    struct qnode *next; // point of the next node
} qnode_t; /* node of queue */

typedef struct {
    qnode_t *head; // head node of queue
    qnode_t *tail; // tail node of queue
    unsigned long size; // size of queue
} queue_t; /* queue */

/**
 * create a new queue, don't forget to free it then
 * return a point to queue_t if success, otherwise return NULL
 */
queue_t *create_queue(void) {
    queue_t *q;
    q = (queue_t *)malloc(sizeof(queue_t));
    if (q == NULL) {
        printf("malloc failed.\n");
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/**
 * enqueue a number
 * return a point of queue_t if success, otherwise return NULL
 */
queue_t *enqueue(queue_t *q, int value) {
    qnode_t *node;
    node = (qnode_t *)malloc(sizeof(qnode_t));
    if (node == NULL) {
        printf("malloc failed.\n");
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    if (q->size == 0) {
        q->head = node;
        q->tail = node;
    } else {
        qnode_t *tail = q->tail;
        tail->next = node;
        q->tail = node;
    }
    q->size++;
    return q;
}

/**
 * dequeue a number
 * return a number in the head of the queue, if queue size is zero return 0
 */
int dequeue(queue_t *q) {
    if (q->size == 0) {
        return 0;
    }
    qnode_t *head = q->head;
    qnode_t *next = head->next;
    q->head = next;
    q->size--;
    int value = head->value;
    free(head);
    return value;
}

int visited[kMaxVextex];

typedef struct {
    int vexnum; // number of vextex
    int arcnum; // number of arc
    char vexs[kMaxVextex]; // vextexs
    int arcs[kMaxVextex][kMaxVextex]; // arcs
} mgraph_t; /* matrix graph */

/* print matrix graph for debuging */
void print_mgraph(mgraph_t *graph) {
    int i, j;
    printf("输出的图的顶点为：\n");
    for (i = 0; i < graph->vexnum; i++) {
        printf("%3c", graph->vexs[i]);
    }
    printf("\n图的邻接矩阵为：\n");
    for (i = 0; i < graph->vexnum; i++) {
        for (j = 0; j < graph->vexnum; j++) {
            printf("%3d", graph->arcs[i][j]);
        }
        printf("\n");
    }
}

/**
 * create a new matrix graph
 */
void create_mgraph(mgraph_t *graph) {
    int i, j, k, w;
    printf("请输入顶点数和边数：\n");
    scanf("%d%d", &graph->vexnum, &graph->arcnum);
    int arcsum = graph->vexnum * (graph->vexnum - 1) / 2; // maxium vextex count
    if (graph->vexnum > kMaxVextex) {
        printf("暂时不支持超过%d个顶点的图.\n", kMaxVextex);
        exit(0);
    }
    if (graph->arcnum < 1 || graph->arcnum > arcsum) {
        printf("边数输入不合法！\n");
        exit(0);
    }
    printf("请输入%d个顶点序号\n", graph->vexnum);
    for (i = 0; i < graph->vexnum; i++) {
        for (j = 0; j < graph->vexnum; j++) {
            graph->arcs[i][j] = 0;
        }
        getchar();
        graph->vexs[i] = getchar();
    }
    getchar();
    for (k = 0; k < graph->vexnum; k++) {
        printf("请输入第%d对边的起点、终点和权值信息：\n", k+1);
        scanf("%d%d%d", &i, &j, &w);
        graph->arcs[i][j] = w;
        graph->arcs[j][i] = w;
    }
    //print_mgraph(graph);
}

/**
 * for dfs_traverse_mgraph function
 */
void dfs_mgraph(mgraph_t *graph, int i) {
    printf("%c-->", graph->vexs[i]);
    visited[i] = 1;
    int j;
    for (j = 0; j < graph->vexnum; j++) {
        if (graph->arcs[i][j] != 0 && !visited[j]) {
            dfs_mgraph(graph, j);
        }
    }
}

/**
 * traverse a matrix graph by depth first searching
 * i is the start vextex
 */
void dfs_traverse_mgraph(mgraph_t *graph, int i) {
    int j;
    for (j = 0; j < graph->vexnum; j++) {
        visited[j] = 0;
    }
    dfs_mgraph(graph, i);
}

/**
 * traverse a matrix graph by breadth first searching
 * i is the start vextex
 */
void bfs_traverse_mgraph(mgraph_t *graph, int i) {
    int j, k;
    for (j = 0; j < graph->vexnum; j++) {
        visited[j] = 0;
    }
    queue_t *queue = create_queue();
    printf("%c-->", graph->vexs[i]);
    visited[i] = 1;
    enqueue(queue, i);
    while(queue->size > 0) {
        k = dequeue(queue);
        for (j = 0; j < graph->vexnum; j++) {
            if (graph->arcs[k][j] != 0 && !visited[j]) {
                printf("%c-->", graph->vexs[j]);
                visited[j] = 1;
                enqueue(queue, j);
            }
        }
    }
    free(queue);
}

typedef struct arcnode{
    int adjvex; // adjacency vextex number
    int weight; // arc weight
    struct arcnode *next; // point of the next arc
} arc_t; /* arc or edge of graph */

typedef struct {
    char vextex; // vextex number
    arc_t *head; // point of the arc
} vex_t; /* vextex of graph */

typedef struct {
    vex_t adjlist[kMaxVextex]; // adjacency list
    int vexnum; // vextex number
    int arcnum; // arc number
} algraph_t; /* adjacency list graph structure */

/* print adjacency list graph for debuging */
void print_algraph(algraph_t *graph) {
    int i;
    arc_t *head;
    printf("图的邻接表为：\n");
    for (i = 0; i < graph->vexnum; i++) {
        printf("%c\n", graph->adjlist[i].vextex);
        head = graph->adjlist[i].head;
        while(head) {
            printf("%d-->", head->adjvex);
            head = head->next;
        }
        printf("\n");
    }
}

/*
 * create a new adjacency list graph
 */
void create_algraph(algraph_t *graph) {
    int i, j, k, w;
    printf("请输入顶点数和边数：\n");
    scanf("%d%d", &graph->vexnum, &graph->arcnum);
    int arcsum = graph->vexnum * (graph->vexnum - 1) / 2; // maxium vextex count
    if (graph->vexnum > kMaxVextex) {
        printf("暂时不支持超过%d个顶点的图.\n", kMaxVextex);
        exit(0);
    }
    if (graph->arcnum < 1 || graph->arcnum > arcsum) {
        printf("边数输入不合法！\n");
        exit(0);
    }
    printf("请输入%d个顶点序号\n", graph->vexnum);
    for (i = 0; i < graph->vexnum; i++) {
        getchar();
        graph->adjlist[i].vextex = getchar();
        graph->adjlist[i].head = NULL;
    }
    for (k = 0; k < graph->vexnum; k++) {
        printf("请输入第%d对边的起点、终点和权值信息：\n", k+1);
        scanf("%d%d%d", &i, &j, &w);
        arc_t *arc;

        arc = (arc_t *)malloc(sizeof(arc_t));
        arc->adjvex = j;
        arc->weight = w;
        arc->next = graph->adjlist[i].head;
        graph->adjlist[i].head = arc;

        arc = (arc_t *)malloc(sizeof(arc_t));
        arc->adjvex = i;
        arc->weight = w;
        arc->next = graph->adjlist[j].head;
        graph->adjlist[j].head = arc;
    }
    print_algraph(graph);
}

/*
 * for dfs_traverse_algraph function
 */
void dfs_algraph(algraph_t *graph, int i) {
    printf("%c-->", graph->adjlist[i].vextex);
    visited[i] = 1;
    arc_t *head = graph->adjlist[i].head;
    while(head) {
        if (!visited[head->adjvex]) {
            dfs_algraph(graph, head->adjvex);
        }
        head = head->next;
    }
}

/**
 * traverse a adjacency list graph by depth first searching
 * i is the start vextex
 */
void dfs_traverse_algraph(algraph_t *graph, int i) {
    int j;
    for (j = 0; j < graph->vexnum; j++) {
        visited[j] = 0;
    }
    dfs_algraph(graph, i);
}

/**
 * traverse a adjacency list graph by breadth first searching
 * i is the start vextex
 */
void bfs_traverse_algraph(algraph_t *graph, int i) {
    int j, k;
    for (j = 0; j < graph->vexnum; j++) {
        visited[j] = 0;
    }
    queue_t *queue = create_queue();
    printf("%c-->", graph->adjlist[i].vextex);
    visited[i] = 1;
    enqueue(queue, i);
    while(queue->size > 0) {
        k = dequeue(queue);
        arc_t *head = graph->adjlist[k].head;
        while(head) {
            if (!visited[head->adjvex]) {
                printf("%c-->", graph->adjlist[head->adjvex].vextex);
                visited[head->adjvex] = 1;
                enqueue(queue, head->adjvex);
            }
            head = head->next;
        }
    }
    free(queue);
}

/* main function */
int main(int argc, char const *argv[])
{
    int i;
    mgraph_t mgraph;
    algraph_t *algraph;

    printf("===    图的遍历课程设计    ===\n\n");
    printf("---    图的邻接矩阵的遍历    ---\n");
    create_mgraph(&mgraph);
    printf("请输入按图的深度优先遍历的起始顶点：\n");
    scanf("%d", &i);
    dfs_traverse_mgraph(&mgraph, i);
    printf("\n请输入按图的广度优先遍历的起始顶点：\n");
    scanf("%d", &i);
    bfs_traverse_mgraph(&mgraph, i);
    printf("\n\n");

    printf("---    图的邻接表的遍历    ---\n");
    algraph = (algraph_t *)malloc(sizeof(algraph_t));
    if (algraph == NULL) {
        printf("malloc failed.\n");
        exit(EXIT_FAILURE);
    }
    create_algraph(algraph);
    printf("请输入按图的深度优先遍历的起始顶点：\n");
    scanf("%d", &i);
    dfs_traverse_algraph(algraph, i);
    printf("\n请输入按图的广度优先遍历的起始顶点：\n");
    scanf("%d", &i);
    bfs_traverse_algraph(algraph, i);
    free(algraph);

    return 0;
}