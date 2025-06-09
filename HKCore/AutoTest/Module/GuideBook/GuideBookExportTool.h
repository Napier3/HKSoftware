#pragma once
#include "GuideBook.h"
#include "../GuideBookExportConfig.h"

class CGuideBookExportTool : public CExBaseList
{
public:
	CGuideBookExportTool(void);
	virtual ~CGuideBookExportTool(void);

// 	//guidebook
// 	long m_nExportGlobalDatas; //ȫ������
// 	long m_nExportJobGuide; //��ҵָ��
// 	long m_nExportExtendRptDef;  //��չ����
// 
// 	//device
// 	long m_nExportDeviceModule; //�豸ģ��
// 	long m_nExportSysParas;  //ϵͳ����
// 
// 	//Item
// 	long m_nExportRptMap; //����ӳ��
// 	long m_nExportReports; //��������
// 
// 	//sysparaedit
// 	long m_nExportSysParaEditValues; //ϵͳ�����༭��Ŀ�Ĳ���
// 
// 	//safety
// 	long m_nExportSafetyDatas; //���ݶ���
// 	long m_nExportSafetyDllCall;   //��̬�����
// 	long m_nExportSafetyMsg; //��ʾ��Ϣ
// 
// 	//commoncmd
// 	long m_nExportCmdPara;  //�������
// 	long m_nExportCmdDatas; //����������
// 	long m_nExportCmdDsvScript; //ģ����֤�ű�
// 
// 	//macrotest
// 	long m_nExportMacroTestParas;  //���������ܲ���

public:
	void ExportGuideBook(CGuideBook *pGuideBook, const CString &strXmlFile);
	void ExportGuideBook(CGuideBook *pGuideBook, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportTest(CGuideBook *pGuideBook);

	//shaolei 20210724 
	void ExportItems(CItems *pItems, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);

protected:
	BOOL ExportItemChild(CExBaseObject *p, UINT nClassID, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	BOOL ExportItemsChild(CExBaseObject *p, UINT nClassID, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void Export(CDevice *pDevice, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void Export(CJobGuide *pJobGuide, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void Export(CItems *pItems, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void Export(CSysParaEdit *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void Export(CSafety *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void Export(CMacroTest *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void Export(CCommCmd *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void Export(CMacroCharItems *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);

// 	void Export(CReportMap *pRptMap, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
// 	void Export(CReports *pReorts, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);

};
