//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttGdColDef_Fuc_Min.h  CSttGdColDef_Fuc_Min

#pragma once

#include "SttTestGridDefineGlobal.h"


#include "SttGdColDef_Para.h"
#include "SttGdColDef_TextComb.h"

class CSttGdColDef_Fuc_Min : public CExBaseList
{
public:
	CSttGdColDef_Fuc_Min();
	virtual ~CSttGdColDef_Fuc_Min();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTGDCOLDEF_FUC_MIN;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestGridDefineXmlRWKeys::CSttGdColDef_Fuc_MinKey();     }
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
};

