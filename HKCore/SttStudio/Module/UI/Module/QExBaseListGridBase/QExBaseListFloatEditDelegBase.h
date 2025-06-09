#ifndef QExBaseListFloatEditDelegBase_H
#define QExBaseListFloatEditDelegBase_H

#include "QExBaseListGridBase.h"
#include <QItemDelegate>
#include "../CommonCtrl_QT/QFloatLineEdit.h"


//////////////////////////////////////////////////////////////////////////
class QExBaseListFloatEditDelegBase : public QItemDelegate
{
public:
	//����Data�ڵ㣬������Զ���ȡ��ǰ�к��У�������ֵ
	QExBaseListFloatEditDelegBase(QObject *parent=NULL);
	~QExBaseListFloatEditDelegBase();

	void SetEditable(BOOL bEditable = TRUE)       { m_bEditable = bEditable;          }
	void InitCoverage(float fMinValue,float fMaxValue,int nDecimals = 3)
	{
		m_fMinValue = fMinValue;
		m_fMaxValue = fMaxValue;
		m_nDecimals = nDecimals;
	}

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, 
		const QModelIndex &index ) const;

	virtual void setEditorData(QWidget * ditor, const QModelIndex &index) const;

	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
		const QModelIndex &index) const;

private:
	BOOL m_bEditable;//�ܷ��޸�
	float m_fMinValue;
	float m_fMaxValue;
	long m_nDecimals;
};


//////////////////////////////////////////////////////////////////////////

#endif // QIecCfgGout_ComboBoxDelegate_H
