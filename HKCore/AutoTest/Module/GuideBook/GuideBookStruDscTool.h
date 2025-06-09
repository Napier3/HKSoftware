#pragma once
#include "GuideBook.h"

 //���������棺0 = ���������棻 1 = ������ʼ�����棨ID = STT_REPORT_ID_INIT����2 = ����ȫ������
#define EXPROT_RPT_NONE   0
#define EXPROT_RPT_INIT   1
#define EXPROT_RPT_ALL    2

class CGuideBookStruDscTool : public CExBaseList
{
public:
	CGuideBookStruDscTool(void);
	virtual ~CGuideBookStruDscTool(void);

	BOOL m_bExportDsvScript;
	BOOL m_bExportMacroUIParas;  //�����������Ľ�������ڵ�
	BOOL m_bExportRsltExpr; //��������ж�
	long m_nExportRpt;
	BOOL m_bExportGlobalDatas;  //����ȫ������
	BOOL m_bExportSysParas;   //����ϵͳ����
	BOOL m_bExportCharacteristic;   //������������
	BOOL m_bExportCmd;   //����ͨѶ����Ĳ���CCmd
	BOOL m_bExportItemDatas; //�Ƿ񵼳���Ŀ�����ݶ���
	BOOL m_bExportItemsTecs;  //������Ŀ����Ҫ��+�������ݱ���С��λ������
	CGuideBook *m_pGuideBook;

public:
	//2021-8-5  lijunqing
	void ExportGuideBookStruDscToString(CGuideBook *pGuideBook, CString &strXml);
	void ExportGuideBookStruDscToString_UTF8(CGuideBook *pGuideBook, char **ppszBuffer, long &nLen);

	void ExportGuideBookStruDsc(CGuideBook *pGuideBook, const CString &strXmlFile);
	void ExportGuideBookStruDsc(CGuideBook *pGuideBook, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CItems *pItems, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);

protected:
	void ExportStruDscItemsChild(CExBaseList *pList, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	BOOL ExportStruDscItemsChild(CExBaseObject *p, UINT nClassID, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CDevice *pDevice, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CTestGlobalDatasMngr *pDataMngr, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CJobGuide *pJobGuide, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CDvmDataset*pDataset, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CDataGroup *pGrp, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CSysParas *pSysParas, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	//void ExportStruDsc(CItems *pItems, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);  //2023-9-9  lijunqing ��Ϊpublic
	void ExportStruDsc(CSysParaEdit *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CSafety *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CMacroTest *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CCommCmd *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CMacroCharItems *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CTestMacroUiParas *pUIParas, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CTestMacroCharParas *pCharParas, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CMacroTestPara *pMacroTestPara, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CItemRsltExprRun *pRsltExprRun, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CReports *pReports, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CCharacteristic *pCharacteristic, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CShortDatas *pDatas, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ProcessReportsBack_BF_Export(CGbItemBase *pGbItemBase);
};
