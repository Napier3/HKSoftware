﻿#ifndef SttReportViewHtml_H
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
	//zhouhj 2023.11.6更新报告头里面的开始停止测试时间
	void UpdateReportHead_StartEndTestTime(BOOL bUpdateStartTime,BOOL bUpdateEndTime);

	void SetValues_ReportHead(CDataGroup *pReportHead);//20220712 zhouhj 设备报告头中的额定值、测试设备信息等内容

	bool m_bUpdateReportHead;//20240511 suyang 增加对开始测试后更新报告头数据不一致 导致删除html
	
	//2022-10-3  lijunqing
	void FillReportDataset(const CString &strParentItemsPath, const CString &strItemID, CDvmDataset *pDataset);
	void FillRptMapDatas(CSttRptMapDatas *pRptMapDatas, const CString &strState);

public:
	//////////////////////////////////////////////////////////////////////////
	//CSttHtmlReportVIewInterface
	//20230217 zhangyq 增加strRptFileData，避免函数调用全局变量m_strCurrRptFileData
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

	virtual void FillReportTitle(const CString &strItemsID,const CString &strGroupData);//2023.7.24 zhouhj 修改测试项标题
	virtual void FillReportTitle(const CString &strItemsID,const char *pszGroupData);
	virtual void FillReportTitle(const CString &strItemsID,CDataGroup *pDataGroup);

	virtual void OpenReportFile(const CString &strReportFile);
	virtual void SaveHtmlReportFile(const CString &strHtmlFile);
	virtual BOOL SaveWordReportFile(const CString &strWordFile);
	virtual BOOL SavePdfReportFile(const CString &strPdfFile);
	virtual BOOL OpenRptFileData(const CString &strFile, const CString &strParentPath, const CString &strItemsID);

public slots:
	void SetReportFillMode(QVariant strRptFillMode);

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
	void msg_ClearRptResults(QVariant strItemsID);//2023.7.17 zhouhj 清除当前测试项的结果
	void msg_FillReportTitle(QVariant strItemsID,QVariant strGroupData);//2023.7.24 zhouhj 修改测试项标题

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
	void stt_FillReportTitle(const CString &strItemsID,const char *pszGroupData);//2023.7.24 zhouhj 修改测试项标题
	void stt_FillReportTitle(const CString &strItemsID,const CString &strGroupData);

	//HTML ==>> APP

};

#endif // SttReportViewHtml_H
