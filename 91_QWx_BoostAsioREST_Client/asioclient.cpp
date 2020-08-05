#include "asioclient.h"
#include <QDebug>

asioClient::asioClient(QObject *parent) : QObject(parent)
    ,work(new boost::asio::io_service::work(ioservice)) // 명시적으로 프로그램이 종료할떄까지 비동기 이벤트를 기다린다!
    ,resolver(ioservice),socket(ioservice)
{

   worker =  std::thread([&](){
         ioservice.run(); // 별도의 스레드에서 계속 루프돌면서 비동기 이벤트를 처리한다. thread로 안뺴주면, 프로그램이 Block되기 때문이다.
    });

}

asioClient::~asioClient()
{
    ioservice.stop();
    worker.join();
    work.reset();
}

void asioClient::get(const QString &url, const QString &p)
{
    server = url.toStdString();
    path = p.toStdString();

    //1. url->ep resolve //end-point형태로 resolve
    boost::asio::ip::tcp::resolver::query query(server, "http");
    resolver.async_resolve(query, boost::bind(&asioClient::handle_resolve, this, boost::asio::placeholders::error,
                                              boost::asio::placeholders::iterator));
    //2. connect // resolve한 형태로 connect
    //3. send'
    //4. receive
}

void asioClient::handle_resolve(const boost::system::error_code &err, boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
    if(!err){
        boost::asio::ip::tcp::endpoint ep = *endpoint_iterator;
        qDebug() << ep.address().to_string().c_str();

        // Connect를 시도한다.(Connect요청)
        socket.async_connect(ep,boost::bind(
                                 &asioClient::handle_connect,
                                 this,
                                 boost::asio::placeholders::error,
                                 endpoint_iterator)
                             );
    }
}

void asioClient::handle_connect(const boost::system::error_code &err, boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
    if(!err){
        //success
        std::ostream os(&requestbuf );
        os << "GET " << path << " HTTP/1.0\r\n";
        os << "Host : " << server << "\r\n";
        os << "Accept: */*\r\n";
        os << "Connection: close\r\n\r\n";

        // write
        boost::asio::async_write(socket,requestbuf,
                                 boost::bind(&asioClient::handle_write, this, boost::asio::placeholders::error)
                                 );
    }
    else{
        qDebug() << err.message().c_str()<<endl;
    }
}

void asioClient::handle_write(const boost::system::error_code &err)
{
    // recv
    if(!err){
        // 특정 지점("\r\n")까지 읽게되면 반환한다.!
        boost::asio::async_read_until(socket, responsebuf, "\r\n",
                                      boost::bind(&asioClient::handle_read_line, this, boost::asio::placeholders::error));
    }
    else{
        qDebug() << "handle_Write error : " << err.message().c_str() << endl;
    }
}

void asioClient::handle_read_line(const boost::system::error_code &err)
{
    if(!err){
        std::istream is(&responsebuf);
        std::string http_version;
        unsigned int status_code;
        std::string status_message;

        is>> http_version;
        is>> status_code;
        std::getline(is, status_message); // 개행문자가 포함되어 있기 때문이다!

        if(status_code != 400)
            return;
        // 두번의 개행문자 읽는 곳까지 읽은 이후에 그다음 본 내용을 읽어온다.
        boost::asio::async_read_until(socket, responsebuf, "\r\n\r\n",
                                      boost::bind(&asioClient::handle_read_header, this, boost::asio::placeholders::error)
                                      );
    }
    else{

    }
}

void asioClient::handle_read_header(const boost::system::error_code &err)
{
    // "\r\n\r\n" 까지 읽는다고 했지만, 이를 완전 보장하는 것은 아니다...
    // Async특성상 불가능할 수도 있다. 여기서는 헤더와 본문을 일단 다 읽어온다.

    std::istream istrm(&responsebuf);
    std::string header;
    while (std::getline(istrm, header) && header != "\r")
    {
        //header
        oss << header << std::endl; // 한줄씩 읽어서 oss에 넣는다.. 굳이 넣는다.
    }

    //
    boost::asio::streambuf::const_buffers_type bufs = responsebuf.data();
    std::string str(boost::asio::buffers_begin(bufs),
                    boost::asio::buffers_begin(bufs)+responsebuf.size());
    oss<<str;
    //qDebug() << oss.str().c_str()<<endl;

    boost::asio::async_read(socket, responsebuf,
                            boost::asio::transfer_at_least(1),
                            boost::bind(&asioClient::handle_read_content, this, boost::asio::placeholders::error));
}

void asioClient::handle_read_content(const boost::system::error_code &err)
{
    if(!err){
        oss << &responsebuf;

        // 다 읽을 때까지 재귀적으로 요청한다.
        boost::asio::async_read(socket, responsebuf,
                                boost::asio::transfer_at_least(1),
                                boost::bind(&asioClient::handle_read_content, this, boost::asio::placeholders::error));
    }
    // 에러난경우와 다읽은 경우를 분기처리한다.
    else if(err == boost::asio::error::eof)
    {
        qDebug() << oss.str().c_str() << endl;
    }
    else {

    }

}






















