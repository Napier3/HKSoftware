#ifndef QExBaseListFloatEditDelegBase_H
#define QExBaseListFloatEditDelegBase_H

#include "QExBaseListGridBase.h"
#include <QItemDelegate>
#include "../CommonCtrl_QT/QFloatLineEdit.h"


//////////////////////////////////////////////////////////////////////////
class QExBaseListFloatEditDelegBase : public QItemDelegate
{
public:
	//设置Data节点，代理会自动获取当前行和列，并设置值
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
	BOOL m_bEditable;//能否被修改
	float m_fMinValue;
	float m_fMaxValue;
	long m_nDecimals;
};


//////////////////////////////////////////////////////////////////////////

#endif // QIecCfgGout_ComboBoxDelegate_H
