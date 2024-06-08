#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BRAND_NAME_SIZE_MIN 3
#define BRAND_NAME_SIZE_MAX 30
#define MODEL_NAME_SIZE_MIN 3
#define MODEL_NAME_SIZE_MAX 30
#define COLOR_NAME_SIZE_MIN 3
#define COLOR_NAME_SIZE_MAX 15
#define SCREEN_SIZE_MIN 0

#define DEFAULT_VALUE_CHAR "none"
#define DEFAULT_VALUE_INT 0

typedef struct TV {
    char brand[BRAND_NAME_SIZE_MAX], model[MODEL_NAME_SIZE_MAX], color[COLOR_NAME_SIZE_MAX];
    int screen_size;
} TV;

char *setBrandName(char *brand) {
    if (strlen(brand) >= BRAND_NAME_SIZE_MIN && strlen(brand) <= BRAND_NAME_SIZE_MAX)
        return brand;
    return DEFAULT_VALUE_CHAR;
}

char *setModelName(char *model) {
    if (strlen(model) >= MODEL_NAME_SIZE_MIN && strlen(model) <= MODEL_NAME_SIZE_MAX)
        return model;
    return DEFAULT_VALUE_CHAR;
}

char *setColor(char *color) {
    if (strlen(color) >= COLOR_NAME_SIZE_MIN && strlen(color) <= COLOR_NAME_SIZE_MAX)
        return color;
    return DEFAULT_VALUE_CHAR;
}

int setScreenSize(int screen_size) {
    if (screen_size >= SCREEN_SIZE_MIN && screen_size <= INT32_MAX)
        return screen_size;
    return DEFAULT_VALUE_INT;
}

void InitTV(TV *tv, char *brand, char *model, char *color, int screen_size) {
    strncpy(tv->brand, setBrandName(brand), BRAND_NAME_SIZE_MAX);
    strncpy(tv->model, setModelName(model), MODEL_NAME_SIZE_MAX);
    strncpy(tv->color, setColor(color), COLOR_NAME_SIZE_MAX);
    tv->screen_size = setScreenSize(screen_size);
}

TV *Init(char *brand, char *model, char *color, int screen_size) {
    TV *newTV = (TV *) malloc(sizeof(TV));
    InitTV(newTV, brand, model, color, screen_size);
    return newTV;
}

int isTVsEquals(TV *tv_1, TV *tv_2) {
    if (strcmp(tv_1->brand, tv_2->brand) != 0)
        return 0;
    if (strcmp(tv_1->model, tv_2->model) != 0)
        return 0;
    if (strcmp(tv_1->color, tv_2->color) != 0)
        return 0;
    return 1;
}

int isTVSmaller(TV *tv_1, TV *tv_2) {
    int tv_1_points = 0;
    int tv_2_points = 0;
    if (strlen(tv_1->brand) <= strlen(tv_2->brand))
        tv_1_points++;
    else tv_2_points++;
    if (strlen(tv_1->model) <= strlen(tv_2->model))
        tv_1_points++;
    else tv_2_points++;
    if (strlen(tv_1->color) <= strlen(tv_2->color))
        tv_1_points++;
    else tv_2_points++;
    if (tv_1->screen_size <= tv_2->screen_size)
        tv_1_points++;
    else tv_2_points++;

    if (tv_1_points > tv_2_points) {
        return 1;
    }
    return 0;
}

void printData(TV *tv) {
    printf("\n———— TV data ————");
    printf("\nBrand: %s", tv->brand);
    printf("\nModel: %s", tv->model);
    printf("\nColor: %s", tv->color);
    printf("\nScreen Size: %d", tv->screen_size);
}
