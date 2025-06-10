#ifndef QSttExportWordReport_H
#define QSttExportWordReport_H

#include <QDialog>
#include <QFont>
#include <QLabel>
#include "SttGbTreeCtrl_ExportRpt.h"
#include "SttGrid_ExportRpt_Tec.h"
#include "..\..\..\SttCmd\GuideBook\SttGuideBook.h"

namespace Ui {
class QSttExportWordReport;
}

//����word���棬����ǰ�Ա����еġ�����Ҫ�󡱡����������ݱ���С��λ�������б༭������
//������νṹ����ʾģ��ṹ������ʾ�˹�������CSttItems��roonode��CSttItems
//�ұ߱����ʾ���༭�ġ�����Ҫ�󡱺ʹ����õġ��������ݱ���С��λ����
//������νṹ�л�ѡ���ұ߱��ˢ����ʾ
class QSttExportWordReport : public QDialog, public CExBaseListTreeOptrInterface
{
    Q_OBJECT

	virtual void OnItemCheckChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj);
	virtual void OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj);
	virtual BOOL OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj);

public:
    explicit QSttExportWordReport(CSttGuideBook *pGuideBook, QFont font,QWidget *parent = 0);
    virtual ~QSttExportWordReport();

	QSttGbTreeCtrl_ExportRpt *m_pTree_Gb;
	CSttGrid_ExportRpt *m_pGrid_DataDecimal;  //����С��λ�����õı��
	CSttGrid_ExportRpt_Tec *m_pGrid_ItemsTec; //����Ҫ��༭�ı��
	QLabel *m_pCurrSelText;
	QFont m_font;
	CDataGroup *m_pItemsTec;  //����Ҫ��༭
	CSttGuideBook *m_pGuideBook;
	CExBaseObject *m_pCurrSetItems;
	CString *m_pszFilePath;
	CExBaseList m_oListItems;  //�����������Ŀ�б����ڡ���һ�������һ�ʱ����
	CExBaseList m_oDataTypes;  //��¼���м���Ҫ�������������ݣ���Ϊ������������ǿɱ༭���Ƕ�̬�ġ�Ϊ�ˡ���һ�������һ�֮ǰ������

public:
	void Init(CDataGroup *pItemsTec, CString* pszFilePath);
	void InitItemsEnables();
	void InitItemsEnables(CDataGroup *pItemTec, const CString &strMacroUiID);
	void InitItemsTecDataTypes(CDataGroup *pItemTec);
	void UI_SetFont();
    void InitLanguage();
	void InitSttGuideBook(CSttGuideBook *pGuideBook);
	void InitSttGuideBook_Items(CSttItems *pNewItems, CSttItems *pItems);
	void ShowSttGuideBook(CSttGuideBook *pGuideBook);
	void OnGbTreeItemChanged(CExBaseObject *pSelObj);
	void GetItemsTecFromRptDataXml(CDataGroup *pItemTec, const CString &strMacroUiID);

	CString ExportWordRptDlg();
	void EnableBtns();
	void ExpandItems(CSttItems *pItems);
	void ClearItemsTecEnables();  //����ǰ���Ƴ�data�µ�enable�ڵ�
	void FormatItemsTec();  //����ǰ��������Ҫ��༭���õ�ѡ�������ƴ�ӡ���ֵ����Ӧ��data��value����
	void FormatItemsTec(CDvmData *pData);

public slots:
	void slot_SelPath();
	void slot_ExportRpt();
	void slot_PrevClicked();
	void slot_NextClicked();

signals:

private slots:

private:
    Ui::QSttExportWordReport *ui;


};

#endif // QSttExportWordReport_H
