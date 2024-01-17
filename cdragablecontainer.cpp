#include "cdragablecontainer.h"
#include "ui_cdragablecontainer.h"

//构建
CDragableContainer::CDragableContainer(QWidget *widget) :
	QWidget(0),
	ui(new Ui::CDragableContainer),
	_widget(widget)
{
	ui->setupUi(this);
    ui->horizontalLayout->insertWidget(0, widget);
    ui->horizontalLayout->setStretch(0, 10);
    ui->horizontalLayout->setStretch(1, 0);

    //因为QWidget设置的Cursor会应用至内部全体控件，这里需要手动全部设置回鼠标指针
    ui->tbnUp->setCursor(Qt::ArrowCursor);
    ui->tbnDown->setCursor(Qt::ArrowCursor);
    ui->tbnClose->setCursor(Qt::ArrowCursor);
    widget->setCursor(Qt::ArrowCursor);

    connect(ui->tbnUp, SIGNAL(clicked()), this, SIGNAL(movingUp()));
    connect(ui->tbnDown, SIGNAL(clicked()), this, SIGNAL(movingDown()));
    connect(ui->tbnClose, &QPushButton::clicked, this, [=]{
        emit close(this);
    });

    this->installEventFilter(this);
}

//析构
CDragableContainer::~CDragableContainer()
{
	delete ui;
}

//事件过滤
bool CDragableContainer::eventFilter(QObject *object, QEvent *event)
{
    Q_UNUSED(object);

    if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if(mouseEvent->button() == Qt::LeftButton)
        {
            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;

            const QByteArray data(QString::number((quintptr)this).toLatin1());
            mimeData->setData(gDragableContainerMimeType, data);
            drag->setMimeData(mimeData);
            drag->exec();
        }
    }

	return false;
}
