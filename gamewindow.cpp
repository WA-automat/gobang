#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "endwidget.h"
#include <cstring>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>

#define RELEASE

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow),
    flag(false),
    num(0), _x(), _y(), map()
{
    // 导入ui配置元素内容
    ui->setupUi(this);

    // 初始化坐标与地图
    memset(this->_x, 0, sizeof this->_x);
    memset(this->_y, 0, sizeof this->_y);
    memset(this->map, 0, sizeof this->map);

    // 设置游戏界面窗口
    this->setFixedSize(900, 900);
    this->setWindowTitle("gobang井字棋游戏界面");
    this->setAttribute(Qt::WA_DeleteOnClose);

    // 设置快捷键
    ui->actionclose->setShortcut(QKeySequence(tr("Esc")));
    ui->actionreload->setShortcut(QKeySequence(tr("Ctrl+r")));
    ui->revocation->setShortcut(QKeySequence(tr("Ctrl+z")));

    // 设置信号槽功能
    // 设置重新开始一个游戏进程，功能是关闭当前页面并创建一个新的游戏页面
    connect(ui->actionreload,&QAction::triggered,this,[=](){
        GameWindow* gamewindow = new GameWindow;
        gamewindow->setAttribute(Qt::WA_DeleteOnClose);
        gamewindow->show();
        this->close();
    });
    // 关闭当前页面
    connect(ui->actionclose,&QAction::triggered,this,[=](){
        this->close();
    });
    // 撤回上一步
    connect(ui->revocation,&QAction::triggered,this,[=](){
        if(num){
            --num;
            map[ _x[num] / 300 ][ _y[num] / 300 ] = 0;
            this->update();
        }
        else{
            QMessageBox::warning(this, "警告", "游戏还未开始，无法撤回");
        }
    });
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::paintEvent(QPaintEvent *){
    // 绘制游戏操控界面的绘图对象
    QPainter painter(this);
    // 绘图风格设置
    QPen pen(Qt::black, 1);
    pen.setWidth(5);
    painter.setPen(pen);

    // 绘制井字棋基础场景
    painter.drawLine(300, 0, 300, 900);
    painter.drawLine(600, 0, 600, 900);
    painter.drawLine(0, 300, 900, 300);
    painter.drawLine(0, 600, 900, 600);

    // 当鼠标被点击时，会执行下面的绘图操作
    // 当没有鼠标点击过的时候，num == 0，不会执行下面的循环
    for(int i = 0; i < num; ++i){
        int tmp[2] = { _x[i] / 300, _y[i] / 300};
        if(!(i&1)){
            painter.drawEllipse(tmp[0] * 300 + 50, tmp[1] * 300 + 50, 200, 200);
        }
        else{
            painter.drawLine(tmp[0] * 300 + 50, tmp[1] * 300 + 50, tmp[0] * 300 + 250, tmp[1] * 300 + 250);
            painter.drawLine(tmp[0] * 300 + 250, tmp[1] * 300 + 50, tmp[0] * 300 + 50, tmp[1] * 300 + 250);
        }
        // 测试
#ifdef DEBUG
      qDebug() << flag << ' ' << _x[i] << ' ' << _y[i] << '\n';
#endif
    }
}

void GameWindow::mousePressEvent(QMouseEvent *ev){
    // 将点击时的flag改为true
    // 获取点击时的坐标
    // 其中num存储的是当前已经点击了多少次，并将当前点击时的坐标放入数组中
    this->flag = true;
    this->_x[num] = ev->pos().x();
    this->_y[num] = ev->pos().y();

    // 当点击到已经点击过的区域时，删除这个点击效果
    // 不让num加一就可以完成删除点击的效果
    if(!this->map[ _x[num] / 300 ][ _y[num] / 300 ]){
        map[ _x[num] / 300 ][ _y[num] / 300 ] = (num & 1) + 1;
        ++num;
    }

    // 更新一次界面，使得paintEvent能够被重新调用
    this->update();

    // 游戏结束
    // 判断胜利的一方：
    // 创建一个结束的窗口，询问是否重新玩
    if(num){
        // 判断游戏哪方胜利
        int winPlayer = 0;

        // 判断先手是否胜利
        if(map[0][0] == 1 && map[1][1] == 1 && map[2][2] == 1) winPlayer = 1;
        else if(map[0][0] == 1 && map[0][1] == 1 && map[0][2] == 1) winPlayer = 1;
        else if(map[1][0] == 1 && map[1][1] == 1 && map[1][2] == 1) winPlayer = 1;
        else if(map[2][0] == 1 && map[2][1] == 1 && map[2][2] == 1) winPlayer = 1;
        else if(map[0][0] == 1 && map[1][0] == 1 && map[2][0] == 1) winPlayer = 1;
        else if(map[0][1] == 1 && map[1][1] == 1 && map[2][1] == 1) winPlayer = 1;
        else if(map[0][2] == 1 && map[1][2] == 1 && map[2][2] == 1) winPlayer = 1;
        else if(map[0][2] == 1 && map[1][1] == 1 && map[2][0] == 1) winPlayer = 1;

        // 判断后手是否胜利
        if(map[0][0] == 2 && map[1][1] == 2 && map[2][2] == 2) winPlayer = 2;
        else if(map[0][0] == 2 && map[0][1] == 2 && map[0][2] == 2) winPlayer = 2;
        else if(map[1][0] == 2 && map[1][1] == 2 && map[1][2] == 2) winPlayer = 2;
        else if(map[2][0] == 2 && map[2][1] == 2 && map[2][2] == 2) winPlayer = 2;
        else if(map[0][0] == 2 && map[1][0] == 2 && map[2][0] == 2) winPlayer = 2;
        else if(map[0][1] == 2 && map[1][1] == 2 && map[2][1] == 2) winPlayer = 2;
        else if(map[0][2] == 2 && map[1][2] == 2 && map[2][2] == 2) winPlayer = 2;
        else if(map[0][2] == 2 && map[1][1] == 2 && map[2][0] == 2) winPlayer = 2;

        // 测试
#ifdef DEBUG
        qDebug() << winPlayer << '\n';
#endif
        // 创建新页面并关闭当前页面
        // 新页面内容需要告知胜利方，并询问是否要继续
        // 继续，则返回起始界面
        // 退出，则直接退出全部界面，释放所有内存

        // 有玩家胜利的情况
        if(winPlayer){
            endWidget * newPage = new endWidget(nullptr, winPlayer);
            newPage->setAttribute(Qt::WA_DeleteOnClose);
            newPage->show();
            this->close();
        }
        // 平局情况
        else if(num == 9){
            endWidget * newPage = new endWidget(nullptr, winPlayer);
            newPage->setAttribute(Qt::WA_DeleteOnClose);
            newPage->show();
            this->close();
        }
    }

    // 测试
#ifdef DEBUG
    qDebug() << flag << ' ' << _x[num - 1] << ' ' << _y[num - 1] << '\n';

    qDebug() << num << '\n';
#endif
}

void GameWindow::mouseMoveEvent(QMouseEvent *){
    // 将移动时flag改为false
    // 出现点击后就改为false的效果
    this->flag = false;

    // 测试
#ifdef DEBUG
    qDebug() << flag << ' ' << _x[num - 1] << ' ' << _y[num - 1] << '\n';
#endif
}
