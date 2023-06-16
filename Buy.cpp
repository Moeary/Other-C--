#include "function.hpp"
#include "snake.hpp"
int main(int argc, char *argv[]) { 

    Set_Font();
    int choice;
    bool flag=true;
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(1000, 2000);
    double money=dis(gen);
    vector<Goods*> purchasedGoods;
    snake s;
    
    while (flag) {
        cout << "\x1B[2J\x1B[H"; 
        if(choice == -1) {
            cout << "输入有误,请重新输入" << endl;
        }
        PRINT_2();
        cout<<"当前余额"<<money<<endl;
        cin >> choice;
        if (cin.fail()) {  // 输入不是一个数字
            cin.clear();  // 清除错误状态
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 忽略无效输入
            choice = -1;  // 设置choice为-1
        }
        switch (choice) {
            case 1:
                goto_supermarket(money,purchasedGoods);
                press_any_key_to_continue();
                break;
            case 2:
                s.move();
                money+=s.money();
                press_any_key_to_continue();
                break;
            case 3:
                showPurchasedGoods(purchasedGoods);
                press_any_key_to_continue();
                break;
            case 4:
                cout << "程序已退出" << endl;
                flag=false;
                return 0;
            default:
                break;
            }
    }
    return 0;
}