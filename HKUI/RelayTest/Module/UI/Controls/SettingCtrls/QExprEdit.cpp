#include "StdAfx.h"
#include "QExprEdit.h"
#include "settingselectdlg.h"

BOOL QExprEdit::g_bIsInProcessing = FALSE;
CString QExprEdit::g_strExprEditCopyString = _T("");


QExprEdit::QExprEdit(QWidget *parent) : QTextEdit(parent)
{
	m_bPressSHIFT = false;
	m_bPressCONTROL = false;
	installEventFilter(this);
}

QExprEdit::~QExprEdit()
{
}

void QExprEdit::SetExprScript(const CString &strScript)
{
	m_oExprTextUnitList.DeleteAll();
	setText("");

	//20241009 huangliang ����ʾԭ��ֵ
	//if (g_pDvmDevice_AttachSetting == NULL)
	//{
	//	return ;
	//}

	////20240909 huangliang �Ѿ�ȥ�����ڵ�ID�����Դ˴�����Ҫ��ת��
	////����������ģ���ж���ȫ·���ǰ���������ģ���ļ�·�������²�֧�ֽ����������滻
	////QString sRepaceHead = HL_REPACE_FULLPATH_HEAD;
	////QString sHeadPath = g_pDvmDevice_AttachSetting->m_strID;
	//QString strNewSrcPath = strScript;
	////strNewSrcPath.replace(sHeadPath, sRepaceHead);
	//m_oExprTextUnitList.SetExprScript(strNewSrcPath);

	////�ٰѱ��ʽ������ID�滻��ȥ����������ʾ����
	//POS pos = m_oExprTextUnitList.GetHeadPosition();
	//CExprTextUnit *pExpVar = NULL;
	//while (pos != NULL)
	//{
	//	pExpVar = m_oExprTextUnitList.GetNext(pos);
	//	if (pExpVar != NULL)
	//	{
	//		//if (pExpVar->m_strUnitScpt.indexOf(sRepaceHead) != -1)
	//		{
	//			//pExpVar->m_strUnitScpt.replace(sRepaceHead, sHeadPath);	//�滻��ԭȫ·��ID

	//			CExBaseObject * pFindItem = CSttGlobalModel::FindObjectFromDeviceModel(pExpVar->m_strUnitScpt);
	//			if (pFindItem != NULL)
	//				pExpVar->m_strUnitText = pFindItem->m_strName;
	//			//else
	//			//	pExpVar->m_strUnitText = "δ�ҵ�";
	//		}				
	//	}
	//}

	//QString sText = m_oExprTextUnitList.GetExprScriptText();
	//setText(sText);
}
void QExprEdit::SetExprScriptText(const CString &strScriptText)
{
	m_oExprTextUnitList.DeleteAll();
	m_strExprScript = strScriptText;
	m_oExprTextUnitList.SetExprScript(strScriptText);

	QString sText = m_oExprTextUnitList.GetExprScriptText();
	setText(sText);
}

void QExprEdit::GetExprScript(CString& strString) const
{
	if (g_bIsInProcessing)
	{
		strString = m_strExprScript;
	}
	else
	{
		m_oExprTextUnitList.GetExprScript(strString);
	}
}

void QExprEdit::GetWindowShowText(CString& strString) const
{
	if (g_bIsInProcessing)
	{
		strString = m_strExprScript;
	}
	else
	{
		m_oExprTextUnitList.GetExprScriptText(strString);
	}
}

void QExprEdit::InsertFunc(const CString &strFunc)
{
	int nBegin, nEnd;
	getPosition(nBegin, nEnd);

	InsertText(strFunc, strFunc);
	nBegin += strFunc.GetLength();

	setPosition(nBegin, nBegin);

	InsertText(_T("("), _T("("));
	InsertText(_T(")"), _T(")"));

	//������Ӻ����󣬹���ں���()�м�
	nBegin += 1;
	setPosition(nBegin, nBegin);
}

