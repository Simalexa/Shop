#include <fstream>
#include <sstream>
#include <iostream>
#include "Products.h"
#include <QDebug>


Buy::Buy()
{
    NumberOfCompetitor=0;
}
Buy::~Buy()
{
}
QStringList Buy::findUniqueShop(class MainWindow *m, int lineNumber)
{
    QStringList Shop;
        int i,j;
        bool flag = true;
        //k=0;
        for(i=0;i<= lineNumber;i++)
           {
            for(j=0;j <= i;j++)
            {
                if(flag==true)
                {
                    if(m->Shop[i]==m->Shop[j] && i!=j)
                        flag=false;
                }
            }
            if(flag==true)
            {
                //Shop[k] << m->Shop[i];
                //k++;
                Shop.append(m->Shop[i]);
            }
            flag=true;
           }
        return Shop;
}
QStringList Buy::calculateTotalPrice(class MainWindow *m, QStringList ListShops, QStringList ListProduct, int lineNumber)
{
    int totalPrice=0;
    int counter = 0;
    QStringList ListOfAvalibleShops;
    for(int i = 0; i < ListShops.size(); i++)
    {
        for(int j = 0; j <= lineNumber; j++)
        {
            if(ListShops[i]==m->Shop[j])
            {
                for (int k = 0; k < ListProduct.size(); k++)
                {
                    if(m->Name[j]==ListProduct[k])
                    {
                        QString Price = m->Price[j];
                        totalPrice += Price.toInt();
                        counter++;
                    }
                }
            }
        }
        if(counter==ListProduct.size())
            ListOfAvalibleShops.append(ListShops[i] + "->" + QString::number(totalPrice));
        totalPrice=0;
        counter=0;
    }
    totalPrice=0;
    counter=0;
    return ListOfAvalibleShops;
}
BestPlace Buy::FindBestShop(QStringList Shop)
{
    BestPlace pl;
    int position = 0, massive[Shop.size()],el;
    qDebug()<<Shop.size();
    for(int i=0; i<Shop.size(); i++)
    {
        QString devide1 = Shop[i].split("->")[1];
        massive[i]=devide1.toInt();
        qDebug()<<massive[i];
    }
    el=massive[0];
    for(int i=1; i<Shop.size(); i++)
        {
            if(massive[i]<el)
            {
               position=i;
               el=massive[i];
            }
         }
    pl.BestShop=Shop[position].split("->")[0];
    pl.BestPrice=massive[position];
    return pl;
}
