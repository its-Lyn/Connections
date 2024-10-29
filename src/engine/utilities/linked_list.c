#include <stdio.h>
#include <stdlib.h>

#include "engine/utilities/linked_list.h"

linked_list* linked_list_insert(linked_list* list, void* new_data) {
	linked_list* new_elem = calloc(1, sizeof(linked_list));

	new_elem->data = new_data;
	new_elem->next = list;

	if (list != NULL) {
		if (list->prev != NULL) {
			new_elem->prev = list->prev;
			list->prev->next = new_elem;
		}
		list->prev = new_elem;
	}

	return new_elem;
}

linked_list* linked_list_append(linked_list* list, void* new_data) {
	if (list == NULL) {
		return NULL; // for append list cant be null, insert must be called instead
	}

	linked_list* new_elem = calloc(1, sizeof(linked_list));

	new_elem->data = new_data;
	new_elem->prev = list;

	if (list->next != NULL) {
		list->next->prev = new_elem;
		new_elem->next = list->next;
	}

	list->next = new_elem;

	return new_elem;
}

linked_list* linked_list_delete_element(linked_list* list, linked_list* element) {
	if (element->next != NULL) element->next->prev = element->prev;
	if (element->prev != NULL) element->prev->next = element->next;
	else list = element->next;

	free(element);
	return list;
}

void linked_list_destroy(linked_list* list) {
	linked_list* curr = list;
	while (curr != NULL) {
		linked_list* next = curr->next;
		free(curr);
		curr = next;
	}
}

