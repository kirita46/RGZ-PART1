#ifndef PROG_RGZ_C_TVLIST_H
#define PROG_RGZ_C_TVLIST_H

#include "TV.h"

typedef struct TVList {
    TV* tv;
    struct TVList* next;
} TVList;

TVList* InitTVList(TV *tv) {
    TVList* list = malloc(sizeof(TVList));
    list->tv = tv;
    list->next = NULL;
    return list;
}

int AddItem(TVList* list, TV* item) {
    if (list == NULL) {
        return 0;
    }

    TVList* current = list;
    while (current->next != NULL) {
        current = current->next;
    }

    TVList* newItem = (TVList*)malloc(sizeof(TVList));
    if (newItem == NULL) {
        return 0;
    }
    newItem->tv = item;
    newItem->next = NULL;
    current->next = newItem;

    return 1;
}

int GetListSize(TVList *list) {
    TVList *q = list;
    int count = 0;
    while (q != NULL) {
        count++;
        q = q->next;
    }
    return count;
}

void DropList(TVList **list) {
    if (*list == NULL) {
        return;
    }

    TVList* current = *list;
    TVList* next;

    while (current != NULL) {
        next = current->next;
        free(current->tv);
        free(current);
        current = next;
    }
    *list = NULL;
    printf("List has been dropped");
}

int DropItemAtIndex(TVList **list, int atIndex) {
    if (*list == NULL) {
        return 0;
    }

    TVList *current = *list;
    if (atIndex == 0) {
        TVList *toDelete = current;
        *list = current->next;
        free(toDelete->tv);
        free(toDelete);
        return 1;
    }

    int count = 0;
    TVList *previous = NULL;

    while (current != NULL) {
        if (count == atIndex) {
            previous->next = current->next;
            free(current->tv);
            free(current);
            return 1;
        }
        previous = current;
        current = current->next;
        count++;
    }
    return 0;
}

TVList *GetItemByIndex(TVList *list, int index) {
    if (list == NULL || index < 0) {
        return NULL;
    }

    TVList *current = list;
    int count = 0;

    while (current != NULL) {
        if (count == index) {
            return current;
        }
        count++;
        current = current->next;
    }

    return NULL;
}

void PrintList(TVList *list) {
    if (list == NULL) {
        printf("\nList is null");
        return;
    }
    if (GetListSize(list) == 0) {
        printf("\nList is empty");
        return;
    }
    TVList *q = list;
    int count = 0;
    while (q != NULL && q->tv != NULL) {
        count++;
        printf("\n———— List item [%d] data ————", count);
        printData(q->tv);
        q = q->next;
    }
}

#endif //PROG_RGZ_C_TVLIST_H
