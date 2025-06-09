// HeaderCtrlEx.cpp : 实现文件
//

#include "stdafx.h"
#include "HeaderCtrlEx.h"


// CHeaderCtrlEx

IMPLEMENT_DYNAMIC(CHeaderCtrlEx, CHeaderCtrl)


static BOOL s_bDeleteFont = TRUE;

CHeaderCtrlEx::CHeaderCtrlEx()
{
	m_pFont = new CFont;

	m_pFont->CreateFont(12, //以逻辑单位方式指定字体的高度
		0, //以逻辑单位方式指定字体中字符的平均宽度
		0, //指定偏离垂线和X轴在显示面上的夹角（单位：0.1度）
		0, //指定字符串基线和X轴之间的夹角（单位：0.1度）
		FW_NORMAL, //指定字体磅数
		FALSE, //是不是斜体
		FALSE, //加不加下划线
		0, //指定是否是字体字符突出
		ANSI_CHARSET, //指定字体的字符集
		OUT_DEFAULT_PRECIS, //指定所需的输出精度
		CLIP_DEFAULT_PRECIS, //指定所需的剪贴精度
		DEFAULT_QUALITY, //指示字体的输出质量
		DEFAULT_PITCH | FF_SWISS, //指定字体的间距和家族
		_T("宋体") //指定字体的字样名称
		);

	m_clrBK = RGB(255, 255, 255); 
	m_clrFont = RGB(0, 0, 0);
}

CHeaderCtrlEx::~CHeaderCtrlEx()
{
	if (m_pFont && s_bDeleteFont)
	{
		m_pFont->DeleteObject();
		delete m_pFont;
		m_pFont = NULL;
	}
}


BEGIN_MESSAGE_MAP(CHeaderCtrlEx, CHeaderCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CHeaderCtrlEx::OnNMCustomdraw)
	ON_MESSAGE(HDM_LAYOUT, &CHeaderCtrlEx::OnLayout)
	/*ON_NOTIFY_REFLECT(HDN_BEGINTRACKA, 0, &CHeaderCtrlEx::OnHdnBegintrack)
	ON_NOTIFY_REFLECT(HDN_BEGINTRACKW, 0, &CHeaderCtrlEx::OnHdnBegintrack)*/
END_MESSAGE_MAP()


// CHeaderCtrlEx 消息处理程序
void CHeaderCtrlEx::OnNMCustomdraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = CDRF_DODEFAULT;
	if (pNMCD->dwDrawStage == CDDS_PREPAINT)
	{
		CDC* pDC = CDC::FromHandle(pNMCD->hdc);
		CRect rect(0, 0, 0, 0);
		GetClientRect(&rect);
		/*rect.top = rect.top-2;
		rect.left = rect.left-2;
		rect.right = rect.right+2;
		rect.bottom = rect.bottom+2;*/
		pDC->FillSolidRect(&rect, m_clrBK);

		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (pNMCD->dwDrawStage == CDDS_ITEMPREPAINT)
	{
		HDITEM hditem;
		TCHAR buffer[MAX_PATH] = { 0 };
		SecureZeroMemory(&hditem, sizeof(HDITEM));
		hditem.mask = HDI_TEXT;
		hditem.pszText = buffer;
		hditem.cchTextMax = MAX_PATH;
		GetItem(pNMCD->dwItemSpec, &hditem);

		CDC* pDC = CDC::FromHandle(pNMCD->hdc);
		pDC->SetTextColor(m_clrFont);
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		CFont* pOldFont = pDC->SelectObject(m_pFont);
		CString str(buffer);
		CRect rect = pNMCD->rc;
		/*rect.top = rect.top-1;
		rect.left = rect.left-1;
		rect.right = rect.right+1;
		rect.bottom = rect.bottom+2;*/

		/*CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(240, 240, 240));
		CPen* pOldPen = pDC->SelectObject(&pen);
		pDC->Rectangle(&rect);
		pDC->SelectObject(pOldPen);
		pen.DeleteObject();*/

		//rect.OffsetRect(6, 0);
		pDC->DrawText(str, CRect(rect), DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		pDC->SelectObject(pOldFont);
		//pDC->Detach();
		//ReleaseDC(pDC);
		*pResult = CDRF_SKIPDEFAULT;
	}
}


LRESULT CHeaderCtrlEx::OnLayout(WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam);
	HD_LAYOUT& hdl = *(HD_LAYOUT*)lParam;

	RECT* prc = hdl.prc;            // The table list rectangle
	WINDOWPOS* pwpos = hdl.pwpos;   // The table header rectangle

	//int nHeight = (int)(pwpos->cy * 1);
	int nHeight = 40;

	pwpos->cy = nHeight;            // New table header height
	//pwpos->x += 3;

	prc->top = nHeight;             // Decreases the table list height on the table header height

	return lResult;
}

void CHeaderCtrlEx::SetHeaderCtrlFont(CFont* pFont)
{
	if (m_pFont && s_bDeleteFont)
	{
		m_pFont->DeleteObject();
		delete m_pFont;
		m_pFont = NULL;
	}
	m_pFont = pFont;

	s_bDeleteFont = FALSE;
}


void CHeaderCtrlEx::SetHeaderCtrlBKColor(COLORREF clrBk)
{
	m_clrBK = clrBk;
}

void CHeaderCtrlEx::SetHeaderCtrlFontColor(COLORREF clrFont)
{
	m_clrFont = clrFont;
}

//void CHeaderCtrlEx::OnHdnBegintrack(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//
//	int nn = phdr->pitem->cxy;
//	CString ss = phdr->pitem->pszText;
//
//	*pResult = 0;
//}