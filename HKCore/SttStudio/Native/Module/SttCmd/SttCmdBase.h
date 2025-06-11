//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttCmdBase.h  CSttCmdBase

#pragma once

#include "SttCmdData.h"
#include "../../Module/SttGlobalDef.h"
#include "../SttSocket/SttCmdOverTimeMngr.h"
#include "../../../Module/BaseClass/XObjectRefBase.h"

#include "../CmmInterface/SttCmmInterface.h"

//���Գ����IDSoft:Ats,Test,Debug,Record,�����ʼ��
// #define STT_SOFT_ID_ATS			_T("ATS")
// #define STT_SOFT_ID_TEST			_T("TEST")
// #define STT_SOFT_ID_DEBUG		_T("DEBUG")
// #define STT_SOFT_ID_RECORD		_T("RECORD")
extern CString g_strIDSoft;

class CSttSocketDataBase;

class CSttCmdBase : public CSttCmdData
{
public:
	CSttCmdBase();
	virtual ~CSttCmdBase();

	CString m_strToSN;   //2021-8-22  lijunqing
	CString m_strFromSN;  //2021-8-22  lijunqing

	//long m_nFrameHead;		//֡ͷ��ʶ
	long m_nType_Cmd;		//��������
//     long m_nSrcID;		//Դ�˱�ʶ
//     long m_nDestID;		//Ŀ���ʶ
	DWORD m_nIDTester;		//���Զ˱�ʶ
    long m_nPkgSendIndex;		//�������
	long m_nCompress;		//�Ƿ�ѹ��
	long m_nDataLen;		//���ݳ���	

	long m_nMid;
	CString m_strTime;

    void Set_Xml_Pkg_With_Name(BOOL b)      {   m_bXml_Pkg_With_Name = b;   }
	long Get_Xml_Pkg_With_Name(){return m_bXml_Pkg_With_Name;}
protected:
    long m_bXml_Pkg_With_Name;
//���غ���
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTCMDBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttCmdBaseKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
	bool m_bCreateMacroChild;

//˽�г�Ա�������ʷ���
public:
	void SetCreateMacroChild(bool bCreateMacroChild)	{	m_bCreateMacroChild = bCreateMacroChild;	}

public:
	//2022-10-22  lijunqing  �������Ӹ�ʽ��û�в���ȱʡֵ�������ʱ��ᵼ���﷨���󣬴�ǿ���޸ģ�ʵ�ִ����ͳһ
	BOOL GetXml_Pkg(char **ppszBuffer, long &nLen, long nSttCmdDataFormat);
    BOOL ParsePkgHead(BYTE *pPkgBuffer);

	//2022-10-22 lijunqing �������ݸ�ʽ����
    BOOL ParsePkgXml(BYTE *pPkgBuffer, long nLen, char *pwszDestBuffer, const long &nXmlRWType = _PUGI_XML_TYPE_);
    char* ParsePkgOnly(BYTE *pPkgBuffer);

    void ProducePkgHead(BYTE *pPkgBuffer);

	long GetCmdType();//���������ʵ�ǿ��������麯����
	DWORD GetIDTest();	

public:
	//pRetData!=NULL�򷵻�Ӧ����
	long DoWait(CSttSocketDataBase_File *pSocket,STT_CMD_INFO *pCmdInfo,long nTimeOut = -1,CSttCmdData *pRetData=NULL,BOOL bDoEvents=TRUE);

//2020-10-20  lijunqing
private:
	//2021-7-21  lijunqing ��ʱ�����������������ȥ��������ͳһ�ı�׼�Ľӿ�
	CSttSocketDataBase *m_pRefSocketDataBase; 

	//2021-7-21  lijunqing �µĽӿڱ���������ʹ������ӿ�
	void *m_pCmmOptrInterface;   //2022-10-19  lijunqing  ��g��Ϊvoid*

	//˽�г�Ա�������ʷ���
public:
	//2021-7-21  lijunqing ��ʱ�����������������ȥ��������ͳһ�ı�׼�Ľӿ�
	void SetRefSocketData(CSttSocketDataBase *pSocket)  {   m_pRefSocketDataBase = pSocket; }
	CSttSocketDataBase* GetRefSocketData()  {   return m_pRefSocketDataBase;    }

	//2021-7-21  lijunqing �µĽӿڱ���������ʹ������ӿ�
	void SetSttCmmOptrInterface(void *pCmmOptrInterface)  {   m_pCmmOptrInterface = pCmmOptrInterface; }
	void* GetSttCmmOptrInterface()  {   return m_pCmmOptrInterface;    }

public:
	void PraseCmdBuf(char *pBuf,long nLen, char *pszDestBuffer,const CString &strFormat=MQTT_DATA_FORMAT_XML);
	void PraseCmdBuf(char *pBuf,long nLen, char *pszDestBuffer, UINT nFormatType=_PUGI_XML_TYPE_);

	virtual void SetParameter(const CString &strMacroID, CDataGroup *pParas);
};

