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

	//20241009 huangliang 不显示原来值
	//if (g_pDvmDevice_AttachSetting == NULL)
	//{
	//	return ;
	//}

	////20240909 huangliang 已经去掉根节点ID，所以此处不需要再转换
	////因我们数据模板中对象全路径是包含了数据模板文件路径，导致不支持解析，所以替换
	////QString sRepaceHead = HL_REPACE_FULLPATH_HEAD;
	////QString sHeadPath = g_pDvmDevice_AttachSetting->m_strID;
	//QString strNewSrcPath = strScript;
	////strNewSrcPath.replace(sHeadPath, sRepaceHead);
	//m_oExprTextUnitList.SetExprScript(strNewSrcPath);

	////再把表达式链表中ID替换回去，并设置显示名称
	//POS pos = m_oExprTextUnitList.GetHeadPosition();
	//CExprTextUnit *pExpVar = NULL;
	//while (pos != NULL)
	//{
	//	pExpVar = m_oExprTextUnitList.GetNext(pos);
	//	if (pExpVar != NULL)
	//	{
	//		//if (pExpVar->m_strUnitScpt.indexOf(sRepaceHead) != -1)
	//		{
	//			//pExpVar->m_strUnitScpt.replace(sRepaceHead, sHeadPath);	//替换回原全路径ID

	//			CExBaseObject * pFindItem = CSttGlobalModel::FindObjectFromDeviceModel(pExpVar->m_strUnitScpt);
	//			if (pFindItem != NULL)
	//				pExpVar->m_strUnitText = pFindItem->m_strName;
	//			//else
	//			//	pExpVar->m_strUnitText = "未找到";
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

	//设置添加函数后，光标在函数()中间
	nBegin += 1;
	setPosition(nBegin, nBegin);
}

