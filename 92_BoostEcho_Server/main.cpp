#include <QCoreApplication>
#include <QDebug>
#include <boost/asio.hpp>
#include <iostream>
#include <array>
const char SERVER_IP[] = "127.0.0.1";
const unsigned short PORT_NUMBER = 31400;

// 에코 서버 프로그램!;
// 클라이언트의 접속 받고, 클라이언트가 보내는 메시지 받으면 그 메시지를 다시 클라이언트에 보낸다.

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    boost::asio::io_service io_service;
    // io_service I/O 이벤트를 할당하는 객체!! 핵심이다.
    // 네트워크상의 접속 받기, 접속하기, 데이터 받기, 데이터 보내기 이벤트등을 받고, 분재한다.

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), PORT_NUMBER);
    // 클라이언트가 접속할 수도 있도록,  네트워크 주소를 열어둔다. (v4방식은 127.0.0.1의 방식, v6는 맥주소처럼 Ipv6)

    boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);
    //  accepter 클래스는 클라이언트의 접속을 받아들이는 역할을 한다.

    boost::asio::ip::tcp::socket socket(io_service);
    // Client를 받기 위한 소켓을 할당한다.
    acceptor.accept(socket);
    // 클라이언트 접속을 기다린다. (동기 방식이라서 접속완료될때까지 대기한다.)

    std::cout<< "Client Accepted!" << std::endl;

    for (;;)
    {
        std::array<char, 128> buf; // 클라이언트가 보낸 메시지를 담을 버퍼를 만든다.
        buf.fill(0);
        boost::system::error_code error; // 에러코드 Wrapping, 에러발생하면 에러코드와 에러메시지를 얻는다.
        size_t len = socket.read_some(boost::asio::buffer(buf), error);
        // 소켓클래스의 read_some(..)으로 클라이언트가 보낸 데이터를 받는다.
        // 데이터 받은 크기를 반환한다.

        if(error) // 진짜에러인지, 접속이 끊어진것인지 확인해야 한다.
        {
            if(error == boost::asio::error::eof)
            {
                std::cout<< "Disconnect From Client" << std::endl;
            }
            else{
                std::cout << "error No: " << error.value() << " error Message: "
                 << error.message() << std::endl;
            }
            break;
        }
        std::cout << "Receive Message From Client : " << &buf[0] << std::endl;
        char szMessage[128] = {0,};
        sprintf_s(szMessage, 128-1, "Re : %s", &buf[0]);
        int nMsgLen = strnlen_s(szMessage, 128-1);

        boost::system::error_code ignored_error;
        socket.write_some(boost::asio::buffer(szMessage, nMsgLen), ignored_error);
        // 메시지를 보낼때는 socket클래스의 write_some 멤버함수를 사용한다.
        // 지정한 양 nMsgLen만큼만 보낸다.


        std::cout << "Send Message : " << szMessage << std::endl;
    }
    getchar();
    return a.exec();
}
