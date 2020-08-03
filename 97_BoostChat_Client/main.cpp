#include <QCoreApplication>
#include "chatclient.h"
#include <iostream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    boost::asio::io_service io_service;
    auto endPoint = boost::asio::ip::tcp::endpoint(
                        boost::asio::ip::address::from_string("127.0.0.1"),
                        PORT_NUMBER);
    ChatClient Client(io_service);
    Client.Connect(endPoint);
    boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));

    char szInputMessage[MAX_MESSAGE_LEN*2] = {0,};
    while (std::cin.getline(szInputMessage, MAX_MESSAGE_LEN))
    {
        if(strnlen_s(szInputMessage, MAX_MESSAGE_LEN) == 0)
            break;
        if(Client.IsConnecting() == false)
        {
            std::cout << "Server Connection Fail!" << std::endl;
            continue;
        }
        if(Client.IsLogin() == false)
        {
            PKT_REQ_IN SendPkt;
            SendPkt.Init();
            strncpy_s(SendPkt.szName, MAX_NAME_LEN, szInputMessage, MAX_NAME_LEN-1);
            Client.PostSend(false, SendPkt.nSize, (char*)&SendPkt);
        }
        else
        {
            PKT_REQ_CHAT SendPkt;
            SendPkt.Init();
            strncpy_s(SendPkt.szMessage, MAX_MESSAGE_LEN, szInputMessage, MAX_MESSAGE_LEN-1);
            Client.PostSend(false, SendPkt.nSize, (char*)&SendPkt);
        }
    }
    io_service.stop();
    Client.Close();
    thread.join();
    std::cout<< "Please Exit Client" << std::endl;

    return a.exec();
}
