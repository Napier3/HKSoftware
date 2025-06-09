#ifndef STTDVMEDIT_H
#define STTDVMEDIT_H

#include <QLineEdit>
#include <QObject>
#include <QMouseEvent>
#include "../../../../Module/DataMngr/DvmData.h"
#include "SttLineEdit.h"

class QSttDvmEdit : public QSttLineEdit
{
	Q_OBJECT

public:
	QSttDvmEdit();
	explicit QSttDvmEdit(CDvmData *pData,QWidget *parent = 0);

	QWidget *m_Parent;
	CDvmData *m_pData;
protected:
	virtual void mousePressEvent(QMouseEvent *event);

signals:
//	void clicked();

public slots:
	void slot_TextChanged(const QString &text);
	void slot_OnClick();
	void slot_DataEditingFinished();
};

#endif // STTDVMEDIT_H