void QExprEdit::InsertText(const CString &strID, const CString &strName)
{
	int nBegin, nEnd;
	getPosition(nBegin, nEnd);

	//�����ѡ�еĲ��֣��򲻴���
	if (nBegin != nEnd)
	{
		CExprTextUnit *pExptrUnit = m_oExprTextUnitList.GetExprTextUnit(nBegin, nEnd);

		if (pExptrUnit != NULL)
		{
			pExptrUnit->m_strUnitScpt = strID;
			pExptrUnit->m_strUnitText = strName;
			m_oExprTextUnitList.InitStringUnit(pExptrUnit);
			DoUpdate(nBegin + strName.GetLength() + 1);
		}

		return;
	}

	long nLen = strID.GetLength();

	if (nLen == 0)
	{
		return;
	}

	//ֻ��һ���ַ�������OnCharPrintchar
	if (nLen == 1)
	{
		TCHAR chChar = strID.GetAt(0);
		OnCharPrintchar(chChar);
		return;
	}

	CExprTextUnit *pCurr = m_oExprTextUnitList.GetExprTextUnit(nBegin, nBegin);

	if (pCurr == NULL)
	{//1,,pCurr==NULL
		CExprTextUnit *pPrev = m_oExprTextUnitList.FindPrevExprTextUnit(pCurr);

		//1-1,pCurr==NULL��Prev==NULL
		if (pPrev == NULL)
		{
			CExprTextUnit *pExptrUnit = new CExprTextUnit(strID);
			pExptrUnit->m_strUnitText = strName;
			m_oExprTextUnitList.AddTail(pExptrUnit);
			m_oExprTextUnitList.InitStringUnit(pExptrUnit);
			DoUpdate(nBegin);
		}
		else
		{//1-1,pCurr==NULL��Prev!=NULL
			if (pPrev->IsOptr() || pPrev->IsFunc())
			{//1-1-1,pCurr==NULL��Prev!=NULL��pPrevΪOptr����Func
				CExprTextUnit *pExptrUnit = new CExprTextUnit(strID);
				pExptrUnit->m_strUnitText = strName;
				m_oExprTextUnitList.AddTail(pExptrUnit);
				m_oExprTextUnitList.InitStringUnit(pExptrUnit);
				DoUpdate(nBegin);
			}
			else
			{//1-1-2,pCurr==NULL��Prev!=NULL��pPrev��ΪOptr����Func

			}
		}
	}
	else
	{//1-2,pCurr!=NULL
		int nUnitBegin, nUnitEnd;
		m_oExprTextUnitList.GetExprTextUnitPos(pCurr, nUnitBegin, nUnitEnd);

		if (nBegin < nUnitBegin && nBegin <= nEnd)
		{//1-2,pCurr!=NULL����ǰλ�����м䣬������
			return;
		}
		else
		{//1-2,pCurr!=NULL����ǰλ�ò����м�
			CExprTextUnit *pPrev = m_oExprTextUnitList.FindPrevExprTextUnit(pCurr);

			if (pPrev == NULL)
			{//1-2-1,pCurr!=NULL����ǰλ�ò����м䣺pPrev == NULLͷ��
				if (pCurr->IsOptr() || pCurr->IsFunc())
				{//1-2-1,pCurr!=NULL����ǰλ�ò����м䣺ͷ������ǰΪOptr
					CExprTextUnit *pExptrUnit = new CExprTextUnit(strID);
					pExptrUnit->m_strUnitText = strName;
					m_oExprTextUnitList.AddHead(pExptrUnit);
					m_oExprTextUnitList.InitStringUnit(pExptrUnit);
					DoUpdate(nBegin);
				}
				else
				{//

				}
			}
			else
			{//1-2-2,pCurr!=NULL����ǰλ�ò����м䣺pPrev!=NULL����Unit�м�
				if (pPrev->IsOptr() && pCurr->IsOptr())
				{
					CExprTextUnit *pExptrUnit = new CExprTextUnit(strID);
					pExptrUnit->m_strUnitText = strName;
					POS pos = m_oExprTextUnitList.Find(pPrev);
					m_oExprTextUnitList.InsertAfter(pos, pExptrUnit);
					m_oExprTextUnitList.InitStringUnit(pExptrUnit);
					DoUpdate(nBegin);
				}
			}
		}
	}
}

