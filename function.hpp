#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <codecvt>
#include <locale>
#include <limits>
#include <queue>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <Windows.h>
using namespace std;

// 商品类
class Goods {
public:
    string name;  // 商品名称
    int count;    // 商品数量
    double price; //商品价格
    virtual void ShowMe() = 0;  // 显示商品信息(虚函数）
    string GetGoodName() { return name; } // 获取商品名称
    void IncreaseQuantity(int quantityToAdd){
        count += quantityToAdd;
    }
    void SetGoodsQuantity(int quantity){ count = quantity; } // 设置商品数量
    int GetGoodsQuantity(){return count;}
    double GetPrice(){return price;} // 获取商品价格
    void Show_1(){
        cout<<name<< "\t" <<count<<endl;
    }
    Goods(const string& goodName, int quantity, double price)
        : name(goodName), count(quantity), price(price) {
    }

    // 拷贝构造函数
    Goods(const Goods& other) {
        name = other.name;
        count = other.count;
        price = other.price;
    }
    virtual string gettype()=0;
};

// 日常用品类
class DailyGoods : public Goods {
public:
    DailyGoods(const string& goodName, int quantity, double price)
        : Goods(goodName, quantity, price) {
    }
    DailyGoods(const DailyGoods& other)
        : Goods(other) {
        // DailyGoods的特殊成员和函数的拷贝
    }
    void ShowMe() {
        cout <<"普通用品 "<<"\t"<< name<<"\t\t"<< count <<"\t\t"<<price<< endl;
    }
    string gettype(){
        return "DailyGoods";
    }
};

// 食品类
class Food : public Goods {
public:
    string expirationDate;  // 商品保质期
    Food(const string& goodName, int quantity, double price,string exp)
        : Goods(goodName, quantity, price),expirationDate(exp) {
    }
    Food(const Food& other)
        : Goods(other) {
        // Food的特殊成员和函数的拷贝
        expirationDate = other.expirationDate;
    }
    void ShowMe() {
        cout <<"食品 "<<"\t\t" <<name<<"\t\t"<< count<<"\t\t" <<price<<"\t\t"<< expirationDate <<"\t"<< endl;
    }
    string gettype(){
        return "Food";
    }
};

// 家电类
class ElectricalAppliance : public Goods {
public:
    string color;  // 商品颜色
    ElectricalAppliance(const string& goodName, int quantity, double price,string color)
        : Goods(goodName, quantity, price),color(color) {
    }
    ElectricalAppliance(const ElectricalAppliance& other)
        : Goods(other) {
        // ElectricalAppliance的特殊成员和函数的拷贝
        color = other.color;
    }
    void ShowMe() {
        cout <<"家电"<<"\t\t"<< name<<"\t\t"<< count<<"\t\t" <<price<<"\t\t"<< color <<"\t"<< endl;
    }
    string gettype(){
        return "ElectricalAppliance";
    }
};

