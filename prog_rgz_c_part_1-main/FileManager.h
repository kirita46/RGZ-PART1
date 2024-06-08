#ifndef PROG_RGZ_C_FILEMANAGER_H
#define PROG_RGZ_C_FILEMANAGER_H

#include <sys/fcntl.h>
#include "TVList.h"

void SaveListToFile(TVList *list, const char *filename) {
    if (list == NULL || filename == NULL) {
        return;
    }

    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Unable to open file for writing");
        return;
    }

    TVList *current = list;
    while (current != NULL && current->tv != NULL) {
        fwrite(current->tv, sizeof(TV), 1, file);
        current = current->next;
    }

    fclose(file);
}

void LoadListFromFile(TVList **list, char *filename) {
    if (filename == NULL) {
        return;
    }

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Unable to open file for reading");
        return;
    }

    TV temp;
    TVList *current = *list;
    while (fread(&temp, sizeof(TV), 1, file) == 1) {
        TV *newTV = Init(temp.brand, temp.model, temp.color, temp.screen_size);
        if (current == NULL) {
            *list = InitTVList(newTV);
            current = *list;
        } else {
            AddItem(current, newTV);
            current = current->next;
        }
    }

    fclose(file);
}

#endif //PROG_RGZ_C_FILEMANAGER_H
