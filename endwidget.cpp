#include "endwidget.h"
#include "ui_endwidget.h"
#include "startpage.h"
#include <QString>
#include <QFont>

endWidget::endWidget(QWidget *parent, int winplayer) :
    QMainWindow(parent),
    ui(new Ui::endWidget)
{
    // 导入ui配置元素内容
    ui->setupUi(this);

    // 设置窗口界面
    this->setWindowTitle("游戏结束");
    this->setFixedSize(800, 450);

    // 设置label上的内容
    QString str;

    // 根据游戏的胜利方法改变label上的内容
    if(winplayer == 0){
        str = "两玩家打成平手";
    }
    else if(winplayer == 1){
        str = "先手玩家获胜";
    }
    else if(winplayer == 2){
        str = "后手玩家获胜";
    }

    // 设置页面的字体
    QFont font;
    font.setFamily("黑体");           //字体
    font.setPointSize(25);           //文字大小
    font.setWeight(QFont::Bold);     //加粗

    ui->endlabel->setFont(font);

    // 将文字导入label中
    ui->endlabel->setText(str);

    // 设置文字居中
    ui->endlabel->setAlignment(Qt::AlignCenter);

    // 设置图片背景透明度
    this->setWindowOpacity(0.9);

    // 设置图片背景
    QPalette pal = this->palette();
    if(winplayer){
        pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image/winbackground.jpg").scaled(800, 450)));
    }
    else{
        pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image/tiebackground.png").scaled(800, 450)));
    }
    this->setPalette(pal);

    // 设置快捷键与默认选中(默认选中开始游戏):空格是开启游戏的快捷键，Esc是结束游戏的快捷键
    ui->restartbutton->setDefault(true);
    ui->restartbutton->setShortcut(Qt::Key_Return);
    ui->closebutton->setShortcut(QKeySequence(tr("Esc")));

    // 设置信号槽功能
    // 点击重新开始按钮，回到起始页面
    connect(ui->restartbutton,
            &QPushButton::clicked,
            this,
            [=](){
        StartPage * newPage = new StartPage;
        newPage->setAttribute(Qt::WA_DeleteOnClose);
        newPage->show();
        this->close();
    });
    // 点击退出按钮，直接退出页面
    connect(ui->closebutton,
            &QPushButton::clicked,
            this,
            [=](){
        this->close();
    });
}

endWidget::~endWidget()
{
    delete ui;
}
