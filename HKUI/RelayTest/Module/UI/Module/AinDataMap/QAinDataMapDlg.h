#ifndef QAINDATAMAPDLG_H
#define QAINDATAMAPDLG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../../../../Module/DataMngr/DvmDataset.h"
#include "../../../../../Module/DataMngr/DvmDevice.h"
#include "../../../../Module/BaseClass/ExBaseList.h"
#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "QAinDataMapGrid.h"
#include "QAinDataMapDatesetGrid.h"


namespace Ui {
class QAinDataMapDlg;
}

class QAinDataMapDlg : public QDialog , public CExBaseListGridOptrInterface
{
    Q_OBJECT

public:
    explicit QAinDataMapDlg(QWidget *parent, CDataGroup *pAinDataMap, CDataGroup *pAinRatios);
    ~QAinDataMapDlg();

public:
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol) ;
	virtual BOOL OnEditCellLBDblClk(QTableWidget *pGridCtrl, int nRow, int nCol, UINT nChar);

public:
	//QAinDataMapGrid* m_p
	void InitUI();
	void InitGridData();
    void InitLanguage();
	void DevMeasComboBox_Init(QComboBox *pComboBox);
	void InitDataSetPath();
	void GetCurrentDsPath(CString &strDsPath);
	CDvmDataset* GetCurrentDataset();
	void EnableBtns();
	void EnableBtns_DevMeas();
	CDataGroup* GetAinDataMap();
	void SetAinDataMap(CDataGroup* pAinDataMap);
	CDataGroup* GetAinRatios();
	void SetAinRatios(CDataGroup* pAinRatios);
	BOOL IsMapValid();  //映射是否有效
	CDvmData* IsMapRepeat(const CString &strID, const CString &strDsPath);  //检查映射是否重复

private:
	QAinDataMapGrid *m_pAinDataMapGrid;//通道映射表格
	QAinDataMapDataSetGrid *m_pAinDataSetGrid;

	CDvmDevice *m_pDvmDevice;  //模型文件
	CExBaseList m_oListDatasets;  //筛选出的跟遥测相关的数据集。临时对象，需要RemoveAll
	CDataGroup *m_pAinDataMapCfg;  //遥测参数映射
	CDataGroup *m_pAinRatios;  //遥测采样变比信息

private slots:

    void on_m_btnAdd_clicked();
    void on_m_btnDelete_clicked();
    void on_m_btnClearAllMap_clicked();
    void on_m_btnClearClickedMap_clicked();
    void on_m_btnOK_clicked();
    void on_m_btnCancel_clicked();
    void on_m_cmbDataSet_currentIndexChanged(int index);
	void on_m_cmbDevMeas_currentIndexChanged(int index);
	void on_m_edtPtPrimary_textChanged(const QString &arg1);
	void on_m_edtPtSecondary_textChanged(const QString &arg1);
	void on_m_edtCtPrimary_textChanged(const QString &arg1);
	void on_m_edtCtSecondary_textChanged(const QString &arg1);

private:
    Ui::QAinDataMapDlg *ui;
};

#endif // QAINDATAMAPDLG_H
