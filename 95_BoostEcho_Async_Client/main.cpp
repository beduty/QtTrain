#include <QCoreApplication>
#include "tcpclient.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(SERVER_IP), PORT_NUMBER);

    TcpClient client(io_service);
    client.Connect(endpoint);
    io_service.run();
    std::cout << "Network Connection Exit." << std::endl;
    getchar();

    return a.exec();
}
