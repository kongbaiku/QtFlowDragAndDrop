#ifndef CVERTICALCONTAINER_H
#define CVERTICALCONTAINER_H

#include <QtGlobal>
#if QT_VERSION < 0x050000
#include <QtGui>
#else
#include <QtWidgets>
#endif

#include "cdragablecontainer.h"

class CVerticalContainer : public QWidget
{
	Q_OBJECT

public:
    explicit CVerticalContainer(QWidget *parent = 0);//构建
    void appendWidget(QWidget *widget);//新增容器

protected:
    void dragEnterEvent(QDragEnterEvent *event);//拖动进入事件
    void dragMoveEvent(QDragMoveEvent *event);//拖动移动事件
    void dragLeaveEvent(QDragLeaveEvent *event);//拖动离开事件
    void dropEvent(QDropEvent *event);//放置事件

private slots:
    void movingUp();//上移
    void movingDown();//下移
    void removeWidget(QWidget *widget);//移除容器

private:
    QVBoxLayout *_layout;
	QFrame _dropLine;
};

#endif // CVERTICALCONTAINER_H
