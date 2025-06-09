#ifndef QSttCommCfgPointTblFileEditorDlg_H
#define  QSttCommCfgPointTblFileEditorDlg_H
#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>
#include <QTimerEvent>
#include <QLineEdit>
#include "SttPointTblEdtTabIntervalSetGrid.h"
#include "SttPointTblEdtTabTeleParaCommGrid.h"
#include "../../../../../../Module/DataMngr/DvmDevice.h"
#include "../../../Controls/SttLineEdit.h"
#include "../../ScrollCtrl/ScrollComboBox.h"


#define QSTTCOMMCFGPOINTTB_MAX_TABS 16

class GeneralTab : public QWidget
{
	Q_OBJECT

public:
	explicit GeneralTab(QWidget *parent = 0);
	virtual ~GeneralTab();
	void AddDatasetCols(CDvmDataset* pDataset);

	QTabWidget *m_pTeleGridTabWight;

	QWidget * mpParentDlg;

	public slots:
		//void slot_RightTeleParaSetChanged();    //间隔数Combo选择槽函数
};


class QSttCommCfgPointTblFileEditorDlg : public QDialog
{
	Q_OBJECT

public:
	QSttCommCfgPointTblFileEditorDlg(CString strFullPath,QWidget *parent = 0);
	virtual ~QSttCommCfgPointTblFileEditorDlg();

	void initUI();
	void SetDialogFont();
	void ReleaseUI();
	void InitDatas();
	void CalcColums();
	void SaveDvmXmlFile();
	BOOL SaveXmlFile();
	void Append_IntervalSetTab();
	void Append_TeleMeasureTab();
	void Insert_IntervalSetTab();
	void Insert_TeleMeasureTab();
	void SearchDatasetInOtherTab(CString strLdID,CString strDatasetID,	QList<CDvmData*>& pDataCpSrc);
	void CopyToDataListUnExistInApplyAll(CDvmDataset* pDatasetChk,QList<CDvmData*>& pDataCpSrc);
	void SetStartAddrAllTeleTabs();
	void RefreshAllTeleTabs();
	void SyncAddrToInvalSetTable(CString strLdID,CString strDatasetID,long nArgAddr);
	void DeleleIntervalSetTableMultiRow(int nDelNum);
	void ModifyIdxInIntervalSetCombo();
	void UpdateIntervalGrid(int nIndex);//chenling20240301 保存文件后更新间隔表格

	void ProcessOverMaxExtraTabs();
	CString GetLinuxPathAtImportAddrClicked();
	CString GetLinuxPathAtExportAddrClicked(CString strDefFileNm);
	void DeleteDvmDeviceByName(CString strName);
	CDvmLogicDevice* FindDvmDeviceByName(CString strName);
	//单独修改首地址  同步到首地址表中 yuanting
	void EditChangedAdress(QString strtabName,int nChildTabIndex,QString strValue); 

	CString m_pCrtPointTbFullPath;        //当前编辑的点表文件全路径
	CDvmDevice *m_pDvmDevice;             //点表文件解析xml对象

	SttCPointTblEdtTabIntervalSetGrid* m_pIntervalSetGrid;  //间隔表

	QTabWidget *m_pTabWidget;                     //当前使用的Tab控件

	QPushButton *m_pImportPointFile_PushButton;	  //导入
	QPushButton *m_pExportPointFile_PushButton;	  //导出
	QPushButton *m_pSavePointFile_PushButton;	  //保存	
	QPushButton *m_pInsertPointFile_PushButton;	  //插入
	QPushButton *m_pDelPointFile_PushButton;	  //删除
	QPushButton *m_pApplyAll_PushButton;	      //应用到全部
	QPushButton *m_pOK_PushButton;	              //确定按钮
	QPushButton *m_pCancel_PushButton;	          //取消按钮
	
	QLabel *m_pLabelIntSetNum;				      //间隔数Label
	QScrollComboBox *m_pIntervalNums_Combo;             //间隔数
	QLabel *m_pLabelStartAddr;				      //起始地址Label
	QSttLineEdit *m_pStartAddr_LineEdit;             //起始地址

	QHash<CString, QStringList *>  m_pIED_Hash;
	
	//开始从文件中读取出来的个数，电表编辑的间隔数。
	int			m_nIntervalNums;

	BOOL m_bApplyAllFlg;//是否间隔参数同步
	
	
public slots:
	void slot_OKClicked();
	void slot_CancelClicked();
	void slot_SaveClicked();
	void slot_Import_Clicked();          //导入槽函数
	void slot_Export_Clicked();          //导出槽函数
	void slot_DelCurrRow_Clicked();      //删除槽函数
	void slot_InsertRow_Clicked();       //插入槽函数
	void slot_AppendRow_Clicked();       //追加槽函数
	void slot_ApplyAll_Clicked();        //应用到全部槽函数
	void slot_CrtChangedTabWidget(int nCurrIndex);        //Tab切换槽函数
	void slot_StartAddrEdit_Finished();                   //起始地址槽函数
	void slot_IntervalSetComboChanged(int nCurrIndex);    //间隔数Combo选择槽函数

	void slot_IntervalSetTableChanged();    //间隔数Combo选择槽函数

	void slot_RightParaSetTableChanged();  
	void slot_RightTeleMearTableChanged(); //间隔数Combo选择槽函数
	
	//首地址修改 同时改变对应tab的地址的值  yuanting
	void slot_ChangedAdress(int nRow,int nCol,QString strValue); 
	
	void slot_ApplyAll(bool bApplyAllFlg);
	
};

#endif // QSttCommCfgPointTblFileEditorDlg_H
