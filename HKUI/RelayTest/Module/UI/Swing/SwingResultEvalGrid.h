#ifndef QSWINGRESULTEVALGRID_H
#define QSWINGRESULTEVALGRID_H

#include <QTableWidget>
#include "../../UI/Interface/SttMacroParaEditViewOriginal.h"

class QSwingResultEvalGrid : public QTableWidget
{
    Q_OBJECT
public:
    QSwingResultEvalGrid(QWidget *parent);
    virtual ~QSwingResultEvalGrid();

    bool m_bRunning;
    bool eventFilter(QObject *obj, QEvent *event);
    virtual void mousePressEvent(QMouseEvent *);
    bool IsSettingAttach(QTableWidgetItem *pItem);
};

#endif // QSWINGRESULTEVALGRID_H
