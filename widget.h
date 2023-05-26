#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include <QPointF>
#include <QRectF>
#include <QPainter>

//1.按键处理
//2.使用定时器
// 2.1 关联信号槽 2.2启动定时器 2.3实现对应的超时处理函数
//3.渲染
//4.蛇的表示，长度可变的数组


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


//定义一个变量表示方向,定义在里面或外面都行
enum Director{

    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN

};


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    int moveFlag=DIR_UP;
    bool gameStart=false;

    //定时器
    QTimer *timer;

    int time=100;//超时时间间隔

    void addTop();
    void addDown();
    void addLeft();
    void addRight();

    void deleteLast();//删除最后一个

    //添加奖品
    void addNewReword();

    //
    void collide();

    //蛇头碰蛇身
    bool checkContact();


    //蛇，由小方块组成
    QList <QRectF> snake;
    //奖品
    QRectF rewardNode;

    //小方块的大小
    int nodeWidth=20;
    int nodeHeight=20;

    //绘画
    //void paintEvent(QPainter *event);

protected:
    void    paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;




public slots:
     void timeout();






//按键事件
protected:
    void keyPressEvent(QKeyEvent *event);


private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
