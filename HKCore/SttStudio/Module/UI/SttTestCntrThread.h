#ifndef SttTestCntrThread_H
#define SttTestCntrThread_H

#include "../../../../Module/OSInterface/QT/CWinThread_QT.h"
#include "../../../../Module/BaseClass/ExBaseObject.h"

class QSttTestCntrThread : public CWinThread
{
public:
    explicit QSttTestCntrThread();
    virtual ~QSttTestCntrThread();

    virtual void OnThreadMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);

	CExBaseObject *m_pParentItems;
	CString m_strItemsName;
	CString m_strItemsID;
};

extern QSttTestCntrThread *g_theSttTestCntrThread;

void CreateSttTestCntrThread();
void ReleaseSttTestCntrThread();

#endif // SttTestCntrThread_H
