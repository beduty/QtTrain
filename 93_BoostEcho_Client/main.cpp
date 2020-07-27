#include <QCoreApplication>
#include <boost/asio.hpp>
#include <iostream>
#include <array>

const char SERVER_IP[] = "127.0.0.1";
const unsigned short PORT_NUMBER = 31400;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(SERVER_IP), PORT_NUMBER);
    // 클라이언트의 End Point는 접속할 서버의 IP주소로 지정한다.

    boost::system::error_code connect_error;
    boost::asio::ip::tcp::socket socket(io_service);
    socket.connect(endpoint, connect_error);
    // 소켓클래스의 connect 멤버함수를 사용하여 서버 접속을 시도한다.
    // 접속이 성공하거나, 실패할 때까지 대기상태가 된다.

    if(connect_error)
    {
        std::cout << "Connect Fail... error No: " << connect_error.value()
         << ", Message: " << connect_error.message() << std::endl;
         getchar();
         return 0;
    }
    else{
        std::cout<< "Connect Success!!" << std::endl;
    }

    for (int i = 0; i< 7; i++)
    {
        char szMessage[128] = {0,};
        sprintf_s(szMessage, 128-1, "%d - Send Message", i);
        int nMsgLen = strnlen_s(szMessage, 128-1);

        boost::system::error_code ignored_error;
        socket.write_some(boost::asio::buffer(szMessage, nMsgLen), ignored_error);

        std::cout << "Send Message : " << szMessage << std::endl;

        std::array<char, 128> buf;
        buf.fill(0);
        boost::system::error_code error;
        size_t len = socket.read_some(boost::asio::buffer(buf), error);

        if( error )
        {
             if( error == boost::asio::error::eof )
             {
                std::cout << "Disconnect from Server" << std::endl;
             }
             else
             {
                 std::cout << "error No: " << error.value() << " error Message: "
                 << error.message().c_str() << std::endl;
             }
             break;
        }
        std::cout << "Received Message : " << &buf[0] << std::endl;
    }

    // 소켓클래스의 is_open()함수로 네트워크에 연결된 상태인지 아닌지 알 수 있따.
    if(socket.is_open())
        socket.close();

    getchar();
    return a.exec();
}
