#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include "commonlist.h"

typedef CommonList list;

list *list_create(void);
void list_release(list *list);
list *list_add(list *list, void *value);
list *list_add_head(list *list, void *value);
list *list_add_tail(list *list, void *value);
list *list_insert(list *list, Node *old_node, void *value, int after);
list *list_remove(list *list, Node *node);
Node *list_index(list *list, long index);

#endif