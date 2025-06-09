#ifndef QSTTWGTSTYLE_H
#define QSTTWGTSTYLE_H
#include "../SttXuiData/SttXuiDataBase.h"

#define WGT_TYPE_FONT "font"

//控件global样式类
class QSttWgtStyle : public CExBaseList
{
public:
	CString m_strType;
	CString m_strBkColor;//背景
	CString m_strGdColor;//前景
	long m_nSize;

public:
	QSttWgtStyle();
	virtual ~QSttWgtStyle();

	void InitStyle(CSttXuiDataBase* pSttXuiDataBase);
};

#endif//!QSTTWGTSTYLE_H