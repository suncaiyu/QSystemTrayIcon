#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&clickTimer, SIGNAL(timeout()), this, SLOT(slotTimerTimeOut()));
    hideIcon = new QSystemTrayIcon();
    hideIcon->setIcon(QIcon(":/Pic/2.jpg"));
    myMenu = new QMenu();
    quit = new QAction();
    showWindow = new QAction();
    showWindow->setIcon(QIcon(":/Pic/22.jpg"));
    quit->setIcon(QIcon(":/Pic/222.jpg"));
    showWindow->setText(QString::fromLocal8Bit("显示"));
    quit->setText(QStringLiteral("退出"));
    myMenu->addAction(showWindow);
    myMenu->addAction(quit);
    hideIcon->setContextMenu(myMenu);
    connect(showWindow, SIGNAL(triggered()), this, SLOT(slotShow()));
    connect(quit, SIGNAL(triggered()), this, SLOT(close()));
    connect(hideIcon,
            SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,
            SLOT(slotActivated(QSystemTrayIcon::ActivationReason)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    clickTimer.start(250);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    clickTimer.stop();
    qDebug() << "double click";
}

void MainWindow::slotTimerTimeOut()
{
    clickTimer.stop();
    qDebug() << "click";
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_Q) {
        this->hide();
        hideIcon->show();
        hideIcon->showMessage(QStringLiteral("提示信息"),
                              QStringLiteral("已隐藏到系统托盘!"),
                              QSystemTrayIcon::Information,
                              3000);
    }
}

void MainWindow::slotShow()
{
    this->show();
    hideIcon->hide();
}

void MainWindow::slotActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        this->show();
        hideIcon->hide();
        break;
    default:
        break;
    }
}
