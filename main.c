#include "manager.h"

int main() {
    #ifdef DEBUG
    printf("=> DEBUG MODE\n\n");
    #endif

    Product *p[100];
    int count = loadData(p, "product.txt");
    while(1) {
        int select = selectMenu();
        switch(select) {
            case 1:
                count = createProduct(p, count);
		break;
            case 2:
                readProduct(p, count);
                break;
            case 3:
                listProduct(p, count);
                break;
            case 4:
                searchProduct(p, count);
                break;
            case 5:
                updateProduct(p, count);
                break;
            case 6:
                count = deleteProduct(p, count);
                break;
            case 7:
                saveData(p, count, "product.txt");
                break;
            case 0:
                for(int i = 0; i < count; i++) free(p[i]);
                printf("=> 종료합니다.\n");
                return 0;
        }
    }
    return 0;
}
