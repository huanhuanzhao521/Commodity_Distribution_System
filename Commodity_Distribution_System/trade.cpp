#define _CRT_SECURE_NO_WARNINGS
#include"trade.h"
#include<fstream>
#include<time.h>
#include<string.h>
#define CAP 5
#define TLEN 10
#define ALEN 30

using std::ofstream;
using std::ifstream;

/*
errno_t localtime_s(
    struct tm* _tm,
    const time_t* time
);*/
bool trade::buy(int id, int count)
{
    for (auto iter = datalist.begin();iter!=datalist.end();iter++)
    {
        if (iter->getid() == id)
        {
            iter->updatestock(count);

            /*
            struct tm t;   //tm结构指针
            time_t now = time(0);  //声明time_t类型变量
            time(&now);      //获取系统日期和时间
            localtime_s(&t, &now);
            */
            time_t t = time(0);
            char temp[50];
            strftime(temp, sizeof(temp), "%Y年%m月%d日%X%A", localtime(&t));
            buyrecordlist.push_back(record(iter->name, count, temp));
            return true;
        }
    }
    return false;
}

bool trade::sell(int id, int count)
{
    for (auto iter = datalist.begin(); iter != datalist.end(); iter++)
    {
        if (iter->getid() == id&& !(iter->getstock()+count<0))
        {
            iter->updatestock(-count);

            /*
            struct tm t;   //tm结构指针
            time_t now = time(0);  //声明time_t类型变量
            time(&now);      //获取系统日期和时间
            localtime_s(&t, &now);
            */

            time_t t = time(0);
            char temp[50];
            strftime(temp, sizeof(temp), "%Y年%m月%d日%X%A", localtime(&t));
            sellrecordlist.push_back(record(iter->name, count, temp));
            return true;
        }
    }
    return false;
}

void trade::getindex()
{
    for (auto iter = datalist.begin(); iter != datalist.end(); iter++)
    {
        std::cout << "\t   商品编号   "
                  << "商品名称  " << std::endl;
        std::cout << "\t    "<<iter->getid() << "          "
                  << iter->getname() << std::endl;
    }
}

bool trade::getinformation(int index)
{
    for (auto iter=datalist.begin();iter!=datalist.end();iter++)
    {
        if (iter->getid() == index)
        {
            std::cout << "商品编号   ";
            std::cout << "商品名称   "; 
            std::cout << "购入价格   "; 
            std::cout << "售出价格   ";
            std::cout << "商品剩余库存   " << std::endl;
            std::cout << index << "         ";
            std::cout << iter->getname() << "          ";
            std::cout << iter->getbuyvalue() << "          ";
            std::cout << iter->getsellvalue() << "          ";
            std::cout << iter->getstock() << std::endl;
            /*
            std::cout << index << "         "
                << iter->getname()<<"         "
                << iter->getbuyvalue() << "         "
                << iter->getsellvalue() << "         "
                << iter->getstock() << std::endl;
                */
            return true;
        }
    }
    return false;
}

void trade::save()
{
    ofstream file;
    file.open("stock.txt");
    if (!file.fail())
    {
        file << " ════════════════════════════ " << std::endl;
        file << "               ***** 商品信息 *****                       " << std::endl;
        file << " ════════════════════════════ " << std::endl;
        for (auto iter = datalist.begin(); iter != datalist.end(); iter++)
        {
            file << "ID:" << iter->getid()
                << "\tNAME:" << iter->getname()
                << "\tCOST:" << iter->getbuyvalue()
                << "\tVALUE:" << iter->getsellvalue()
                << "\tSTOCK:" << iter->getstock()
                << std::endl;
        }
    }
    else {
        std::cout << "记录文件创建失败！" << std::endl;
    }
    file.close();
    file.open("sellRecord.txt");
    if (!file.fail())
    {
        file << " ════════════════════════════ " << std::endl;
        file << "               ***** 销售信息 *****                       " << std::endl;
        file << " ════════════════════════════ " << std::endl;
        for (auto iter = sellrecordlist.begin(); iter != sellrecordlist.end(); iter++)
        {
            file << "NAME:" << iter->name
                << "\tTIME:" << iter->sTime
                << "\tCOUNT:" << iter->count
                << std::endl;
        }
    }
    else {
        std::cout << "销售文件创建失败！" << std::endl;
    }
    file.close();
    file.open("buyRecord.txt");
    if (!file.fail())
    {
        file << " ════════════════════════════ " << std::endl;
        file << "               ***** 购入信息 *****                       " << std::endl;
        file << " ════════════════════════════ " << std::endl;
        for (auto iter = buyrecordlist.begin(); iter != buyrecordlist.end(); iter++)
        {
            file << "NAME:" << iter->name
                << "\tTIME:" << iter->sTime
                << "\tCOUNT:" << iter->count
                << std::endl;
        }
    }
    else {
        std::cout << "购入文件创建失败！" << std::endl;
    }
    file.close();
}

bool trade::init()
{
    ifstream file("stock.txt");
    if (!file.fail())
    {
        char titles[CAP][TLEN] = { "ID","NAME","COST","VALUE","STOCK" };
        char saves[CAP][TLEN] = {};
        int tindex = 0;
        char buf[128];
        int kinds = 0;
        for (int i = 0; i < 3; i++)
        {
            file.getline(buf, 128);
        }
        while (!file.eof())
        {
            char temp[TLEN] = "";
            for (int i = 0; i < TLEN && !file.eof(); i++)
            { 
                file.get(temp[i]);
                if (strcmp(temp, titles[tindex]) == 0)
                {
                    for (int j = 0; j < TLEN && !file.eof(); i++)
                    {
                        char  c;
                        file.get(c);
                        if (c != '\t' && c != '\n')
                        {
                            saves[tindex][j] = c;
                        }
                        else if (c != '\n')
                        {
                            if (tindex > 4)
                            {
                                return false;
                            }
                            tindex++;
                            break;
                        }
                        else {
                            datalist.push_back(commodity(atoi(saves[0]), saves[1],
                                atof(saves[2]), atof(saves[3]), atoi(saves[4])));
                            tindex = 0;
                            kinds++;
                            break;
                        }
                        if (j == ALEN - 1)
                        {
                            return false;
                        }
                    }
                    break;
                }
                if (i == TLEN - 1)
                {
                    return false;
                }
            }
        }
        commodity::kinds = kinds;
        return true;
    }
    return false;
}


void trade::addnew(char name[], float buyvalue, float sellvalue)
{
    datalist.push_back(commodity(name, buyvalue, sellvalue));
}
void trade::getsellrecord()
{
    for (auto iter = sellrecordlist.begin(); iter != sellrecordlist.end(); iter++)
    {
        std::cout << "\t出售商品名称:" << iter->name << std::endl;
        std::cout << "\t交易日期:" << iter->sTime << std::endl;
        std::cout << "\t出售数目:" << iter->count << std::endl;
        std::cout << "\t ════════════════════════════" << std::endl;
    }
}
void trade::getbuyrecord()
{
    for (auto iter = buyrecordlist.begin(); iter != buyrecordlist.end(); iter++)
    {
        std::cout << "\t购入商品名称:" << iter->name << std::endl;
        std::cout << "\t交易日期:" << iter->sTime << std::endl;
        std::cout << "\t购入数目:" << iter->count << std::endl;
        std::cout << "\t ════════════════════════════" << std::endl;
    }
}