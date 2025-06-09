#ifndef SttReportViewHtml_H
#define SttReportViewHtml_H

#include "SttWebViewBase.h"
#include "../Interface/SttHtmlReportVIewInterface.h"
#include "../../SttCmd/SttRptMapDatas.h"

class QSttReportViewHtml : public QSttWebViewBase, public CSttHtmlReportVIewInterface
{
	Q_OBJECT

public:
    QSttReportViewHtml(QWidget* parent = 0);
	virtual void OnHtmlLoadFinish(bool b);

	CDataGroup *m_pGlobalDatas;
	void SetGlobalDatas(CDataGroup *pSttReport);
	void UpdateReportHead(CDataGroup *pSttReport);
	//zhouhj 2023.11.6���±���ͷ����Ŀ�ʼֹͣ����ʱ��
	void UpdateReportHead_StartEndTestTime(BOOL bUpdateStartTime,BOOL bUpdateEndTime);

	void SetValues_ReportHead(CDataGroup *pReportHead);//20220712 zhouhj �豸����ͷ�еĶֵ�������豸��Ϣ������

	bool m_bUpdateReportHead;//20240511 suyang ���ӶԿ�ʼ���Ժ���±���ͷ���ݲ�һ�� ����ɾ��html
	
	//2022-10-3  lijunqing
	void FillReportDataset(const CString &strParentItemsPath, const CString &strItemID, CDvmDataset *pDataset);
	void FillRptMapDatas(CSttRptMapDatas *pRptMapDatas, const CString &strState);

public:
	//////////////////////////////////////////////////////////////////////////
	//CSttHtmlReportVIewInterface
	//20230217 zhangyq ����strRptFileData�����⺯������ȫ�ֱ���m_strCurrRptFileData
	virtual void InsertRptHtml(const CString &strParentItemsPath, const CString &strItemsIDl, const char *strGbDatas, const CString &strRptFileData);
	virtual void UpdateRptHtml(const CString &strParentItemsPath, const CString &strItemsID, const CString &strGbDatas, const CString &strRptFileData);
	virtual void UpdateRptHtml(const CString &strParentItemsPath, const CString &strItemsID, const char *strGbDatas, const CString &strRptFileData);

	virtual void DeleteRptHtml(const CString &strParentItemsPath, const CString &strItemsID);
	virtual void ItemStateChanged(const CString &strParentItemsPath, const CString &strItemID, const CString &strState);
	virtual void FillReportData(const CString &strParentItemsPath, const CString &strItemID, const CString &strState,  char *pszReport);
	virtual void FillReportImg(const CString &strParentItemsPath, const CString &strItemID, const CString &strImgBase64);
	virtual void FillReportDataset(const CString &strParentItemsPath, const CString &strItemID, const char *pszDataset);
	virtual void FillRptMapDatas(const char *pszRptMapDatas, const CString &strState);
	virtual void QueryReportFillMode();
	virtual void ClearRptResults(const CString &strItemsID);

	virtual void FillReportTitle(const CString &strItemsID,const CString &strGroupData);//2023.7.24 zhouhj �޸Ĳ��������
	virtual void FillReportTitle(const CString &strItemsID,const char *pszGroupData);
	virtual void FillReportTitle(const CString &strItemsID,CDataGroup *pDataGroup);

