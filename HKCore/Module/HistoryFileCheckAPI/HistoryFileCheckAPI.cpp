#include "Stdafx.h"
#include "HistoryFileCheckAPI.h"

CString GetEncodingValueFromXML(const CString &strBuff)
{
	CString strValue = _T("");
	int nIndex = 0;
	nIndex = strBuff.Find("encoding");

	if (nIndex == -1)
	{
		return strValue;
	}

	strValue = strBuff.Mid(nIndex);
	nIndex = strValue.Find('\"');

	if (nIndex == -1)
	{
		return _T("");
	}

	strValue = strValue.Mid(nIndex+1);

	nIndex = strValue.Find('\"');

	if (nIndex == -1)
	{
		return _T("");
	}

	strValue = strValue.Left(nIndex);

	return strValue;
}

BOOL find_child_puginode(pugi::xml_node &oRoot,pugi::xml_node &oChildNode,CString strChildNodeName,CString strChildAttrName1,CString strChildAttrName2)
{
	oChildNode = oRoot.child(strChildNodeName.AllocSysString());

	if (oChildNode == NULL)
	{
		oChildNode = oRoot.child_ignore_case(strChildNodeName.AllocSysString());

		if (oChildNode == NULL)
		{
			oChildNode = oRoot.find_child_by_attribute2(L"fileType",L"fileVer");

			if (oChildNode == NULL)
			{
				return 0;
			}
		}
	}

	return 1;
}

BOOL find_pugiattr(pugi::xml_node &oNode,pugi::xml_attribute &oAttr,CString strAttrName,CString strAttrValue)
{
	oAttr = oNode.attribute_ignore_case(strAttrName.AllocSysString());

	if (oAttr == NULL)
	{
		if (strAttrValue.IsEmpty())
		{
			return 0;
		} 
		else
		{
			oAttr = oNode.attribute_byvalue_ignore_case(strAttrValue.AllocSysString());

			if (oAttr == NULL)
			{
				return 0;
			}
		}
	}

	return 1;
}

BOOL check_decimal_format(const CString &strDecimal)
{
	long nIndex = strDecimal.GetLength();

	if (nIndex == 0)
	{
		return 0;
	}

	for (int nCount = 0;nCount<nIndex;nCount++)
	{
		if ((strDecimal.GetAt(nCount)<'0')||(strDecimal.GetAt(nCount)>'9'))
		{
			return 0;
		}
	}
	return 1;
}

BOOL check_hex_format(const CString &strHex)
{
	long nLenth = strHex.GetLength();

	if (nLenth<3)
	{
		return 0;
	}

	CString strTmp1,strTmp2;

	strTmp1 = strHex.Left(2);
	strTmp2 = strHex.Mid(2);

	if ((strTmp1!="0x")&&(strTmp1!="0X"))
	{
		return 0;
	}

	nLenth-=2;
	for (int nCount =0;nCount<nLenth;nCount++)
	{
		char zfTmp = strTmp2.GetAt(nCount);
		if ((zfTmp<'0')||((zfTmp>'9')&&(zfTmp<'A'))||((zfTmp>'F')&&(zfTmp<'a'))||(zfTmp>'f'))
		{
			return 0;
		}
	}

	return 1;
}

BOOL check_decimal_DoublePoint_format(const CString &strDecimal)
{
	long nIndex = strDecimal.GetLength();

	if (nIndex == 0)
	{
		return 0;
	}

	if ((strDecimal.GetAt(nIndex-1)<'0')||(strDecimal.GetAt(nIndex-1)>'3'))
	{
		return 0;
	}

	for (int nCount = 0;nCount<(nIndex-1);nCount++)
	{
		if ((strDecimal.GetAt(nCount) != '0'))
		{
			return 0;
		}
	}
	return 1;
}

BOOL check_binary_format(const CString &strDecimal)
{
	long nIndex = strDecimal.GetLength();

	if (nIndex == 0)
	{
		return 0;
	}

	for (int nCount = 0;nCount<nIndex;nCount++)
	{
		if ((strDecimal.GetAt(nCount)<'0')||(strDecimal.GetAt(nCount)>'1'))
		{
			return 0;
		}
	}
	return 1;
}

BOOL check_XML_SOE_date_format(const CString &strDate)
{
	long nIndex = strDate.GetLength(),nNum = 0;

	for (int nCount=0;nCount<nIndex;nCount++)
	{   
		if (strDate.GetAt(nCount)=='_')
		{
			nNum++;
		}
	}

	if (nNum!=2)
	{
		return 0;
	}

	CString strTmp,strTmp2;
	nIndex = strDate.Find('_');
	strTmp = strDate.Left(nIndex);

	if ((nIndex != 6)||(!check_decimal_format(strTmp)))
	{
		return 0;
	}

	long nTmp1,nTmp2;
	nTmp1 = _ttoi(strTmp);
	nTmp1 = nTmp1%10000;
	nTmp2 = nTmp1/100;

	if ((nTmp2<1)||(nTmp2>12))
	{
		return 0;
	}

	nTmp2 = nTmp1%100;

	if ((nTmp2<1)||(nTmp2>31))
	{
		return 0;
	}

	strTmp = strDate.Mid(nIndex+1);
	nIndex = strTmp.Find('_');
	strTmp2 = strTmp.Left(nIndex);

	if ((nIndex != 6)||(!check_decimal_format(strTmp2)))
	{
		return 0;
	}

	nTmp1 = _ttoi(strTmp2);
	nTmp2 = nTmp1/10000;

	if ((nTmp2<0)||(nTmp2>24))
	{
		return 0;
	}

	nTmp1 = nTmp1%10000;

	nTmp2 = nTmp1/100;

	if ((nTmp2<0)||(nTmp2>60))
	{
		return 0;
	}

	nTmp2 = nTmp1%100;

	if ((nTmp2<0)||(nTmp2>60))
	{
		return 0;
	}

	nIndex = strDate.ReverseFind('_');

	strTmp2 = strDate.Mid(nIndex+1);
	nIndex = strTmp2.GetLength();

	if ((nIndex==0)||(nIndex>3))
	{
		return 0;
	}

	if (!check_decimal_format(strTmp2))
	{
		return 0;
	}

	return 1;
}

