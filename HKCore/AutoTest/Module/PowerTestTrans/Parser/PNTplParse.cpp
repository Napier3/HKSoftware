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
	//return PopupOpenFileDialog(NULL, strPath, _T("tpl | *.tpl;|tpl (*.tpl)|*.tpl|"), _T("tpl"), _T("ѡ��PowerTestģ���ļ�"));
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

//�ж��ַ��Ƿ�Ϊ��ĸ�����ǣ�����TRUE�����򷵻�FALSE
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

//������ֽ�ȡ��������һ������ĸ���ַ�Ϊ��>��������strKey������ǰλ���Ƶ���>���󣬲�����Element����
UINT CPNTplParse::GetElementKey(CStringA &strKey, char *_pBuffer)
{
	long nCurrPos = m_nCurrParsePos;
	char ch = _pBuffer[nCurrPos];

	while (IsChar(ch))
	{
		nCurrPos++;
		ch = _pBuffer[nCurrPos];
	}
	//�������ĵ�һ������ĸ�ַ����ǡ�>����˵������Element
	if (ch != '>')
	{
// 		char *pTmp = _pBuffer + nCurrPos;
// 		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("����Powertestģ�����ʱ<>����."));
		return ELEMENT_KEY_ERR;
	}

	char *pTemp = _pBuffer + nCurrPos - 3;

	//�����End������strKey�󷵻�
	if (*pTemp == 'E' && *(pTemp + 1) == 'n' && *(pTemp + 2) == 'd')
	{
		strKey.SetString(_pBuffer+m_nCurrParsePos, nCurrPos - m_nCurrParsePos - 3);
		m_nCurrParsePos = nCurrPos+1;
		return ELEMENT_KEY_END;
	}

	//�����Begin������strKey�󷵻�
	//��ǰĬ��Element��ǩֻ��End��Begin
	else
	{
		if ((nCurrPos - m_nCurrParsePos - 5)<0)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,_T("����Powertestģ�����ʱ<>����."));
			return ELEMENT_KEY_ERR;
		}

		char *pTmp = (_pBuffer+nCurrPos-5);

		if (strnicmp(pTmp,("Begin"),5) != 0)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,_T("����Powertestģ�����ʱ<>����."));
			return ELEMENT_KEY_ERR;
		}

		strKey.SetString(_pBuffer+m_nCurrParsePos, nCurrPos - m_nCurrParsePos - 5);
		m_nCurrParsePos = nCurrPos+1;
		return ELEMENT_KEY_BEGIN;
	}
}

//������Ч�ַ����ո�tab�������з���
void CPNTplParse::Offset(char* _pBuffer)
{
	char chCurr = _pBuffer[m_nCurrParsePos];

	while (chCurr == VK_SPACE || chCurr == VK_TAB || chCurr == '\r' || chCurr == '\n')
	{
		m_nCurrParsePos++;
		chCurr = _pBuffer[m_nCurrParsePos];
	}
}

//�����������
BOOL CPNTplParse::Parse_PN_Tpl_ex(char *_pTplBuff, long nLen)
{
	int i = 0;
	char chCurr;
	m_nCurrParsePos = 0;
	//char* pFileBuff = _pTplBuff;
	m_oRoot.DeleteAll();

	//������Ч�ַ�
	Offset(_pTplBuff);

	//ģ���ļ��ĵ�һ����Ч�ַ�Ϊ��<��
	ASSERT (_pTplBuff[m_nCurrParsePos] == '<');

	UINT nKeyType = 0;
	CStringA strKey;
	long nBufferLen = nLen;

	while (TRUE)
	{
		//����ǰ����λ�ó���������ʱ������ѭ��
		if (m_nCurrParsePos >= nBufferLen)
		{
			break;
		}

		Offset(_pTplBuff);
		
		//��ֹģ���ļ�ĩβ������Ч�ַ���
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

			//ģ���ļ��ĵ�һ��Element��Ȼ��Begin
			ASSERT (nKeyType == ELEMENT_KEY_BEGIN);

			//��ǰλ���ڡ�>���󣬵��ú���ParseElement_Ex(pPNTplElement)
			CPNTplElement *pPNTplElement = new CPNTplElement;   
			pPNTplElement->m_strName = strKey;  
			m_oRoot.AddNewChild(pPNTplElement);
			ParseElement_Ex(pPNTplElement, _pTplBuff, nBufferLen);
		}
		else
		{
			//��ʾ������Ϣ
			break;
		}
	}

	return TRUE;
}

//Equation�������⴦��
//����=�����Ϊ��TESTNAME��ʱ���϶���Ҫ���⴦������TRUE�����򷵻�FALSE��
//��ǰ������TESTNAME��������������������������ڴ˴���ӣ�
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

