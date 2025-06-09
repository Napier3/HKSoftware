//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElement.h  CCharElement

#pragma once

#include "CharacteristicGlobal.h"
#include "CharElementTestLine.h"
#include "CharElementTestPoint.h"
#include "../../../Module/XDrawBase/XDrawLine.h"
#include "../../../Module/BaseClass/ComplexNumber.h"
#include "../../../Module/API/MathApi.h"

#include "../../../Module/XDrawBase/XDrawDataDef.h"
#include "../../../Module/XDrawBase/XDrawList.h"

#define CHAR_ERROR_LENGTH_TYPE_ABS   0
#define CHAR_ERROR_LENGTH_TYPE_ABS   0

class CCharElement : public CExBaseList
{
public:
	CCharElement();
	virtual ~CCharElement();

	CString  m_strDir;
	CString  m_strErrLength;
	long m_nErrorLengthType;   //0=绝对；1=相对
	double   m_dErrLength;

	//关联的数据引用
	CExBaseObject *m_pDataRef;

	//CharElement编号，用于标识角平分线
	long m_nCharElementID;  

	//坐标点，使用极坐标描述，例如：linep、arcp、circlep等命令，暂时不用，导出为xrio文件时可能用到
	long m_nPointUsePolorAxis;  

//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENT;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual long InsertToListCtrl(CListCtrl *pListCtrl,long lItemIndex);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

	virtual void Draw(CDC *pDC);
	virtual void GetBeginPoint(CString &strX, CString &strY);
	virtual void GetEndPoint(CString &strX, CString &strY);
	virtual void SetBeginPoint(const CString &strX, const CString &strY);
	virtual void SetEndPoint(const CString &strX, const CString &strY);

	virtual void SetTestPoint(long nPoints);
	virtual void SetUserTestPoint(long nPoints);
	virtual long GetUserTestPoints();
//私有成员变量
private:

protected:
	long     m_nTestPoints;
	long m_nUserTestPoints;

//私有成员变量访问方法
public:
	virtual CString ReturnXml();
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);

	virtual CXDrawDataBase* GetCXDrawDataBase();
	virtual CXDrawBase* CreateDrawElement();

	BOOL CalCharElementExpression(CString &strExpression, double &dVAlue, BOOL bLogError);
	double GetErrorLength();
	long* GetTestPointsRef()	{	return &m_nTestPoints;	}

//测试线定义的内容
public:
	virtual void CalTestLines_Plumb_Arc(CXDrawData_Arc *pOwnArc);
	virtual void CalTestLines_Plumb_Line(CXDrawData_Line *pOwnLine);

	////CalTestLines:总的接口，CalTestLines_####为具体测试线类型的接口，也可以直接被调用
	//根据m_nTestPoints进行计算
	virtual void BeforeCalTestLines();
	virtual void CalTestLines(UINT nTestLineMode); 
	virtual void CalTestLines_Plumb();
	virtual void CalTestLines_Vert();
	virtual void CalTestLines_Horz();

	//根据传入的始值和终值进行计算：计算一批次的测试线
	virtual void CalTestLines(CXDrawData_Line *pValRange, double dLenStep, UINT nTestLineMode); 
	virtual void CalTestLines_Plumb(CXDrawData_Line *pValRange, double dLenStep);
	virtual void CalTestLines_Vert(CXDrawData_Line *pValRange, double dLenStep);
	virtual void CalTestLines_Horz(CXDrawData_Line *pValRange, double dLenStep);

	//根据传入的始值和终值进行计算：计算一批次的测试线
	virtual void CalTestLine(CXDrawData_Line *pCurrValLine, UINT nTestLineMode); 
	virtual void CalTestLine_Plumb(CXDrawData_Line *pCurrValLine);
	virtual void CalTestLine_Vert(CXDrawData_Line *pCurrValLine);
	virtual void CalTestLine_Horz(CXDrawData_Line *pCurrValLine);

	long GetTestLines_Sys();
	void SelectLines(CExBaseList &oListSys, CExBaseList &oListOther);
};

inline long char_GetTestLineID(CCharElement *pChar1, CCharElement *pChar2)
{
	return (pChar1->m_nCharElementID << 16) + pChar2->m_nCharElementID;
}

inline long char_GetTestLineID(CCharElement *pChar1, long nIndex)
{
	return pChar1->m_nCharElementID * 255 + nIndex;
}
