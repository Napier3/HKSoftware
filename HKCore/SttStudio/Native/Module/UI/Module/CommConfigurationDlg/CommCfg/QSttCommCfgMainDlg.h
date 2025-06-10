#ifndef QSttCommCfgMainDlg_H
#define QSttCommCfgMainDlg_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>
#include <QTimerEvent>
#include <QLineEdit>
#include "SttCommCfgDeviceAttrsGrid.h"
#include "../../../Module/DataMngr/DvmData.h"
#include "../../../Module/DataMngr/DvmDevice.h"
#include "../../ScrollCtrl/ScrollComboBox.h"
#include "../../../../SmartTestInterface/QT/PpSttIotEngineClientWidgetMain.h"

#define CFMDLG_COMBO_TYPE_PPXMLFILE 1
#define CFMDLG_COMBO_TYPE_DVMFILE 2

class QSttCommCfgMainDlg: public QDialog ,public CPpSttIotEngineClientInterface
{
	Q_OBJECT
public:
	QSttCommCfgMainDlg(QWidget *parent = 0);
	virtual ~QSttCommCfgMainDlg();
	void initUI();                 //��ʼ��UI
	void SetDialogFont();          //����ͨѶ����Dialog����
	void InitDatas();              //��ʼ������
	void SetComboItemIndex(int iComboType);          //����ͨѶ����DialogComboѡ����
	void UpdateConnectStateUI(long nHasConnected);   //�������Ӱ�ť�ı�
	QStringList* ScanDataDir(CString strScanPath, CString fileSuffix); //ɨ���ļ�·����ȡ���-��Լ�ļ�
	void OpenPpSttCommConfigFile(int iModType, CString& upStrPpXmlFile, CString& upStrDvmFile); //�������ļ�
	void SavePpSttCommConfigFile(int iModType, CString& upStrPpXmlFile, CString& upStrDvmFile); //���������ļ�
	void ParseProtolTmplXmlFile(CString upStrPpXmlFile);  //������Լ�ļ�Xml����
	void SaveSerialTableProtolFile(CString strPpXmlFile); //�����Լ�ļ���������
	void SaveNetTableProtolFile(CString strPpXmlFile);    //�����Լ�ļ���������
	void SaveTcpclientDataToCfgXml();                     //�����Լ�ļ����ڵ�TcpClient����
	// ���ȷ��/���� ���������ݱ��� 2014-01-31 yuanting
	bool SaveAll();

	CDvmData *m_pPpxmlFileData;                      //xml�����ļ�
	CString m_strProproTemplatePath;                 //��Լ�ļ�ȫ·��
	QLabel *m_pLabelProtolType;                      //��ԼLabel
	QLabel *m_pLabelPointXmlType;                    //���Label
	QScrollComboBox *m_pProproTemplate_ComboBox;     //��Լģ��ѡ���
	QScrollComboBox *m_pPointFile_ComboBox;          //����ļ�ѡ���
	QPushButton *m_pConnect_PushButton;              //���Ӱ�ť
	QPushButton *m_pOK_PushButton;                   //ȷ����ť
	QPushButton *m_pCancel_PushButton;               //ȡ����ť

	SttCCommCfgDeviceAttrsGrid *m_pCommCfgDevcieAttrsGrid;   //װ�����öԻ�����

	CDvmDevice *m_pDevAddrDvmDevice;            //װ�õ�ַ�����ļ�
	CString m_strDevAddrPintPath;               //�׵�ַ��Ӧ�ĵ��·��
	BOOL m_bNetTableSave;						//�������ͱ�񱣴��־
	BOOL m_bSerialTableSave;					 //�������ͱ�񱣴��־
	//zhouhj 2024.8.10 ȥ���˱��
//	long m_nConnectStateIndex;//�ñ����������ʹ��,�ڴ����豸����ʱ,���صĽ����������״̬,��һ������״̬����豸�����ɹ�,ʵ������״̬��Ҫ��s�󷵻�
	//2014-01-31 yuanting  �ж��Ƿ���Ҫ���� ���ӵ�ʱ��
	bool m_bIsSaveFlag;


	virtual void OnCommCommandMsg(WPARAM wParam,LPARAM lParam);   //ͨѶ�ص�Command����
	virtual void OnEngineSystemMessage(WPARAM wParam, LPARAM lParam); //ͨѶ�ص�Engine����
public slots:
	void slot_ProtolTempateComboChanged(int index);   //��Լģ��Combo�л��ۺ���
	void slot_PointFileComboChanged(int index);      //����ļ�Combo�л��ۺ���
	void slot_ConnectClicked();   //���Ӱ�ť�ۺ���
	void slot_OKClicked();        //ȷ����ť�ۺ���
	void slot_CancelClicked();     //ȡ����ť�ۺ���
	void slot_ChangedDevAddr(long lRes);   //�׵�ַ�޸ĵĲۺ���
	void slot_ChangedNetTable();          //�������ͱ��Ĳۺ���
	void slot_ChangedSerialTable();       //�������ͱ��Ĳۺ���
};

CString  Global_GetProtolTemplPath();       //��ȡ��Լģ���ļ�ȫ·��
CString Global_GetPointTbFilePath();	    //��ȡ����ļ�ȫ·��
void Global_SetLinuxDevIP(CString strIP, CString strMask);  //����linux IP
CDvmData* Global_OpenPpxmlFile(CString srFilePath);         //������Լ�ļ�xml

#endif // QSttCommCfgMainDlg_H
