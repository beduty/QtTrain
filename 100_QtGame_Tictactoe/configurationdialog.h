#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>

namespace Ui {
class ConfigurationDialog;
}

class ConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationDialog(QWidget *parent = nullptr);
    ~ConfigurationDialog();

private:
    Ui::ConfigurationDialog *ui;

private slots:
    void updateOKButtonState();

public:
    void setPlayer1Name(const QString &p1name);
    void setPlayer2Name(const QString &p2name);
    QString player1Name() const;
    QString player2Name() const;
};

#endif // CONFIGURATIONDIALOG_H
