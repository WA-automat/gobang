#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class StartPage; }
QT_END_NAMESPACE

class StartPage : public QMainWindow
{
    Q_OBJECT

public:
    StartPage(QWidget *parent = nullptr);
    ~StartPage();

private:
    Ui::StartPage *ui;
};
#endif // STARTPAGE_H
