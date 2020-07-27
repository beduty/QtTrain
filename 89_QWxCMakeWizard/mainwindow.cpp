#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->flagsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->flagsTable->horizontalHeader()->setStretchLastSection(true);

    ui->sourcesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->sourcesTable->horizontalHeader()->setStretchLastSection(true);

    //connect(&sender, SIGNAL, &receiver, SLOT)
    QObject::connect(ui->tabWidget,SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertFlagItem(QString &key, QString &value)
{
    int nRow = ui->flagsTable->rowCount();
    ui->flagsTable->insertRow(nRow);

    auto keyColumn = new QTableWidgetItem(key);
    auto valueColumn = new QTableWidgetItem(value);
    ui->flagsTable->setItem(nRow,0, keyColumn);
    ui->flagsTable->setItem(nRow,1, valueColumn);
}

void MainWindow::insertNewIncludeDirectory(const QString &path)
{
    QListWidgetItem* newItem = new QListWidgetItem(path);
    newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);

    ui->IncludeList->addItem(newItem);
}

void MainWindow::addSource(const QString &target, const QString & sources)
{
    int nRow = ui->sourcesTable->rowCount();
    ui->sourcesTable->insertRow(nRow);

    auto targetColumn = new QTableWidgetItem(target);
    auto sourcesColumn = new QTableWidgetItem(sources);

    ui->sourcesTable->setItem(nRow, 0, targetColumn);
    ui->sourcesTable->setItem(nRow, 1, sourcesColumn);
}


void MainWindow::on_actionExport_triggered()
{
    // Export Action이 클릭되면(Trigger) 수행할 내용정의(Signal-> Slot)

    //    // ProjectTab의 LineEdit 값을 읽어온다.
    //    qDebug()<< "Export Action(Button) Triggered!(Clicked)";

    //    QString projectName = ui->projectNameEdit->text();
    //    qDebug()<< "Project Name : " + projectName;

    QString selDir = QFileDialog::getExistingDirectory(this,"Directory to save", QDir::currentPath(),QFileDialog::ShowDirsOnly);
    if(selDir.length() == 0 ){
        QMessageBox::critical(this, "Failed to get Dir", "Failed to get SaveDirectory", QMessageBox::Ok);
        return;
    }

    auto filePath = QDir(selDir).filePath("CMakeLists.txt"); // 얻어온 폴더 경로를 바탕으로 File경로 만들기 쉽다.
    QFile file(filePath);
    if(false == file.open(QIODevice::WriteOnly|QIODevice::Text))
        return;

    QTextStream stream(&file); // Stream에 텍스트 입력하면  File에다가  쓴다!

    prepareCMakeListsVariables();
    stream<< cmakeListResult<<endl;
    file.close();
}

void MainWindow::on_flagsAddBtn_clicked()
{
    QString key = "<key>";
    QString value = "<value>";
    insertFlagItem(key, value);
}

void MainWindow::on_flagsRemoveBtn_clicked()
{
    int nRow = ui->flagsTable->currentRow(); // 현재 선택되어 있는 Row
    ui->flagsTable->removeRow(nRow);
}

void MainWindow::on_addSourceBtn_clicked()
{
    addSource("<Target>", "main.cpp");
}

void MainWindow::on_removeSourceBtn_clicked()
{
    ui->sourcesTable->removeRow(ui->sourcesTable->currentRow());
}

void MainWindow::currentTabChanged(int index)
{
    qDebug()<< "Current Tab : " << index ;

    // preview tab selected 되면, 다른 탭들의 UI 객체들의 값을 받아와서
    // PreviewTab의 Plain Text Edit 위젯에 입력한다.
    if(index == 4){
        //ui->previewEdit
        prepareCMakeListsVariables();
    }
}

void MainWindow::prepareCMakeListsVariables()
{
    CMakeLists cmakeLists;

    // 0. project Tab
    QString projectName = ui->projectNameEdit->text();
    cmakeLists.setProjectName(projectName);

    // 1. flags Tab
    auto flagsCount = ui->flagsTable->rowCount();
    for (int row= 0 ; row < flagsCount; row ++)
    {
        auto keyItem = ui->flagsTable->item(row, 0);
        auto valueItem = ui->flagsTable->item(row, 1);

        // QString, QString형태로 받아오려면,
        QString flagKey = keyItem->text();
        QString flagValue = valueItem->text();
        cmakeLists.addCMakeFlags(flagKey,flagValue);
    }

    // 2. preprocessor Tab
    // PlainTextEdit Widget의 내용을 한번에 읽어올 수 있다. toPlainText
    if(ui->definesEdit->toPlainText().size() > 0){
        QStringList defines = ui->definesEdit->toPlainText().split(QRegExp("\\ |\\;|\\n")); // 공백, 세미콜론, 개행문자로 쪼개서, QStringList에 넣는다.
        for(int index = 0; index < defines.length(); index++){
            qDebug()<<defines.at(index)<<endl;
            cmakeLists.addDefine(defines.at(index));
        }
    }

    // 3. directory Tab
    //   1) Include Dir(QListWidget)
    for(int row = 0; row < ui->IncludeList->count(); row++){
        auto item = ui->IncludeList->item(row); // QListWidtgetItem
        QString includeDir = item->text();
        cmakeLists.addIncludeDirectory(includeDir);
    }
    //   2) Sources(QTableWidget)
    for(int row = 0; row<ui->sourcesTable->rowCount(); row++){
        auto target = ui->sourcesTable->item(row,0);
        auto sources = ui->sourcesTable->item(row,1);
        // target , sources files 얻어온다.
        cmakeLists.addSource(target->text(), sources->text());
    }

    // 4. preview Tab
    QString previewCmakeList_txt = cmakeLists.GenerateCMakeLists();
    ui->previewEdit->clear();
    ui->previewEdit->appendPlainText(previewCmakeList_txt);

    cmakeListResult = previewCmakeList_txt;
}

void MainWindow::on_addIncludeBtn_clicked()
{
    insertNewIncludeDirectory("<path>");
}

void MainWindow::on_IncludeList_itemChanged(QListWidgetItem *item)
{
    if(item->text().length() == 0)
        ui->IncludeList->takeItem(ui->IncludeList->row(item)); // takeItem은 Remove이다.
}



































