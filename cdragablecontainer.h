#ifndef CDRAGABLECONTAINER_H
#define CDRAGABLECONTAINER_H

#include <QtGlobal>
#if QT_VERSION < 0x050000
#include <QtGui>
#else
#include <QtWidgets>
#endif

namespace Ui {
class CDragableContainer;
}

//const static QString gDragableContainerMimeType = "qapplication/dragableContainer";
const static QString gDragableContainerMimeType = "随意填写";//可拖动容器类型，这里用于判断是否接受拖动

class CDragableContainer : public QWidget
{
	Q_OBJECT

public:
    explicit CDragableContainer(QWidget *widget);//构建
    ~CDragableContainer();//析构

    inline QWidget* widget() {return _widget;}//返回容器内的控件指针，便于后续处理

signals:
    void movingUp();
    void movingDown();
    void close(QWidget*);

protected:
    bool eventFilter(QObject *object, QEvent *event);//事件过滤

private:
	Ui::CDragableContainer *ui;
    QWidget *_widget;

};

#endif // CDRAGABLECONTAINER_H
