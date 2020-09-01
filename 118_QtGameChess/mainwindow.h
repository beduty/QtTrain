#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "chessview.h"

/// 예제 프로젝트의 구성은 다음과 같다.
/// 1. MainWindow : ChessView를 포함하는 메인 윈도우.
/// 2. ChessView : 체스보드를 디스플레이하는 위젯
/// 3. ChessAlgorithm : 게임 로직을 담당한다.
/// 4. ChessBoard : 체스판 상태를 저장하며, ChessView와 ChessAlgorithm에서는 이 정보를 가지고 작업을 한다.
///
/// ChessAlgorithm에서 ChessBoard를 생성하여, ChessView로 포인터를 넘긴다. 공유한다.

class ChessAlgorithm;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

public slots:
    void viewClicked(const QPoint &field);  // View에서 클릭할 때 보내는 시그널 처리한다.

protected:
    Ui::MainWindow *ui;

private:
    ChessView *m_view;
    ChessAlgorithm *m_algorithm;
    QPoint m_clickPoint;    // View에서 클릭한 위치를 저장한다.
    ChessView::FieldHighlight *m_selectedField; // 선택된 체스판의 타일 위치 정보이다.
};

#endif // MAINWINDOW_H
