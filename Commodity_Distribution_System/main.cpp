#include<iostream>
#include"trade.h"

void tobuy(int &id,int &count)
{
    std::cout << "请输入购买商品的编号" << std::endl;
    std::cin >> id;
    std::cout << "请输入购买商品的数量" << std::endl;
    std::cin >> count;
    getchar();
}
void tosell(int& id, int& count)
{
    std::cout << "请输入卖出商品的编号" << std::endl;
    std::cin >> id;
    std::cout << "请输入卖出商品的数量" << std::endl;
    std::cin >> count;
    getchar();
}
void operate()
{
    std::cout << "按任意键继续";
    getchar();
    system("cls");
}
void drawindex()
{
    system("cls");
    std::cout << "\t ════════════════════════════ " << std::endl;
    std::cout << "\t                ***** 商品目录 *****                        " << std::endl;
    std::cout << "\t ════════════════════════════ " << std::endl;
}
void drawline()
{
    std::cout << "\t ════════════════════════════ " << std::endl;
}
/*主窗体模块*/
void drawmainMenu()
{
    std::cout << "\t==================================================== " << std::endl;
    std::cout << "\t                    欢迎使用销售系统                 " << std::endl;
    std::cout << "\t                    1- 购进商品                      " << std::endl;
    std::cout << "\t                    2- 卖出商品                      " << std::endl;
    std::cout << "\t                    3- 添加新品                      " << std::endl;
    std::cout << "\t                    4- 查看商品信息                  " << std::endl;
    std::cout << "\t                    5- 查看采购记录                  " << std::endl;
    std::cout << "\t                    6- 查看销售记录                  " << std::endl;
    std::cout << "\t                    7- 退出                          " << std::endl;
    std::cout << "\t==================================================== " << std::endl;
}
void drawbuyrecord()
{

    system("cls");
    std::cout << "\t ════════════════════════════ " << std::endl;
    std::cout << "\t                ***** 采购记录 *****                        " << std::endl;
    std::cout << "\t ════════════════════════════ " << std::endl;
}
void drawsellrecord()
{

    system("cls");
    std::cout << "\t ════════════════════════════ " << std::endl;
    std::cout << "\t                ***** 销售记录 *****                        " << std::endl;
    std::cout << "\t ════════════════════════════ " << std::endl;
}
int main()
{
    trade MyTrade;
    if (!MyTrade.init())
    {
        MyTrade = trade();
    }
    bool quitFlag = false;
    while (!quitFlag)
    {
        drawmainMenu();
        std::cout << "请输入你的选项:" << std::endl;
        int selection;
        std::cin >> selection;
        getchar();
        int id;
        int count;
        switch (selection)
        {
        case 1:
            drawindex();
            MyTrade.getindex();
            //drawline();
            tobuy(id, count);
            if (MyTrade.buy(id, count))
            {
                system("cls");
                std::cout << "操作成功" << std::endl;
            }
            else {
                system("cls");
                std::cout << "您的输入有误" << std::endl;
            }
            operate();
            break;
        case 2:
            drawindex();
            MyTrade.getindex();
            //drawline();
            tosell(id, count);
            if (MyTrade.sell(id, count))
            {
                system("cls");
                std::cout << "操作成功" << std::endl;
            }
            else {
                system("cls");
                std::cout << "您的输入有误" << std::endl;
            }
            operate();
            break;
        case 3:
            char name[30];
            float value;
            float cost;
            system("cls");
            std::cout << "请输入商品名称" << std::endl;
            std::cin >> name;
            getchar();
            std::cout << "请输入购入价格" << std::endl;
            std::cin >> cost;
            getchar();
            std::cout << "请输入售出价格" << std::endl;
            std::cin >> value;
            getchar();
            MyTrade.addnew(name, cost, value);
            system("cls");
            std::cout << "操作成功" << std::endl;
            operate();
            break;
        case 4:
            drawindex();
            MyTrade.getindex();
            drawline();
            std::cout << "请输入商品编号" << std::endl;
            int index;
            std::cin >> index;
            getchar();
            system("cls");
            if (!MyTrade.getinformation(index))
            {
                std::cout << "无效的商品号" << std::endl;
                operate();
            }
            else {
                operate();
            }
            break;
        case 5:
            drawbuyrecord();
            MyTrade.getbuyrecord();
            operate();
            break;
        case 6:
            drawsellrecord();
            MyTrade.getsellrecord();
            operate();
            break;
        case 7:
            quitFlag = true;
            break;
        default:
            system("cls");
            std::cout << "无效的选项" << std::endl;
            operate();
        }
    }
    MyTrade.save();
    return 0;
}