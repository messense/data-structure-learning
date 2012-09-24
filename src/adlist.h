#ifndef __ADLIST_H__
#define __ADLIST_H__

typedef struct listNode {
	struct listNode *prev;
	struct listNode *next;
	void * value;
} listNode;

typedef struct listIter {
	listNode *next;
	int direction;
} listIter;

typedef struct list
{
	listNode *head;
	listNode *tail;
	void *(*dup)(void *ptr);
	void (*free)(void *ptr);
	int (*match)(void *ptr, void *key);
	unsigned long len;
} list;

list *list_create(void);
void list_release(list* list);
list *list_add_head(list *list, void *value);
list *list_add_tail(list *list, void *value);
list *list_insert(list *list, listNode *old_node, void *value, int after);
void list_remove(list *list, listNode *node);
listIter *list_get_iterator(list *list, int direction);
listNode *list_next(listIter *iter);
void list_release_iterator(listIter *iter);
list *list_dup(list *orig);
listNode *list_search_key(list *list, void *key);
listNode *list_index(list *list, long index);
void list_rewind(list *list, listIter *li);
void list_rewind_tail(list *list, listIter *li);
void list_rotate(list *list);

/* Directions for iterators */
#define AL_START_HEAD 0
#define AL_START_TAIL 1


#endif