#ifndef PRODUCTS_H
#define PRODUCTS_H
#include <QTextStream>
#include "mainwindow.h"

struct BestPlace
{
    QString BestShop;
    int BestPrice;
};

class Buy
{
private:
    class MainWindow* m;
public:
    int NumberOfCompetitor;
    Buy();
    ~Buy();
    QStringList findUniqueShop(class MainWindow *m, int lineNumber);
    QStringList calculateTotalPrice(class MainWindow *m, QStringList ListShops, QStringList ListProduct, int lineNumber);
    BestPlace FindBestShop(QStringList Shop);
};

#endif // PRODUCTS_H
