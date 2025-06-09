#include "StdAfx.h"
#include "PNTplParse.h"
#include "PNTplEquation.h"
#include "PNTplText.h"
#include "PNTplGroup.h"
#include "../../../../Module/XfileMngrBase/XFileMngr.h"
#include "..\PttGlobalDefine.h"

CPNTplParse::CPNTplParse()
{
	m_pBuffer = NULL;
}

CPNTplParse::~CPNTplParse()
{
}

BOOL CPNTplParse::GetTempFilePath(CString &strPath)
{
	//return PopupOpenFileDialog(NULL, strPath, _T("tpl | *.tpl;|tpl (*.tpl)|*.tpl|"), _T("tpl"), _T("选择PowerTest模板文件"));
	return ptt_PopOpenPowerTestTplFileDlg(strPath);
}

BOOL CPNTplParse::ReadFromTemplate(const CString &strFile)
{
	if (!m_oBuffer.ReadFromFile(strFile))
	{
		return FALSE;
	}

	m_pBuffer = m_oBuffer.GetBufferBeginPos();
	long nBufferLen = m_oBuffer.GetLength();

	Parse_PN_Tpl_ex(m_pBuffer, nBufferLen);

	AdjustAllGroupKeys( &m_oRoot);

	return TRUE;
}

//判断字符是否为字母，若是，返回TRUE；否则返回FALSE
BOOL CPNTplParse::IsChar(char ch)
{
	if(( ('a'<=ch) && (ch<='z') ) || (('A'<=ch) && (ch<='Z')) )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

#define ELEMENT_KEY_ERR   0
#define ELEMENT_KEY_BEGIN   1
#define ELEMENT_KEY_END   2

//向后逐字节取，遇到第一个非字母的字符为“>”则设置strKey，将当前位置移到‘>’后，并返回Element类型
UINT CPNTplParse::GetElementKey(CStringA &strKey, char *_pBuffer)
{
	long nCurrPos = m_nCurrParsePos;
	char ch = _pBuffer[nCurrPos];

	while (IsChar(ch))
	{
		nCurrPos++;
		ch = _pBuffer[nCurrPos];
	}
	//当遇到的第一个非字母字符不是‘>’，说明不是Element
	if (ch != '>')
	{
// 		char *pTmp = _pBuffer + nCurrPos;
// 		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("解析Powertest模板解析时<>出错."));
		return ELEMENT_KEY_ERR;
	}

	char *pTemp = _pBuffer + nCurrPos - 3;

	//如果是End，设置strKey后返回
	if (*pTemp == 'E' && *(pTemp + 1) == 'n' && *(pTemp + 2) == 'd')
	{
		strKey.SetString(_pBuffer+m_nCurrParsePos, nCurrPos - m_nCurrParsePos - 3);
		m_nCurrParsePos = nCurrPos+1;
		return ELEMENT_KEY_END;
	}

	//如果是Begin，设置strKey后返回
	//当前默认Element标签只有End和Begin
	else
	{
		if ((nCurrPos - m_nCurrParsePos - 5)<0)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,_T("解析Powertest模板解析时<>出错."));
			return ELEMENT_KEY_ERR;
		}

		char *pTmp = (_pBuffer+nCurrPos-5);

		if (strnicmp(pTmp,("Begin"),5) != 0)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,_T("解析Powertest模板解析时<>出错."));
			return ELEMENT_KEY_ERR;
		}

		strKey.SetString(_pBuffer+m_nCurrParsePos, nCurrPos - m_nCurrParsePos - 5);
		m_nCurrParsePos = nCurrPos+1;
		return ELEMENT_KEY_BEGIN;
	}
}

//跳过无效字符（空格、tab符及换行符）
void CPNTplParse::Offset(char* _pBuffer)
{
	char chCurr = _pBuffer[m_nCurrParsePos];

	while (chCurr == VK_SPACE || chCurr == VK_TAB || chCurr == '\r' || chCurr == '\n')
	{
		m_nCurrParsePos++;
		chCurr = _pBuffer[m_nCurrParsePos];
	}
}

