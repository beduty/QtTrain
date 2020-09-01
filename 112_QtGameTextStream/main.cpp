#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QString>
#include <QStringLiteral>
#include <QDataStream>
#include <QColor>
#include <QStringList>
#include <QBuffer>
#include <QIODevice>
#include <QtDebug>


struct Player{
    QString name;
    qint64 experience;
    QPoint position;
    QChar direction;
};
QDataStream& operator<<(QDataStream &stream, const Player &p) {
    stream << p.name;
    stream << p.experience;
    stream << p.position;
    stream << p.direction;
    return stream;
}

QDataStream& operator>>(QDataStream &stream, Player &p) {
    stream >> p.name;
    stream >> p.experience;
    stream >> p.position;
    stream >> p.direction;
    return stream;
}


int main(int argc, char *argv[])
{
    //////////////////////////////////////////////////
    QFile  file("output.txt");
    file.open(QFile::WriteOnly | QFile::Text);
    QTextStream stream(&file);
    stream << "Today is " << QDate::currentDate().toString() << endl;
    QTime t = QTime::currentTime();
    stream << "Current Time is " << t.hour() << " h and " << t.minute() << "m. " << endl;
    file.close();
    //////////////////////////////////////////////////

    //////////////////////////////////////////////////
    QVector<Player> players;
    Player temp;
    temp.name =QString("Gondael");
    temp.experience = 46783;
    temp.position = QPoint(10,-5);
    temp.direction = 'n';
    players.push_back(temp);

    temp.name =QString("Olrael");
    temp.experience = 123648;
    temp.position = QPoint(-5,103);
    temp.direction = 'e';
    players.push_back(temp);

    temp.name =QString("Nazaal");
    temp.experience = 99372641;
    temp.position = QPoint(48,634);
    temp.direction = 's';
    players.push_back(temp);

    QFile file2("players.txt");
    file2.open(QFile::WriteOnly | QFile::Text);
    QTextStream stream2(&file2);
    stream2 << center;
    stream2 << qSetFieldWidth(16) << "Player" << qSetFieldWidth(0) << " ";
    stream2 << qSetFieldWidth(10) << "Experience" << qSetFieldWidth(0) << " ";
    stream2 << qSetFieldWidth(13) << "Position" << qSetFieldWidth(0) << " ";
    stream2 << "Direction" << endl;
    for(const Player &player : players)
    {
        stream2 << left << qSetFieldWidth(16) << player.name << qSetFieldWidth(0) << " ";
        stream2 << right << qSetFieldWidth(10) << player.experience << qSetFieldWidth(0) << " ";
        stream2 << right << qSetFieldWidth(6) << player.position.x() << qSetFieldWidth(0) << " ";
        stream2 << qSetFieldWidth(6) << player.position.y() << qSetFieldWidth(0) << " ";
        stream2 << center << qSetFieldWidth(10);
        if(player.direction == 'n')
            stream2 << "north" ;
        else if(player.direction == 's')
            stream2 << "south" ;
        else if(player.direction == 'e')
            stream2 << "east" ;
        else if(player.direction == 'w')
            stream2 << "west" ;
        else
            stream2 << "unknown" ;
        stream2 << qSetFieldWidth(0) << endl;
    }
    ////////////////////////////////////////////////


    // 바이너리 데이터 직렬화. --> QDataStream
    //////////////////////////////////////////////////
    QFile file3("binaryData.dat");
    file3.open(QFile::WriteOnly | QFile::Truncate);
    QDataStream stream3(&file3);
    double dbl = 3.13156265359;
    QColor color = Qt::red;
    QPoint point(10.,-4);
    QStringList stringList = {"foo", "bar"};
    stream3 << dbl << color << point << stringList;
    file3.close();

    QFile file4("binaryData.dat");
    file4.open(QFile::ReadOnly);
    QDataStream stream4(&file4);
    double restoredDbl;
    QColor restoredColor;
    QPoint restoredPoint;
    QStringList restoredStringList;
    stream4 >> restoredDbl;
    stream4 >> restoredColor;
    stream4 >> restoredPoint;
    stream4 >> restoredStringList;
    qDebug() << restoredDbl << restoredColor<< restoredPoint<< restoredStringList;
    file4.close();
    //////////////////////////////////////////////////

    //////////////////////////////////////////////////
    Player player4;
    player4.name = "John Doe";
    player4.experience = 1234;
    player4.position = QPoint(1,2);
    player4.direction = 'n';

    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    {
        QDataStream stream(&buffer);
        stream << player4;
        qDebug() << buffer.data().toHex();
    }
    buffer.close();
    buffer.open(QIODevice::ReadOnly);
    Player restoredPlayer4;
    {
        QDataStream stream(&buffer);
        stream >> restoredPlayer4;
        qDebug() << restoredPlayer4.name << restoredPlayer4.experience
                 << restoredPlayer4.position << restoredPlayer4.direction;
    }
    //////////////////////////////////////////////////

    //////////////////////////////////////////////////

    //////////////////////////////////////////////////



    return 0;
}



























