//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PxPkgDataBase.cpp  CPxPkgDataBase


#include "stdafx.h"
#include "PxPkgDataBase.h"
#include <QDateTime>

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CPxPkgDataBase::CPxPkgDataBase()
{
	//初始化属性

	//初始化成员变量
}

CPxPkgDataBase::~CPxPkgDataBase()
{
}

long CPxPkgDataBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPxPkgDataBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPxPkgDataBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CPxPkgDataBase::InitAfterRead()
{
}

BOOL CPxPkgDataBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CPxPkgDataBase *p = (CPxPkgDataBase*)pObj;

	return TRUE;
}

BOOL CPxPkgDataBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase *p = (CPxPkgDataBase*)pDest;

	return TRUE;
}

CBaseObject* CPxPkgDataBase::Clone()
{
	CPxPkgDataBase *p = new CPxPkgDataBase();
	Copy(p);
	return p;
}

CBaseObject* CPxPkgDataBase::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPxPkgDataBase *p = new CPxPkgDataBase();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPxPkgDataBase::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPxPkgDataBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPxPkgDataBase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

//类CPxPkgDataBaseArrayObj
long CPxPkgDataBaseArrayObj::XmlWriteChildrenEx(CPxPkgDataBase* pData, CJSON* pJson)
{
	POS pos = pData->GetHeadPosition();
	while (pos)
	{
		CPxPkgDataBase* pChild = (CPxPkgDataBase*)pData->GetNext(pos);
		CString strJson;
		pChild->GetXml(CTcpEdgePkgXmlRWKeys::g_pXmlKeys, strJson, _JSON_TYPE_);
		CJSON* pObj = CJSON_Parse(strJson.GetString());
		char* pStrTemp = NULL;
		BSTR_to_char(pChild->GetXmlElementKey(), &pStrTemp);
		CJSON_AddItemToObject(pJson, pStrTemp, pObj);
		delete pStrTemp;
	}

	return 0;
}

long CPxPkgDataBaseArrayObj::XmlWriteChildrenEx(CPxPkgDataBase* pData, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = pData->GetHeadPosition();
	while (pos)
	{
		CPxPkgDataBase* pChild = (CPxPkgDataBase*)pData->GetNext(pos);
		pChild->XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	}

	return 0;
}


//判断百分比类的参数格式和范围是否正确
QString CPxPkgDataBase::CheckRangePer(CString strPkgID, CString strObjectID, CString strNodeID, CString strNode)
{
	//lmy,20230915注释
	QString strTemp = _T("");
	/*BOOL bNum = FALSE;
	char* pTemp = const_cast<char*>(strNode.GetString());*/

	//for(char a = '0'; a <= '9';a++)
	//{
	//	if(pTemp[0] == a)
	//	{
	//		bNum = TRUE;
	//		break;
	//	}
	//}

	//if(bNum && pTemp[strNode.GetLength()-1] == '%')
	//{
	//	CString strTemp = _T("");
	//	for(int i=0; i<strNode.GetLength()-1; i++)
	//	{
	//		strTemp += pTemp[i];
	//	}

	//	strNode = strTemp;
	//}

	//if(bNum)
	//{
		if(atof(strNode.GetString())<0 || atof(strNode.GetString()) >100)
		{
			strTemp = QString(_T("【错误】【超过范围】%1[Data]=>[%2$%3]字段超出范围;\n")).arg(strPkgID).arg(strObjectID).arg(strNodeID);
		}
	//}
	//else
	//{
	//	strTemp = QString(_T("【错误】【超过范围】%1[Data]=>[%2$%3]字段格式超出范围;\n")).arg(strPkgID).arg(strObjectID).arg(strNodeID);
	//}

	return strTemp;
}

//判断日期是否合法,格式是否正确
QString CPxPkgDataBase::CheckTimeFormat(CString strPkgID, CString strArrayID1, CString strArrayID2, CString strArrayID3, 
										CString strNodeID, CString strTime)
{
	QString strCheckResult = _T("");

	QDateTime dateTime = QDateTime::fromString(strTime, "yyyy-M-d H:m:s.z");
	bool bRet = dateTime.isValid();
	if(!bRet)
	{
		//lmy,20230915添加判断时间格式是否为不带毫秒的格式，目前两种格式都认为没问题
		dateTime = QDateTime::fromString(strTime, "yyyy-MM-dd hh:mm:ss");
		bRet = dateTime.isValid();
		if(!bRet)
		{
			strCheckResult = QString(_T("【错误】【格式不正确】%1：[Data]=>[%2$%3%4%5]字段格式不正确;\n")).arg(strPkgID).arg(
				strArrayID1).arg(strArrayID2).arg(strArrayID3).arg(strNodeID);
			return strCheckResult;
		}
	}

	QDate date = dateTime.date();
	QTime time = dateTime.time();
	strCheckResult = CheckDateLegal(strPkgID, strArrayID1, strArrayID2, strArrayID3, strNodeID, date.year(), 
		date.month(), date.day(), time.hour(), time.minute(), time.second(), time.msec());


	return strCheckResult;
}

