#pragma once

typedef struct linked_list {
	void* data;
	struct linked_list* next;
	struct linked_list* prev;
} linked_list;

linked_list* linked_list_insert(linked_list* list, void* new_elem);
linked_list* linked_list_append(linked_list* list, void* new_elem);
linked_list* linked_list_delete_element(linked_list* list, linked_list* element);
void linked_list_destroy(linked_list* list);

