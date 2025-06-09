//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//VFlowShapeBase.h  CVFlowShapeBase

#pragma once

#include "LogicShapeMngrGlobal.h"
#include "../Visio/MSVisio15.h"

#define  VISIO_SHAPE_SHOW_LINE_TYPE_DATA               MSVisio15::visSolid   //����ԭʼ���������ʾ��������
#define  VISIO_SHAPE_SHOW_LINE_TYPE_FALSE               MSVisio15::visThinCross   //ֵΪ0����ʾ��������
#define  VISIO_SHAPE_SHOW_LINE_TYPE_TRUE               MSVisio15::visSolid   //ֵΪ1����ʾ��������

#define  VISIO_SHAPE_SHOW_TYPE_COLOR_DATA               _T("THEMEGUARD(RGB(0,0,255))")   //����ԭʼ���������ʾ������ɫ
#define  VISIO_SHAPE_SHOW_TYPE_COLOR_FALSE               _T("THEMEGUARD(RGB(255,0,0))")   //ֵΪ0����ʾ������ɫ
#define  VISIO_SHAPE_SHOW_TYPE_COLOR_TRUE               _T("THEMEGUARD(RGB(0,255,0))")  //ֵΪ1����ʾ������ɫ



#include "VFlowShapeProperty.h"

class CVFlowShapeBase : public CExBaseList
{
public:
	CVFlowShapeBase();
	virtual ~CVFlowShapeBase();


	long  m_nVisioID;
	CString  m_strDataType;
	CString  m_strHelp;
	CString  m_strData1;
	CString  m_strData2;
	CString  m_strData3;
	CString  m_strUnit;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CVFLOWSHAPEBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CLogicShapeMngrXmlRWKeys::CVFlowShapeBaseKey();     }
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
	BOOL Has_VisioShapeObj();

	BOOL SetData3_UI(const CString &strValue);//����Data3ֵ�����½�����ʾ
	BOOL GetData3_UI(CString &strValue);//����Data3ֵ�����½�����ʾ

	void AddNewProperty(const long &nRowIndex);
	BOOL SetShapeLineType(const long &nLineType);
	BOOL SetShapeColor(const CString &strColor);
//	BOOL SetPropertyValueByRowIndex_UI(const long &nRowIndex,const CString &strPropertyValue);//������ֵ�������Բ�����Visioͼ
//	BOOL GetPropertyValueByRowIndex_UI(const long &nRowIndex,const CString &strPropertyValue);//����RowIndex��������ֵ
	BOOL SetPropertyValueByPath_UI(const CString &strPropertyPath,const CString &strValue);//��������·����������ֵ��ͬʱ����Visioͼ
	BOOL GetPropertyValueByPath_UI(const CString &strPropertyPath,CString &strValue);//��������·���ӽ����ȡ����ֵ
	BOOL GetPropertyValueByPath(const CString &strPropertyPath,CString &strValue);//��������·�����ڴ��ȡ����ֵ

	BOOL SetPropertyDataTypeUnitByID(const CString &strPropertyID,const CString &strDataType,const CString &strUnit);//��������ID�������Ե�λ���������ͣ�ʵ�ʸ���Visioͼ


	BOOL GetPropertyValueByID(const CString &strPropertyID,CString &strValue);//�������л�ȡ����ֵ
	BOOL SetPropertyValueByID(const CString &strPropertyID,const CString &strValue);//��������������ֵ
	BOOL GetPropertyValueByID_UI(const CString &strPropertyID,CString &strValue);//�ӽ����ȡ����ֵ
	BOOL SetPropertyValueByID_UI(const CString &strPropertyID,const CString &strValue);//���ý�������ֵ����������ֵ

	BOOL GetPropertyValuesByRowIndex_UI(CVFlowShapeProperty *pShapeProperty);//���ݸö��������е�RowIndex��ȡ����������Visio����ֵ
	BOOL GetPropertyByRowIndex_UI(const long &nRowIndex,CString &strPropertyName,CString &strPropertyValue,CString &strPropertyLabel,CString &strPropertyTip);
	virtual void UpdateLineType_Color();

	CVFlowShapeProperty* FindByPath(const CString &strPath);

	MSVisio15::CVShape m_oShape;
};

