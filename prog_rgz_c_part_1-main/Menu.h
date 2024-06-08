#ifndef PROG_RGZ_C_MENU_H
#define PROG_RGZ_C_MENU_H

#include "TV.h"
#include "TVList.h"
#include "FileManager.h"

#define MAX_CHOICE_VALUE 5
#define MIN_CHOICE_VALUE 0
#define PATH "file.bin"

void PrintMenu() {
    printf("\n———— Menu ————");
    printf("\n1) Add item");
    printf("\n2) Remove item (by index)");
    printf("\n3) Print List");
    printf("\n4) Drop List");
    printf("\n5) Load List from saved file");
    printf("\n0) Exit menu");
}

int AwaitChoice() {
    int choice;
    printf("\nEnter your choice:\n");
    scanf("%d", &choice);
    if (choice < MIN_CHOICE_VALUE || choice > MAX_CHOICE_VALUE) {
        printf("Unsupported choice");
        AwaitChoice();
        return -1;
    }
    return choice;
}

void ActionAddItem(TVList **list) {
    char brand[BRAND_NAME_SIZE_MAX];
    char model[MODEL_NAME_SIZE_MAX];
    char color[COLOR_NAME_SIZE_MAX];
    int screen_size;

    printf("\nEnter brand: ");
    scanf("%s", brand);
    printf("\nEnter model: ");
    scanf("%s", model);
    printf("\nEnter color: ");
    scanf("%s", color);
    printf("\nEnter screen size: ");
    scanf("%d", &screen_size);
    TV *newTV = Init(brand, model, color, screen_size);
    if (*list == NULL) {
        *list = InitTVList(newTV);
        SaveListToFile(*list, PATH);
    } else {
        AddItem(*list, newTV);
        SaveListToFile(*list, PATH);
    }
}

void ActionRemoveItem(TVList **list) {
    int index;
    printf("\nEnter index to remove: ");
    scanf("%d", &index);

    if (*list == NULL) {
        printf("\nList is null\n");
        return;
    }

    if (DropItemAtIndex(list, index)) {
        printf("Item at index %d removed\n", index);
    } else {
        printf("Failed to remove item at index %d.\n", index);
    }

    if (GetListSize(*list) == 0) {
        DropList(list);
        *list = NULL;
    }
}

int PerformAction(TVList **list, int choice) {
    switch (choice) {
        case 1:
            ActionAddItem(list);
            SaveListToFile(*list, PATH);
            break;
        case 2:
            ActionRemoveItem(list);
            SaveListToFile(*list, PATH);
            break;
        case 3:
            PrintList(*list);
            break;
        case 4:
            DropList(list);
            break;
        case 5:
            LoadListFromFile(list, PATH);
            break;
        default:
            break;
    }
    return 1;
}

void Run() {
    TVList *list = NULL;
    LoadListFromFile(&list, PATH);
    int choice;
    do {
        PrintMenu();
        choice = AwaitChoice();
        PerformAction(&list, choice);
    } while (choice != 0);

    DropList(&list);
}

#endif //PROG_RGZ_C_MENU_H
