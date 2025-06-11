#include "SwingResultEvalGrid.h"
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>

QSwingResultEvalGrid::QSwingResultEvalGrid(QWidget* parent) :QTableWidget(parent)
{
    m_bRunning = false;
    installEventFilter(this);
}

QSwingResultEvalGrid::~QSwingResultEvalGrid()
{

}

bool QSwingResultEvalGrid::IsSettingAttach(QTableWidgetItem *pItem)
{
    QSettingItem* pSettingItem = dynamic_cast<QSettingItem*>(pItem);
    if (pSettingItem != NULL)
    {
        if (pSettingItem->inherits(STT_SETTING_ITEM_ClassID/*QSettingItem*/))
        {
            if (pSettingItem->IsSetting())
            {
                return true;
            }
        }
    }

    return false;
}

bool QSwingResultEvalGrid::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick)
    {
        QMouseEvent *pMouseEvent = (QMouseEvent *)event;

        //如果定值关联了，单元格应不可编辑
        QPoint clickPosition = pMouseEvent->pos();
        QModelIndex index = indexAt(clickPosition);
        if (index.isValid())
        {
            int row = index.row();
            int column = index.column();
            QTableWidgetItem *pItem = item(row, column);
            if(IsSettingAttach(pItem))
                return QTableWidget::eventFilter(obj, event);
        }

        m_bRunning = true;
        mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
        m_bRunning = false;
        return true;
    }

    return QTableWidget::eventFilter(obj, event);
}

void QSwingResultEvalGrid::mousePressEvent(QMouseEvent * event)
{
    //如果定值关联了,单元格应不可编辑
    QPoint clickPosition = event->pos();
    QModelIndex index = indexAt(clickPosition);
    if (index.isValid())
    {
        int row = index.row();
        int column = index.column();
        QTableWidgetItem *pItem = item(row, column);
        if(IsSettingAttach(pItem))
            return QTableWidget::mousePressEvent(event);
    }

    if (m_bRunning)
    {
        return QTableWidget::mousePressEvent(event);
    }

    QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick, event->pos(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::postEvent(this, pEvent);
    QTableWidget::mousePressEvent(event);
}
