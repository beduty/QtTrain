#include "wxmultifiledownload.h"
#include <QApplication>

/// Qt에서 네트워크를 사용하는 가장 쉬운방법은 QNetworkAccessManager이다!
/// 프로그램과 인터넷을 연결 시켜주는 가장 빠르고 간단한 방법이다!
/// 비동기로 동작하기 때문에 데이터 다운받는 중에도 Block되는 것 없이 GUI는 잘 돌아간다>!
/// 하지만 여러 요청을 한번에 했을 때는??
///     문제가 발생하는 것은 Finished signal이 여러번 들어오므로 이에 대한 slot을 여러개 만들어줘야 한다.
///     --> 115번 예제를 참조하시오!

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WxMultiFileDownload w;
    w.show();
    return a.exec();
}
