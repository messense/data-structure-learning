#ifndef __LINKLIST_H__
#define __LINKLIST_H__

typedef struct listNode {
	struct listNode *next;
	void *value;
} listNode;

typedef struct list {
	listNode *head;
	listNode *tail;
	unsigned long len;
	void (*free)(void *ptr);
} list;

typedef struct listIter{
	listNode *next;
} listIter;

list *list_create(void);
void list_release(list *list);
list *list_add(list *list, void *value);
list *list_add_head(list *list, void *value);
list *list_add_tail(list *list, void *value);
list *list_insert(list *list, listNode *old_node, void *value, int after);
list *list_remove(list *list, listNode *node);
listIter *list_get_iterator(list *list);
listNode *list_next(listIter *iter);
void list_release_iterator(listIter *iter);
listNode *list_index(list *list, long index);
void list_rewind(list *list, listIter *li);

#endif