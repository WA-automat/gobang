#ifndef ENDWIDGET_H
#define ENDWIDGET_H

#include <QMainWindow>

namespace Ui {
class endWidget;
}

class endWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit endWidget(QWidget *parent = nullptr, int winplayer = 0);
    ~endWidget();

private:
    Ui::endWidget *ui;
};

#endif // ENDWIDGET_H
