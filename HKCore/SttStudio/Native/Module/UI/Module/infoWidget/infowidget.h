#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QTableWidget>
#include <QList>
#include "../../../SttTest/Common/tmt_result_def.h"
#include "../ScrollCtrl/ScrollTableWidget.h"

enum InPutDispNum{Input10 = 0,Input74};

class QInfoWidget : public QScrollTableWidget
{
	Q_OBJECT

public:
	explicit QInfoWidget(QWidget *parent = 0);
	~QInfoWidget();

	void init();
	void updateSwitchInfoTable(QList<CEventResult*> list);
	void InsertSwitchInfoTable(CEventResult* pEventResult,BOOL bUpdateStateIndex = FALSE);//��Ӧ�ֶ�ʱ�䲻��Ҫ����StateIndex��ͳһ���丳ֵΪ0
	
	void clear();
	void setProperty(InPutDispNum eflag);

	QString msformatTime(long us);
	CString FindBinInChange(long *pnNewArr, int size);
	void ShowBinInResultMsg(CEventResult* pEventResult);//20230904 suyang �����ڽ������ʾ���붯��

private:
	InPutDispNum m_eDispFlag;
	long m_nBinIn[MAX_BINARYIN_COUNT];//20230725 wxy �洢ԭ���Ŀ�����
	long m_nBinInResult[MAX_BINARYIN_COUNT];//20241023  suyang �洢ԭ����ʼ���ԵĵĿ��������ڸ��¿����λ

//2024-9-10 lijunqing �Ż�ϵͳ����������Ч��
protected:
	bool m_bHasInitFinished;  //�Ƿ��Ѿ���ʼ����ɣ�û�г�ʼ�������ܽ��в���
	CExBaseList m_listEventResult; //û�е㿪���棬���ݻ�����ˣ��㿪�˽��棬��Grid����ʾ

	void ShowListEventResult();
	void ShowEventResult(CEventResult* pEventResult,BOOL bUpdateStateIndex = FALSE);//��Ӧ�ֶ�ʱ�䲻��Ҫ����StateIndex��ͳһ���丳ֵΪ0

    virtual void showEvent(QShowEvent *event);
};

extern QFont *g_pSttGlobalFont; 

#endif // INFOWIDGET_H
