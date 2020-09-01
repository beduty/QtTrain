#include <QApplication>
#include <QBuffer>
#include <QtDebug>
#include "encryptdevice.h"

// m_key의 역할은 문자기준으로 Offset역할을 한다.
// m_key값이 3이면, A가 들어왔을 때 A+3 = D 인 D로 변환된다.
// 이렇게 하여 Offset을 통한 암호화를 수행한다.

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QByteArray ba = "plaintext";
    QBuffer buf;
    buf.open(QIODevice::WriteOnly);

    EncryptDevice encrypt;
    encrypt.setKey(3);
    encrypt.setBaseDevice(&buf);
    encrypt.open(buf.openMode());
    encrypt.write(ba);
    qDebug() << buf.data();

    EncryptDevice decrypt;
    decrypt.setKey(3);
    decrypt.setBaseDevice(&buf);
    buf.open(QIODevice::ReadOnly);
    decrypt.open(buf.openMode());
    qDebug() << decrypt.readAll();



    return a.exec();
}