bool QExprEdit::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::KeyPress /*|| event->type() == QEvent::KeyRelease*/)
	{
		QKeyEvent *keyEvent = (QKeyEvent *)(event);
		int nChar = keyEvent->key();		
		if (keyEvent->key() == Qt::Key_Backspace)
		{
			OnCharBackspace(nChar);
			return true;//��ʶִ�й��ˣ�eventFilter���ٴ���
		}
		else if (keyEvent->key() == Qt::Key_Delete)
		{
			if (!m_bPressSHIFT)
			{
				// Special processing
				OnCharDelete(nChar);
				return true;//��ʶִ�й��ˣ�eventFilter���ٴ���
			}
		}
		else if (!m_bPressCONTROL)
		{
			OnCharPrintchar(nChar);
			return true;
		}
	}

	if (event->type() == QEvent::KeyPress )
	{
		QKeyEvent *keyEvent = (QKeyEvent *)(event);
		if (keyEvent->key() == Qt::Key_Control)
		{
			m_bPressCONTROL = true;			//��¼Ctrl����
		}
		else if (keyEvent->key() == Qt::Key_Shift)
		{
			m_bPressSHIFT = true;			//��¼Shift����
		}
	}
	else if ( event->type() == QEvent::KeyRelease)
	{
		QKeyEvent *keyEvent = (QKeyEvent *)(event);
		if (keyEvent->key() == Qt::Key_Control)
		{
			m_bPressCONTROL = false;
		}
		else if (keyEvent->key() == Qt::Key_Shift)
		{
			m_bPressSHIFT = false;
		}
	}

	return QTextEdit::eventFilter(obj, event);
}

void QExprEdit::mousePressEvent(QMouseEvent *event)
{
	//��������˾ʹ���clicked�ź�
	if (event->button() == Qt::LeftButton)
	{
		QTextEdit::mousePressEvent(event);
		OnLButtonUp();
		return;
	}

	//�����¼��������ദ��
	QTextEdit::mousePressEvent(event);
}
void QExprEdit::OnLButtonUp()
{
	int nStart, nEnd;
	getPosition(nStart, nEnd);

	CExprTextUnitList oExprTextUnitList;
	m_oExprTextUnitList.GetExprTextUnits(nStart, nEnd, oExprTextUnitList);
	BOOL bSetSel = FALSE;

	if (oExprTextUnitList.GetCount() == 1)
	{
		CExprTextUnit *pExprTextUnit = oExprTextUnitList.GetHead();

		if (pExprTextUnit->IsOptr())
		{
			nStart = nEnd;
			//CEdit::SetSel(nEnd, nEnd);
		}
		else
		{
			m_oExprTextUnitList.GetExprTextUnitPos(pExprTextUnit, nStart, nEnd);
			//CEdit::SetSel(nStart, nEnd);
		}
	}
	else
	{
		nStart = nEnd;
		//CEdit::SetSel(nEnd, nEnd);
	}

	oExprTextUnitList.RemoveAll();

	setPosition(nStart, nEnd);
}

BOOL QExprEdit::IsCharOptr(TCHAR chChar)
{
	static QString g_ptcharOptr = _T("+-*/(),\0\0\0\0\0\0\0\0");
	//ASSERT(_istprint(chChar) != FALSE);
	for (int i = 0; i < g_ptcharOptr.length(); i++)
	{
		if (chChar == g_ptcharOptr.at(i))
		{
			return true;
		}
	}
	return FALSE;
}

