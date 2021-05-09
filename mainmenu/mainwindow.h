#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginwindow.h"
#include "register.h"
#include "changepassword.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    LoginWindow *loginwindow;
    Register *registerwindow;
    ChangePassword *changepasswordwindow;

private slots:
    void on_LogInButton_clicked();



    void on_RegisterButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_ChangePasswordPushButton_clicked();

private:
    Ui::MainWindow *ui;
    const QString Logo=":/Logo/Logo/TypeMaster.jpg";
    void paintEvent(QPaintEvent *);    //绘图事件
    void keyPressEvent(QKeyEvent *event);
    const int WindowX = 1200;
    const int WindowY = 800;
    void iSlot(QString GetData);
};

#endif // MAINWINDOW_H
