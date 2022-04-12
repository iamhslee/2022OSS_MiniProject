#include "manager.h"

char dType[2][20] = {"새벽배송", "택배배송"};

int selectMenu() {
    #ifdef DEBUG
    printf("=> DEBUG: Function > selectMenu() Called\n");
    #endif
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
    #ifdef DEBUG
    printf("=> DEBUG: selectMenu() > Selection = %d\n", select);
    #endif
    return select;
}

int loadData(Product *p[], char fileName[]) {
    #ifdef DEBUG
    printf("=> DEBUG: Function > loadData() Called\n");
    #endif
    int count = 0;
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        #ifdef DEBUG
        printf("=> DEBUG: Function > loadData() > File \"%s\": Open Error\n", fileName);
        #endif
        printf("=> 파일을 열 수 없습니다.\n");
        return count;
    }
    else {
        #ifdef DEBUG
        printf("=> DEBUG: Function > loadData() > File \"%s\": Opened\n", fileName);
        #endif
        while(!feof(fp)) {
            p[count] = (Product *)malloc(sizeof(Product));
            int ret = fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%d\n%d\n", p[count]->name, p[count]->info, p[count]->weight, &p[count]->price, &p[count]->deliveryType);
            #ifdef DEBUG
            printf("=> DEBUG: Function > loadData() > Batch: %d\n", count + 1);
            
            #endif
	        if(ret < 5) {
                #ifdef DEBUG
                printf("=> DEBUG: Function > loadData() > Batch: %d\n not loaded properly. Skip...", count + 1);
                printf("=> DEBUG: Function > loadData() > Format count: %d\n", ret);
                #endif
                continue;
            }
            else {
                #ifdef DEBUG
                printf("=> DEBUG: Function > loadData() > Batch: %d\n loaded properly.\n", count + 1);
                printf("=> DEBUG: Function > loadData() > Raw Data: %s / %s / %s / %d / %d\n", p[count]->name, p[count]->info, p[count]->weight, p[count]->price, p[count]->deliveryType);
                printf("=> DEBUG: Function > loadData() > Format count: %d\n", ret);
                #endif
                count++;
            }
        }
        #ifdef DEBUG
        printf("=> DEBUG: Function > loadData() > Loaded Data: %d\n", count);
        #endif
        printf("=> %d개의 상품이 읽어졌습니다.\n", count);
        fclose(fp);
        return count;
    }
}

int createProduct(Product *p[], int count) {
    #ifdef DEBUG
    printf("=> DEBUG: Function > createProduct() Called\n");
    #endif
    p[count] = (Product *)malloc(sizeof(Product));
    #ifdef DEBUG
    printf("=> DEBUG: Function > createProduct() > Memory Allocated\n");
    #endif

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
    #ifdef DEBUG
    printf("=> DEBUG: Function > deleteProduct() Called\n");
    #endif
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
        #ifdef DEBUG
        printf("=> DEBUG: Function > deleteProduct() > Index: %d\n", index);
        #endif
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
    #ifdef DEBUG
    printf("=> DEBUG: Function > updateProduct() Called\n");
    #endif
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
        #ifdef DEBUG
        printf("=> DEBUG: Function > updateProduct() > Index: %d\n", index);
        #endif
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
    #ifdef DEBUG
    printf("=> DEBUG: Function > readProduct() Called\n");
    #endif
    listProduct(p, count);
    int index;
    printf("\n=> 상품번호 (0: 취소): ");
    scanf("%d", &index);
    getchar();

    if(index == 0) return;
    else if(index > count || index < 0) {
        printf("=> 입력한 상품이 없습니다.\n");
        return;
    }
    else {
        index--;
        #ifdef DEBUG
        printf("=> DEBUG: Function > readProduct() > Index: %d\n", index);
        #endif
        printf("=> 번호 %d : %10s ===============\n", index + 1, p[index]->name);
        printf("상품정보 : %s\n", p[index]->info);
        printf("상품중량 : %s\n", p[index]->weight);
        printf("상품가격 : %d\n", p[index]->price);
        printf("배송방법 (1: 새벽배송 / 2: 택배배송): %d\n", p[index]->deliveryType);
    }
}

void listProduct(Product *p[], int count) {
    #ifdef DEBUG
    printf("=> DEBUG: Function > listProduct() Called\n");
    printf("=> DEBUG: Function > listProduct() > Count: %d\n", count);
    #endif
    if(count == 0) {
        printf("\n=> 등록된 상품이 없습니다.\n");
        return;
    }
    printf("=> 상품 목록 ========================================\n");
    printf("번호 상품명              상품중량   상품가격 배송방법\n");
    printf("-----------------------------------------------------\n");
    for(int i = 0; i < count; i++) {
        printf("%4d %-s %-s %-d %-s\n", i + 1, p[i]->name, p[i]->weight, p[i]->price, dType[p[i]->deliveryType - 1]);
    }
    printf("=====================================================\n");
}

void searchProduct(Product *p[], int count) {
    #ifdef DEBUG
    printf("=> DEBUG: Function > searchProduct() Called\n");
    #endif
    char keyword[20];
    if(count == 0) {
        printf("\n=> 등록된 상품이 없습니다.\n");
        return;
    }
    printf("=> 검색할 상품명을 입력하세요 : ");
    scanf("%s", keyword);
    getchar();

    printf("=> 검색 목록 ========================================\n");
    printf("번호 상품명              상품중량   상품가격 배송방법\n");
    printf("-----------------------------------------------------\n");
    int flag = 0;
    for(int i = 0; i < count; i++) {
        if(strstr(p[i]->name, keyword) != NULL) {
            #ifdef DEBUG
            printf("=> DEBUG: Function > searchProduct() > Keyword: %s , Index: %d\n", keyword, i);
            #endif
            printf("%4d %-s %-s %-d %-s\n", i + 1, p[i]->name, p[i]->weight, p[i]->price, dType[p[i]->deliveryType - 1]);
            flag = 1;
        }
    }
    if(flag == 0) printf("\n=> 검색 결과가 없습니다.\n\n");
    printf("=====================================================\n");
}

void saveData(Product *p[], int count, char filename[]) {
    #ifdef DEBUG
    printf("=> DEBUG: Function > saveData() Called\n");
    #endif
    FILE *fp = fopen(filename, "w");
    if(fp == NULL) {
        #ifdef DEBUG
        printf("=> DEBUG: Function > saveData() > File \"%s\": Open Error\n", filename);
        #endif
        printf("=> 상품 데이터 저장에 실패했습니다.\n");
        return;
    }

    #ifdef DEBUG
    printf("=> DEBUG: Function > saveData() > File \"%s\": Opened\n", filename);
    #endif
    for(int i = 0; i < count; i++) {
        fprintf(fp, "%s\n%s\n%s\n%d\n%d\n", p[i]->name, p[i]->info, p[i]->weight, p[i]->price, p[i]->deliveryType);
    }
    fclose(fp);
    #ifdef DEBUG
    printf("=> DEBUG: Function > saveData() > File \"%s\": Closed\n", filename);
    #endif
    printf("=> 상품 데이터가 저장되었습니다.\n");
}