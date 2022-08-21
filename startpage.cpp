#include "startpage.h"
#include "ui_startpage.h"
#include "gamewindow.h"
#include <QPalette>
#include <QProxyStyle>

StartPage::StartPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartPage)
{
    // 导入ui配置元素内容
    ui->setupUi(this);

    // 设置起始界面风格
    this->setWindowTitle("gobang井字棋");
    this->setFixedSize(600, 800);
    this->setStyle(new QProxyStyle);

    // 设置图片背景透明度
    this->setWindowOpacity(0.9);

    // 设置图片背景
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image/startpagebackground.jpg").scaled(600, 800)));
    this->setPalette(pal);

    // 设置快捷键与默认选中(默认选中开始游戏):空格是开启游戏的快捷键，Esc是结束游戏的快捷键
    ui->startbutton->setDefault(true);
    ui->startbutton->setShortcut(Qt::Key_Return);
    ui->exitbutton->setShortcut(QKeySequence(tr("Esc")));

    // 设置信号槽功能
    // 开始游戏，创建新的游戏页面
    connect(ui->startbutton,&QPushButton::clicked,this,[=](){
        GameWindow* gamewindow = new GameWindow;
        gamewindow->setAttribute(Qt::WA_DeleteOnClose);
        gamewindow->show();
        this->close();
    });
    // 关闭当前页面
    connect(ui->exitbutton,&QPushButton::clicked,this,[=](){
        this->close();
    });
}

StartPage::~StartPage()
{
    delete ui;
}

