#ifndef QGOOSETABLE_H
#define QGOOSETABLE_H

#include <QTableWidget>
#include <QStandardItemModel>
#include <QHash>

#include "../../../61850/Module/CfgDataMngr/IecCfgGoutDatas.h"

class QGooseTable :public QTableWidget
{
	Q_OBJECT

public:
	QGooseTable(QWidget* pparent);
	~QGooseTable(void);

	void initData();
	void initUI();
	
	void setGooseData(CIecCfgGoutData *pCfgGoutData);
	void setEnableChangedType(bool bEdit);
	void setEnableChangeValue(bool bEdit);

	void enablechangedsignal(bool bchanged);

private:
	CIecCfgGoutData *m_pData;

protected:
	QString getDataType(QString strDataType);
	QString getDataValue(CIecCfgGoutCh* pChannel);
	void InsertDataAtom(CIecCfgDataChBase* pChannel,int nIndex);
	void InsertDataAtomByIndex(CIecCfgDataChBase* pChanel,int nIndex,int nRow);

	void reverseValue(int nrow,int ncol);
	void chanelTypeChanged(int nrow,int ncol);
	void initDataHash();
	QStandardItemModel *m_chanModel;
	QHash<int, int> m_rowChannelHash; //将表的行与通道索引进行配对
	QHash<int,CIecCfgDataChBase*> m_rowdata;

protected slots:
	void OnChanDataChanged( QTableWidgetItem * current);
	void on_cellChanged(int nrow,int ncol);
	void on_updateData();

signals:
	void sigUpdateData();
	void sigdatachanged();
};

#endif