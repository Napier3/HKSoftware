//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//VFlowShapeLines.h  CVFlowShapeLines

#pragma once

#include "LogicShapeMngrGlobal.h"

#include "VFlowShapesBase.h"

#include "VFlowShapeLine.h"

class CVFlowShapeLines : public CVFlowShapesBase
{
public:
	CVFlowShapeLines();
	virtual ~CVFlowShapeLines();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CVFLOWSHAPELINES;   }
	virtual BSTR GetXmlElementKey()  {      return CLogicShapeMngrXmlRWKeys::CVFlowShapeLinesKey();     }
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
	virtual void InitDataTypeUnit(const CString &strDataType,const CString &strUnit);//��ʼ��Line�����������ͼ���λ
};

