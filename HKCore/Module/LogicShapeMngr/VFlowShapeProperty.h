//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//VFlowShapeProperty.h  CVFlowShapeProperty

#pragma once

#include "LogicShapeMngrGlobal.h"



class CVFlowShapeProperty : public CExBaseObject
{
public:
	CVFlowShapeProperty();
	virtual ~CVFlowShapeProperty();


	CString  m_strValue;
	CString  m_strPath;
	long  m_nRowIndex;
	CString  m_strDataType;
	CString  m_strUnit;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CVFLOWSHAPEPROPERTY;   }
	virtual BSTR GetXmlElementKey()  {      return CLogicShapeMngrXmlRWKeys::CVFlowShapePropertyKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	BOOL SetValue_UI(const CString &strValue);
	BOOL GetValue_UI(CString &strValue);
	BOOL UpdataValue_UI();
};

