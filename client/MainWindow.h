#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onMessageRecv(QString msg);

private:
    QWidget *m_rootWidget;
    QVBoxLayout *m_rootLay;
    QLineEdit *m_sendMsgEdit;
    QPushButton *m_sendBtn;
    QLineEdit *m_recvMsgEdit;
};
#endif // MAINWINDOW_H