//解析函数入口
BOOL CPNTplParse::Parse_PN_Tpl_ex(char *_pTplBuff, long nLen)
{
	int i = 0;
	char chCurr;
	m_nCurrParsePos = 0;
	//char* pFileBuff = _pTplBuff;
	m_oRoot.DeleteAll();

	//跳过无效字符
	Offset(_pTplBuff);

	//模板文件的第一个有效字符为‘<’
	ASSERT (_pTplBuff[m_nCurrParsePos] == '<');

	UINT nKeyType = 0;
	CStringA strKey;
	long nBufferLen = nLen;

	while (TRUE)
	{
		//当当前解析位置超出缓存区时，跳出循环
		if (m_nCurrParsePos >= nBufferLen)
		{
			break;
		}

		Offset(_pTplBuff);
		
		//防止模板文件末尾存在无效字符；
		if (m_nCurrParsePos >= nBufferLen)
		{
			break;
		}

		chCurr = _pTplBuff[m_nCurrParsePos];
		ASSERT (chCurr == '<');

		if (chCurr == '<')
		{
			m_nCurrParsePos++;
			nKeyType = GetElementKey(strKey, _pTplBuff);

			//模板文件的第一个Element必然是Begin
			ASSERT (nKeyType == ELEMENT_KEY_BEGIN);

			//当前位置在‘>’后，调用函数ParseElement_Ex(pPNTplElement)
			CPNTplElement *pPNTplElement = new CPNTplElement;   
			pPNTplElement->m_strName = strKey;  
			m_oRoot.AddNewChild(pPNTplElement);
			ParseElement_Ex(pPNTplElement, _pTplBuff, nBufferLen);
		}
		else
		{
			//显示错误信息
			break;
		}
	}

	return TRUE;
}

