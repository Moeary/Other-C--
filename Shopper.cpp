#include "function.hpp"

int main(int argc, char *argv[]) { 

    Set_Font();
    Supermarket supermarket;
    string filename = "goods.txt";
    supermarket.loadFromFile(filename);
    int choice,count;
    double price;
    string goodName, expirationDate, color;
    bool flag=true;
    
    while (flag) {
        cout << "\x1B[2J\x1B[H"; 
        if(choice == -1) {
            cout << "输入有误,请重新输入" << endl;
        }
        PRINT_1();
        cin >> choice;
        if (cin.fail()) {  // 输入不是一个数字
            cin.clear();  // 清除错误状态
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 忽略无效输入
            choice = -1;  // 设置choice为-1
        }
        switch (choice) {
            case 1:
                supermarket.ShowAll();
                press_any_key_to_continue();
                break;
            case 2:
                supermarket.Replenishment();
                supermarket.saveToFile(filename);
                cout << "已将补货信息保存到文件" << endl;
                press_any_key_to_continue();
                break;
            case 3:
                supermarket.ShowMinimumQuantity();
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