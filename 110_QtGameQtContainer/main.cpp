#include <QApplication>
#include <QVector>
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //////////////////////////////////
    QVector<int> numbers;
    numbers.append(1);
    numbers.push_back(3);
    numbers.append(5);
    numbers.append(7);
    numbers.append(9);
    qDebug() << numbers.at(1);
    //////////////////////////////////

    //////////////////////////////////
    QMap<int, QString> map;
    map[3] = "three";
    map[1] = "one";
    map[2] = "two";
    for(auto i = map.begin(); i != map.end(); ++i){
        qDebug() << i.key() << i.value();
    }
    //////////////////////////////////
    std::vector<int> x{1,2,3};
    std::vector<int> y = x; // full copy
    //std::vector<int> *y = &x; // 레퍼런스 Copy
    x[1] = 0;
    qDebug() << x.at(0)<< x.at(1)<< x.at(2);
    qDebug() << y.at(0)<< y.at(1)<< y.at(2);

    QVector<int> xq { 1, 2, 3};
    QVector<int> yq = xq;
    // 여기서는 Full Copy가 아닌 레퍼런스 카피이다.
    yq[0] = 5;
    // 여기서 원본개체나 복사본을 편집하지 않는 이상 레퍼런스 Copy.
    // 편집을 시작하면 New Allocation을 한다!
    //////////////////////////////////
    QVector<int> x1{1,2,3};
    int *x0 = x1.begin();
    QVector<int> y1 = x1;
    x1[0] = 42;
    qDebug() << *x0;
    qDebug() << y1[0];
    qDebug() << x1[0];
    //////////////////////////////////
    QString string = QString("abc").replace('a', 'z');
    for(QChar c : string){
        qDebug() << c;
    }
    //////////////////////////////////
    qDebug()<< "currentPath : " << QDir::currentPath();
    qDebug()<< "homePath : " << QDir::homePath();
    qDebug()<< "rootPath : " << QDir::rootPath();
    qDebug()<< "tempPath : " << QDir::tempPath();
    //////////////////////////////////

    //////////////////////////////////

    //////////////////////////////////

    //////////////////////////////////




    return a.exec();
}
