#ifndef MANAGER_H
#define MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    char info[100];
    char weight[10];
    int price;
    int deliveryType;
} Product;

int selectMenu();
int loadData(Product *p[], char filename[]);
int createProduct(Product *p[], int size);
int deleteProduct(Product *p[], int count);
void updateProduct(Product *p[], int count);
void readProduct(Product *p[], int count);
void listProduct(Product *p[], int count);
void searchProduct(Product *p[], int count);
void saveData(Product *p[], int count, char filename[]);

#endif