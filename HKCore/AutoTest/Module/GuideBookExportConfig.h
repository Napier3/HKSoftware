#pragma once

/*
	�����������Զ�����GuideBook��xml�ļ��������ã�
	�����ļ���GuideBookExportConfig.xml
*/
#include "../../Module/BaseClass/ExBaseObject.h"
#include "AutoTestXMLRWKeys.h"


class CGuideBookExportConfig : public CExBaseObject
{
private:
	CGuideBookExportConfig();
	virtual ~CGuideBookExportConfig();

public:
	//guidebook
	long m_nExportGlobalDatas; //ȫ������  ��ʵ��
	long m_nExportJobGuide; //��ҵָ��   ��ʵ��
	long m_nExportExtendRptDef;  //��չ����  ��ʵ��

	//guidebook-��������
	long m_nExportGuideBookAttrGbxml; //����ģ���ļ���Ϣ  ��Ҫ��CGuideBook����������
	long m_nExportGuideBookAttrPpxml; //��Լģ����Ϣ
	long m_nExportGuideBookAttrDvmxml;  //ģ���ļ���Ϣ��device-model-file��

	//device
	long m_nExportDeviceModule; //�豸ģ��   ��ʵ��
	long m_nExportSysParas;  //ϵͳ����      ��ʵ��

	//Item
	long m_nExportRptMap; //����ӳ��    ��ʵ��
	long m_nExportReports; //��������   ��ʵ��

	//Item-��������
	long m_nExportItemAttrSimplify; //CItems��CSafety��CMacroTest��CCommCmd��CSysParaEdit���Լ򻯣�������name��id    ��ʵ��

	//sysparaedit
	long m_nExportSysParaEditValues; //ϵͳ�����༭��Ŀ�Ĳ���   ��ʵ��

	//safety
	long m_nExportSafetyDatas; //���ݶ���    ��ʵ��
	long m_nExportSafetyDllCall;   //��̬�����   ��ʵ��
	long m_nExportSafetyMsg; //��ʾ��Ϣ   ��ʵ��

	//commoncmd
	long m_nExportCmdPara;  //�������            ��ʵ��
	long m_nExportCmdDatas; //����������      ��ʵ��
	long m_nExportCmdDsvScript; //ģ����֤�ű�    ��ʵ��

	//macrotest
	long m_nExportMacroTestParas;  //���������ܲ���   ��ʵ��

	//report
	long m_nExportRptmapNotSaveNull;   //������ӳ��Ϊ��ʱ�������汨��ӳ�����   ��ʵ��
	long m_nExportRptOnlySaveBkmk;   //CReport��m_pValues��ֻ��������ǩ������
	long m_nExportRptOnlySaveLast;   //ֻ�������һ�εı�������   ��ʵ��
	
	//script
	long m_nExportScriptExprScript;  //����жϱ��ʽ   ��ʵ��
	long m_nExportScriptName;     //script-name   ��ʵ��
	long m_nExportScriptInit;     //��ʼ���ű�    ��ʵ��
	long m_nExportScriptRslt;     //����ű�      ��ʵ��

	CString m_strFile;

public:
	static CGuideBookExportConfig* g_pGuideBookExportConfig;
	static long g_nGuideBookExportConfigRef;

	static CGuideBookExportConfig* Create();
	static void Release();

public:


public:
	long Save();
	long Open();

public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{      return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strGuideBookExportConfigKey;	}

};
