#ifndef ENCRYPTDEVICE_H
#define ENCRYPTDEVICE_H

#include <QObject>
#include <QIODevice>

// m_key의 역할은 문자기준으로 Offset역할을 한다.
// m_key값이 3이면, A가 들어왔을 때 A+3 = D 인 D로 변환된다.
// 이렇게 하여 Offset을 통한 암호화를 수행한다.

class EncryptDevice : public QIODevice
{
    Q_OBJECT
    Q_PROPERTY(int key READ key WRITE setKey)

public:
    explicit EncryptDevice(QObject *parent = 0);
    int key() const;
    void setKey(int key);
    void setBaseDevice(QIODevice *dev);
    QIODevice *baseDevice() const;
    //bool open(OpenMode mode) override;

private:
    int m_key;
    QIODevice *m_baseDevice;

    // QIODevice interface
public:
    bool open(OpenMode mode);

protected:
    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);
};

#endif // ENCRYPTDEVICE_H
