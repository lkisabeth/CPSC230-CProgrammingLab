#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

struct list_t
{
	struct node_t *first;
	struct node_t *last;
	int size;
};

struct node_t
{
	struct node_t *next;
	int data;
};

typedef struct node_t node_t;

list_t *create_list ()
{
	list_t *list = malloc (sizeof(list_t));

	list->first = NULL;
	list->last = NULL;
	list->size = 0;

	return list;
}

void free_list (list_t *list)
{
	node_t *head = list->first;
	node_t *tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}

	free(list);
}

int list_size (list_t *list)
{
    	return list->size;
}

void list_append (list_t *list, int item)
{
	node_t *node = malloc(sizeof(node_t));
	node->data = item;

	if (list->first == NULL) list->first = node;

	if (list->last != NULL) list->last->next = node;

	list->last = node;
	list->last->next = NULL;
	list->size++;
}

bool list_insert (list_t *list, int item, int index)
{
	node_t *newNode = malloc(sizeof(node_t));
	newNode->data = item;

	node_t *preceedingNode = list->first;

	if (index == 0)
	{
		newNode->next = preceedingNode;
		list->first = newNode;
		list->size++;
		return true;
	}

	for (int i = 0; preceedingNode != NULL && i != index-1; i++)
	{
		preceedingNode = preceedingNode->next;
	}

	if (preceedingNode == NULL)
	{
		return false;
	}

	node_t *trailingNode = preceedingNode->next;

	preceedingNode->next = newNode;
	newNode->next = trailingNode;
	list->size++;

	return true;
}

bool list_remove (list_t *list, int index)
{
	node_t *preceedingNode = list->first;

	if (preceedingNode == NULL) return false;

	if (index == 0)
	{
		list->first = preceedingNode->next;
		free(preceedingNode);
		list->size--;
		return true;
	}

	for (int i=0; preceedingNode != NULL && i < index-1; i++)
		preceedingNode = preceedingNode->next;

	node_t *node = preceedingNode->next;

	if (node == NULL) return false;

	node_t *trailingNode = node->next;

	free(node);

	preceedingNode->next = trailingNode;
	list->size--;
	return true;
}

int list_find (list_t *list, int item)
{
	int index = 0;
	node_t *node = list->first;

	while (node != NULL && node->data != item)
	{
		node = node->next;
		index++;
	}

	return (node != NULL) ? index : -1;
}

int list_get (list_t *list, int index)
{	
	node_t *node = list->first;

	for (int i = 0; node != NULL && i != index; i++)
	{
		node = node->next;
	}

	return (node != NULL) ? node->data : -1;
}
