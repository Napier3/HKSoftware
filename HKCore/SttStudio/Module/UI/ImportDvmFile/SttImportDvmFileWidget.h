#ifndef SttImportDvmFileWidget_H
#define SttImportDvmFileWidget_H

#include <QDialog>
#include <QFont>
#include "..\Module\QExBaseListGridBase\QExBaseListGridBase.h"

//lijunqing 2022-9-9
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
#include "SttImportDvmFile_StepGrid.h"
#include "SttImportDvmFile_EditGrid.h"

namespace Ui {
class QSttImportDvmFileWidget;
}

//ͨѶ�����򵼣�������
class QSttImportDvmFileWidget : public QDialog, public CExBaseListGridOptrInterface 
{
    Q_OBJECT
public:
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

public:
    explicit QSttImportDvmFileWidget(QFont font,QWidget *parent = 0);
    virtual ~QSttImportDvmFileWidget();

	QFont m_font;
	CSttItems *m_pItems;  //����ģ�ͺ�19815���ص�Ӧ���Ľṹ
	CSttItems *m_pCurrStep;  //��ǰ����
	CExBaseList *m_pListSort;  //�����������б�
	CSttImportDvmFile_StepGrid *m_pGridStep;  //��ʾ����ı��
	CSttImportDvmFile_EditGrid *m_pGridEdit;  //�༭�����ı��

public:
	virtual void reject();
	virtual void accept();
	void UI_SetFont();
	long InitShow();
	void ShowSetp(CSttItems *pItemsStep);
	void GetCommCmds(CSttItems *pItemsStep, CExBaseList *pListCommCmds);//���ݵ�ǰ���裬���Ҷ�Ӧ�����ͨѶ����
	void SortItems();
	BOOL IsItemsDevReset(const CString &strID);  //�ж��Ƿ��Ǹ���̬
	void GetCmdArray(CStringArray &strCmdArray, CSttItems *pItems); //�ҳ��м������͵�ͨѶ����
	void GetItemName(CString &strName, const CString &strPath, const CString &strCmdKey);  //������Ŀ·�������ҹ���ģ�������
	void InitLanguage();
	
	BOOL IsFirstStep();
	BOOL IsLastStep();
	CSttItems* GetNextStep();
	CSttItems* GetPreStep();

	void NextClick_Finish();
	void UpdateCommCmds();
	BOOL UpdateCommCmd(CSttCommCmd *pCommCmd, CExBaseList *pListDatas);

public slots:
	void slot_PreClick();
	void slot_NextClick();
	void slot_CancelClick();

signals:
	void sig_FreeImportDvmFileWidget();

private slots:

private:
    Ui::QSttImportDvmFileWidget *ui;
};

#endif // SttImportDvmFileWidget_H
