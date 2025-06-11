#ifndef QSttFAParasSetWidget_H
#define QSttFAParasSetWidget_H


#include <QWidget>
#include "../../../Module/DataMngr/DataGroup.h"


namespace Ui{
	class QSttFAParasSetWidget;
}

class QSttFAParasSetWidget : public QWidget
{
	Q_OBJECT

public:
	Ui::QSttFAParasSetWidget *ui;

	QSttFAParasSetWidget(QWidget *parent = NULL);
	virtual ~QSttFAParasSetWidget();
	void InitUI();
	void InitData(CDataGroup *pParas);
	void InitIntervalListDatas();
	void SetFAParasFont();
	void InitConnections();
	QStringList m_pOutputItem;
	QStringList m_pSignalItem;
	void UpdateOpenCloseCombox(QComboBox* pCombox, const QStringList& pItems, const QString& strText);
	void SaveData();	
	void SaveBoutDataValue(CString strText, const CString& strDinValue);
	void SaveBinDataValue(CString strText, const CString& strValue);
	void DeleteIntervalListDatas();

protected:
	CDataGroup *m_pParas;
	//CExBaseList m_IntervalList;         //间隔选择
	BOOL m_bRemoteMonitor;//判断是否开环闭环

public slots:
	void slot_m_editErrorTime();
	void slot_m_editxTime();
	void slot_m_edityTime();
	void slot_m_editzTime();
	void slot_m_editxlTime();
	void slot_m_editsTime();
	void slot_m_editx2Time();

	void slot_m_editVol();//残压定值
	void slot_m_editFaultCur();//故障电流
	void slot_m_editFaultHoldTime();//故障电流持续时间

	//void slot_InterSelectIndexChanged(int nIndex);
	void slot_TermCloseOutputIndexChanged(int index); 
	void slot_TermOpenOutputIndexChanged(int index); 
	void slot_TermCloseSignalIndexChanged(int index);
	void slot_TermQuantileSignalIndexChanged(int index);

};

#endif
