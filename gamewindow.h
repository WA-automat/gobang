#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();


protected:
    // 绘画事件(通过调用update函数刷新)
    void paintEvent(QPaintEvent *) override;

    // 鼠标点击事件和鼠标移动事件
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *) override;

private:
    Ui::GameWindow *ui;
    // 捕获鼠标是否点击以及点击时光标所在的位置
    // 其中num存储的是当前已经点击了多少次
    // _x[i],_y[i],存储的是第i+1次点击时的坐标
    bool flag;
    int num;
    int _x[9], _y[9];

    // 设定一个 3 * 3 的游戏判断区域
    // 先手玩家设为1，后手玩家设为2
    // 未被占领的区域设为0
    int map[3][3];
};

#endif // GAMEWINDOW_H
