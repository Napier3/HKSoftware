#pragma once
#include "ExBaseList.h"
#include "ProtocolXmlRWKeys.h"
#include "PpNode.h"
#include "BbVariables.h"

#define PP_PRIORITY_LOWEST               3
#define PP_PRIORITY_BELOW_NORMAL    2
#define PP_PRIORITY_NORMAL               1
#define PP_PRIORITY_HIGHEST              0

#define PP_PROCEDURE_RUN_STATE_NOMAL   0
#define PP_PROCEDURE_RUN_STATE_ERROR    1
#define PP_PROCEDURE_RUN_STATE_RESET    2

class CPpProcedure :	public CExBaseList
{
public:
	CPpProcedure(void);
	virtual ~CPpProcedure(void);

	CBbVariables *m_pDataInterface;
	CBbVariables *m_pVariables;
	CPpScript *m_pInitScript;
	CPpScript *m_pEndScript;

	CExBaseList m_oAllVariables;
	CExBaseList m_listPackageRefs;//������ʱ�Ľӿڰ󶨱���
	LONG m_nType;				  //���ֹ������ͣ�

	CString m_strChannelID;       //����ʹ�õ�ͨѶͨ��ID
	CString m_strChCmmMode;
	long m_nPriority;          //���ȼ�
	long m_nExclusive;         //��ռ״̬����
	long m_nReleaseT;          //�೤ʱ��ȡ����ռһ��,��ʱ����

	DWORD m_dwRunState;

	CExBaseObject *m_pPackageRef;   //ִ�нű�ʱ�����ù����ı���֡
	BOOL  m_bValid;   //�����Ƿ���Ч�����磺�޸�ѹ����̣�û����Ҫ�޸ĵ����ݣ�����̾���Ч

public:
	virtual UINT GetClassID(){ return PPCLASSID_PPPROCEDURE; };
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPpProcedureKey;     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

public:
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	//���Һ���
	void InitPackageRefs();
	CExBaseObject* FindPackageRefByPkID(CString strPkgID);

	//����ID�����Ʋ���Node
	CPpNode* FindNodeByID(CString strID);
	CPpNode* FindNodeByName(CString strName);

	//�������д���ڵ㲢����list��,list�е�����ʹ��RemoveAll�Ƴ�Ԫ��
	void InsertNodesIntoList(CExBaseList* pList);
	void InsertNodesIntoList(CExBaseList* pRcList,CExBaseList* pList);
	 
	//��ң�ع�����Ҫ�������ʱ����ң�ز�������ң�ع����޶�������2������1Ϊ��ţ�2Ϊֵ��
	void SetDataInterface(long nIndex,long nValue);
	 
	void LogProcedureRunInfor();
	CPpNode* GetRootNode();
	void RunInitScript();
	void RunEndScript();

	CBbVariable* FindVariableByID(const CString &strID);

private:
	void RunScript(CPpScript *pScript, CBbVariables *pVariables);
};
