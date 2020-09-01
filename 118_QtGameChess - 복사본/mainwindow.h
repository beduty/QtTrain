#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chessview.h"
#include "chessboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/// 예제 프로젝트의 구성은 다음과 같다.
/// 1. MainWindow : ChessView를 포함하는 메인 윈도우.
/// 2. ChessView : 체스보드를 디스플레이하는 위젯
/// 3. ChessAlgorithm : 게임 로직을 담당한다.
/// 4. ChessBoard : 체스판 상태를 저장하며, ChessView와 ChessAlgorithm에서는 이 정보를 가지고 작업을 한다.
///
/// ChessAlgorithm에서 ChessBoard를 생성하여, ChessView로 포인터를 넘긴다. 공유한다.
///

class ChessView;
class ChessAlgorithm;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void viewClicked(const QPoint &field);

private:
    Ui::MainWindow *ui;
    QPoint m_clickPoint;
    ChessView *m_view;  /// 체스판과 Column, Rank정보가 그려진다.
    ChessAlgorithm *m_algorithm; /// 체스게임을 시작하고, 보드 정보를 리턴한다.
    ChessView::FieldHighlight *m_selectedField;
    ChessBoard* m_board;
};
#endif // MAINWINDOW_H
