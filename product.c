#include "product.h"

int selectMenu() {
    int select;
    printf("\n*** 쇼핑몰 관리 프로그램***\n\n");
    printf("1. 상품 등록\n");
    printf("2. 상품 조회\n");
    printf("3. 상품 전체 조회\n");
    printf("4. 상품 검색\n");
    printf("5. 상품 수정\n");
    printf("6. 상품 삭제\n");
    printf("7. 상품 저장\n");
    printf("0. 종료\n");
    printf("\n원하는 메뉴를 선택하세요: ");
    scanf("%d", &select);
    getchar();
    return select;
}

int loadData(Product *p[], char fileName[]) {
    int count = 0;
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("=> 파일을 열 수 없습니다.\n");
        return count;
    }
    else {
        while(!feof(fp)) {
            p[count] = (Product *)malloc(sizeof(Product));
            int ret = fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%d\n%d\n", p[count]->name, p[count]->info, p[count]->weight, &p[count]->price, &p[count]->deliveryType);
            if(ret < 5) continue;
            count++;
        }
        printf("=> %d개의 상품이 읽어졌습니다.\n", count);
        fclose(fp);
        return count;
    }
}

int createProduct(Product *p[], int count) {
    p[count] = (Product *)malloc(sizeof(Product));

    printf("=> 상품명 : ");
    scanf("%[^\n]", p[count]->name);
    getchar();
    printf("=> 상품정보 : ");
    scanf("%[^\n]", p[count]->info);
    getchar();
    printf("=> 상품중량 : ");
    scanf("%[^\n]", p[count]->weight);
    getchar();
    printf("=> 상품가격 : ");
    scanf("%d", &p[count]->price);
    printf("=> 배송방법 (1: 새벽배송 / 2: 택배배송): ");
    scanf("%d", &p[count]->deliveryType);
    
    return count + 1;
}

int deleteProduct(Product *p[], int count) {
    listProduct(p, count);
    int index;
    printf("\n=> 삭제할 상품번호 (0: 취소): ");
    scanf("%d", &index);
    getchar();

    if(index == 0) return count;
    else if(index > count || index < 0) {
        printf("=> 삭제할 상품이 없습니다.\n");
        return count;
    }
    else {
        index--;
        for(int i = index; i < count - 1; i++) {
            p[i] = p[i + 1];
        }
        free(p[count - 1]);
        printf("=> 상품이 삭제되었습니다.\n");
        return count - 1;
    }
}

void updateProduct(Product *p[], int count) {
    listProduct(p, count);
    int index;
    printf("\n=> 수정할 상품번호 (0: 취소): ");
    scanf("%d", &index);
    getchar();

    if(index == 0) return;
    else if(index > count || index < 0) {
        printf("=> 수정할 상품이 없습니다.\n");
        return;
    }
    else {
        index--;
        printf("=> 상품명 : ");
        scanf("%[^\n]", p[index]->name);
        getchar();
        printf("=> 상품정보 : ");
        scanf("%[^\n]", p[index]->info);
        getchar();
        printf("=> 상품중량 : ");
        scanf("%[^\n]", p[index]->weight);
        getchar();
        scanf("%d", &p[index]->price);
        printf("=> 배송방법 (1: 새벽배송 / 2: 택배배송): ");
        scanf("%d", &p[index]->deliveryType);

        printf("=> 상품 정보가 수정되었습니다.\n");
    }
}

void readProduct(Product *p[], int count) {
    listProduct(p, count);
    int index;
    printf("\n=> 상품번호 (0: 취소): ");
    scanf("%d", &index);
    getchar();

    if(index == 0) return;
    else if(index > count || index < 0) {
        printf("=> 상품이 없습니다.\n");
        return;
    }
    else {
        index--;
        printf("=> 상품명 : %s\n", p[index]->name);
        printf("=> 상품정보 : %s\n", p[index]->info);
        printf("=> 상품중량 : %s\n", p[index]->weight);
        printf("=> 상품가격 : %d\n", p[index]->price);
        printf("=> 배송방법 (1: 새벽배송 / 2: 택배배송): %d\n", p[index]->deliveryType);
    }
}

void listProduct(Product *p[], int count) {
    printf("\n상품번호\t상품명\t상품정보\t상품중량\t상품가격\t배송방법\n");
    for(int i = 0; i < count; i++) {
        printf("%d\t%s\t%s\t%s\t%d\t%d\n", i + 1, p[i]->name, p[i]->info, p[i]->weight, p[i]->price, p[i]->deliveryType);
    }
}

void searchProduct(Product *p[], int count) {
    char keyword[20];
    printf("=> 검색할 상품명을 입력하세요 : ");
    scanf("%s", keyword);
    getchar();

    printf("\n=> 상품번호\t상품명\t상품정보\t상품중량\t상품가격\t배송방법\n");
    for(int i = 0; i < count; i++) {
        if(strstr(p[i]->name, keyword) != NULL) {
            printf("%d\t%s\t%s\t%s\t%d\t%d\n", i + 1, p[i]->name, p[i]->info, p[i]->weight, p[i]->price, p[i]->deliveryType);
        }
    }
}

void saveData(Product *p[], int count, char filename[]) {
    FILE *fp = fopen(filename, "w");
    if(fp == NULL) {
        printf("=> 파일 저장에 실패했습니다.\n");
        return;
    }

    for(int i = 0; i < count; i++) {
        fprintf(fp, "%s\n%s\n%s\n%d\n%d\n", p[i]->name, p[i]->info, p[i]->weight, p[i]->price, p[i]->deliveryType);
    }
    fclose(fp);
    printf("=> 파일에 저장되었습니다.\n");
}
