#include"commodity.h"
int commodity::kinds = 0;
int commodity::getid()
{
    return id;
}
char* commodity::getname()
{
    return name;
}
void commodity::updatestock(int n)
{
    stock += n;
}
int commodity::getstock()
{
    return stock;
}
float commodity::getbuyvalue()
{
    return buyvalue;
}
float commodity::getsellvalue()
{
    return sellvalue;
}