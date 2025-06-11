#ifndef QSttMacroParaEditViewTURecloseAccWidget_H
#define QSttMacroParaEditViewTURecloseAccWidget_H
#include "../Controls/SttCheckBox.h"
#include "../Interface/SttMacroParaEditViewOriginal.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>


class QSttMacroParaEditViewTURecloseAccWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	explicit QSttMacroParaEditViewTURecloseAccWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewTURecloseAccWidget();

	void InitUI();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_TURecloseAccTest; }
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);//dingxy 20241120 切换模板获取数据
	void SaveParasXml();
	//void GetCheckBoxValue(QSttCheckBox * pCheckBox,const CString strID);
	void GetLineEditValue(CDataGroup *pParas,QLineEdit * pLineEdit,const CString strID);
	void setGroupBoxEnabled(QGroupBox *pGroupBox, bool enabled);
	void GetComboxValue(CDataGroup *pParas,QComboBox *pComboBox,const CString strID);

	QSttCheckBox* FindCheckBoxByID(const QList<QSttCheckBox*>& checkBoxList, const CString& strID);
	void GetGroupBoxCheckable( CDataGroup *pParas,QGroupBox * pGroupBox,CString strID);
	void OpenBinBoutMapXml();
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);
	void UpdateDataValue( CDataGroup *pParas,const CString &strID1,const CString &strID2);
	CString  UpdateDataValue(const CString &strID);
	virtual BOOL GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem);

private:
	CDataGroup m_pTURecloseAccDataGroup;
	QPushButton *m_pEstimateBtn;
	//QLineEdit *m_pOutPutTimeEdit;
	//QList<QSttCheckBox*> m_pAllCheckBoxList;
	QList<QLineEdit *> m_pAllLineEditList;
	QList<QGroupBox *> m_pGroupBoxList;

	QComboBox *m_pRecAccCombox; //过流重合闸投入区段
	QComboBox *m_pZeroAccCombox;//零序重合闸投入区段


protected slots:
	void slot_Estimate();
	//void slot_CheckBoxStateChanged(int);
	void slot_LineEditFinished();
	void slot_GroupBoxtoggled(bool);
	void slot_ComboBoxChanged(int index);

};


class QTURecloseAccEstimateDlg : public QDialog
{
	Q_OBJECT

public:
	explicit QTURecloseAccEstimateDlg(CDataGroup* pParas, QWidget* parent = NULL);
	virtual ~QTURecloseAccEstimateDlg();

public:
	void InitUI();	
	void GetLineEditValue( QLineEdit * pLineEdit,const CString strID );
	CDataGroup* m_pParas;
	QSttLineEdit *m_pTtripDLineEdit;
	QSttLineEdit *m_pTtripAccLineEdit;
	QSttLineEdit *m_pTtripLineEdit;


protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
	void slot_TtripDEditFinished();
	void slot_TtripAccEditFinished();
	void slot_TtripEditFinished();
};

#endif