//Equation对象特殊处理
//当‘=’左边为‘TESTNAME’时，认定需要特殊处理，返回TRUE；否则返回FALSE；
//当前仅处理‘TESTNAME’，后续若有其它特殊情况，在此处添加；
BOOL CPNTplParse::IsKey_Name(const CStringA &strText)
{
	if (strText == "TESTNAME")
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//解析Group对象，nBegin和nEnd分别是Group对象的起止位置；
void CPNTplParse::ParseGroup(CPNTplGroup *pGroup, long nBegin, long nEnd, char* _pBuffer)
{
	long nLeft, nRight;
	long i = nBegin;
	nLeft = nBegin;
	CStringA strText;
	//char nextCh;

	while (i <= nEnd)
	{
		if (_pBuffer[i] == '=')
		{
			//记录Equation对象的名称；
			strText.SetString(_pBuffer+nLeft, i - nLeft);
			strText.Trim();
			nRight = i + 1;
			i++;

			while (i<nEnd)
			{
				if (_pBuffer[i] == ',')
				{
					if (_pBuffer[i+1] == ',') //连续两个“,”
					{
						i++;
					}
					else
					{
					//新建等式对象
						NewEquation(pGroup, strText, _pBuffer+nRight, i - nRight);
						i++;
						nLeft = i;

						break;
					}
				}

				i++;
			}

			if (i == nEnd)
			{
				//Group对象结束的位置，新建最后一个Equation对象
				NewEquation(pGroup, strText, _pBuffer+nRight, i - nRight );
				break;
			}
		}
		else
		{
			i++;
		}
	}
}

//新建等式对象，pParentElement为等式对象的父节点，可以是Element或Group；strName为Equation对象的名称；
void CPNTplParse::NewEquation( CExBaseList *pParentElement, const CStringA &strName, char *pBuffer, long nLen )
{
	CStringA strText;

	CPNTplEquation *pPNTplEquation = new CPNTplEquation;  
	pPNTplEquation->m_strName = strName;
	pPNTplEquation->m_strID = strName; 
	strText.SetString(pBuffer, nLen);
	pPNTplEquation->m_strValue = strText;
	pParentElement->AddNewChild(pPNTplEquation);
}

//解析Element对象函数入口，当解析到Element对象时，递归调用
void CPNTplParse::ParseElement_Ex(CExBaseList *pCurrElement, char* _pBuffer, long nLen)
{
	if (pCurrElement->m_strName == PTT_KEY_CFG || pCurrElement->m_strName == PTT_KEY_IECParameter)
	{
		ParseElement_CDATA(pCurrElement, _pBuffer, nLen);
		return;
	}

	CStringA strText;
	char currCh;
	long nLeft, nRight;
	UINT nKeyType = 0;
	
	Offset(_pBuffer);
	nLeft = m_nCurrParsePos;
	long nBufferLen = nLen;

	while (m_nCurrParsePos < nBufferLen)
	{
		Offset(_pBuffer);
		currCh = _pBuffer[m_nCurrParsePos];

		switch(currCh)
		{
		case '<':
			{
				m_nCurrParsePos++;
				nKeyType = GetElementKey(strText, _pBuffer);  //获取Element对象标签名称

				//当Element的标签类型为Begin，则新建一个Element对象
				if (nKeyType == ELEMENT_KEY_BEGIN)
				{
					CPNTplElement *pPNTplElement = NULL;
					CString strTmp;
					strTmp = strText;

					if ((pCurrElement->GetClassID()==MNGRCLASSID_CPNTPLELEMENT)&&(((CPNTplElement*)pCurrElement)->IsRepeatNode(strTmp)))
					{
						pPNTplElement = (CPNTplElement *)pCurrElement;
					}
					else
					{
						pPNTplElement = new CPNTplElement;   
						pPNTplElement->m_strName = strText;  
						pCurrElement->AddNewChild(pPNTplElement);
						ParseElement_Ex(pPNTplElement, _pBuffer, nBufferLen);    //递归调用
					}
					
					nLeft = m_nCurrParsePos;
				}

				//当Element的标签类型为End时，认为当前Element对象解析完毕，该函数返回
				else if (nKeyType == ELEMENT_KEY_END)
				{
					return;
				}

				break;
			}
		case '=':
			{
				//解析到‘=’，有可能是Group对象，有可能仅是Equation对象
				Parse_GroupAndEquation(nLeft, nRight, (CPNTplElement*)pCurrElement, _pBuffer);
				
				break;
			}

		case ';':
			{
				//直接解析到‘；’，是Text对象
				Parse_Text(nLeft, (CPNTplElement*)pCurrElement, _pBuffer);

				break;
			}

		default:
			m_nCurrParsePos++;
			break;
		}//end of switch(currCh)
	}
}

void CPNTplParse::ParseElement_CDATA(CExBaseList *pCurrElement, char* pBuffer, long nLen)
{
	CStringA strElement;
	strElement = pCurrElement->m_strName;
	CStringA strText;
	char currCh;
	long nLeft, nRight;
	UINT nKeyType = 0;

	Offset(pBuffer);
	nLeft = m_nCurrParsePos;
	long nBufferLen = nLen;

	while (m_nCurrParsePos < nBufferLen)
	{
		Offset(pBuffer);
		currCh = pBuffer[m_nCurrParsePos];

		if(currCh == '<')
		{
			nRight = m_nCurrParsePos-1;
			m_nCurrParsePos++;
			nKeyType = GetElementKey(strText, pBuffer);  //获取Element对象标签名称

			if (nKeyType == ELEMENT_KEY_END)
			{
				if (strElement == strText)
				{
					strText.SetString(pBuffer+nLeft, nRight - nLeft);
					break;
				}
			}
		}
		else
		{
			m_nCurrParsePos++;   //shaolei  2018.11.09
		}
	}
}

//解析‘=’的函数入口
void CPNTplParse::Parse_GroupAndEquation(long &nLeft, long &nRight, CPNTplElement *pCurrElement, char* _pBuffer)
{
	CStringA strText;
	BOOL bGroup = FALSE;
	char currCh;
	CPNTplGroup* pPNTplGroup = NULL;
	long i;

	strText.SetString(_pBuffer + nLeft, m_nCurrParsePos - nLeft);
	strText.Trim();
	m_nCurrParsePos++;  //跳过=
	nRight = m_nCurrParsePos;

	currCh = _pBuffer[m_nCurrParsePos];
	bGroup = FALSE;

	//当当前字符不为‘;’时，获取下一个字符；
	//此为获取Equation对象结束的位置
	while (currCh != ';')
	{
		if (currCh == '<')
		{
			CStringA strTemp;
			m_nCurrParsePos++;  //执行GetElementKey前，m_nCurrParsePos++跳过“<”
			long nCurrPos = m_nCurrParsePos;

			//如果是End
			if (GetElementKey(strTemp, _pBuffer) == ELEMENT_KEY_END)
			{
				m_nCurrParsePos = nCurrPos - 2;  //在GetElementKey中，判断为End时，m_nCurrParsePos = nCurrPos+1；所以此处 -2；
				break;
			}
			else
				m_nCurrParsePos--;//如果不是ElementKey，则回到原指针位置
		}

		m_nCurrParsePos++;
		currCh = _pBuffer[m_nCurrParsePos];
	}

	//判断Equation对象是否需要特殊处理
	if (IsKey_Name(strText))
	{
	}
	else
	{
		i=nRight;

		for (i=nRight; i<m_nCurrParsePos; i++)
		{
			//当前Equation对象中还有其它‘=’，说明是一个Group对象；
			//将标识bGroup设置为TRUE；
			if (_pBuffer[i] == '=')
			{
				bGroup = TRUE;
				break;
			}
		}
	}

	//当是Group对象时，新建Group对象
	if (bGroup)
	{
		pPNTplGroup = new CPNTplGroup;
		pCurrElement->AddNewChild(pPNTplGroup);
		ParseGroup(pPNTplGroup, nLeft, m_nCurrParsePos, _pBuffer);
	}
	//否则新建Equation对象
	else
	{
		NewEquation(pCurrElement, strText, _pBuffer+nRight, m_nCurrParsePos - nRight );
	}

	m_nCurrParsePos++;
	nLeft = m_nCurrParsePos;
}

//解析Text对象的函数入口
void CPNTplParse::Parse_Text(long &nLeft, CPNTplElement *pCurrElement, char* _pBuffer)
{
	CStringA strText;
	CPNTplText *pPNTplText = new CPNTplText;
	long i = nLeft;

	while (i < m_nCurrParsePos)
	{
		//当解析到‘[’时，将‘[’之前的字符作为Text对象的名称
		if (_pBuffer[i] == '[')
		{
			strText.SetString(_pBuffer+nLeft, i-nLeft);
			strText.Trim();
			pPNTplText->m_strName = strText;
			break;
		}

		i++;
	}

	//当‘[’之前的字符为空或不存在‘[’时，设置Text对象的名称为Text
	if (pPNTplText->m_strName.GetLength() == 0)
	{
		pPNTplText->m_strName = _T("Text");
	}

	//将‘[’后面的字符作为Text对象的Text值
	strText.SetString(_pBuffer+nLeft, m_nCurrParsePos-nLeft);
	strText.Trim();
	pPNTplText->m_strText = strText;
	pCurrElement->AddNewChild(pPNTplText);

	m_nCurrParsePos++;
	nLeft = m_nCurrParsePos;      //iLeft记录上一个间隔符的位置；
}

void CPNTplParse::AdjustAllGroupKeys(CPNTplRoot* pPNTplRoot)
{
	//遍历Element：CommParameter、Setting、Binary、GlobalSetting、Report
	POS pos = NULL;
	CExBaseList* p = NULL;
	pos = pPNTplRoot->GetHeadPosition();

	while(pos != NULL)
	{
		p = (CExBaseList*)pPNTplRoot->GetNext(pos);

		if (p->m_strName != PTT_KEY_ProtectionRelay)
		{
			continue;
		}
			
		POS pos2 = p->GetHeadPosition();
		CExBaseObject *p2 = NULL;

		while (pos2 != NULL)
		{
			p2 = p->GetNext(pos2);

			if (IsNeedAdjust(p2))
			{
				AdjustElementKeys((CPNTplElement *)p2);
			}
		}
	}	
}

BOOL CPNTplParse::IsNeedAdjust(CExBaseObject *pElement)
{
	CString strElementName = pElement->m_strName;

	if (pElement->m_strName == PTT_KEY_CommonParameter)
	{
		return TRUE;
	}

	if (pElement->m_strName == PTT_KEY_Binary)
	{
		return TRUE;
	}

	if (pElement->m_strName == PTT_KEY_GlobalSetting)
	{
		return TRUE;
	}

	if (pElement->m_strName == PTT_KEY_Setting)
	{
		return TRUE;
	}

	if (pElement->m_strName == PTT_KEY_Report)
	{
		return TRUE;
	}

	if (pElement->m_strName == PTT_KEY_TextInput)
	{
		return TRUE;
	}
	
	return FALSE;
}

void CPNTplParse::AdjustElementKeys(CPNTplElement *pElement)
{
	if (pElement->GetCount() == 0)
	{
		return;
	}

	POS pos = NULL;
	CExBaseObject* p = NULL;
	CPNTplGroup *pGroup = NULL;

	p = pElement->GetHead();

	if (p->GetClassID() == MNGRCLASSID_CPNTPLGROUP)
	{
		return;
	}

	if (p->GetClassID() == MNGRCLASSID_CPNTPLELEMENT)
	{
		if (IsNeedAdjust(p))
		{
			AdjustElementKeys((CPNTplElement *)p);
			return;
		}
	}

	CExBaseList listElement;
	listElement.Append(pElement);//把pElement所有子节点放到ListElement
	pElement->RemoveAll();
	pos = listElement.GetHeadPosition();
	long nLen = 0;
	char chHead = 0;
	char ch2 = 0;

	while (pos != NULL)
	{
		p = listElement.GetNext(pos);
		chHead = p->m_strName.GetAt(0);

		if (chHead == 'N')
		{
			ch2 = p->m_strName.GetAt(1);

			if ('0' <= ch2 && ch2 <= '9')
			{
				pGroup = new CPNTplGroup();
				pElement->AddNewChild(pGroup);
				nLen = p->m_strName.GetLength() - 1;
			}
		}

		ASSERT( pGroup != NULL);

		if (chHead == 'S')
		{
			p->m_strName.Delete(1, nLen);
		}
		else
		{
			p->m_strName = p->m_strName.Left(p->m_strName.GetLength() - nLen);
		}

		p->m_strID = p->m_strName;
		pGroup->AddNewChild(p);
	}

	listElement.RemoveAll();
}

BOOL CPNTplParse::Save_PNTpleFile()
{
	CString strFile;
	strFile = _P_GetLibraryPath();
	CString strFilter = _T("设备点表文件(*.xml)|*.xml||");

	if (!PopupSaveAsFileDialog(NULL, strFile, strFilter, _T("xml")))
	{
		return FALSE;
	}

	m_oRoot.SaveXmlFile(strFile,CPNTplMngrXmlRWKeys::g_pXmlKeys);
	return TRUE;
}