BOOL check_soe_msg_date(const CString &strDate)
{
	CString strTmp = strDate;
	long nLenth = strTmp.Replace("-","");

	if (nLenth != 2)
		return 0;

	nLenth = strTmp.Replace(":","");

	if (nLenth != 2)
		return 0;

	nLenth = strTmp.Replace(".","");

	if (nLenth != 1)
		return 0;

	nLenth = strTmp.Replace(" ","");

	if (nLenth != 1)
		return 0;

	if (!check_decimal_format(strTmp))
		return 0;

	return 1;
}

void get_line_from_filebuf(CBufferBase *pFileBuf ,CString &strLineMsg)
{
	char szLineMsg[200] = {0};
	char *pCurrPoint = pFileBuf->GetPointer();
	long nLenth = 0;

	while(pFileBuf->IsPoiterInBuffer(pCurrPoint)&&(!((*pCurrPoint=='\r')&&((*(pCurrPoint+1))=='\n'))))
	{
		szLineMsg[nLenth] = *pCurrPoint;
		pCurrPoint++;
		nLenth++;
	}

	szLineMsg[nLenth] = '\0';

	if (pFileBuf->IsPoiterInBuffer(pCurrPoint))
	{
		pFileBuf->OffsetPointer(nLenth+2);
	}
	else
		pFileBuf->OffsetPointer(nLenth);

	strLineMsg = szLineMsg;
}

BOOL check_soe_msg_header(const CString &strLineMsg,CString &strTmp1,CString &strTmp2,CString &strTmp3)
{
	long nLenth = 0;
	CString strTmp;
	nLenth = strLineMsg.Find("ÎÄ¼þÍ·");
	if (nLenth == -1)
	{
		strTmp1 = "";
		strTmp2 = "";
		strTmp3 = "";
		return 0;
	} 

	strTmp1 = strLineMsg.Left(nLenth+8);
	strTmp = strLineMsg.Mid(nLenth+8);
	nLenth = strTmp.Find(',');

	if (nLenth == -1)
	{
		strTmp2 = strTmp;
		strTmp3 = "";
	} 
	else
	{
		strTmp2 = strTmp.Left(nLenth);
		strTmp3 = strTmp.Mid(nLenth+1);
	}

	return 1;
}

BOOL check_soe_msg_deviceID(const CString &strLineMsg,CString &strTmp1,CString &strTmp2,CString &strTmp3)
{
	long nLenth = 0;
	CString strTmp;
	nLenth = strLineMsg.Find(',');

	if ((strLineMsg.Find(':')!=-1)||(strLineMsg.Find('£º')!=-1)||(nLenth == -1))
	{
		strTmp1 = "";
		strTmp2 = "";
		strTmp3 = "";
		return 0;
	} 

	strTmp1 = strLineMsg.Left(nLenth);
	strTmp = strLineMsg.Mid(nLenth+1);
	nLenth = strTmp.Find(',');

	if (nLenth == -1)
	{
		strTmp2 = strTmp;
		strTmp3 = "";
	} 
	else
	{
		strTmp2 = strTmp.Left(nLenth);
		strTmp3 = strTmp.Mid(nLenth+1);
	}

	return 1;
}

BOOL check_soe_msg_body(const CString &strLineMsg,CString &strTmp1,CString &strTmp2,CString &strTmp3,CString &strTmp4)
{
	long nLenth = 0;
	CString strTmp;
	nLenth = strLineMsg.Find("£º");

	if (nLenth == -1)
	{
		strTmp1 = "";
		strTmp2 = "";
		strTmp3 = "";
		strTmp4 = "";
		return 0;
	} 

	strTmp1 = strLineMsg.Left(nLenth+2);
	strTmp = strLineMsg.Mid(nLenth+2);
	nLenth = strTmp.Find(',');

	if (nLenth == -1)
	{
		strTmp2 = strTmp;
		strTmp3 = "";
		strTmp4 = "";
	} 
	else
	{
		strTmp2 = strTmp.Left(nLenth);
		strTmp = strTmp.Mid(nLenth+1);
		nLenth = strTmp.Find(',');

		if (nLenth == -1)
		{
			strTmp3 = strTmp;
			strTmp4 = "";
		} 
		else
		{
			strTmp3 = strTmp.Left(nLenth);
			strTmp4 = strTmp.Mid(nLenth+1);
		}
	}

	return 1;
}