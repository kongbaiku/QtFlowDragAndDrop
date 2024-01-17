#include "cverticalcontainer.h"

//构建
CVerticalContainer::CVerticalContainer(QWidget *parent) :
	QWidget(parent),
    _layout(new QVBoxLayout)
{
    this->setLayout(_layout);
    this->setAcceptDrops(true);

    if(0)//绘制分隔线
    {
        _dropLine.setFrameShape(QFrame::HLine);
        //_dropLine.setLineWidth(5);//线条宽度
        _dropLine.setStyleSheet("border: 5px solid rgb(102, 204, 255);");
    }
    else//绘制分隔框
    {
        _dropLine.setFrameShape(QFrame::Box);
        //_dropLine.setLineWidth(2);//线条宽度
        //_dropLine.setMidLineWidth(2);//中间线宽度
        //_dropLine.setFrameShadow(QFrame::Raised);//阴影效果
        _dropLine.setMinimumSize(20, 40);//需要由最小值撑起空间高度
        _dropLine.setStyleSheet("border-radius: 1px;"
                                "border: 2px dashed rgb(102, 204, 255);");
    }
}

//新增控件
void CVerticalContainer::appendWidget(QWidget *widget)
{
	CDragableContainer *container = new CDragableContainer(widget);
	connect(container, SIGNAL(movingUp()), this, SLOT(movingUp()));
	connect(container, SIGNAL(movingDown()), this, SLOT(movingDown()));
    connect(container, SIGNAL(close(QWidget*)), this, SLOT(removeWidget(QWidget*)));
	_layout->addWidget(container);
}

//移除控件
void CVerticalContainer::removeWidget(QWidget *widget)
{
    _layout->removeWidget(widget);
    delete widget;
}

//拖动进入事件
void CVerticalContainer::dragEnterEvent(QDragEnterEvent *event)
{
	QWidget::dragEnterEvent(event);

    if(event->mimeData()->hasFormat(gDragableContainerMimeType))
        event->accept();
}

//拖动移动事件
void CVerticalContainer::dragMoveEvent(QDragMoveEvent *event)
{
	QWidget::dragMoveEvent(event);

	const int currentLineIndex = _layout->indexOf(&_dropLine);

	QWidget *child = childAt(event->pos());
	while(child && _layout->indexOf(child) == -1)
		child = child->parentWidget();

	if(child)
	{
		int newLineIndex = _layout->indexOf(child);
		if(event->pos().y() > child->pos().y() + (child->height() / 2))
			newLineIndex++;

		if(currentLineIndex != -1
				&& currentLineIndex < newLineIndex)
			newLineIndex--;

		if(newLineIndex != currentLineIndex)
		{
			if(currentLineIndex != -1)
				_layout->removeWidget(&_dropLine);

			_layout->insertWidget(newLineIndex, &_dropLine);
			_dropLine.show();
		}
	}
	event->accept();
}

//拖动离开事件
void CVerticalContainer::dragLeaveEvent(QDragLeaveEvent *event)
{
	QWidget::dragLeaveEvent(event);

	if(QRect(QPoint(), size()).contains(mapFromGlobal(QCursor::pos()), false) == false)	//fix from wrong leave event.
	{
		_layout->removeWidget(&_dropLine);
		_dropLine.hide();
		event->accept();
	}
}

//拖动事件
void CVerticalContainer::dropEvent(QDropEvent *event)
{
	QWidget::dropEvent(event);

	const QByteArray data = event->mimeData()->data(gDragableContainerMimeType);
	CDragableContainer *dragingWidget = (CDragableContainer*)data.toULongLong();
	const int dragingIndex = _layout->indexOf(dragingWidget);
	int newIndex = _layout->indexOf(&_dropLine);
	if(dragingIndex != -1 && dragingIndex != newIndex)
	{
		if(dragingIndex < newIndex)
			newIndex--;
		_layout->removeWidget(dragingWidget);
		_layout->insertWidget(newIndex, dragingWidget);
	}

	_layout->removeWidget(&_dropLine);
	_dropLine.hide();
	event->acceptProposedAction();
	event->accept();
}

//上移
void CVerticalContainer::movingUp()
{
	CDragableContainer *container = static_cast<CDragableContainer*>( QObject::sender() );
	const int index = _layout->indexOf(container);
	if(index < 1)
		QApplication::beep();
	else
	{
		_layout->removeWidget(container);
		_layout->insertWidget(index - 1, container);
	}
}

//下移
void CVerticalContainer::movingDown()
{
	CDragableContainer *container = static_cast<CDragableContainer*>( QObject::sender() );
	const int index = _layout->indexOf(container);
	if(index < 0 || index >= _layout->count() - 1)
		QApplication::beep();
	else
	{
		_layout->removeWidget(container);
		_layout->insertWidget(index + 1, container);
	}
}
