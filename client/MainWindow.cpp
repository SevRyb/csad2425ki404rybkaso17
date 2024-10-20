#include "MainWindow.h"
#include "GameHost.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(500, 150);
    m_rootWidget = new QWidget(this);
    setCentralWidget(m_rootWidget);

    m_rootLay = new QVBoxLayout(m_rootWidget);

    m_sendMsgEdit = new QLineEdit(this);
    m_sendMsgEdit->setPlaceholderText("Message to send");
    m_sendBtn = new QPushButton("Send");
    m_sendBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_recvMsgEdit = new QLineEdit(this);
    m_recvMsgEdit->setPlaceholderText("Received message");
    m_recvMsgEdit->setReadOnly(true);

    m_rootLay->addWidget(m_sendMsgEdit);
    m_rootLay->addWidget(m_sendBtn, 1);
    m_rootLay->addWidget(m_recvMsgEdit);

    g_GameHost::Instance();
    connect(g_GameHost::Instance(), &GameHost::sigMessageRecv, this, &MainWindow::onMessageRecv);
    connect(m_sendBtn, &QPushButton::released, g_GameHost::Instance(),
            [this]()
            {
                g_GameHost::Instance()->reqMessage(m_sendMsgEdit->text());
            });
}

MainWindow::~MainWindow() {}

void MainWindow::onMessageRecv(QString msg)
{
    m_recvMsgEdit->setText(msg);
}