//����Group����nBegin��nEnd�ֱ���Group�������ֹλ�ã�
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
			//��¼Equation��������ƣ�
			strText.SetString(_pBuffer+nLeft, i - nLeft);
			strText.Trim();
			nRight = i + 1;
			i++;

			while (i<nEnd)
			{
				if (_pBuffer[i] == ',')
				{
					if (_pBuffer[i+1] == ',') //����������,��
					{
						i++;
					}
					else
					{
					//�½���ʽ����
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
				//Group���������λ�ã��½����һ��Equation����
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

//�½���ʽ����pParentElementΪ��ʽ����ĸ��ڵ㣬������Element��Group��strNameΪEquation��������ƣ�
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

//����Element��������ڣ���������Element����ʱ���ݹ����
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
				nKeyType = GetElementKey(strText, _pBuffer);  //��ȡElement�����ǩ����

				//��Element�ı�ǩ����ΪBegin�����½�һ��Element����
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
						ParseElement_Ex(pPNTplElement, _pBuffer, nBufferLen);    //�ݹ����
					}
					
					nLeft = m_nCurrParsePos;
				}

				//��Element�ı�ǩ����ΪEndʱ����Ϊ��ǰElement���������ϣ��ú�������
				else if (nKeyType == ELEMENT_KEY_END)
				{
					return;
				}

				break;
			}
		case '=':
			{
				//��������=�����п�����Group�����п��ܽ���Equation����
				Parse_GroupAndEquation(nLeft, nRight, (CPNTplElement*)pCurrElement, _pBuffer);
				
				break;
			}

		case ';':
			{
				//ֱ�ӽ���������������Text����
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
			nKeyType = GetElementKey(strText, pBuffer);  //��ȡElement�����ǩ����

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

//������=���ĺ������
void CPNTplParse::Parse_GroupAndEquation(long &nLeft, long &nRight, CPNTplElement *pCurrElement, char* _pBuffer)
{
	CStringA strText;
	BOOL bGroup = FALSE;
	char currCh;
	CPNTplGroup* pPNTplGroup = NULL;
	long i;

	strText.SetString(_pBuffer + nLeft, m_nCurrParsePos - nLeft);
	strText.Trim();
	m_nCurrParsePos++;  //����=
	nRight = m_nCurrParsePos;

	currCh = _pBuffer[m_nCurrParsePos];
	bGroup = FALSE;

	//����ǰ�ַ���Ϊ��;��ʱ����ȡ��һ���ַ���
	//��Ϊ��ȡEquation���������λ��
	while (currCh != ';')
	{
		if (currCh == '<')
		{
			CStringA strTemp;
			m_nCurrParsePos++;  //ִ��GetElementKeyǰ��m_nCurrParsePos++������<��
			long nCurrPos = m_nCurrParsePos;

			//�����End
			if (GetElementKey(strTemp, _pBuffer) == ELEMENT_KEY_END)
			{
				m_nCurrParsePos = nCurrPos - 2;  //��GetElementKey�У��ж�ΪEndʱ��m_nCurrParsePos = nCurrPos+1�����Դ˴� -2��
				break;
			}
			else
				m_nCurrParsePos--;//�������ElementKey����ص�ԭָ��λ��
		}

		m_nCurrParsePos++;
		currCh = _pBuffer[m_nCurrParsePos];
	}

	//�ж�Equation�����Ƿ���Ҫ���⴦��
	if (IsKey_Name(strText))
	{
	}
	else
	{
		i=nRight;

		for (i=nRight; i<m_nCurrParsePos; i++)
		{
			//��ǰEquation�����л���������=����˵����һ��Group����
			//����ʶbGroup����ΪTRUE��
			if (_pBuffer[i] == '=')
			{
				bGroup = TRUE;
				break;
			}
		}
	}

	//����Group����ʱ���½�Group����
	if (bGroup)
	{
		pPNTplGroup = new CPNTplGroup;
		pCurrElement->AddNewChild(pPNTplGroup);
		ParseGroup(pPNTplGroup, nLeft, m_nCurrParsePos, _pBuffer);
	}
	//�����½�Equation����
	else
	{
		NewEquation(pCurrElement, strText, _pBuffer+nRight, m_nCurrParsePos - nRight );
	}

	m_nCurrParsePos++;
	nLeft = m_nCurrParsePos;
}

//����Text����ĺ������
void CPNTplParse::Parse_Text(long &nLeft, CPNTplElement *pCurrElement, char* _pBuffer)
{
	CStringA strText;
	CPNTplText *pPNTplText = new CPNTplText;
	long i = nLeft;

	while (i < m_nCurrParsePos)
	{
		//����������[��ʱ������[��֮ǰ���ַ���ΪText���������
		if (_pBuffer[i] == '[')
		{
			strText.SetString(_pBuffer+nLeft, i-nLeft);
			strText.Trim();
			pPNTplText->m_strName = strText;
			break;
		}

		i++;
	}

	//����[��֮ǰ���ַ�Ϊ�ջ򲻴��ڡ�[��ʱ������Text���������ΪText
	if (pPNTplText->m_strName.GetLength() == 0)
	{
		pPNTplText->m_strName = _T("Text");
	}

	//����[��������ַ���ΪText�����Textֵ
	strText.SetString(_pBuffer+nLeft, m_nCurrParsePos-nLeft);
	strText.Trim();
	pPNTplText->m_strText = strText;
	pCurrElement->AddNewChild(pPNTplText);

	m_nCurrParsePos++;
	nLeft = m_nCurrParsePos;      //iLeft��¼��һ���������λ�ã�
}

void CPNTplParse::AdjustAllGroupKeys(CPNTplRoot* pPNTplRoot)
{
	//����Element��CommParameter��Setting��Binary��GlobalSetting��Report
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
	listElement.Append(pElement);//��pElement�����ӽڵ�ŵ�ListElement
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
	CString strFilter = _T("�豸����ļ�(*.xml)|*.xml||");

	if (!PopupSaveAsFileDialog(NULL, strFile, strFilter, _T("xml")))
	{
		return FALSE;
	}

	m_oRoot.SaveXmlFile(strFile,CPNTplMngrXmlRWKeys::g_pXmlKeys);
	return TRUE;
}