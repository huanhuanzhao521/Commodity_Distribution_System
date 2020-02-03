#pragma once
#include<iostream>
#include<string.h>
class commodity
{
public:
    //commodity(char name[], float buyvalue, float sellvalue);
    //commodity(int id, char name[], float buyvalue, float sellvalue, int stock);
    int getid();
    char* getname();
    void updatestock(int n);
    int getstock();
    float getbuyvalue();
    float getsellvalue();
    friend class trade;
private:
    int static kinds; // 商品种类
    int id; // 货品ID
    int stock;
    float buyvalue;
    float sellvalue;
    char name[30];

commodity(char name[], float buyvalue, float sellvalue)
{
    kinds++;
    id = kinds;
    this->stock = 0;
    this->buyvalue = buyvalue;
    this->sellvalue = sellvalue;
    strncpy_s(this->name, name,sizeof(name));
}
commodity(int id, char name[], float buyvalue, float sellvalue, int stock)
{
    kinds++;
    this->id = id;
    this->stock = stock;
    this->buyvalue = buyvalue;
    this->sellvalue = sellvalue;
    strncpy_s(this->name, name,sizeof(name));
}
};
