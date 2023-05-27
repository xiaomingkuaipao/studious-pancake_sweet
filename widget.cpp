#include "widget.h"
#include "ui_widget.h"

#include <QPixmap>

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    qDebug()<<"远程库你好"<<endl;

    timer=new QTimer();
    //定时器有一个超时信号，timeout()信号
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));


    //初始化蛇身
    QRectF rect(300,250,nodeWidth,nodeHeight);
    snake.append(rect);
    addTop();
    addTop();

    //初始化奖品
    addNewReword();


}

Widget::~Widget()
{
    delete ui;
}

void Widget::addTop()
{
    QPointF leftTop;
    QPointF rightBotom;

    if(snake[0].y()-nodeHeight<0)
    {
        leftTop=QPointF(snake[0].x(),this->height()-nodeHeight);
        rightBotom=QPointF(snake[0].x()+nodeWidth,this->height());
    }
    else{

    leftTop=QPointF(snake[0].x(),snake[0].y()-nodeHeight);
    rightBotom=snake[0].topRight();

    }

    snake.insert(0,QRectF(leftTop,rightBotom));

}

void Widget::addDown()
{
    QPointF leftTop;
    QPointF rightBotom;

    if(snake[0].y()+nodeHeight*2>this->height())
    {
        leftTop=QPointF(snake[0].x(),0);
        rightBotom=QPointF(snake[0].x()+nodeWidth,nodeHeight);
    }
    else{

    leftTop=snake[0].bottomLeft();
    rightBotom=snake[0].bottomRight()+QPointF(0,nodeHeight);

    }

    snake.insert(0,QRectF(leftTop,rightBotom));





}

void Widget::addLeft()
{
    QPointF leftTop;
    QPointF rightBotom;

    if(snake[0].x()-nodeWidth<0)
    {
        leftTop=QPointF(this->width()-nodeWidth,snake[0].y());

    }
    else{

    leftTop=snake[0].topLeft()-QPointF(nodeWidth,0);



    }
    rightBotom=leftTop+QPointF(nodeWidth,nodeHeight);

    snake.insert(0,QRectF(leftTop,rightBotom));

}

void Widget::addRight()
{
    QPointF leftTop;
    QPointF rightBotom;

    if(snake[0].x()+nodeWidth*2>this->width())
    {
        leftTop=QPointF(0,snake[0].y());

    }
    else{

    leftTop=snake[0].topRight();



    }
    rightBotom=leftTop+QPointF(nodeWidth,nodeHeight);

    snake.insert(0,QRectF(leftTop,rightBotom));

}

void Widget::deleteLast()
{
    snake.removeLast();

}

void Widget::addNewReword()
{
    rewardNode=QRect(qrand()%(this->width()/20)*20,qrand()%(this->height()/20)*20,nodeWidth,nodeHeight);

}

void Widget::collide()
{
//    if(snake[0].topLeft()==rewardNode)
    //    addTop();
}

bool Widget::checkContact()
{
    for(int i=0;i<snake.length();i++){

    for(int j=i+1;j<snake.length();j++)
    {
        if(snake[i]==snake[j])
        {
            return true;
        }
    }

    }
    return false;

}

void Widget::paintEvent(QPaintEvent *event)
{
    //背景图片


        QPainter painter(this);

        QPixmap pix;

        painter.drawPixmap(rect(),QPixmap(":/image/image/snake.jpg"));

        //画蛇
        QPen pen;
        pen.setColor(Qt::black);
        QBrush brush;
        brush.setColor(Qt::darkMagenta);
        brush.setStyle(Qt::SolidPattern);

        painter.setPen(pen);
        painter.setBrush(brush);



        for(int i=0;i<snake.length();i++)
        {
            painter.drawRect(snake[i]);
        }

        //画奖品

        pen.setColor(Qt::red);

        brush.setColor(Qt::red);
        brush.setStyle(Qt::SolidPattern);

        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawEllipse(rewardNode);


        if(checkContact())
        {
            QFont font("方正舒体",30,QFont::ExtraLight,false);
            painter.setFont(font);
            painter.drawText((this->width()-300)/2,(this->height()-30)/2,QString("GAME OVER"));

            timer->stop();


        }

}


void Widget::timeout()
{
    int count=1;
    //判断有没有相交或重合
    if(snake[0].intersects(rewardNode))//相交
    {
        count++;
        addNewReword();


    }

    //while(0)就是一次都不执行循环，while(1)就是一直执行循环
    while(count--)
    {
    switch (moveFlag) {
    case DIR_UP:
       //在顶部加一个小方块
        addTop();
        break;
    case DIR_DOWN:
        addDown();
        break;
    case DIR_LEFT:
        addLeft();

        break;
    case DIR_RIGHT:
        addRight();

        break;


    default:
        break;
    }
}
    deleteLast();
    update();
}

//控制方向
void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        if(moveFlag!=DIR_DOWN)
        {
           moveFlag=DIR_UP;

        }

        break;
    case Qt::Key_Down:
        if(moveFlag!=DIR_UP)
        {
          moveFlag=DIR_DOWN;
        }
        break;
    case Qt::Key_Left:
        if(moveFlag!=DIR_RIGHT)
        {
          moveFlag=DIR_LEFT;
        }
        break;
    case Qt::Key_Right:
        if(moveFlag!=DIR_LEFT)
        {
          moveFlag=DIR_RIGHT;
        }
        break;
    case Qt::Key_Space:
        if(gameStart==false)
        {

           gameStart=true;
           //启动定时器
           timer->start(100);
        }
        else{

            gameStart=false;

            timer->stop();
        }


        break;

    default:
        break;
    }
}

