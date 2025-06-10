//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttHdChs.h  CSttHdChs

#pragma once

#include "SttCmdDefineGlobal.h"


#include "SttHdCh.h"

class CSttHdChs : public CExBaseList
{
public:
	CSttHdChs();
	virtual ~CSttHdChs();


//���غ���
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTHDCHS;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttHdChsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	BOOL HasHdCh(char zfChType,const long &nModuleIndex,long nChIndex);
	CSttHdCh* AddHdCh(const CString &strHdRsName,const CString &strHdRsID,float fHdChCoef = 1.0f);
	CSttHdCh* FindAddHdCh(const CString &strHdRsName,const CString &strHdRsID,float fHdChCoef = 1.0f);//�Ȳ��Ҹ�ͨ��,������Ҳ���,�򴴽��ö���
	void InitHdChsByString(char zfChType,CString &strHdChsString);//����1Ϊ��ѹ����ͨ����ʶֵΪ'U'��'I',����2ΪӲ��ͨ���ַ���,��:"U1_1;U1_2;U1_3;",���ַ����д�����Ч�ַ�,����ɾ��,����2ΪӲ��ͨ������,������֤ͨ��
	BOOL HasAnalogCurrModuleHdCh(long nModuleIndex);//�ж��Ƿ����ģ�����������ģ��,Index��1��ʼ���  zhouhj20211005

protected:
	void InitHdChsByString_Analog(char zfChType,CString &strHdChsString);//����1ΪӲ��ͨ���ַ���,��:"U1_1;U1_2;U1_3;",���ַ����д�����Ч�ַ�,����ɾ��,����2ΪӲ��ͨ������,������֤ͨ��
	void InitHdChsByString_Digital(char zfChType,CString &strHdChsString);//����1ΪӲ��ͨ���ַ���,��:"U1_1;U1_2;U1_3;",���ַ����д�����Ч�ַ�,����ɾ��,����2ΪӲ��ͨ������,������֤ͨ��
	void InitHdChsByString_Weak(char zfChType,CString &strHdChsString);//����1ΪӲ��ͨ���ַ���,��:"U1_1;U1_2;U1_3;",���ַ����д�����Ч�ַ�,����ɾ��,����2ΪӲ��ͨ������,������֤ͨ��
};

