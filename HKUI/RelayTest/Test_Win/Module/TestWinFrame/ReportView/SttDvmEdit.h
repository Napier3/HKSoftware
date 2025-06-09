#ifndef STTDVMEDIT_H
#define STTDVMEDIT_H

#include <QLineEdit>
#include <QObject>
#include "../../../../Module/DataMngr/DvmData.h"

class QSttDvmEdit : public QLineEdit
{
	Q_OBJECT

public:
	QSttDvmEdit();
	explicit QSttDvmEdit(CDvmData *pData,QWidget *parent = 0);

	QWidget *m_Parent;
	CDvmData *m_pData;

public slots:
	void slot_OnEdited();
};

#endif // STTDVMEDIT_H
