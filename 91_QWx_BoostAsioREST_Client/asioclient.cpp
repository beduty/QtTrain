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
        boost::asio::async_write(socket,buffer, );
    }
    else{
        qDebug() << err.message().c_str()<<endl;
    }
}

void asioClient::handle_write(const boost::system::error_code &err, boost::asio::ip::basic_resolver::iterator endpoint_iterator)
{

}






















