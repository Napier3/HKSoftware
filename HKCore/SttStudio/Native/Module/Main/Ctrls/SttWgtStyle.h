#ifndef QSTTWGTSTYLE_H
#define QSTTWGTSTYLE_H
#include "../SttXuiData/SttXuiDataBase.h"

#define WGT_TYPE_FONT "font"

//�ؼ�global��ʽ��
class QSttWgtStyle : public CExBaseList
{
public:
	CString m_strType;
	CString m_strBkColor;//����
	CString m_strGdColor;//ǰ��
	long m_nSize;

public:
	QSttWgtStyle();
	virtual ~QSttWgtStyle();

	void InitStyle(CSttXuiDataBase* pSttXuiDataBase);
};

#endif//!QSTTWGTSTYLE_H