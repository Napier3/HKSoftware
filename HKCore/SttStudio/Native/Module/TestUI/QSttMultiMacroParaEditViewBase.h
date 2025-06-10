#ifndef QSTTMULTIMACROPARAEDITVIEWBASE_H
#define QSTTMULTIMACROPARAEDITVIEWBASE_H

#include <QTabWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "Interface/QItemParaEditWidgetBase.h"

#include "../UI/Interface/SttMacroParaEditViewOriginal.h"
#include "../UI/Module/GooseParaWidget/qgooseparawidget.h"
#include "../SttCmd/GuideBook/SttItems.h"
#include "Module/CommonGrid/QSttMacroParaEditGrid.h"
#include "Module/SttTestGridDefine/SttTestGridDefine.h"

class QSttMultiMacroParaEditViewBase : public CSttMacroParaEditViewOriginal, public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QSttMultiMacroParaEditViewBase(const CString &strGridFile,QWidget *parent);
	virtual ~QSttMultiMacroParaEditViewBase();

	//���������ܶ�����
	virtual void InitUI_OneMacro();
	//�����๦�ܶ�����
	virtual void InitUI_MultiMacro();
	virtual void InitDatas();
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

	virtual void ConnectAll_SigSlot();
	virtual void DisConnectAll_SigSlot();


public:
	//�ϰ벿�ֽ�����ʾ��QTabWidget,��ʾ��ǰ���ѡ��ĵ���������Ĳ���
	QTabWidget *m_pSingleItemEditTab;
	QItemParaEditWidgetBase *m_pSingleItemParaEditWidget;//�������Թ��ܱ༭����
	QGooseParaWidget* m_pGoosePubsWidget;//GOOSE��������

	//��ǰ��ʾ��������
	QSttMacroParaEditGrid *m_pCurrMacroParaEditGrid;


	//�๦�ܶ��ģʽʱ,����Tab����,��ͬ��Tab��ʾ��ͬ�Ĳ��Թ��ܱ��
	QTabWidget *m_pMultiMacroGridTab;


	QPushButton *m_pAddOneItemBtn;//��ӵ���������
	QPushButton *m_pAddMultiItemBtn;//���ϵ��
	QPushButton *m_pCommonParasBtn;//ͨ�ò���
	QPushButton *m_pBinarysBtn;//������
	QPushButton *m_pDeleteItemBtn;//ɾ��������
	QPushButton *m_pClearResultBtn;//������Խ��
	QVBoxLayout *m_pMainVboxLayout;
	QHBoxLayout *m_pBottomHboxLayout;


	CSttItems *m_pCurrRootItems;//��ǰ�������Ӧ�ĸ�Ŀ¼
	CSttTestGridDefine m_oSttTestGridDefine;//���Թ��ܱ������

public slots:
	virtual void slot_AddOneItemBtnClick();//��ӵ���������
	virtual void slot_AddMultiItemBtnClick();//���ϵ��
	virtual void slot_CommonParasBtnClick();//ͨ�ò���
	virtual void slot_BinarysBtnClick();//������
	virtual void slot_DeleteItemBtnClick();//ɾ��������
	virtual void slot_ClearResultBtnClick();//������Խ��
};

extern QFont *g_pSttGlobalFont;

#endif // QSTTMULTIMACROPARAEDITVIEWBASE_H