void QExprEdit::InsertText(const CString &strID, const CString &strName)
{
	int nBegin, nEnd;
	getPosition(nBegin, nEnd);

	//如果有选中的部分，则不处理
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

	//只有一个字符，调用OnCharPrintchar
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

		//1-1,pCurr==NULL：Prev==NULL
		if (pPrev == NULL)
		{
			CExprTextUnit *pExptrUnit = new CExprTextUnit(strID);
			pExptrUnit->m_strUnitText = strName;
			m_oExprTextUnitList.AddTail(pExptrUnit);
			m_oExprTextUnitList.InitStringUnit(pExptrUnit);
			DoUpdate(nBegin);
		}
		else
		{//1-1,pCurr==NULL：Prev!=NULL
			if (pPrev->IsOptr() || pPrev->IsFunc())
			{//1-1-1,pCurr==NULL：Prev!=NULL：pPrev为Optr或者Func
				CExprTextUnit *pExptrUnit = new CExprTextUnit(strID);
				pExptrUnit->m_strUnitText = strName;
				m_oExprTextUnitList.AddTail(pExptrUnit);
				m_oExprTextUnitList.InitStringUnit(pExptrUnit);
				DoUpdate(nBegin);
			}
			else
			{//1-1-2,pCurr==NULL：Prev!=NULL：pPrev不为Optr或者Func

			}
		}
	}
	else
	{//1-2,pCurr!=NULL
		int nUnitBegin, nUnitEnd;
		m_oExprTextUnitList.GetExprTextUnitPos(pCurr, nUnitBegin, nUnitEnd);

		if (nBegin < nUnitBegin && nBegin <= nEnd)
		{//1-2,pCurr!=NULL：当前位置在中间，不处理
			return;
		}
		else
		{//1-2,pCurr!=NULL：当前位置不在中间
			CExprTextUnit *pPrev = m_oExprTextUnitList.FindPrevExprTextUnit(pCurr);

			if (pPrev == NULL)
			{//1-2-1,pCurr!=NULL：当前位置不在中间：pPrev == NULL头部
				if (pCurr->IsOptr() || pCurr->IsFunc())
				{//1-2-1,pCurr!=NULL：当前位置不在中间：头部：当前为Optr
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
			{//1-2-2,pCurr!=NULL：当前位置不在中间：pPrev!=NULL两个Unit中间
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
			return true;//标识执行过滤，eventFilter不再处理
		}
		else if (keyEvent->key() == Qt::Key_Delete)
		{
			if (!m_bPressSHIFT)
			{
				// Special processing
				OnCharDelete(nChar);
				return true;//标识执行过滤，eventFilter不再处理
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
			m_bPressCONTROL = true;			//记录Ctrl按下
		}
		else if (keyEvent->key() == Qt::Key_Shift)
		{
			m_bPressSHIFT = true;			//记录Shift按下
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
	//如果单击了就触发clicked信号
	if (event->button() == Qt::LeftButton)
	{
		QTextEdit::mousePressEvent(event);
		OnLButtonUp();
		return;
	}

	//将该事件传给父类处理
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

	//如果有选中的部分，不能插入
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

	//只能处理数字和运算符号的输入
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

	//获取当前位置的TextUnit，当前位置是指光标位置之后的TextUnit
	CExprTextUnit *pExptrUnit = m_oExprTextUnitList.GetExprTextUnit(nEndPos, nEndPos);

	//////////////////////////////////////////////////////////////////////////
	//1,如果没有找到，表示为空或者光标位于末尾
	if (pExptrUnit == NULL)
	{
		CExprTextUnit *pTail = m_oExprTextUnitList.GetTail();

		//1-1,为空
		if (pTail == NULL)
		{
			pExptrUnit = new CExprTextUnit(chChar);
			m_oExprTextUnitList.AddTail(pExptrUnit);
			DoUpdate(nEndPos + 1);
			return;
		}
		else
		{//1-2
			//1-2-1不为空
			if (IsCharDigit(chChar))
			{
				if (pTail->IsVariable())
				{//1-2-1-1当前输入的是数字，最后一个是变量，不能处理
					return;
				}

				if (pTail->IsOptr() || pTail->IsFunc())
				{//1-2-1-3函数或者运算符号，创建数字对象
					pExptrUnit = new CExprTextUnit(chChar);
					m_oExprTextUnitList.AddTail(pExptrUnit);
					DoUpdate(nEndPos + 1);
					return;
				}

				if (pTail->IsNumber())
				{//1-2-1-2数字，则添加到字符串的末尾
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

		//其他的各种情况，不处理
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	//2,当前位置有对象
	int nUnitBegin, nUnitEnd;
	m_oExprTextUnitList.GetExprTextUnitPos(pExptrUnit, nUnitBegin, nUnitEnd);

	//2-1:当前位置有对象：光标位置位于当前对象的中间
	if (nUnitBegin < nEndPos && nEndPos <= nEndPos)
	{
		if (pExptrUnit->IsNumber() && IsCharDigit(chChar))
		{//2-1-1:当前位置有对象：光标位置位于当前对象的中间：当前位置为数字并且当前字符为数字
			nUnitBegin = nEndPos - nUnitBegin;
			pExptrUnit->InsertChar(chChar, nUnitBegin);
			DoUpdate(nEndPos + 1);
		}

		return;
	}

	//2-2 :当前位置有对象：当前光标不位于当前对象的中间
	//2-2-1  当前位置有对象：当前光标不位于当前对象的中间：当前字符为Optr
	if (IsCharOptr(chChar))
	{
		CExprTextUnit *pPrev = m_oExprTextUnitList.FindPrevExprTextUnit(pExptrUnit);

		if (pPrev == NULL)
		{//2-2-1-1 当前位置有对象：当前光标不位于当前对象的中间：当前字符为Optr：之前没有对象，插入到头部
			pExptrUnit = new CExprTextUnit(chChar);
			m_oExprTextUnitList.AddHead(pExptrUnit);
			DoUpdate(nEndPos + 1);
		}
		else
		{//2-2-1-2 当前位置有对象：当前光标不位于当前对象的中间：当前字符为Optr：之前有对象，插入到中间位置
			POS pos = m_oExprTextUnitList.Find(pPrev);
			ASSERT(pos != NULL);
			pExptrUnit = new CExprTextUnit(chChar);
			m_oExprTextUnitList.InsertAfter(pos, pExptrUnit);
			DoUpdate(nEndPos + 1);
		}

		return;
	}

	//2-2-2 :当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字
	if (IsCharDigit(chChar))
	{
		CExprTextUnit *pPrev = m_oExprTextUnitList.FindPrevExprTextUnit(pExptrUnit);

		if (pPrev == NULL)
		{//2-2-2-1：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于头部
			if (pExptrUnit->IsOptr())
			{//2-2-2-1-2：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于头部：当前位置为运算符号
				pExptrUnit = new CExprTextUnit(chChar);
				m_oExprTextUnitList.AddHead(pExptrUnit);
				DoUpdate(nEndPos + 1);
			}
			else if (pExptrUnit->IsNumber())
			{//2-2-2-1-1：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于头部：当前位置为数字
				pExptrUnit->m_strUnitScpt = chChar + pExptrUnit->m_strUnitScpt;
				pExptrUnit->m_strUnitText = pExptrUnit->m_strUnitScpt;
				DoUpdate(nEndPos + 1);
			}
			else
			{//2-2-2-1-2：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于头部：当前位置为其他情况，不处理

			}

			return;
		}
		else
		{//2-2-2-2：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于中间
			if (pPrev->IsOptr() || pPrev->IsFunc())
			{//2-2-2-2-1：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于中间：pPrev为运算符号或者函数
				if (pExptrUnit->IsNumber())
				{///2-2-2-2-1-1：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于中间：pPrev为运算符号或者函数：当前位置为数字
					pExptrUnit->m_strUnitScpt = chChar + pExptrUnit->m_strUnitScpt;
					pExptrUnit->m_strUnitText = pExptrUnit->m_strUnitScpt;
					DoUpdate(nEndPos + 1);
				}
				else if (pExptrUnit->IsOptr() || pExptrUnit->IsFunc())
				{///2-2-2-2-1-1：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于中间：pPrev为运算符号或者函数：当前位置为函数、运算符
					POS pos = m_oExprTextUnitList.Find(pPrev);
					ASSERT(pos != NULL);
					pExptrUnit = new CExprTextUnit(chChar);
					m_oExprTextUnitList.InsertAfter(pos, pExptrUnit);
					DoUpdate(nEndPos + 1);
				}
				else
				{///2-2-2-2-1-1：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于中间：pPrev为运算符号或者函数：其他情况不处理

				}
			}
			else
			{//2-2-2-2-1：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于中间：pPrev为其他情况不处理
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
	//获取当前位置，获取前一位置的数据
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
