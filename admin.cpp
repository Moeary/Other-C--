#include "function.hpp"
/*
 * 
 * 　　┏┓　　　┏┓+ +
 * 　┏┛┻━━━┛┻┓ + +
 * 　┃　　　　　　　┃ 　
 * 　┃　　　━　　　┃ ++ + + +
 *  ████━████ ┃+
 * 　┃　　　　　　　┃ +
 * 　┃　　　┻　　　┃
 * 　┃　　　　　　　┃ + +
 * 　┗━┓　　　┏━┛
 * 　　　┃　　　┃　　　　　　　　　　　
 * 　　　┃　　　┃ + + + +
 * 　　　┃　　　┃
 * 　　　┃　　　┃ +  神兽保佑
 * 　　　┃　　　┃    代码无bug　　
 * 　　　┃　　　┃　　+　　　　　　　　　
 * 　　　┃　 　　┗━━━┓ + +
 * 　　　┃ 　　　　　　　┣┓
 * 　　　┃ 　　　　　　　┏┛
 * 　　　┗┓┓┏━┳┓┏┛ + + + +
 * 　　　　┃┫┫　┃┫┫
 * 　　　　┗┻┛　┗┻┛+ + + +
 * 
 */

int main(int argc, char *argv[]) { 
    Set_Font();
    Supermarket supermarket;
    string filename = "goods.txt";
    supermarket.loadFromFile(filename);
    cout << "已从文件中加载商品信息" << endl;
    int choice,count;
    double price;
    string goodName, expirationDate, color;
    bool flag=true;
    
    while (flag) {
        cout << "\x1B[2J\x1B[H"; 
        if(choice == -1) {
            cout << "输入有误,请重新输入" << endl;
        }
        PRINT();
        
        cin >> choice;
        if (cin.fail()) {  // 输入不是一个数字
            cin.clear();  // 清除错误状态
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 忽略无效输入
            choice = -1;  // 设置choice为-1
        }
        switch (choice) {
        case 1:
            addGoods(goodName,count,price,choice ,expirationDate,color);
            supermarket.Add(goodName, count,price, choice, expirationDate, color);
            supermarket.saveToFile(filename);
            cout << "已将商品信息保存到文件" << endl;
            press_any_key_to_continue();
            break;
        case 2:
            cout << "请输入商品名称和数量:" << endl;
            cin >> goodName >> count;
            supermarket.Sale(goodName, count);
            supermarket.saveToFile(filename);
            cout << "已将商品信息保存到文件" << endl;
            press_any_key_to_continue();
            break;
        case 3:
            cout << "请输入要查询的商品名称" << endl;
            supermarket.Search();
            press_any_key_to_continue();
            break;
        case 4:
            cout << "请输入你要删除的商品名:" << endl;
            cin >> goodName;
            supermarket.Delete(goodName);
            supermarket.saveToFile(filename);
            cout << "已将修改信息保存到文件" << endl;
            press_any_key_to_continue();
            break;

        case 5:
            cout << "请输入你要修改信息的商品名:" << endl;
            cin >> goodName;
            supermarket.Update(goodName);
            supermarket.saveToFile(filename);
            cout << "已将修改信息保存到文件" << endl;
            press_any_key_to_continue();
            break;

        case 6:
            cout << "程序已退出" << endl;
            flag=false;
            return 0;
        default:
            break;
        }
    }
    return 0;
}