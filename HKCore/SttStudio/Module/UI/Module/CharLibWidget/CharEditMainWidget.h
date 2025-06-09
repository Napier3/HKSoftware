#ifndef CharEditMainWidget_H
#define CharEditMainWidget_H

#include <QWidget>
#include <QItemDelegate>
#include "ui_CharEditMainWidget.h"
#include "../../../../../Module/OSInterface/OSInterface.h"
#include "QImpCharactWidget.h"
#include "CharEditWidgetBase.h"

/*  2022-9-5  lijunqing
������ܣ��������ڵ���������û����������ͼ�Ĳ��֣����Խ��������߹��ܷŵ����࣬����QCharEditMainWidget_RElay
*/

class QCharEditMainWidget : public QWidget
{
	Q_OBJECT
public:
	QCharEditMainWidget(QWidget* pParent = NULL);
	virtual ~QCharEditMainWidget();

	Ui::QCharEditMainWidget ui;

public:
	BOOL m_bSetting;
//	CCharacteristic *m_pCurrCharaObj;
//	CCharInterface *m_pInterface;
//	CCharacterArea *m_pCharArea;
//	CCharInterface *m_pInterfacebak;
//	CCharacterArea *m_pCharAreabak;

	QStringList m_PeriodList;
	QStringList m_ErrorPhaseList;
	QList<QComboBox*> m_CmbListParaNo;
	QList<QComboBox*> m_CmbListFaultPha;

	QImpCharactWidget* m_pImpCharactWidget;
//	CString m_strLastCharaID;
	CString m_strCharParasFile;//���Թ��ܶ�Ӧ�����������ļ���·��,���ڱ���

//	int m_nZKCurrentRow;
	BOOL m_bCharChanged;
	CString m_strUI_ID;//���湦��ID

public:
	void UpdateZKFeature(CCharacteristic *pObj,BOOL bSetting);
//	void DrawSearchPointLine(CPoint ptBegin, CPoint ptEnd, const CString& strCharLib);
//	void DrawSearchPointPoint(CPoint ptCur, const CString& strCharLib);
//	void DrawSearchPointLine(CPoint ptBegin, CPoint ptEnd, CCharacteristic* pChar);
//	void DrawSearchPointPoint(CPoint ptCur, CCharacteristic* pChar);
	void UpdateCharAxisType(const CString& strAxis,BOOL bLockXY);
	void UpdateCharScriptByUIParas(CDataGroup *pCurrentUIParas);
	void AddTestResultPoint(CExBaseList* pValue);//��Ӳ��Խ����

	void GroupDatasToChar(CDataGroup *pDatas);//��ģ����ͼ���ݸ�ֵ���������߽���
	void CharToGroupDatas(CDataGroup *pDatas);//���������߽���������ݸ�ֵ��ģ����ͼ����

	//2022-9-3  lijunqing
	void InitCharacteristicsLib(const CString &strUI_ID,const CString &strCharLibFile);//����1Ϊ�����������ID
	void ShowCharacteristics(CCharacteristics *pCharacteristics);
	CString GetCharLibID();
	void UpdateAxisDesc(const CString &strXAxisName, const CString &strYAxisName, 
		const CString &strAxisTitle,CString strUniuX,CString strUnitY);//��������������
	BOOL IsViewTestLines();
	void UI_SetActiveElement(CXDrawElement *pElement);

protected:
	void CreateCharEditWidgetUI_ID(const CString &strUI_ID);

	CCharacteristicLib *m_pCharacteristicsLib;
	QCharEditWidgetBase *m_pCharEditWidget;
//	CString m_strLastCharLibID;

private:
	void InitUI();
	void InitTableWidget();
	void InitCharactWidget();
	void InitConnect();

	void AddCharacter(CCharacteristic *pChar);
	CXDrawList* GetDrawListByID(const CString& strID);
	void RemoveCurrWidget();

signals:
//	void sig_CharChanged(CExBaseObject *pCharacteristic);
	// 	void sig_UpdataCheck(bool, bool, bool);
public slots:
//	void slot_CharChanged();
	void slot_UpdateDrawCharacters(CExBaseObject *pCharacteristic,int bCharChanged);//���øòۺ��������ò����Ƿ�ı�
	void slot_UpdateDrawCharacters(CExBaseObject *pCharacteristic);//���øòۺ���,Ĭ�ϲ����Ѹı�
	void slot_LeftButtonDown();
};

#endif//!CharEditMainWidget_H