QString CPxPkgDataBase::CheckDateLegal(CString strPkgID, CString strArrayID1, CString strArrayID2, CString strArrayID3, 
									   CString strNodeID, long nyear, long nmonth, long nday, long nHour, long nMinute, 
									   long nSecond, long nMillisecond)
{
	QString strCheckResult = _T("");
	//lmy,20230915修改
	//if(!isdigit(nyear))
	if(nyear < 1)
	{
		strCheckResult = QString(_T("【错误】【超过范围】%1：[Data]=>[%2$%3%4%5]字段类型中Year超过范围;\n")).arg(strPkgID).arg(
			strArrayID1).arg(strArrayID2).arg(strArrayID3).arg(strNodeID);
		return strCheckResult;
	}
	else if (nmonth > 12 || nmonth < 1)
	{
		strCheckResult = QString(_T("【错误】【超过范围】%1：[Data]=>[%2$%3%4%5]字段类型中Month超过范围;\n")).arg(strPkgID).arg(
			strArrayID1).arg(strArrayID2).arg(strArrayID3).arg(strNodeID);
		return strCheckResult;
	}
	else
	{
		if (nyear % 4 == 0 && nyear % 100 != 0 || nyear % 400 == 0)//是闰年
		{
			if (nmonth == 2)
			{
				if (nday > 29 || nday < 1)
				{
					strCheckResult = QString( _T("【错误】【超过范围】%1：[Data]=>[%2$%3%4%5]字段类型中Day超过范围;\n")).arg(strPkgID).arg(
						strArrayID1).arg(strArrayID2).arg(strArrayID3).arg(strNodeID);
					return strCheckResult;
				}
				else
				{
					strCheckResult = _T("");
					return strCheckResult;
				}
			}
		}

		if (nmonth == 4 || nmonth == 6 || nmonth == 9 || nmonth == 11)
		{
			if (nday < 1 || nday>30)
			{
				strCheckResult = QString( _T("【错误】【超过范围】%1：[Data]=>[%2$%3%4%5]字段类型中Day超过范围;\n")).arg(
					strPkgID).arg(strArrayID1).arg(strArrayID2).arg(strArrayID3).arg(strNodeID);
				return strCheckResult;
			}
			else 
			{
				strCheckResult = _T("");
				return strCheckResult;
			}
		}
		else if (nmonth != 2)
		{
			if (nday < 1 || nday>31)
			{
				strCheckResult = QString( _T("【错误】【超过范围】%1：[Data]=>[%2$%3%4%5]字段类型中Day超过范围;\n")).arg(
					strPkgID).arg(strArrayID1).arg(strArrayID2).arg(strArrayID3).arg(strNodeID);
				return strCheckResult;
			}
			else
			{
				strCheckResult = _T("");
				return strCheckResult;
			}
		}
		else
		{
			if (nday < 1 || nday>28)
			{
				strCheckResult = QString( _T("【错误】【超过范围】%1：[Data]=>[%2$%3%4%5]字段类型中Day超过范围;\n")).arg(
					strPkgID).arg(strArrayID1).arg(strArrayID2).arg(strArrayID3).arg(strNodeID);
				return strCheckResult;
			}
			else
			{
				strCheckResult = _T("");
				return strCheckResult;
			}
		}
	}

	if(nHour<0 || nHour>23)
	{
		strCheckResult = QString( _T("【错误】【超过范围】%1：[Data]=>[%2$%3%4%5]字段类型中Hour超过范围;\n")).arg(
			strPkgID).arg(strArrayID1).arg(strArrayID2).arg(strArrayID3).arg(strNodeID);
		return strCheckResult;
	}
	else
	{
		if(nMinute<0 || nMinute>60)
		{
			strCheckResult = QString(_T("【错误】【超过范围】%1：[Data]=>[%2$%3%4%5]字段类型中Minute超过范围;\n")).arg(
				strPkgID).arg(strArrayID1).arg(strArrayID2).arg(strArrayID3).arg(strNodeID);
			return strCheckResult;
		}
		else
		{
			if(nSecond<0 || nSecond>60)
			{
				strCheckResult = QString(_T("【错误】【超过范围】%1：[Data]=>[%2$%3%4%5]字段类型中Second超过范围;\n")).arg(
					strPkgID).arg(strArrayID1).arg(strArrayID2).arg(strArrayID3).arg(strNodeID);
				return strCheckResult;
			}
			else
			{
				if(nMillisecond<0 || nMillisecond>999)
				{
					strCheckResult = QString(_T("【错误】【超过范围】%1：[Data]=>[%2$%3%4%5]字段类型中Millisecond超过范围;\n")).arg(
						strPkgID).arg(strArrayID1).arg(strArrayID2).arg(strArrayID3).arg(strNodeID);
					return strCheckResult;
				}
			}
		}
	}

	return strCheckResult;
}