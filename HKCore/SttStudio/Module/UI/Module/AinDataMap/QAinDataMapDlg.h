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
	BOOL IsMapValid();  //ӳ���Ƿ���Ч
	CDvmData* IsMapRepeat(const CString &strID, const CString &strDsPath);  //���ӳ���Ƿ��ظ�

private:
	QAinDataMapGrid *m_pAinDataMapGrid;//ͨ��ӳ����
	QAinDataMapDataSetGrid *m_pAinDataSetGrid;

	CDvmDevice *m_pDvmDevice;  //ģ���ļ�
	CExBaseList m_oListDatasets;  //ɸѡ���ĸ�ң����ص����ݼ�����ʱ������ҪRemoveAll
	CDataGroup *m_pAinDataMapCfg;  //ң�����ӳ��
	CDataGroup *m_pAinRatios;  //ң����������Ϣ

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
