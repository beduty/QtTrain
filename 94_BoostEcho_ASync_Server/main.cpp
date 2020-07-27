#include <QCoreApplication>
#include <QDebug>
#include "tcpserver.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    boost::asio::io_service io_service;
    TcpServer server(io_service);
    io_service.run();
    std::cout << "NetWork Connection Exit." <<std::endl;
    getchar();

    return a.exec();
}
