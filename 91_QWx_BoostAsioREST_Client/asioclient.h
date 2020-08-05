#ifndef ASIOCLIENT_H
#define ASIOCLIENT_H
#include <boost/asio.hpp>
#include <QObject>
#include <QString>
#include <memory>
#include <thread>
#include <boost/bind.hpp>

class asioClient : public QObject
{
    Q_OBJECT
public:
    explicit asioClient(QObject *parent = nullptr);
    ~asioClient();

    // http://127.0.0.1/todo/ + 기본 url과 뒤에 오는 Path로 여러 동작한다.
    void get(const QString& url, const QString& path);
    void handle_resolve(const boost::system::error_code& err,
                        boost::asio::ip::tcp::resolver::iterator endpoint_iterator); // 요청하고 나서 결과는 비동기CallBack으로 받는데, 이 콜백 함수를 정의한다.
    void handle_connect(const boost::system::error_code& err,
                        boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
    void handle_write(const boost::system::error_code& err);
    void handle_read_line(const boost::system::error_code& err);
    void handle_read_header(const boost::system::error_code& err);
    void handle_read_content(const boost::system::error_code& err);

private:
    // 사용자는 비동기 요청을 하고, io서비스가 작업을 완료하면, 얻어온 결과를 리턴한다.
    boost::asio::io_service ioservice;
    std::shared_ptr<boost::asio::io_service::work> work;//계속해서 기다린다. 비동기 io_service가 들어오기까지
    std::thread worker;

    std::string server,path;
    boost::asio::ip::tcp::resolver resolver;
    boost::asio::ip::tcp::socket socket;

    boost::asio::streambuf requestbuf;
    boost::asio::streambuf responsebuf;

    std::ostringstream oss;

};

#endif // ASIOCLIENT_H
