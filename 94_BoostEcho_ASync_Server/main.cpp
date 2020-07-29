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
    //    핵심!! 실행되는 동시에 무한대기 상태가 된다.
    //      비동기요청(클라이언트받기, 데이터받기, 데이터보내기 등등)를 수행하고,
    //      다음 요청이 없으면, run()함수를 빠져나와서 다음작업을 진행한다.!
    //   --> 비동기 요청을 하기 전에 io_service.run()하면 run()함수는 실행할 비동기 요청이 없으므로 바로 종료된다!

    //     Server에서는  m_Socket.async_read_some으로 읽기 대기하다가,
    //       데이터 받으면 다시 Echo로 돌려준다.(boost::asio::async_write) 돌려주고 마지막에 다시
    //       m_Socket.async_read_some을 해주므로, 종료되지 않고 계속 대기한다.


    std::cout << "NetWork Connection Exit." <<std::endl;
    getchar();

    return a.exec();
}