BOOL QExprEdit::IsCharDigit(TCHAR chChar)
{
	if ('0' <= chChar && chChar <= '9')
	{
		return TRUE;
	}

	if (chChar == '.')
	{
		return TRUE;
	}

	return FALSE;
}

BOOL QExprEdit::CheckChar(TCHAR chChar, int nPos) // returns TRUE if the symbol is valid
{
	if (IsCharOptr(chChar))
	{
		return TRUE;
	}

	if (IsCharDigit(chChar))
	{
		return TRUE;
	}
	return FALSE;
}

void QExprEdit::OnCharPrintchar(UINT nChar)
{
	TCHAR chChar = (TCHAR)nChar;
	ASSERT(_istprint(chChar) != FALSE);

	int nStartPos, nEndPos;
	getPosition(nStartPos, nEndPos);

	ASSERT(nStartPos >= 0);
	ASSERT(nEndPos >= 0);
	ASSERT(nEndPos >= nStartPos);

	//�����ѡ�еĲ��֣����ܲ���
	if (nEndPos != nStartPos)
	{
		CExprTextUnit *pExptrUnit = m_oExprTextUnitList.GetExprTextUnit(nStartPos, nEndPos);

		if (pExptrUnit != NULL)
		{
			pExptrUnit->m_strUnitScpt = QString(chChar, 1);
			pExptrUnit->m_strUnitText = QString(chChar, 1);
			DoUpdate(nStartPos + 1);
		}

		return;
	}

	//ֻ�ܴ������ֺ�������ŵ�����
	if (IsCharDigit(chChar) || IsCharOptr(chChar))
	{

	}
	else
	{
		return;
	}

	// 	if (!m_oExprTextUnitList.CanInsertChar(nEndPos))
	// 	{
	// 		return;
	// 	}

	//��ȡ��ǰλ�õ�TextUnit����ǰλ����ָ���λ��֮���TextUnit
	CExprTextUnit *pExptrUnit = m_oExprTextUnitList.GetExprTextUnit(nEndPos, nEndPos);

	//////////////////////////////////////////////////////////////////////////
	//1,���û���ҵ�����ʾΪ�ջ��߹��λ��ĩβ
	if (pExptrUnit == NULL)
	{
		CExprTextUnit *pTail = m_oExprTextUnitList.GetTail();

		//1-1,Ϊ��
		if (pTail == NULL)
		{
			pExptrUnit = new CExprTextUnit(chChar);
			m_oExprTextUnitList.AddTail(pExptrUnit);
			DoUpdate(nEndPos + 1);
			return;
		}
		else
		{//1-2
			//1-2-1��Ϊ��
			if (IsCharDigit(chChar))
			{
				if (pTail->IsVariable())
				{//1-2-1-1��ǰ����������֣����һ���Ǳ��������ܴ���
					return;
				}

				if (pTail->IsOptr() || pTail->IsFunc())
				{//1-2-1-3��������������ţ��������ֶ���
					pExptrUnit = new CExprTextUnit(chChar);
					m_oExprTextUnitList.AddTail(pExptrUnit);
					DoUpdate(nEndPos + 1);
					return;
				}

				if (pTail->IsNumber())
				{//1-2-1-2���֣�����ӵ��ַ�����ĩβ
					pTail->AppendChar(chChar);
					DoUpdate(nEndPos + 1);
					return;
				}

				return;
			}
			else if (IsCharOptr(chChar))
			{//1-2-2
				pExptrUnit = new CExprTextUnit(chChar);
				m_oExprTextUnitList.AddTail(pExptrUnit);
				DoUpdate(nEndPos + 1);
			}
		}

		//�����ĸ��������������
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	//2,��ǰλ���ж���
	int nUnitBegin, nUnitEnd;
	m_oExprTextUnitList.GetExprTextUnitPos(pExptrUnit, nUnitBegin, nUnitEnd);

	//2-1:��ǰλ���ж��󣺹��λ��λ�ڵ�ǰ������м�
	if (nUnitBegin < nEndPos && nEndPos <= nEndPos)
	{
		if (pExptrUnit->IsNumber() && IsCharDigit(chChar))
		{//2-1-1:��ǰλ���ж��󣺹��λ��λ�ڵ�ǰ������м䣺��ǰλ��Ϊ���ֲ��ҵ�ǰ�ַ�Ϊ����
			nUnitBegin = nEndPos - nUnitBegin;
			pExptrUnit->InsertChar(chChar, nUnitBegin);
			DoUpdate(nEndPos + 1);
		}

		return;
	}

	//2-2 :��ǰλ���ж��󣺵�ǰ��겻λ�ڵ�ǰ������м�
	//2-2-1  ��ǰλ���ж��󣺵�ǰ��겻λ�ڵ�ǰ������м䣺��ǰ�ַ�ΪOptr
	if (IsCharOptr(chChar))
	{
		CExprTextUnit *pPrev = m_oExprTextUnitList.FindPrevExprTextUnit(pExptrUnit);

		if (pPrev == NULL)
		{//2-2-1-1 ��ǰλ���ж��󣺵�ǰ��겻λ�ڵ�ǰ������м䣺��ǰ�ַ�ΪOptr��֮ǰû�ж��󣬲��뵽ͷ��
			pExptrUnit = new CExprTextUnit(chChar);
			m_oExprTextUnitList.AddHead(pExptrUnit);
			DoUpdate(nEndPos + 1);
		}
		else
		{//2-2-1-2 ��ǰλ���ж��󣺵�ǰ��겻λ�ڵ�ǰ������м䣺��ǰ�ַ�ΪOptr��֮ǰ�ж��󣬲��뵽�м�λ��
			POS pos = m_oExprTextUnitList.Find(pPrev);
			ASSERT(pos != NULL);
			pExptrUnit = new CExprTextUnit(chChar);
			m_oExprTextUnitList.InsertAfter(pos, pExptrUnit);
			DoUpdate(nEndPos + 1);
		}

		return;
	}

	//2-2-2 :��ǰλ���ж��󣺵�ǰ��겻λ�ڵ�ǰ������м䣺��ǰ�ַ�Ϊ����
	if (IsCharDigit(chChar))
	{
		CExprTextUnit *pPrev = m_oExprTextUnitList.FindPrevExprTextUnit(pExptrUnit);

		if (pPrev == NULL)
		{//2-2-2-1����ǰλ���ж��󣺵�ǰ��겻λ�ڵ�ǰ������м䣺��ǰ�ַ�Ϊ���� �� λ��ͷ��
			if (pExptrUnit->IsOptr())
			{//2-2-2-1-2����ǰλ���ж��󣺵�ǰ��겻λ�ڵ�ǰ������м䣺��ǰ�ַ�Ϊ���� �� λ��ͷ������ǰλ��Ϊ�������
				pExptrUnit = new CExprTextUnit(chChar);
				m_oExprTextUnitList.AddHead(pExptrUnit);
				DoUpdate(nEndPos + 1);
			}
			else if (pExptrUnit->IsNumber())
			{//2-2-2-1-1����ǰλ���ж��󣺵�ǰ��겻λ�ڵ�ǰ������м䣺��ǰ�ַ�Ϊ���� �� λ��ͷ������ǰλ��Ϊ����
				pExptrUnit->m_strUnitScpt = chChar + pExptrUnit->m_strUnitScpt;
				pExptrUnit->m_strUnitText = pExptrUnit->m_strUnitScpt;
				DoUpdate(nEndPos + 1);
			}
			else
			{//2-2-2-1-2����ǰλ���ж��󣺵�ǰ��겻λ�ڵ�ǰ������м䣺��ǰ�ַ�Ϊ���� �� λ��ͷ������ǰλ��Ϊ���������������

			}

			return;
		}
		else
		{//2-2-2-2����ǰλ���ж��󣺵�ǰ��겻λ�ڵ�ǰ������м䣺��ǰ�ַ�Ϊ���� �� λ���м�
			if (pPrev->IsOptr() || pPrev->IsFunc())
			{//2-2-2-2-1����ǰλ���ж��󣺵�ǰ��겻λ�ڵ�ǰ������м䣺��ǰ�ַ�Ϊ���� �� λ���м䣺pPrevΪ������Ż��ߺ���
				if (pExptrUnit->IsNumber())
				{///2-2-2-2-1-1����ǰλ���ж��󣺵�ǰ��겻λ�ڵ�ǰ������м䣺��ǰ�ַ�Ϊ���� �� λ���м䣺pPrevΪ������Ż��ߺ�������ǰλ��Ϊ����
					pExptrUnit->m_strUnitScpt = chChar + pExptrUnit->m_strUnitScpt;
					pExptrUnit->m_strUnitText = pExptrUnit->m_strUnitScpt;
					DoUpdate(nEndPos + 1);
				}
				else if (pExptrUnit->IsOptr() || pExptrUnit->IsFunc())
				{///2-2-2-2-1-1����ǰλ���ж��󣺵�ǰ��겻λ�ڵ�ǰ������м䣺��ǰ�ַ�Ϊ���� �� λ���м䣺pPrevΪ������Ż��ߺ�������ǰλ��Ϊ�����������
					POS pos = m_oExprTextUnitList.Find(pPrev);
					ASSERT(pos != NULL);
					pExptrUnit = new CExprTextUnit(chChar);
					m_oExprTextUnitList.InsertAfter(pos, pExptrUnit);
					DoUpdate(nEndPos + 1);
				}
				else
				{///2-2-2-2-1-1����ǰλ���ж��󣺵�ǰ��겻λ�ڵ�ǰ������м䣺��ǰ�ַ�Ϊ���� �� λ���м䣺pPrevΪ������Ż��ߺ������������������

				}
			}
			else
			{//2-2-2-2-1����ǰλ���ж��󣺵�ǰ��겻λ�ڵ�ǰ������м䣺��ǰ�ַ�Ϊ���� �� λ���м䣺pPrevΪ�������������
				if (pPrev->IsNumber())
				{
					pPrev->m_strUnitScpt = pPrev->m_strUnitScpt + chChar;
					pPrev->m_strUnitText = pPrev->m_strUnitScpt;
					DoUpdate(nEndPos + 1);
				}
			}
			return;
		}
	}

}

int QExprEdit::GetSelExprTextUnits(CExprTextUnitList &oList)
{
	oList.RemoveAll();

	int nStartPos, nEndPos;
	getPosition(nStartPos, nEndPos);

	m_oExprTextUnitList.GetExprTextUnits(nStartPos, nEndPos, oList);

	long nCount = oList.GetCount();
	oList.RemoveAll();

	return nCount;
}

void QExprEdit::OnCharBackspace(UINT nChar)
{
	g_bIsInProcessing = TRUE;
	//��ȡ��ǰλ�ã���ȡǰһλ�õ�����
	int nStartPos, nEndPos;
	getPosition(nStartPos, nEndPos);

	ASSERT(nStartPos >= 0);
	ASSERT(nEndPos >= 0);
	ASSERT(nEndPos >= nStartPos);

	if (nStartPos == 0 && nEndPos == 0)
	{
		g_bIsInProcessing = FALSE;
		return;
	}

	CExprTextUnitList oList;
	m_oExprTextUnitList.GetExprTextUnits(nStartPos, nEndPos, oList);

	if (oList.GetCount() == 0)
	{
		CString strText = m_oExprTextUnitList.GetExprScriptText();
		if (nStartPos == nEndPos && nStartPos == strText.GetLength())
		{
			CExprTextUnit *p = m_oExprTextUnitList.GetTail();
			m_oExprTextUnitList.DeleteExprTextUnit(p);
			g_bIsInProcessing = FALSE;
			DoUpdate(nStartPos);
		}

		g_bIsInProcessing = FALSE;
		return;
	}

	if (nStartPos == nEndPos)
	{
		CExprTextUnit *p = oList.GetHead();
		CExprTextUnit *pPrev = m_oExprTextUnitList.FindPrevExprTextUnit(p);

		if (pPrev != NULL)
		{
			m_oExprTextUnitList.GetExprTextUnitPos(pPrev, nStartPos, nEndPos);
			m_oExprTextUnitList.DeleteExprTextUnit(pPrev);
			oList.RemoveAll();
			g_bIsInProcessing = FALSE;
			DoUpdate(nStartPos);			
		}
	}
	else
	{
		POS pos = oList.GetHeadPosition();
		CExprTextUnit *p = NULL;

		while (pos != NULL)
		{
			p = oList.GetNext(pos);
			m_oExprTextUnitList.DeleteExprTextUnit(p);
		}

		oList.RemoveAll();
		g_bIsInProcessing = FALSE;
		DoUpdate(nStartPos);
	}

}

void QExprEdit::OnCharDelete(UINT nChar)
{
	g_bIsInProcessing = TRUE;
	int nStartPos, nEndPos;
	getPosition(nStartPos, nEndPos);

	ASSERT(nStartPos >= 0);
	ASSERT(nEndPos >= 0);
	ASSERT(nEndPos >= nStartPos);

	CExprTextUnitList oList;
	m_oExprTextUnitList.GetExprTextUnits(nStartPos, nEndPos, oList);

	if (oList.GetCount() == 0)
	{
		g_bIsInProcessing = FALSE;
		return;
	}

	POS pos = oList.GetHeadPosition();
	CExprTextUnit *p = oList.GetHead();
	m_oExprTextUnitList.GetExprTextUnitPos(p, nStartPos, nEndPos);

	while (pos != NULL)
	{
		p = oList.GetNext(pos);
		m_oExprTextUnitList.DeleteExprTextUnit(p);
	}

	oList.RemoveAll();
	g_bIsInProcessing = FALSE;

	DoUpdate(nStartPos);
}

void QExprEdit::GetGroupBounds(int &nBegin, int &nEnd, int nStartPos, BOOL bForward)
{
	nBegin = 0;
	nEnd = 1024;
}

BOOL QExprEdit::DoUpdate(int nPos)
{
	m_strExprScript = m_oExprTextUnitList.GetExprScriptText();
	setText(m_strExprScript);

	setPosition(nPos, nPos);

	m_strExprScript = m_oExprTextUnitList.GetExprScript();

	if (m_oExprTextUnitList.m_pExprVariableFind != NULL)
	{
		m_oExprTextUnitList.m_pExprVariableFind->OnExprScriptChanged(m_strExprScript);
	}

	return TRUE;
}

void QExprEdit::UpdateCursor()
{
	CString sText;
	GetWindowShowText(sText);

	int nPos = sText.length();
	setPosition(nPos, nPos);
}

void QExprEdit::getPosition(int &nBegin, int &nEnd)
{
	QTextCursor cursor = this->textCursor();
	nBegin = cursor.selectionStart();
	nEnd = cursor.selectionEnd();
}
void QExprEdit::setPosition(int nBegin, int nEnd)
{
	QTextCursor cursor = this->textCursor();
	int iLen = toPlainText().length();
	if (nBegin > iLen || nEnd > iLen)
	{
		cursor.movePosition(QTextCursor::End);
		this->setTextCursor(cursor);
	}
	else
	{
		cursor.setPosition(nBegin);
		cursor.setPosition(nEnd, QTextCursor::KeepAnchor);
		this->setTextCursor(cursor);
	}
}
