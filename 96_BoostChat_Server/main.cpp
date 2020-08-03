#include <QCoreApplication>
#include "chatserver.h"
const int MAX_SESSION_COUNT = 100;

/*주요개념
    * 서버-클라이언트간 Ip주소, Port번호가 맞아야한다.
    * 클라이언트는 하나의 소켓만을 가진다.
    * 서버는 연결된 클라이언트만큼 소켓의 개수를 가져야 한다.
    * 서버에는 소켓을 포함해 클라이언트 관리를 해야한다. 이를 세션이 수행한다.
    * 세션에는 기본적으로 다음과 같은 정보를 가져야 한다.
    *     1. 클라이언트가 연결된 소켓
    *     2. 클라이언트 ID
    *     3. 클라이언트 이름
    *     4. 서버 포인터
    *     5. 인터페이스_데이터 쓰기(클라이언트에게 전송)
    *     6. 인터페이스_데이터 읽기(클라이언트 데이터 읽기)
    *     7. 버퍼_클라이언트로부터 받은 데이터.
*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    boost::asio::io_service io_service;
    ChatServer server(io_service);
    server.Init(MAX_SESSION_COUNT); // 세션 공간 할당한다. (클라이언트 정보 저장하기 위함)
    server.Start(); // 클라이언트의 접속 요청을 기다린다.(요청 올떄까지 대기_async_accept)
    io_service.run();

    std::cout << "NetWork Service Exit!!"<< std::endl;
    return a.exec();

}
