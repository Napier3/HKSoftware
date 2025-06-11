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
	CExBaseList m_listPackageRefs;//保存临时的接口绑定变量
	LONG m_nType;				  //区分过程类型；

	CString m_strChannelID;       //过程使用的通讯通道ID
	CString m_strChCmmMode;
	long m_nPriority;          //优先级
	long m_nExclusive;         //独占状态属性
	long m_nReleaseT;          //多长时间取消独占一次,暂时不用

	DWORD m_dwRunState;

	CExBaseObject *m_pPackageRef;   //执行脚本时，引用关联的报文帧
	BOOL  m_bValid;   //过程是否有效，例如：修改压板过程，没有需要修改的数据，则过程就无效

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

	//查找函数
	void InitPackageRefs();
	CExBaseObject* FindPackageRefByPkID(CString strPkgID);

	//根据ID和名称查找Node
	CPpNode* FindNodeByID(CString strID);
	CPpNode* FindNodeByName(CString strName);

	//查找所有处理节点并放入list中,list有调用者使用RemoveAll移除元素
	void InsertNodesIntoList(CExBaseList* pList);
	void InsertNodesIntoList(CExBaseList* pRcList,CExBaseList* pList);
	 
	//当遥控过程需要输入参数时设置遥控参数，此遥控过程限定至少有2参数，1为点号，2为值。
	void SetDataInterface(long nIndex,long nValue);
	 
	void LogProcedureRunInfor();
	CPpNode* GetRootNode();
	void RunInitScript();
	void RunEndScript();

	CBbVariable* FindVariableByID(const CString &strID);

private:
	void RunScript(CPpScript *pScript, CBbVariables *pVariables);
};
