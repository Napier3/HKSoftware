//SttAssistWndInterface.h
#ifndef _SttAppWndAssistInterface_H__
#define _SttAppWndAssistInterface_H__

#include "../../../Module/DataMngr/DataGroup.h"

//2023.9.14 ����ԭ�е����ַ�ʽ���ƿ�ѡ��,����ʹ���µ�ˢ�µķ�ʽ
//#define  STT_MUTest_CBSelect_USE_Assist

//������ǰ������ast_ǰ׺����Ϊ�˱�����Ѿ��еĶ����෽������
class CSttWndAssistInterface
{
public:
	CSttWndAssistInterface()	{};
	virtual ~CSttWndAssistInterface()	{};

//����
public:
	void *m_pWndRef;    //MFC Windows������ָ��    QT��Widgetָ��
	CString m_strWndID; 

public:
	//��ʾ/����һ���Ӵ���
	virtual void ast_Show(const CString &strWndIdPath, bool bShow);
	
	//������ʽ
	virtual void ast_SetStyle(const CString &strWndIDPath, const CString &strStyle);
	virtual CString ast_GetStyle(const CString &strWndIDPath);
	
	//��ȡ����λ�� �ҵ����ڷ���true�����򷵻�false
	virtual bool ast_GetWndPos(const CString &strWndIdPath, CRect &rcWndPos);

	//���Ҵ��ڣ������� �ҵ����ش���,      ���򷵻�NULL
	//�������������ش˺�������Ϊ���ֱ�ӷ��ش���ָ�룬Ȼ��ǿ��ת��ΪCSttWndAssistInterface�������
	virtual CSttWndAssistInterface* ast_FindWnd(const CString &strWndID);

	//����ִ�нӿ�
	virtual bool ast_ExecCmd(const CString &strCmdID,const CString &strParas) = 0;
	virtual bool ast_ExecCmd_Data(const CString &strCmdID, const CString &strDataID) = 0;
	virtual bool ast_ExecCmd_DataFile(const CString &strCmdID, const CString &strDataFile) = 0;

};


class CSttAppAssistInterface
{
public:
	CSttAppAssistInterface()	{};
	virtual ~CSttAppAssistInterface()	{};

public:
	//����ִ�нӿ�
	virtual bool ast_ExecCmd(const CString &strCmdID,const CString &strParas) = 0;
	virtual bool ast_ExecCmd_Data(const CString &strCmdID, const CString &strDataID) = 0;
	virtual bool ast_ExecCmd_DataFile(const CString &strCmdID, const CString &strDataFile) = 0;

};


#endif//_SttAssistWndInterface_H__