	virtual void OpenReportFile(const CString &strReportFile);
	virtual void SaveHtmlReportFile(const CString &strHtmlFile);
	virtual BOOL SaveWordReportFile(const CString &strWordFile);
	virtual BOOL SavePdfReportFile(const CString &strPdfFile);
	virtual BOOL OpenRptFileData(const CString &strFile, const CString &strParentPath, const CString &strItemsID);
	virtual void MoveRptPos(const CString &strParentItemsPath, const CString &strItemID, const CString &strPos);//20241224 chenling �ƶ�����0-���ϡ�1-����

public slots:
	void SetReportFillMode(QVariant strRptFillMode);
#ifdef _PSX_QT_LINUX_
#ifndef STT_NOT_TESTCNTRFRAME
	void slot_UpdateRptData();
#endif
#endif
signals:
	//APP ==>> HTML
	void msg_InsertRptHtml(QVariant strParentItemsPath, QVariant strItemsID, QVariant strRptHtml, QVariant strGbDatas);
	void msg_UpdateRptHtml(QVariant strParentItemsPath, QVariant strItemsID, QVariant strRptHtml, QVariant strGbDatas);
	void msg_DeleteRptHtml(QVariant strParentItemsPath, QVariant strItemsID);
	void msg_ItemStateChanged(QVariant strParentItemsPath, QVariant strItemID, QVariant strState);
	void msg_FillReportData(QVariant strParentItemsPath, QVariant strItemID, QVariant strState, QVariant strReport);
	void msg_FillReportImg(QVariant strParentItemsPath, QVariant strItemID, QVariant strImgBase64);
	void msg_FillReportDataset(QVariant strParentItemsPath, QVariant strItemID, QVariant strDataset); //2022-9-30  lijunqing
	void msg_FillRptMapDatas(QVariant pszRptMapDatas, QVariant strState); //2022-10-02  lijunqing
	void msg_QueryReportFillMode(); //2022-10-02  lijunqing
	void msg_ClearRptResults(QVariant strItemsID);//2023.7.17 zhouhj �����ǰ������Ľ��
	void msg_FillReportTitle(QVariant strItemsID,QVariant strGroupData);//2023.7.24 zhouhj �޸Ĳ��������
	void msg_MoveRptPos(QVariant strParentItemsPath, QVariant strItemID, QVariant strPos);
#ifdef _PSX_QT_LINUX_
	void msg_FillReport_HtmlRptData();
#endif

public slots:
	//APP ==>> HTML
	void slot_InsertRptHtml(const CString &strParentItemsPath, const CString &strItemsID, const CString &strRptHtml, const char *strGbDatas);
	void slot_UpdateRptHtml(const CString &strParentItemsPath, const CString &strItemsID, const CString &strRptHtml, const CString &strGbDatas);
	void slot_UpdateRptHtml2(const CString &strParentItemsPath, const CString &strItemsID, const CString &strRptHtml, const char *strGbDatas);
	void slot_DeleteRptHtml(const CString &strParentItemsPath, const CString &strItemsID);
	void slot_ItemStateChanged(const CString &strParentItemsPath, const CString &strItemID, const CString &strState);
	void slot_FillReportData(const CString &strParentItemsPath, const CString &strItemID, const CString &strState,  char *pszReport);
	void slot_FillReportImg(const CString &strParentItemsPath, const CString &strItemID, const CString &strImgBase64);
	void slot_FillReportDataset(const CString &strParentItemsPath, const CString &strItemID, const char *pszDataset);
	void slot_FillRptMapDatas(const char *pszRptMapDatas, const CString &strState);
	void slot_QueryReportFillMode();
	void slot_ClearRptResults(const CString &strItemsID);
	void stt_FillReportTitle(const CString &strItemsID,const char *pszGroupData);//2023.7.24 zhouhj �޸Ĳ��������
	void stt_FillReportTitle(const CString &strItemsID,const CString &strGroupData);
	void slot_MoveRptPos(const CString &strParentItemsPath, const CString &strItemID, const CString &strPos);

	//HTML ==>> APP
#ifndef STT_NOT_TESTCNTRFRAME
//2024-9-12 lijunqing �Ż�ϵͳ����������Ч��
public:
#ifdef _PSX_QT_LINUX_
	virtual void showEvent(QShowEvent *event);
	void InitReportView();
#endif
	CSttMacroTestUI_TestMacroUI *m_pXAddRpt_TestMacroUI;
	CExBaseObject *m_pXAddRpt_pParent;
	CString m_strXAddRpt_strItemsName;
	CString m_strXAddRpt_strItemsID;
	CString m_strStartTestTime;
	CString m_strEndTestTime;
	long m_nCurrIndex;

public:
	void XAddMacroTestReport(CSttMacroTestUI_TestMacroUI *pTestMacroUI, CExBaseObject *pParent, const CString &strItemsName, const CString &strItemsID);
	bool m_bUpdateRptHtml;//���ε��Ӧ�ø�����Դ�����±���ͨ����״̬������������ʼ���ҵ�һ�μ���ͨ������Ӧ�ø��ݴ����Ľ����䱨��
	bool m_bHasInitFinished; //�Ƿ��Ѿ���ʼ����ɣ�û�г�ʼ�������ܽ��в���
#endif	 
};

#endif // SttReportViewHtml_H