// 超市类
class Supermarket {
private:
    vector<Goods*> goodsList;  // 所有商品列表
public:
    // 增加商品
    void Add(string name, int count, double price, int type, string expirationDate = "", string color = "") {
        
        Goods* goods = nullptr;
        if (type == 1) {  // 日常用品
            goods = new DailyGoods(name, count, price);
        }
        else if (type == 2) {  // 食品
            goods = new Food(name, count, price, expirationDate);
        }
        else if (type == 3) {  // 家电
            goods = new ElectricalAppliance(name, count, price, color);
        }
        // 查找是否已有该商品
        bool found = false;
        for (int i = 0; i < goodsList.size(); i++) {
            if (goodsList[i]->name == goods->name) {
                goodsList[i]->count += goods->count;
                found = true;
                break;
            }
        }
        if (!found) {
            goodsList.push_back(goods);
        }
        //goods->ShowMe();
    }
    // 卖出商品
    void Sale(string name, int count) {
        // 查找是否有该商品
        bool found = false;
        for (int i = 0; i < goodsList.size(); i++) {
            if (goodsList[i]->name == name) {
                if (goodsList[i]->count < count) {
                    cout << "当前库存不足" << endl;
                }
                else {
                    goodsList[i]->count -= count;
                }
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "没有找到该商品" << endl;
        }
    }
    // 查询商品
    void Search() {
        string goodName;
        cin>>goodName;
        cout << "----- 查询结果 -----" << endl;
        bool found = false;
        for (int i = 0; i < goodsList.size(); i++) {
            if (goodsList[i]->GetGoodName() == goodName) {
                goodsList[i]->ShowMe();
                found = true;
            }
        }
        if (!found) {
            cout << "未找到该商品" << endl;
        }
    }
    void Replenishment() {
        cout<<"请输入你要补货的商品名称";
        string goodName;
        cin >> goodName;

        cout << "----- 查询结果 -----" << endl;
        bool found = false;
        for (int i = 0; i < goodsList.size(); i++) {
            if (goodsList[i]->GetGoodName() == goodName) {
                goodsList[i]->ShowMe();
                found = true;

                cout << "请输入要增加的货物数量: ";
                int quantityToAdd;
                cin >> quantityToAdd;

                // 增加货物数量
                goodsList[i]->IncreaseQuantity(quantityToAdd);
                cout << "货物数量已增加。" << endl;
            }
        }

        if (!found) {
            cout << "未找到该商品" << endl;
        }
    }
    void ShowAll() {
        cout << "\x1B[2J\x1B[H"; 
        cout << "--------------------------------------------------------------- 所有商品信息 ---------------------------------------------------------------" << endl;
        cout << "类别\t\t商品名称\t商品数量\t商品价格\t保质期/颜色" << endl;
        
        for (int i = 0; i < goodsList.size(); i++) {
            goodsList[i]->ShowMe();
        }
    }
    void shopping(double& money, vector<Goods*>& purchasedGoods) {
        string goodsName;
        int quantity;

        cout << "请输入要购买的商品名称：" << endl;
        cin >> goodsName;

        // 遍历购买记录，查找之前是否购买过该商品
        for (int i = 0; i < purchasedGoods.size(); i++) {
            if (purchasedGoods[i]->GetGoodName() == goodsName) {
                cout << "请输入要购买的数量：" << endl;
                cin >> quantity;

                // 检查库存是否足够
                if (quantity > goodsList[i]->GetGoodsQuantity()) {
                    cout << "库存不足。" << endl;
                    return;
                }

                // 计算购买后的总价
                float totalPrice = quantity * goodsList[i]->GetPrice();

                // 检查金额是否足够支付
                if (totalPrice > money) {
                    cout << "购买失败，金额不足。" << endl;
                    return;
                }

                cout << "购买成功！总价为：" << totalPrice << "元。" << endl;

                // 更新库存
                goodsList[i]->SetGoodsQuantity(goodsList[i]->GetGoodsQuantity() - quantity);

                // 扣款处理
                money -= totalPrice;

                // 增加购买数量
                purchasedGoods[i]->IncreaseQuantity(quantity);

                return;
            }
        }

        // 如果之前未购买过该商品，则添加到购买记录中
        for (int i = 0; i < goodsList.size(); i++) {
            if (goodsList[i]->GetGoodName() == goodsName) {
                cout << "请输入要购买的数量：" << endl;
                cin >> quantity;

                // 检查库存是否足够
                if (quantity > goodsList[i]->GetGoodsQuantity()) {
                    cout << "库存不足。" << endl;
                    return;
                }

                // 计算购买后的总价
                float totalPrice = quantity * goodsList[i]->GetPrice();

                // 检查金额是否足够支付
                if (totalPrice > money) {
                    cout << "购买失败，金额不足。" << endl;
                    return;
                }

                cout << "购买成功！总价为：" << totalPrice << "元。" << endl;

                // 更新库存
                goodsList[i]->SetGoodsQuantity(goodsList[i]->GetGoodsQuantity() - quantity);

                // 扣款处理
                money -= totalPrice;

                // 创建新的派生类对象并将其添加到 purchasedGoods 中
                if (goodsList[i]->gettype() == "DailyGoods") {
                    purchasedGoods.push_back(new DailyGoods(*dynamic_cast<DailyGoods*>(goodsList[i])));
                } else if (goodsList[i]->gettype() == "ElectricalAppliance") {
                    purchasedGoods.push_back(new ElectricalAppliance(*dynamic_cast<ElectricalAppliance*>(goodsList[i])));
                } else if (goodsList[i]->gettype() == "Food") {
                    purchasedGoods.push_back(new Food(*dynamic_cast<Food*>(goodsList[i])));
                } else {
                    cout << "错误：未知的派生类类型。" << endl;
                    return;
                }

                // 更新购买数量
                purchasedGoods.back()->SetGoodsQuantity(quantity);

                return;
            }
        }

        cout << "未找到该商品，请重新输入。" << endl;
    }


    void ShowMinimumQuantity() {
        if (goodsList.empty()) {
            cout << "当前没有商品" << endl;
            return;
        }

        priority_queue<int, vector<int>, greater<int>> minHeap;
        unordered_set<string> printedGoods;  // 用于记录已经输出的商品名称

        // 构建最小堆
        for (int i = 0; i < goodsList.size(); i++) {
            int quantity = goodsList[i]->GetGoodsQuantity();

            if (minHeap.size() < 10) {
                minHeap.push(quantity);
            } else {
                if (quantity < minHeap.top()) {
                    minHeap.pop();
                    minHeap.push(quantity);
                }
            }
        }

        cout << "当前商品数量最少的十个商品列表：" << endl;
        for (int i = 0; i < goodsList.size(); i++) {
            int minQuantity = minHeap.top();
            minHeap.pop();

            for (int j = 0; j < goodsList.size(); j++) {
                if (goodsList[j]->GetGoodsQuantity() == minQuantity &&
                    printedGoods.find(goodsList[j]->GetGoodName()) == printedGoods.end()) {
                    goodsList[j]->ShowMe();
                    printedGoods.insert(goodsList[j]->GetGoodName());
                    break;  // 输出了一个商品后跳出内层循环
                }
            }

            if (minHeap.empty()) {
                break;
            }
        }
    }
    void loadFromFile(string filename) {
        ifstream ifs(filename);
        if (!ifs.is_open()) {  // 如果文件不存在,则默认为空
            cout << "文件不存在,将创建一个新文件" << endl;
            return;
        }
        int type;
        string name;
        int count;
        double price;
        string expirationDate;
        string color;

        string line;


        while (getline(ifs, line)) {
            //ifs.ignore();  // 忽略掉空格和换行符
            //getline(ifs, name);
            istringstream iss(line);
            iss >> type;
            iss >> name;
            iss >> count;
            iss >> price;
            if (type == 2) {
                iss >> expirationDate;
                Add(name, count, price, type, expirationDate);
            }
            else if (type == 3) {
                iss >> color;
                Add(name, count, price, type, "", color);
            }
            else {
                Add(name, count, price, type);
            }
        }
        ifs.close();
    }

    // 将商品信息保存到文件中
    void saveToFile(string filename) {
        ofstream ofs(filename);
        for (int i = 0; i < goodsList.size(); i++) {
            //
            if (dynamic_cast<DailyGoods*>(goodsList[i]) != nullptr) {
                ofs << "1 " << goodsList[i]->name << " ";
                ofs << goodsList[i]->count << " ";
                ofs << goodsList[i]->price << endl;
            }
            else if (dynamic_cast<Food*>(goodsList[i]) != nullptr) {
                ofs << "2 " << goodsList[i]->name << " ";
                ofs << goodsList[i]->count << " ";
                ofs << goodsList[i]->price << " ";
                ofs << dynamic_cast<Food*>(goodsList[i])->expirationDate << endl;
            }
            else if (dynamic_cast<ElectricalAppliance*>(goodsList[i]) != nullptr) {
                ofs << "3 " << goodsList[i]->name << " ";
                ofs << goodsList[i]->count << " ";
                ofs << goodsList[i]->price << " ";
                ofs << dynamic_cast<ElectricalAppliance*>(goodsList[i])->color << endl;
            }
        }
        ofs.close();
    }


    void Delete(string goodName) {
        bool exist = false;
        for (int i = 0; i < goodsList.size(); i++)
        {
            if (goodsList[i]->name == goodName) {
                exist = true;
                auto it = goodsList.begin() + i;
                goodsList.erase(it);
                break;
            }
        }
        if (exist == true) {
            cout << "成功删除：" << goodName << endl;
        }
        else {
            cout << "未找到对应的商品，删除失败" << endl;
        }
    }


    void Update(string goodName) {
        bool exist = false;
        int i;
        for (i = 0; i < goodsList.size(); i++)
        {
            if (goodsList[i]->name == goodName) {
                exist = true;
                break;
            }
        }
        if (exist == true) {
            Goods* good = goodsList[i];
            cout << "商品信息为：" << endl;
            good->ShowMe();
            if (dynamic_cast<DailyGoods*>(good) != nullptr) {
                cout << "请输入商品名称、数量、价格" << endl;
                cin >> good->name >> good->count >> good->price;
            }
            else if (dynamic_cast<ElectricalAppliance*>(good) != nullptr) {
                cout << "请输入商品名称、数量、价格、颜色" << endl;
                cin >> good->name >> good->count >> good->price;
                cin>>dynamic_cast<ElectricalAppliance*>(good)->color;
            }
            else if(dynamic_cast<Food*>(good) != nullptr){
                cout << "请输入商品名称、数量、价格、保质期" << endl;
                cin >> good->name >> good->count >> good->price;
                cin >> dynamic_cast<Food*>(good)->expirationDate;
            }
        }
        else {
            cout << "未找到对应的商品，修改失败" << endl;
        }
    }
    void displayByGoodsType() {
        int type;
        cout << "请选择要查看的商品类型：" << endl;
        cout << "1. 普通用品" << endl;
        cout << "2. 食品类" << endl;
        cout << "3. 家电" << endl;
        cin >> type;

        switch (type) {
            case 1:
                for (int i = 0; i < goodsList.size(); i++) {
                    if (dynamic_cast<DailyGoods*>(goodsList[i]) != nullptr) {
                        goodsList[i]->ShowMe();
                    }
                }
                break;
            case 2:
                for (int i = 0; i < goodsList.size(); i++) {
                    if (dynamic_cast<Food*>(goodsList[i]) != nullptr) {
                        goodsList[i]->ShowMe();
                    }
                }
                break;
            case 3:
                for (int i = 0; i < goodsList.size(); i++) {
                    if (dynamic_cast<ElectricalAppliance*>(goodsList[i]) != nullptr) {
                        goodsList[i]->ShowMe();
                    }
                }
                break;
            default:
                cout << "输入有误，请重新输入" << endl;
                break;
        }
    }
};
void addGoods(string &name,int &count,double &price,int &type ,string &expirationDate,string &color){
    cout << "请输入商品名称、数量、价格和类型(1:日常用品,2:食品,3:家电):" << endl;
    cin >> name >> count >>price>> type;
    if (type == 2) {
        cout << "请输入保质期:" << endl;
        cin >> expirationDate;
    }
    else if (type == 3) {
        cout << "请输入颜色:" << endl;
        cin >> color;
    }
    cout<<name<<" "<<count <<" "<<price << " " << type << " " << expirationDate << " "<<endl; 
}
void login(string username ,string password);
void clear(){
    cout << "\x1B[2J\x1B[H"; 
}
void PRINT(){
    /*
        "                                         **                                                                                          ****\n"
        "          *                                ***                                                     *                                 *  *  **\n"
        "          ***    ***                       ****    ***                   ********                  **                            *   *  *****\n"
        "          ***      **                      *************          *    ***     **                   *                          ******   ****\n"
        "          ***      **                      *************          *    ***     **                   *                          ******   ****\n"
        "          ****   ***                *******      *                 ****  ***   **                  **                          *** ** *****\n"
        "      *******   *******           ******   ***                     **********  **                *******                      ****   ****    **\n"
        "       ******   *** ***           ***       ***                    *** ***** ***              *********    *******          *****    *  ********\n"
        "         **  ***   **                   *   ******                   *   *** ***             ********     ****   ***       *******\n"
        "         **  ***   **                   *   ******                   *   *** ***             ********     ****   ***       *******\n"
        "         *****  ***                     *******  **                  * ********                    **  ***     *****           ***    *****\n"
        "      *******   *  *****                *** ***  **                   ******                       ****   **** ***             *** ***   **\n"
        "   ****  ****   **** ***                *** ***  **                      *** **                  ****     **** ***             **  ***** **\n"
        "   ****  ****   **** ***                *** ***  **                      *** **                  ****     **** ***             **  ***** **\n"
        "****   *******  *** ***                **   ***  **                   **********              *******      **  ***                 ** ** **\n"
        " **    ** ***   *******                **   ** ****                   ******                 ****  **   **********                 ** ** **\n"
        "         **                                 ** ****                      ***   **            ***   **   **********                 ***** **\n"
        "      **************                        **   *                     ************                **                              ***   **\n"
        "      **************                        **   *                     ************                **                              ***   **\n"
        "                *************               **                    ********      ***              ****                              ***  ****\n"
        "                    ***                     **                     ***                             **                             ***    ***\n"
    */
    cout <<"\t\t\t\t\t\t\t\t请选择功能:\n"
        "----------------------------------------------------------------------------------------------------------------------------------------------\n" 
        "                                             (1) 增加商品\t\t\t(2) 卖出商品\n"
        "                                             \n"
        "                                             (3) 查询商品\t\t\t(4) 删除商品\n"
        "                                             \n"
        "                                             (5) 修改商品\t\t\t(6) 退出程序\n"
        "----------------------------------------------------------------------------------------------------------------------------------------------\n";
}
void PRINT_1(){
    cout <<"\t\t\t\t\t\t\t\t请选择功能:\n"
        "----------------------------------------------------------------------------------------------------------------------------------------------\n" 
        "                                             (1) 查看全部货物状态     \t\t\t(2)给货物上架(增加商品数量)        \n"
        "                                             \n"
        "                                             (3) 查看余量最少的几个货物\t\t\t(4) 退出\n"
        "----------------------------------------------------------------------------------------------------------------------------------------------\n";
}
void PRINT_2(){
    cout <<"\t\t\t\t\t\t\t\t请选择功能:\n"
        "----------------------------------------------------------------------------------------------------------------------------------------------\n" 
        "                                             (1) 去超市     \t\t\t(2) 去打工        \n"
        "                                             \n"
        "                                             (3) 背包\t\t\t(4) 退出地球Online\n"
        "----------------------------------------------------------------------------------------------------------------------------------------------\n";
}
void PRINT_3(){
    
    cout<<"                                         **                                                                                          ****\n"
        "          *                                ***                                                     *                                 *  *  **\n"
        "          ***    ***                       ****    ***                   ********                  **                            *   *  *****\n"
        "          ***      **                      *************          *    ***     **                   *                          ******   ****\n"
        "          ***      **                      *************          *    ***     **                   *                          ******   ****\n"
        "          ****   ***                *******      *                 ****  ***   **                  **                          *** ** *****\n"
        "      *******   *******           ******   ***                     **********  **                *******                      ****   ****    **\n"
        "       ******   *** ***           ***       ***                    *** ***** ***              *********    *******          *****    *  ********\n"
        "         **  ***   **                   *   ******                   *   *** ***             ********     ****   ***       *******\n"
        "         **  ***   **                   *   ******                   *   *** ***             ********     ****   ***       *******\n"
        "         *****  ***                     *******  **                  * ********                    **  ***     *****           ***    *****\n"
        "      *******   *  *****                *** ***  **                   ******                       ****   **** ***             *** ***   **\n"
        "   ****  ****   **** ***                *** ***  **                      *** **                  ****     **** ***             **  ***** **\n"
        "   ****  ****   **** ***                *** ***  **                      *** **                  ****     **** ***             **  ***** **\n"
        "****   *******  *** ***                **   ***  **                   **********              *******      **  ***                 ** ** **\n"
        " **    ** ***   *******                **   ** ****                   ******                 ****  **   **********                 ** ** **\n"
        "         **                                 ** ****                      ***   **            ***   **   **********                 ***** **\n"
        "      **************                        **   *                     ************                **                              ***   **\n"
        "      **************                        **   *                     ************                **                              ***   **\n"
        "                *************               **                    ********      ***              ****                              ***  ****\n"
        "                    ***                     **                     ***                             **                             ***    ***\n";
    
    cout <<"\t\t\t\t\t\t\t\t请选择功能:\n"
        "----------------------------------------------------------------------------------------------------------------------------------------------\n" 
        "                                             (1) 查看全部货物     \t\t\t(2)分区查看货物        \n"
        "                                             \n"
        "                                             (3) 根据商品名称购物\t\t\t(4) 退出\n"
        "----------------------------------------------------------------------------------------------------------------------------------------------\n";
}
void Set_Font(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // 设置前景色为白色，背景色为深蓝色，属性为加粗
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | BACKGROUND_INTENSITY);


