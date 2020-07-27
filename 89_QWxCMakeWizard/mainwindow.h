#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
#include "cmakelists.h"


// 셋 중에 아무거나 써주면 된다.
//#include <QListWidgetItem>
//class QListWidgetItem
QT_FORWARD_DECLARE_CLASS(QListWidgetItem);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void insertFlagItem(QString&, QString&);
    void insertNewIncludeDirectory(const QString&);
    void addSource(const QString &, const QString & );
    void prepareCMakeListsVariables();




// 연결된 SLOT은 있는데, Signal이 안보이네..?
// on_ITEMNAME_SIGNAL 로 만들게 되면 알아서 연결된다. (Default 시그널일떄만!)
// connect 없이도 가능하다.
private slots:
    void on_actionExport_triggered();
    void on_flagsAddBtn_clicked();
    void on_flagsRemoveBtn_clicked();
    void on_addIncludeBtn_clicked();
    void on_addSourceBtn_clicked();
    void on_IncludeList_itemChanged(QListWidgetItem *item);
    void on_removeSourceBtn_clicked();

    void currentTabChanged(int index);

private:
    QString cmakeListResult;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
