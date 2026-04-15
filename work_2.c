#include <stdio.h>
#include <stdlib.h> 
#include <windows.h>

int main() {
    //음료명, 가격, 재고
    char* drink_name[] = { "커피", "우유", "콜라" };
    int drink_price[] = { 1500, 1000, 500 };
    int stock[] = { 10, 10, 10 }; //각 음료 초기 재고 10개

    int total_balance = 0; //투입된 총 금액

    while (1) {
        int drink_quantity[3] = { 0 };
        int selected_drink = 0;
        int current_order_total = 0;

        system("cls"); //화면 초기화
        printf("\n==========================================\n");
        printf("          [ 최종 자판기 시스템 ]          \n");
        printf("==========================================\n");
        for (int i = 0; i < 3; i++) {
            printf(" [%d] %-6s : %4d원 (재고: %2d개)\n", i + 1, drink_name[i], drink_price[i], stock[i]);
        }
        printf(" [0] 주문 완료  \n");
        printf("==========================================\n");

        //금액 투입
        if (total_balance == 0) {
            printf(">> 금액을 투입해 주세요 : ");
            scanf_s("%d", &total_balance);
        }
        printf(">> 현재 잔액 : %d원\n", total_balance);

        //주문 루프
        while (1) {
            printf("\n>> 음료 번호 선택 : ");
            scanf_s("%d", &selected_drink);

            if (selected_drink == -1) {
                printf("시스템을 종료합니다...\n");
                return 0;
            }
            if (selected_drink == 0) break;

            if (selected_drink >= 1 && selected_drink <= 3) {
                int idx = selected_drink - 1;
                int qty = 0;

                if (stock[idx] <= 0) {
                    printf("! [%s] 제품은 품절되었습니다.\n", drink_name[idx]);
                    continue;
                }

                printf("[%s] 몇 개를 주문하시겠습니까? (잔여:%d) : ", drink_name[idx], stock[idx]);
                scanf_s("%d", &qty);

                //재고 부족 및 음수 입력 방지
                if (qty <= 0) {
                    printf("! 1개 이상의 올바른 수량을 입력하세요.\n");
                }
                else if (qty > stock[idx]) {
                    printf("! 재고가 부족합니다. (최대 %d개 가능)\n", stock[idx]);
                }
                else {
                    drink_quantity[idx] += qty;
                    stock[idx] -= qty; 
                    printf("=> 장바구니에 담겼습니다.\n");
                }
            }
            else {
                printf("! 잘못된 번호입니다.\n");
            }
        }

        //결제 및 영수증
        system("cls");
        printf("\n==========================================\n");
        printf("            주문 영수증 (Receipt)         \n");
        printf("==========================================\n");

        for (int i = 0; i < 3; i++) {
            if (drink_quantity[i] > 0) {
                int sub_total = drink_price[i] * drink_quantity[i];
                printf("%-10s | %5d원 | %2d개 | : %7d원\n", drink_name[i], drink_price[i], drink_quantity[i], sub_total);
                current_order_total += sub_total;
            }
        }

        printf("------------------------------------------\n");
        printf("  총 결제 금액 : %20d원\n", current_order_total);

        if (total_balance >= current_order_total) {
            total_balance -= current_order_total;
            printf("  남은 잔액    : %20d원\n", total_balance);
            printf("==========================================\n");
            printf("\n구매완료! 잔돈 %d원이 반환됩니다.\n", total_balance);
            total_balance = 0; //잔액 반환
        }
        else {
            printf("! 잔액이 부족합니다. 주문이 취소됩니다.\n");
            
        }

        printf("\n3초 후 메뉴판으로 돌아갑니다...");
        Sleep(3000); //3초 대기
    }

    return 0;
}