    HFONT hFont = CreateFontW(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"微软雅黑");
    // 将字体选入设备环境中
    SelectObject((HDC)hConsole, hFont);
}
void press_any_key_to_continue() {
    cout<<"Press input any words to continue . . . "<<endl;
    string t;
    cin>>t;
}
/* 跑不动 脑子转不动了
void showAndSavePurchasedGoods(const vector<Goods*>& purchasedGoods) {
    cout << "购买的物品：" << endl;
    for (int i = 0; i < purchasedGoods.size(); i++) {
        purchasedGoods[i]->ShowMe();
    }

    // 保存购买的物品到 file.dat 文件
    ofstream file("file.dat");
    if (file.is_open()) {
        for (int i = 0; i < purchasedGoods.size(); i++) {
            file << purchasedGoods[i]->GetGoodName() << endl;
        }
        file.close();
        cout << "购买的物品已保存到 file.dat 文件。" << endl;
    } else {
        cout << "无法打开 file.dat 文件，保存购买的物品失败。" << endl;
    }
}
*/
void showPurchasedGoods(const vector<Goods*>& purchasedGoods) {
    cout << "购买的物品：" << endl;
    for (const auto& goods : purchasedGoods) {
        goods->Show_1();
    }
}
void goto_supermarket(double &money,vector<Goods*> &purchasedGoods) {
    
    Supermarket supermarket;
    string filename = "goods.txt";
    supermarket.loadFromFile(filename);
    cout << "已从文件中加载商品信息" << endl;
    bool flag = true;
    int choice;
    
    while (flag) {
        clear();
        if (choice == -1) {
            cout << "输入有误，请重新输入" << endl;
        }
        PRINT_3();  // 显示二级菜单选项
        cout<<"当前余额"<<money<<endl;
        cin >> choice;
        if (cin.fail()) {  // 输入不是一个数字
            cin.clear();  // 清除错误状态
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 忽略无效输入
            choice = -1;  // 设置choice为-1
        }
        switch (choice) {
            case 1:
                clear();
                supermarket.ShowAll();  // 显示所有商品
                press_any_key_to_continue();
                break;
            case 2:
                clear();
                supermarket.displayByGoodsType();  // 根据商品类型查看
                press_any_key_to_continue();
                break;
            case 3:
                clear();
                supermarket.shopping(money,purchasedGoods);  // 购买物品
                supermarket.saveToFile(filename); //报存到文件
                press_any_key_to_continue();
                break;
            case 4:
                clear();
                cout << "返回上级菜单" << endl;
                flag = false;  // 返回上级菜单
                break;
            default:
                break;
        }
    }
}
