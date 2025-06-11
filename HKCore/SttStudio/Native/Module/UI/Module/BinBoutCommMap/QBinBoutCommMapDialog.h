#ifndef QBINBOUTCOMMMAPDIALOG_H
#define QBINBOUTCOMMMAPDIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include "../../../Module/DataMngr/DataGroup.h"
#include "../ScrollCtrl/ScrollComboBox.h"
#include "../../../Module/BaseClass/QT/ExBaseListComboBox.h"

class QBinBoutCommMapDialog : public QDialog
{
	Q_OBJECT

public:
	QBinBoutCommMapDialog (QWidget* parent = NULL);
	~QBinBoutCommMapDialog();

public:
	void InitUI();
	void GetComboBoxValue(QScrollComboBox* pComboBox,const CString strID,const QStringList& pList = QStringList());
	void UpdateComboBox(QStringList pList,QList<QScrollComboBox*> pComboBoxList,bool bBout);
	void OpenBinBoutMapXml();
	void SaveBinBoutMapXml();
	void InitIntervalListDatas();
	void UpdateData(CDataGroup *pParas);
	void DeleteIntervalListDatas();
	void UpdateBoutData(CExBaseList *pChildList);

protected:
	CDataGroup m_pBinBoutMapDataGroup;
	QMap<QString, QString> m_BinaryValue;
	QList<QScrollComboBox*> m_pBoutComboBoxList;
	QList<QScrollComboBox*> m_pBinComboBoxList;
    QList< QPair<QString, QString> > m_pBoutStringList;
	CDataGroup *m_pBinBoutMapDataCopy;
	CExBaseListComboBox *m_pInterSelect_ComboBox;//间隔选择下拉框
	CExBaseList m_IntervalList;         //间隔选择
	QScrollComboBox *m_pPhaseComboBox;


signals:
	void sig_BinBoutCommMapDataUpdate(CDataGroup *);

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
	void slot_BinComboBoxChanged(int index);
	void Slot_BoutComboBoxChanged(int index);
	void slot_InterSelectIndexChanged(int nIndex);
	void slot_PhaseIndexChanged(int nIndex);
};

#endif
