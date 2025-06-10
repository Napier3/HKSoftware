#ifndef STTLINEEDIT_H
#define STTLINEEDIT_H

#include <QLineEdit>
#include <QObject>
#include <QMouseEvent>
#include "../Module/CommonCtrl_QT/CommonCtrlInterface.h"

class QSttLineEdit : public QLineEdit,public CCommonCtrlInterface
{
	Q_OBJECT

public:
//	QSttLineEdit();
	explicit QSttLineEdit(QWidget *parent = 0);

	void SetEditFinished()
	{
		emit editingFinished();
	}
	virtual void UpdateText(const QString &strText);
protected:
	virtual void mousePressEvent(QMouseEvent *event);

signals:
	void clicked();
};

#endif // STTLINEEDIT_H
