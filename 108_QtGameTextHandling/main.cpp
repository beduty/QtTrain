#include <QApplication>
#include <QStringLiteral>
#include <QFile>
#include <QDebug>
#define FILE_PATH "C:/Users/jungt/Documents/SrcTreeRepo/QtTrain/108_QtGameTextHandling/test"
#include <QObject>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ////--WRITE--//////////////////////////////////////////////////////////////
    QString text = QStringLiteral("I'm writing my games using Qt");
    QString path = QString(FILE_PATH) +"/write.txt";
    QFile file(path);
    file.open(QFile::WriteOnly);
    QByteArray array = text.toUtf8();
    file.write(array);
    file.close();
    //////////////////////////////////////////////////////////////////

    ////--READ--//////////////////////////////////////////////////////////////
    QString path2 = QString(FILE_PATH) +"/read.txt";
    QFile file2(path2);
    file2.open(QFile::ReadOnly);
    QByteArray array2 = file2.readAll();
    qDebug() <<array2;
    file2.close();
    //////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////
    QString str = QStringLiteral("1a2b3c4d5e6f7g8h");
    str.remove(2,4);  // 2부터 4개의 데이터가 지워진다.
    qDebug() << str;
    //////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////
    QString str2 = QStringLiteral("abcd1abcd2abcd3abcd4abcd5");
    str2.remove(QStringLiteral("ab"), Qt::CaseInsensitive);
    qDebug() << str2; // "ab"만 찾아서 다 지운다!
    //////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////
    QString original = QStringLiteral("ABCDEFGHIJK");
    QString left = original.left(3);
    QString right = original.right(2);
    QString middle = original.mid(3,4);
    qDebug() << "left  :  " << left; // 맨왼쪽에서 3개
    qDebug() << "right  :  " << right; // 맨오른쪽에서 2개
    qDebug() << "middle  :  " << middle; // 3번째 부터 4개

    //////////////////////////////////////////////////////////////////
    QString str3 = "Foo";
    QChar f = str3[0];
    str3[0] = 'G';
    qDebug() << f ;
    qDebug() << str3;
    //////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////
    int pos = -1;
    QString str4 = QStringLiteral("Orangutans like bananas.");
    do{
        pos = str4.indexOf("an" , pos+1);
        qDebug() << "'an' found starts at position" << pos;
    }while(pos != -1);
    //////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////
    QString record = "1,4,8,15,16,24,42";
    QStringList items = record.split(",");
    for(const QString& item : items)
    {
        qDebug() << item;
    }
    //////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////
    QStringList fields = {"1","4","8","15","16","24","42"};
    QString record2 = fields.join(",");
    qDebug() << record2;
    //////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////
    bool ok;
    int v1 = QString("42").toInt(&ok, 10);
    double v2 = QString("not really a number").toDouble(&ok);
    QString txt = QString::number(42);
    QString s1 = QString::number(42,16); //  10진수 42 -> 16진수 변환
    QString s2 = QString::number(42.0, 'f', 3); //소수점 3자리까지만 표시

    qDebug() << v1;
    qDebug() << v2;
    qDebug() << txt;
    qDebug() << s1;
    qDebug() << s2;
    //////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////
    int current = 1;
    int total = 5;

    QString strArgu1 = "Copying file " + QString::number(current)
                    +" of " + QString::number(total);
    QString strArgu2 = QObject::tr("Copying file %1 of %2").arg(current).arg(total);
    qDebug() << strArgu1;
    qDebug() << strArgu2;

    const int fieldWidth = 4;
    qDebug() << QStringLiteral("%1 | %2").arg(5, fieldWidth).arg(6, fieldWidth);
    qDebug() << QStringLiteral("%1 | %2").arg(15, fieldWidth).arg(16, fieldWidth);
    // arg(5, fieldWidth)로 쓰면 fieldWidth로 지정된 길이의 문자열을 출력할 수 있도록한다.
    // qDebug() 출력이 보기가 편해진다.
    //////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////

    return a.exec();
}


















