#ifndef SCROLLEXELEMENT_H
#define SCROLLEXELEMENT_H

#include "../../../../../../Module/BaseClass/ExBaseList.h"

class QScrollExElement : public CExBaseList
{
public:
	enum QElementType
	{
		TYPE_BUTTON,
		TYPE_TEXT,
		TYPE_IMAGE
	};

	QElementType m_tagType;
	QRect m_rcLocal;
	QString m_strText;

public:
	QScrollExElement();
	virtual ~QScrollExElement();

private:
	void InitUI();

public:
	void SetType(QElementType nType) { m_tagType = nType; }
	void SetGemoetry(long nLeft, long nTop, long nRight, long nBottom);
};


#endif//!SCROLLEXELEMENT_H