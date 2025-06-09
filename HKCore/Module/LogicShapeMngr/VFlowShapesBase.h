//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//VFlowShapesBase.h  CVFlowShapesBase

#pragma once

#include "LogicShapeMngrGlobal.h"
#include "VFlowShapeBase.h"



class CVFlowShapesBase : public CExBaseList
{
public:
	CVFlowShapesBase();
	virtual ~CVFlowShapesBase();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CVFLOWSHAPESBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CLogicShapeMngrXmlRWKeys::CVFlowShapesBaseKey();     }
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
	virtual BOOL UpdateAllShapes();//���ݵ�ǰֵ,����ȫ��Shape��Line

	CVFlowShapeBase *FindByVisioID(long nVisioID);
	CVFlowShapeBase *FindByData1(const CString &strData1);
	BOOL SetValueByID(const CString &strID,const CString &strValue);
	BOOL GetValueByID(const CString &strID,CString &strValue);
	BOOL SetValueByData1(const CString &strData1,const CString &strValue);
	BOOL SetValueByID_UI(const CString &strID,const CString &strValue);
	BOOL SetValueByData1_UI(const CString &strData1,const CString &strValue);
	BOOL GetValueByData1_UI(const CString &strData1,CString &strValue);
};

