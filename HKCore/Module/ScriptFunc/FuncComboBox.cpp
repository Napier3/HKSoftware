#include "StdAfx.h"
#include "FuncComboBox.h"

CFuncComboBox::CFuncComboBox(void)
{
	PFUNCDATA fData = new FUNCDATA;
	fData->strFunc = L"SetRsltJdg(\"\",);";
	fData->strname = L"SetRsltJdg";
	fData->strMsg = L"���ý������������1Ϊ·��������2Ϊֵ��\r\nʵ����SetRsltJdg(\"\",1);";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc = L"GetRsltJdg(\"\");";
	fData->strname = L"GetRsltJdg";
	fData->strMsg = L"��ȡ�������������1Ϊ·��\r\nʵ����local RsltJdg = GetRsltJdg(\"\");";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc = L"SetPara(\"\",\"\",);";
	fData->strname = L"SetPara";
	fData->strMsg = L"����Item����������1Ϊ·��������2Ϊ����IDֵ������3Ϊ������ֵ,\r\nʵ����SetPara(\"\",\"_Ua\",57);";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc = L"SetParaStr(\"\",\"\");";
	fData->strname = L"SetParaStr";
	fData->strMsg = L"����Item����������1Ϊ·��������2Ϊ����IDֵ������3Ϊ������ֵ,\r\nʵ����SetPara(\"\",\"_Ua\",\"57\");";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc = L"GetPara(\"\",\"\");";
	fData->strname = L"GetPara";
	fData->strMsg = L"��ȡItem����������1Ϊ·��������2Ϊ����IDֵ������ϵͳ����ֵ\r\nʵ����local _Ua = GetPara(\"\",\"_Ua\");";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetParaStr(\"\");";
	fData->strname = L"GetParaStr";
	fData->strMsg = L"��ȡ���Բ���������1Ϊ����IDֵ�������ַ������";
	m_listFunc.push_back(fData);

// 	fData = new FUNCDATA;
// 	fData->strFunc =L"SetSysPara(\"\",);";
// 	fData->strname = L"SetSysPara";
// 	fData->strMsg = L"����ϵͳ����������1Ϊ����IDֵ������2Ϊ������ֵ\r\nʵ����SetSysPara(\"_Un\",57);";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"GetSysPara(\"\");";
// 	fData->strname = L"GetSysPara";
// 	fData->strMsg = L"��ȡϵͳ����������1Ϊ����IDֵ������ϵͳ����ֵ\r\nʵ����local _Un = GetSysPara(\"_Un\");";
// 	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetShow(\"\");";
	fData->strname = L"GetShow";
	fData->strMsg = L"��ȡ��ʾ����������1Ϊ����IDֵ��������ʾ����ֵ\r\nʵ����GetShow(\"\");";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetShow(\"\",);";
	fData->strname = L"SetShow";
	fData->strMsg = L"������ʾ����������1Ϊ����IDֵ������2Ϊ������ֵ\r\nʵ����SetShow(\"\",1);";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetEnable(\"\");";
	fData->strname = L"GetEnable";
	fData->strMsg = L"��ȡEnable����������1Ϊ����IDֵ��������ʾ����ֵ\r\nʵ����GetEnable(\"\");";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetEnable(\"\",);";
	fData->strname = L"SetEnable";
	fData->strMsg = L"����Enable����������1Ϊ����IDֵ������2Ϊ������ֵ\r\nʵ����SetEnable(\"\",1);";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetSelect(\"\");";
	fData->strname = L"GetSelect";
	fData->strMsg = L"��ȡSelect���ԣ�����1Ϊ����IDֵ��������ʾ����ֵ";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetSelect(\"\",);";
	fData->strname = L"SetSelect";
	fData->strMsg = L"����Select���ԣ�����1Ϊ����IDֵ������2Ϊ������ֵ";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetName(\"\");";
	fData->strname = L"GetName";
	fData->strMsg = L"��ȡ���Ʋ���������1Ϊ����IDֵ��������ʾ����ֵ";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetName(\"\",);";
	fData->strname = L"SetName";
	fData->strMsg = L"�������Ʋ���������1Ϊ����IDֵ������2Ϊ������ֵ";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetReportValue(\"\",\"\");";
	fData->strname = L"GetReportValue";
	fData->strMsg = L"��ȡ����ֵ������1Ϊ·��������2Ϊ����IDֵ�����ظ���������ֵ";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptValL(\"\",\"\");";
	fData->strname = L"GetRptValL";
	fData->strMsg = L"��ȡ����ֵ������1Ϊ·��������2Ϊ����IDֵ��������������ֵ";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptValStr(\"\",\"\");";
	fData->strname = L"GetRptValStr";
	fData->strMsg = L"��ȡ����ֵ������1Ϊ·��������2Ϊ����IDֵ�������ַ�������ֵ";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetReportValue(\"\",\"\",);";
	fData->strname = L"SetReportValue";
	fData->strMsg = L"���ñ���ֵ������1Ϊ·��������2ΪIDֵ������3Ϊ������ֵ(������)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetReportValStr(\"\",\"\",);";
	fData->strname = L"SetReportValStr";
	fData->strMsg = L"���ñ���ֵ������1Ϊ·��������2ΪIDֵ������3Ϊ������ֵ(�ַ���)";
	m_listFunc.push_back(fData);


	fData = new FUNCDATA;
	fData->strFunc =L"GetReportValueEx(\"\",\"\", );";
	fData->strname = L"GetReportValueEx";
	fData->strMsg = L"��ȡ����ֵ������1Ϊ·��������2Ϊ����IDֵ������3Ϊ�����ţ����ظ���������ֵ";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptValLEx(\"\",\"\", );";
	fData->strname = L"GetRptValLEx";
	fData->strMsg = L"��ȡ����ֵ������1Ϊ·��������2Ϊ����IDֵ������3Ϊ�����ţ�������������ֵ";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptValStrEx(\"\",\"\", );";
	fData->strname = L"GetRptValStrEx";
	fData->strMsg = L"��ȡ����ֵ������1Ϊ·��������2Ϊ����IDֵ������3Ϊ�����ţ������ַ�������ֵ";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptCount(\"\");";
	fData->strname = L"GetRptCount";
	fData->strMsg = L"��ȡ�������������1Ϊ·�������ر���ĸ��������ԵĴ�����";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"ClearReports(\"\");";
	fData->strname = L"ClearReports";
	fData->strMsg = L"�����Ŀ������Ŀ������ȫ����Ŀ�ı��棬����1Ϊ·��";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetDsDataValue(\"\");";
	fData->strname = L"GetDsDataValue";
	fData->strMsg = L"��ȡ���ݼ�����ֵ������1Ϊ����ID·�������ؽ��(double)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetDsDataValue(\"\",);";
	fData->strname = L"SetDsDataValue";
	fData->strMsg = L"�������ݼ�����ֵ������1Ϊ����ID·��������2Ϊ������ֵ(double)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetDsDataStr(\"\");";
	fData->strname = L"GetDsDataStr";
	fData->strMsg = L"��ȡ���ݼ�����ֵ������1Ϊ����ID·�������ؽ��(�ַ���)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetDsDataStr(\"\",);";
	fData->strname = L"SetDsDataStr";
	fData->strMsg = L"�������ݼ�����ֵ������1Ϊ����ID·��������2Ϊ������ֵ(�ַ���)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetDsDataValueEx(-1,\"\");";
	fData->strname = L"GetDsDataValueEx";
	fData->strMsg = L"��ȡ���ݼ�����ֵ������1Ϊ�豸����ģ�͵ı�ţ�����2Ϊ����ID·�������ؽ��(double)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetDsDataAttr(\"\", \"\");";
	fData->strname = L"GetDsDataAttr";
	fData->strMsg = L"��ȡ���ݼ���������ֵ������1Ϊ�豸����ID������2Ϊ�������ԣ����ؽ��(double)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetDsDataValueEx(-1,\"\",);";
	fData->strname = L"SetDsDataValueEx";
	fData->strMsg = L"�������ݼ�����ֵ������1Ϊ�豸����ģ�͵ı�ţ�����2����ID·��������3Ϊ������ֵ(double)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetDsDataStrEx(-1,\"\");";
	fData->strname = L"GetDsDataStrEx";
	fData->strMsg = L"��ȡ���ݼ�����ֵ������1Ϊ�豸����ģ�͵ı�ţ�����2����ID·�������ؽ��(�ַ���)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetDsDataStrEx(-1,\"\",);";
	fData->strname = L"SetDsDataStrEx";
	fData->strMsg = L"�������ݼ�����ֵ������1Ϊ�豸����ģ�͵ı�ţ�����2����ID·��������3Ϊ������ֵ(�ַ���)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalAinError(\"\", , , );";
	fData->strname = L"CalAinError";
	fData->strMsg = L"����ң�����������ؽ���жϣ�0/1��������1��ң������ID������2��ң�����Ļ�׼ֵ������3����������ޣ�����4����������";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalAinErrorEx(\"\", , , );";
	fData->strname = L"CalAinErrorEx";
	fData->strMsg = L"����ң�����������ؽ���жϣ�0/1��������1��ʵ��ֵ�˵ı���������2��ң������ID������3��ң�����Ļ�׼ֵ������4����������ޣ�����5����������";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalAinErrorNom(\"\", , , , );";
	fData->strname = L"CalAinErrorNom";
	fData->strMsg = L"����ң�����������ؽ���жϣ�0/1��������1��ʵ��ֵ�˵ı���������2��ң������ID������3��ң�����Ļ�׼ֵ������4���������ı�׼ֵ������5����������ޣ�����6����������";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalAinStdError(, \"\", , , );";
	fData->strname = L"CalAinStdError";
	fData->strMsg = L"����ң�����ı�׼�������ؽ���жϣ�0/1��������1��Ҫ�������ݳ˵ı���ϵ��������2��ң������ID������3��ң�����Ļ�׼ֵ������4����������ޣ�����5���������ޣ�";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalAinStdError2(\"\", \"\", , , );";
	fData->strname = L"CalAinStdError2";
	fData->strMsg = L"����ң�����ı�׼�������ؽ���жϣ�0/1��������1��Ҫ�������ݳ˵ı���ϵ��������2��ң������ID������3��ң�����Ļ�׼ֵ������4����������ޣ�����5���������ޣ�";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalAinError2(\"\", \"\", , , );";
	fData->strname = L"CalAinError2";
	fData->strMsg = L"����ң�����������ؽ���жϣ�0/1��������1��ң����ID������2��ң������׼ID������3��������׼ֵ������4����������ޣ�����5����������";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalVariation( , , , );";
	fData->strname = L"CalVariation";
	fData->strMsg = L"���������1��ʵ��ֵ������2������ֵ������3����׼ֵ������4������";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalVariationErr( , , , , );";
	fData->strname = L"CalVariationErr";
	fData->strMsg = L"���������1��ʵ��ֵ������2������ֵ������3����׼ֵ������4������������5������ޣ�����ֵ�����ֵ";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalVariationErrEx(\"\" ,\"\" ,\"\" ,\"\" , \"\", 1);";
	fData->strname = L"CalVariationErrEx";
	fData->strMsg = L"���������1��ʵ��ֵID������2������ֵID������3����׼ֵID�����Բ�����������4����������������ID������5������ޣ����Բ�����������6������������ֵ�����ֵ";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltCalErrMax(\"\", \"\",\"\", , , );";
	fData->strname = L"FltCalErrMax";
	fData->strMsg = L"���㱨�����ݵ������ؽ���жϣ�0/1��������1������ID������2���������ֵID������3��������ֵID������4����׼ֵ������5����������ޣ�����6����������";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltCalErrMin(\"\", \"\",\"\", , , );";
	fData->strname = L"FltCalErrMin";
	fData->strMsg = L"���㱨�����ݵ������ؽ���жϣ�0/1��������1������ID������2���������ֵID������3��������ֵID������4����׼ֵ������5����������ޣ�����6����������";
	m_listFunc.push_back(fData);

// 	fData = new FUNCDATA;
// 	fData->strFunc =L"GetSetValue(\"\");";
// 	fData->strname = L"GetSetValue";
// 	fData->strMsg = L"��ȡ��ֵֵ������1Ϊ����IDֵ�����ؽ��";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"SetSetValue(\"\",);";
// 	fData->strname = L"SetSetValue";
// 	fData->strMsg = L"���ö�ֵֵ������1Ϊ����IDֵ������2Ϊ������ֵ";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"GetSftValue(\"\");";
// 	fData->strname = L"GetSftValue";
// 	fData->strMsg = L"��ȡ��ѹ��ֵ������1Ϊ����IDֵ�����ؽ��";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"SetSftValue(\"\",);";
// 	fData->strname = L"SetSftValue";
// 	fData->strMsg = L"������ѹ��ֵ������1Ϊ����IDֵ������2Ϊ������ֵ";
// 	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetTestPara(\"\");";
	fData->strname = L"GetTestPara";
	fData->strMsg = L"��ȡ���Բ���������1Ϊ����IDֵ�����ظ��������";
	m_listFunc.push_back(fData);
	
	fData = new FUNCDATA;
	fData->strFunc =L"GetTestParaStr(\"\");";
	fData->strname = L"GetTestParaStr";
	fData->strMsg = L"��ȡ���Բ���������1Ϊ����IDֵ�������ַ������";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetTestPara(\"\",);";
	fData->strname = L"SetTestPara";
	fData->strMsg = L"���ò��Բ���������1Ϊ����IDֵ������2Ϊ������ֵ";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetTestParaStr(\"\",\"\");";
	fData->strname = L"SetTestParaStr";
	fData->strMsg = L"���ò��Բ���������1Ϊ����IDֵ������2Ϊ������ֵ";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GotoItem(\"\");";
	fData->strname = L"GotoItem";
	fData->strMsg = L"ת��Item��";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"MtExcuteCmd(\"\", \"\");";
	fData->strname = L"MtExcuteCmd";
	fData->strMsg = L"���ò����������ƽӿڣ�ִ�в����������1���ַ���������ID������2���ַ������������";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"MtRegistPpDataMsg(\"\");";
	fData->strname = L"MtRegistPpDataMsg";
	fData->strMsg = L"���Լ�������ע������������ƽӿڳ����ⲿ��Ϣ��ִ�в����������1���ַ�������Լ�������ݶ���·��";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"MtUnRegistPpDataMsg(\"\");";
	fData->strname = L"MtUnRegistPpDataMsg";
	fData->strMsg = L"ȡ����Լ�������ע������������ƽӿڳ����ⲿ��Ϣ������1���ַ�������Լ�������ݶ���·��";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"MtRegistCmdMsg(\"\", 0, 1, 1);";
	fData->strname = L"MtRegistCmdMsg";
	fData->strMsg = L"���Լ�������ע������������ƽӿڳ����ⲿ��Ϣ��ִ�в����������1���ַ�����ͨѶ�������2������״̬��0ΪͨѶǰ��1ֻ������ɺ󣻲���3����Ϣ��wParam������4��lParam";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"MtUnRegistCmdMsg(\"\");";
	fData->strname = L"MtUnRegistCmdMsg";
	fData->strMsg = L"ȡ����Լ�������ע������������ƽӿڳ����ⲿ��Ϣ������1���ַ�����ͨѶ����ID";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"BreakLoop();";
	fData->strname = L"BreakLoop";
	fData->strMsg = L"�����ظ���β���ʱ�������ظ�����";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"BreakItems();";
	fData->strname = L"BreakItems";
	fData->strMsg = L"������Ŀ����Ĳ��ԣ�����һ�����࿪ʼ���ԣ���������Ŀ����Ĳ�Σ�0��ʾ������ǰ���࣬1��ʾ������һ�����࣬��������";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetUploadRptFile();";
	fData->strname = L"SetUploadRptFile";
	fData->strMsg = L"���ò�����ɺ��Զ����������ļ����ļ���";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"ShowMsg(\"\");";
	fData->strname = L"ShowMsg";
	fData->strMsg = L"��ʾ��Ϣ";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"PlayMusicFile(\"\", );";
	fData->strname = L"PlayMusicFile";
	fData->strMsg = L"��������";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptExVal( , );";
	fData->strname = L"GetRptExVal";
	fData->strMsg = L"��ñ����������Ե�ֵ����һ�����������������������ڶ���������������������ID";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptExValD( , );";
	fData->strname = L"GetRptExValD";
	fData->strMsg = L"��ñ����������Ե�ֵ����һ����������������ID���ڶ���������������������ID�����ظ�����";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptExValL( , );";
	fData->strname = L"GetRptExValL";
	fData->strMsg = L"��ñ����������Ե�ֵ����һ����������������ID���ڶ���������������������ID����������";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptExValS( , );";
	fData->strname = L"GetRptExValS";
	fData->strMsg = L"��ñ����������Ե�ֵ����һ����������������ID���ڶ���������������������ID�������ַ���";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptExCount();";
	fData->strname = L"GetRptExCount";
	fData->strMsg = L"��ȡ�������ݵĸ���";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalTmGap(, , \"\");";
	fData->strname = L"CalTmGap";
	fData->strMsg = L"���㱨��������������֮���ʱ�������������Ա���Ϊʱ�����,����1��2��ʾ�����������ݵ�ID����3��������ʾ��������ID";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalTmGapEx(, , \"\", \"\");";
	fData->strname = L"CalTmGapEx";
	fData->strMsg = L"���㱨��������������֮���ʱ�������������Ա���Ϊʱ�����,����1��2��ʾ�����������ݵ�ID����3��4��������ʾ��������ID";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalTmGapEx2(, , \"\", \"\");";
	fData->strname = L"CalTmGapEx2";
	fData->strMsg = L"���㱨��������������֮���ʱ�������������Ա���Ϊʱ�����,����1��2��ʾ�����������ݵ�ID����3��4��������ʾ������������0��ʼ��";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetTestIndex();";
	fData->strname = L"GetTestIndex";
	fData->strMsg = L"��ȡ�ظ�����ʱ�Ĵ���";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalRptValMax(\"\", \"\", );";
	fData->strname = L"CalRptValMax";
	fData->strMsg = L"���㱨�����ݵ����ֵ������1����Ŀ��·��������Ϊ������Ŀ��Ҳ����Ϊ��Ŀ���ࣻ����2��������ID������3��ȱʡֵ������ֵ�����������ID�������ݴ��ڣ��򷵻����ֵ�����򷵻�ȱʡֵ";
	m_listFunc.push_back(fData);
	
	fData = new FUNCDATA;
	fData->strFunc =L"CalRptValMin(\"\", \"\", );";
	fData->strname = L"CalRptValMin";
	fData->strMsg = L"���㱨�����ݵ���Сֵ������1����Ŀ��·��������Ϊ������Ŀ��Ҳ����Ϊ��Ŀ���ࣻ����2��������ID������3��ȱʡֵ������ֵ�����������ID�������ݴ��ڣ��򷵻���Сֵ�����򷵻�ȱʡֵ";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalRptValAvg(\"\", \"\", );";
	fData->strname = L"CalRptValAvg";
	fData->strMsg = L"���㱨�����ݵ�ƽ��ֵ������1����Ŀ��·��������Ϊ������Ŀ��Ҳ����Ϊ��Ŀ���ࣻ����2��������ID������3��ȱʡֵ������ֵ�����������ID�������ݴ��ڣ��򷵻�ƽ��ֵ�����򷵻�ȱʡֵ";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FilterRptExEqL( \"\", );";
	fData->strname = L"FilterRptExEqL";
	fData->strMsg = L"������չ�������ݣ�����1����չ�������ݵ�����ID������2����չ�������ݵ�����ֵ��������";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FilterRptInit( );";
	fData->strname = L"FilterRptInit";
	fData->strMsg = L"��ʼ��������ˣ�������˵Ľ��";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FilterRptExEqStr( \"\", \"\");";
	fData->strname = L"FilterRptExEqStr";
	fData->strMsg = L"������չ�������ݣ�����1����չ�������ݵ�����ID������2����չ�������ݵ�����ֵ���ַ�����";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FilterRptExHasStr( \"\", \"\");";
	fData->strname = L"FilterRptExHasStr";
	fData->strMsg = L"������չ�������ݣ�����1����չ�������ݵ�����ID������2����չ�������ݵ�����ֵ�������ַ���";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FilterRptExNoStr( \"\", \"\");";
	fData->strname = L"FilterRptExNoStr";
	fData->strMsg = L"������չ�������ݣ�����1����չ�������ݵ�����ID������2����չ�������ݵ�����ֵ���ܰ������ַ���";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FilterCombine( \"\", \"\",  \"\");";
	fData->strname = L"FilterCombine";
	fData->strMsg = L"ƴ�ӹ��˺����չ�������ݣ�����1����չ�������ݵ�����ID������2��ƴ�Ӻ����ݱ���ı�������ID������3��ƴ�ӵķָ����ţ�ȱʡΪ\";\"";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExQuery( \"\");";
	fData->strname = L"FltRptExQuery";
	fData->strMsg = L"�ӹ��˺�ı��������в�ѯ����������һ�����ݣ�����1����������ʽΪ name=˲ʱ�����ٶ϶���;item-index=49;group-index=72";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExGetCount( );";
	fData->strname = L"FltRptExGetCount";
	fData->strMsg = L"�ӹ��˺�ı��������л�ȡ���ݼ�����";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExGetLong( , \"\");";
	fData->strname = L"FltRptExGetLong";
	fData->strMsg = L"�ӹ��˺�ı��������л�ȡһ�����ݶ��������ֵ����������������1�����ݼ��е������� ����2������id";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExGetStr( , \"\");";
	fData->strname = L"FltRptExGetStr";
	fData->strMsg = L"�ӹ��˺�ı��������л�ȡһ�����ݶ��������ֵ�������ַ���������1�����ݼ��е������� ����2������id";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExGetDouble( , \"\");";
	fData->strname = L"FltRptExGetDouble";
	fData->strMsg = L"�ӹ��˺�ı��������л�ȡһ�����ݶ��������ֵ�����ظ�����������1�����ݼ��е������� ����2������id";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExGetValCount( );";
	fData->strname = L"FltRptExGetValCount";
	fData->strMsg = L"�ӹ��˺�ı��������л�ȡ��n�����ݡ���ֵ��������������1����n�����ݵ���������0��ʼ��ţ����ء���ֵ��������";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExGetValLong( , \"\");";
	fData->strname = L"FltRptExGetValLong";
	fData->strMsg = L"�ӹ��˺�ı��������л�ȡ��n�����ݵġ���ֵ����ֵ����������������1����n�����ݵ������� ����2������ֵ�������������ֱ�ʾ������������ַ�����ʾ��ID����";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExGetValStr( , \"\");";
	fData->strname = L"FltRptExGetValStr";
	fData->strMsg = L"�ӹ��˺�ı��������л�ȡ��n�����ݵġ���ֵ����ֵ�������ַ���������1����n�����ݵ������� ����2������ֵ�������������ֱ�ʾ������������ַ�����ʾ��ID����";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExGetValDouble( , \"\");";
	fData->strname = L"FltRptExGetValDouble";
	fData->strMsg = L"�ӹ��˺�ı��������л�ȡ��n�����ݵġ���ֵ����ֵ�����ظ�����double������1����n�����ݵ������� ����2������ֵ�������������ֱ�ʾ������������ַ�����ʾ��ID����";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExCalValError( , \"\");";
	fData->strname = L"FltRptExCalValError";
	fData->strMsg = L"���˺�ı��������У��жϵ�n�����ݵġ���ֵ����ֵ�Ƿ��������Ҫ�󣬷��ؽ��ۣ�0��ʾ�����㣬1��ʾ���㣻����1����n�����ݵ������� ����2������ֵ�������������ֱ�ʾ������������ַ�����ʾ��ID����������3���ο���ֵ������4������������5��������";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExCalValErrEx(\"\", \"\", , , );";
	fData->strname = L"FltRptExCalValErrEx";
	fData->strMsg = L"�����еı��������У��жϵ����ݵġ���ֵ����ֵ�Ƿ��������Ҫ�󣬷��ؽ��ۣ�0��ʾ�����㣬1��ʾ���㣻����1��DataID�� ����2������ֵ��ID������3���ο���ֵ������4������������5��������";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CreateDevice( );";
	fData->strname = L"CreateDevice";
	fData->strMsg = L"������Լ�����豸������1����Լģ�壬����2���豸����ļ�������3���豸����";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"ReleaseDevice( );";
	fData->strname = L"ReleaseDevice";
	fData->strMsg = L"�ͷŹ�Լ�����豸������1���豸����";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetDeviceAttrStr( );";
	fData->strname = L"GetDeviceAttr";
	fData->strMsg = L"��Լ�����豸����ģ�͵��������ݣ�����1������ID�����硰nane��";
	m_listFunc.push_back(fData);
	
	fData = new FUNCDATA;
	fData->strFunc =L"GetDeviceAttrL(\"\");";
	fData->strname = L"GetDeviceAttrL";
	fData->strMsg = L"��Լ�����豸����ģ�͵��������ݣ�����1������ID�����硰nane��";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetDeviceAttrL( );";
	fData->strname = L"SetDeviceAttrL";
	fData->strMsg = L"���ù�Լ�����豸����ģ�͵��������ݣ�����1������ID�����硰value��������2������ֵ������";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetDeviceAttrStr( );";
	fData->strname = L"SetDeviceAttrStr";
	fData->strMsg = L"���ù�Լ�����豸����ģ�͵��������ݣ�����1������ID�����硰value��������2������ֵ�ַ���";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RptGetDevieNodeDatas( );";
	fData->strname = L"RptGetDevieNodeDatas";
	fData->strMsg = L"��Լ�����豸����ģ�͵����ݽڵ����ݣ�����1��·�������硰CPU=1\\\\xYC=4��";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"DeleteAllNodeData( );";
	fData->strname = L"DeleteAllNodeData";
	fData->strMsg = L"ɾ���豸���ݽڵ��ȫ�����ݣ�����1��·�������硰SOE������YX��";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"IsProtocol(\"MmsEngine\");";
	fData->strname = L"IsProtocol";
	fData->strMsg = L"�жϲ���ʹ�õĹ�Լ���͡�MMS�淶ΪMmsEngine����ͳ��ԼΪ��Լģ���ļ�����������׺";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RptGetDeviceAttrs( );";
	fData->strname = L"RptGetDeviceAttrs";
	fData->strMsg = L"��Լ�����豸����ģ�͵����ݽڵ����ݣ��޲���";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetDevieNodeDataAttr( );";
	fData->strname = L"GetDevieNodeDataAttr";
	fData->strMsg = L"��ȡ��Լ�����豸����ģ�͵����ݽڵ��������ԣ�����1��·�������硰CPU=1\\\\xYC=4\\\\item-index=2��������2������ID�����硰nane��";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetDevieNodeDataAttr( );";
	fData->strname = L"SetDevieNodeDataAttr";
	fData->strMsg = L"���ù�Լ�����豸����ģ�͵����ݽڵ��������ԣ�����1��·�������硰CPU=1\\\\xYC=4\\\\item-index=2��������2������ID�����硰nane��������3������";
	m_listFunc.push_back(fData);

// 	fData = new FUNCDATA;
// 	fData->strFunc =L"RecordPkg( );";
// 	fData->strname = L"RecordPkg";
// 	fData->strMsg = L"���ù�Լ����¼����Լ֡������1��ʾ��Լ֡��ID";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"UnRecordPkg();";
// 	fData->strname = L"UnRecordPkg";
// 	fData->strMsg = L"ȡ����Լ����¼����Լ֡������1��ʾ��Լ֡��ID";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"GetPckgPcTm( , , );";
// 	fData->strname = L"GetPckgPcTm";
// 	fData->strMsg = L"�õ���Լ֡�ķ���/����ʱ�䣬����1��ʾ��Լ֡��ID������2��ʾ�洢�ı���������ID������3��ʾ��ȡ���ǵ�һ�����������һ������";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"GetGpsPcTmMap(,);";
// 	fData->strname = L"GetGpsPcTmMap";
// 	fData->strMsg = L"�ӱ�׼Դ��ȡGPSʱ����PCʱ��Ķ�Ӧ��ϵ������1:�洢GPSʱ��ı���; ����2���洢PCʱ��ı���";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"GetOutGpsTm( );";
// 	fData->strname = L"GetOutGpsTm";
// 	fData->strMsg = L"��ȡ��׼Դ���ʱ�̵�GPSʱ��. ����1:�洢ʱ��ı���ID";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"CalGpsPcTmGap(,);";
// 	fData->strname = L"CalGpsPcTmGap";
// 	fData->strMsg = L"��������ʱ��ļ��,���غ�����������1��ʾ��һ��ʱ��ı���������2��ʾ�ڶ���ʱ��ı���";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"RdMacroTest();";
// 	fData->strname = L"RdMacroTest";
// 	fData->strMsg = L"��ȡ��׼Դ�Ľ������";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"CrtGpsDtTm();";
// 	fData->strname = L"CrtGpsDtTm";
// 	fData->strMsg = L"����һ��GPSʱ����󣬰����ꡢ�¡��ա�ʱ���֡��롢���롢΢��";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"CrtGpsTm();";
// 	fData->strname = L"CrtGpsTm";
// 	fData->strMsg = L"����һ��GPSʱ����󣬰���ʱ���֡��롢���롢΢��";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"LGetRptDatas(, , );";
// 	fData->strname = L"LGetRptDatas";
// 	fData->strMsg = L"��ȡ���������ı������ݵĸ���������1����Ŀ��·��������2�����ݵ�ID������3�����ݵ�ֵ";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"DownMacroPara();";
// 	fData->strname = L"DownMacroPara";
// 	fData->strMsg = L"�������ص�����������Ŀ�Ĳ������ݣ������е�ͨѶ������ã�";
// 	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SelectItem();";
	fData->strname = L"SelectItem";
	fData->strMsg = L"ѡ��ĳ����Ŀ������1����Ŀ��·��";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptCnt();";
	fData->strname = L"GtItmRptCnt";
	fData->strMsg = L"��õ�ǰѡ�����Ŀ�ı���ĸ���";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SelItemRpt();";
	fData->strname = L"SelItemRpt";
	fData->strMsg = L"ѡ����Ŀ�ı�����󣬲���1����Ŀ�ı��������";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptVal();";
	fData->strname = L"GtItmRptVal";
	fData->strMsg = L"�����Ŀ��ָ���ı�������ݣ�������������1��ֵ��ID";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptValL();";
	fData->strname = L"GtItmRptValL";
	fData->strMsg = L"�����Ŀ��ָ���ı�������ݣ�����������1��ֵ��ID";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptValS();";
	fData->strname = L"GtItmRptValS";
	fData->strMsg = L"�����Ŀ��ָ���ı�������ݣ��ַ���������1��ֵ��ID";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptVCnt();";
	fData->strname = L"GtItmRptVCnt";
	fData->strMsg = L"�����Ŀ��ָ���ı�������ݸ���";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptVal2();";
	fData->strname = L"GtItmRptVal2";
	fData->strMsg = L"�����Ŀ��ָ���ı�������ݣ�������������1��ֵ������ţ���0��ʼ���";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptValL2();";
	fData->strname = L"GtItmRptValL2";
	fData->strMsg = L"�����Ŀ��ָ���ı�������ݣ�����������1��ֵ������ţ���0��ʼ���";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptValS2();";
	fData->strname = L"GtItmRptValS2";
	fData->strMsg = L"�����Ŀ��ָ���ı�������ݣ��ַ���������1��ֵ������ţ���0��ʼ���";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptDCnt();";
	fData->strname = L"GtItmRptDCnt";
	fData->strMsg = L"�����Ŀ��չ��������ݸ���";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptDVal();";
	fData->strname = L"GtItmRptDVal";
	fData->strMsg = L"�����Ŀ��չ�������ݣ�������������1���������ݵ�����������2���������ݵĲ���ID";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptDValL();";
	fData->strname = L"GtItmRptDValL";
	fData->strMsg = L"�����Ŀ��չ�������ݣ�����������1���������ݵ�����������2���������ݵĲ���ID";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptDValS();";
	fData->strname = L"GtItmRptDValS";
	fData->strMsg = L"�����Ŀ��չ�������ݣ��ַ���������1���������ݵ�����������2���������ݵĲ���ID";
	m_listFunc.push_back(fData);

// 	luabind::def("CalIEC", &GBS_IEC),
// 		luabind::def("CalIEEE", &GBS_IEEE),
// 		luabind::def("CalIAC", &GBS_IAC),
// 		luabind::def("CalI2T", &GBS_I2T)

	fData = new FUNCDATA;
	fData->strFunc =L"CalIEC( , , , );";
	fData->strname = L"CalIEC";
	fData->strMsg = L"IEC(double dValue, double dTp, double dK, double dAlpha)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CmpDouble(  ,  ,  );";
	fData->strname = L"CmpDouble";
	fData->strMsg = L"double�������Ƚϣ�����������Ϊ�ȽϾ���CmpDouble(strVa1, strVal2, strPrecision)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalRelErr(  ,  );";
	fData->strname = L"CalRelErr";
	fData->strMsg = L"�������������1�����������ֵ������2����׼����ֵ";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RunExe( \"\" , \"\" );";
	fData->strname = L"RunExe";
	fData->strMsg = L"����Exe���򣬲���1��Exe����ľ���·�������硰D:\\\\Program Files\\\\EPOTO\\\\e-Report\\\\Bin\\\\CommCmdTest.exe��������2������������в���";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"ExitExe( \"\" );";
	fData->strname = L"ExitExe";
	fData->strMsg = L"�������̣�������Exe��������֣����硰CommCmdTest.exe��";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalIEEE( , , , , , , , );";
	fData->strname = L"CalIEEE";
	fData->strMsg = L"CalIEEE(double dValue, double dTp, double dA, double dB, double dP, double dQ, double dK1, double dK2)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalIAC( , , , , , , , );";
	fData->strname = L"CalIAC";
	fData->strMsg = L"CalIAC(double dValue, double dTp, double dA, double dB, double dC, double dD, double dE, double dBeta)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalI2T( , , );";
	fData->strname = L"CalI2T";
	fData->strMsg = L"CalI2T(double dValue, double dTp, double dA)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalTimeGap( , );";
	fData->strname = L"CalTimeGap";
	fData->strMsg = L"CalTimeGap(string strTime1, string strTime2)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalTimeGapCurr( );";
	fData->strname = L"CalTimeGapCurr";
	fData->strMsg = L"CalTimeGapCurr(string strTime1)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"AddLocalTime( );";
	fData->strname = L"AddLocalTime";
	fData->strMsg = L"AddLocalTime(nHour, nMinute, mSecond)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SubLocalTime( );";
	fData->strname = L"SubLocalTime";
	fData->strMsg = L"SubLocalTime(nHour, nMinute, mSecond)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RptExDsGetCount( );";
	fData->strname = L"RptExDsGetCount";
	fData->strMsg = L"RptExDsGetCount(string strPath)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RptExDsGetValueD( );";
	fData->strname = L"RptExDsGetValueD";
	fData->strMsg = L"RptExDsGetValueD(string strPath, long nIndex)";
	m_listFunc.push_back(fData);


	fData = new FUNCDATA;
	fData->strFunc =L"RptExDsGetValueL( );";
	fData->strname = L"RptExDsGetValueL";
	fData->strMsg = L"RptExDsGetCount(string strPath, long nIndex)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RptExDsGetValueStr( );";
	fData->strname = L"RptExDsGetValueStr";
	fData->strMsg = L"RptExDsGetValueStr(string strPath, long nIndex)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"DsvClear( );";
	fData->strname = L"DsvClear";
	fData->strMsg = L"DsvClear()";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"DsvAddElement( );";
	fData->strname = L"DsvAddElement";
	fData->strMsg = L"DsvAddElement(string strText, long nOption, long nUnbound)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"DsvAddEChoice( );";
	fData->strname = L"DsvAddEChoice";
	fData->strMsg = L"DsvAddEChoice(string strText, long nOption, long nUnbound)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"DsvValid( );";
	fData->strname = L"DsvValid";
	fData->strMsg = L"DsvValid(long nValidateHead)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RecordCmd(\"\", \"\");";
	fData->strname = L"RecordCmd";
	fData->strMsg = L"RecordCmd(string strCmdID, string strCmdPara)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"AdjustWord( 0 );";
	fData->strname = L"AdjustWord";
	fData->strMsg = L"AdjustWord(long nPopDlg)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalSoeTime(\"\", \"\", \"\");";
	fData->strname = L"CalSoeTime";
	fData->strMsg = L"CalSoeTime(char *pszRptID, char *pszSoe1Attr, char *pszSoe2Attr)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalSoeTimeEx(\"\", \"\", \"\");";
	fData->strname = L"CalSoeTimeEx";
	fData->strMsg = L"CalSoeTime(char *pszRptID, char *pszSoe1Attr,char *pszVal1, char *pszSoe2Attr,char *pszVal2)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalSoeTripDesc(\"\", \"\");";
	fData->strname = L"CalSoeTripDesc";
	fData->strMsg = L"CalSoeTripDesc(char *pszRptID, char *pszSoeID)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetItemTestTime(\"\");";
	fData->strname = L"GetItemTestTime";
	fData->strMsg = L"GetItemTestTime(const char* pszPath)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalSoeError( , \"\" , \"\" , \"\", , , );";
	fData->strname = L"CalSoeError";
	fData->strMsg = L"CalSoeError(double dRate, char* pszPath, char *pszRptID, char *pszAbsErrID, char* pszRelErrID, double dStdVal, double dAbsErr, double dRelErr)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalSoeError2( , \"\" , \"\" , \"\", , , , );";
	fData->strname = L"CalSoeError2";
	fData->strMsg = L"CalSoeError2(double dRate, char* pszPath, char *pszRptID, char *pszAbsErrID, char* pszRelErrID, double dStdVal, double dRelCalStdVal, double dAbsErr, double dRelErr)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RcdSelect(\"\");";
	fData->strname = L"RcdSelect";
	fData->strMsg = L"RcdSelect(const char* pszPara)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RcdConfig();";
	fData->strname = L"RcdConfig";
	fData->strMsg = L"RcdConfig()";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RcdValidate(\"\");";
	fData->strname = L"RcdValidate";
	fData->strMsg = L"RcdValidate(const char* pszRsltID)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRepeatTimes(\"\");";
	fData->strname = L"GetRepeatTimes";
	fData->strMsg = L"GetRepeatTimes(const char* pszItemPath)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRepeatSuccTimes(\"\");";
	fData->strname = L"GetRepeatSuccTimes";
	fData->strMsg = L"GetRepeatSuccTimes(const char* pszItemPath)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetCmdZoneIndex( );";
	fData->strname = L"SetCmdZoneIndex";
	fData->strMsg = L"SetCmdZoneIndex(long nZoneIndex)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"ValidBeginEndValRange(\"BeginVal\",\"EndVal\", \"Step\", 0.1, 0.001, 10, 200, 0);";
	fData->strname = L"ValidBeginEndValRange";
	fData->strMsg = L"SetCmdZoneIndex(char *pBeginValID, char *pEndValID, char *pStepID, double dMinRange, double dMinStep, long nMinSteps, long nMaxSteps, long nUseNeg)";
	m_listFunc.push_back(fData);
}

void CFuncComboBox::DeleteAll()
{
	LISTFUNC::const_iterator iter = m_listFunc.begin();
	for (;iter != m_listFunc.end();iter++)
	{
		PFUNCDATA pData = *iter;
		delete pData;
	}
}

CFuncComboBox::~CFuncComboBox(void)
{
	DeleteAll();
}
BEGIN_MESSAGE_MAP(CFuncComboBox, CComboBox)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int CFuncComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}

void CFuncComboBox::PreSubclassWindow()
{
	LISTFUNC::const_iterator iter = m_listFunc.begin();
	for (;iter != m_listFunc.end();iter++)
	{
		PFUNCDATA pData = *iter;
		AddString(pData->strname);
	}

	CComboBox::PreSubclassWindow();
}

CString CFuncComboBox::GetSelectedstrFunc()
{
	PFUNCDATA pData = GetSelectedData();
	if (pData == NULL)
	{
		return L"";
	}
	return pData->strFunc;

}

struct FuncData;

PFUNCDATA CFuncComboBox::GetSelectedData()
{
	int nIndex = GetCurSel();
	if (nIndex ==-1)
	{
		return NULL;
	}

	CString strName;
	GetLBText(nIndex,strName);
	PFUNCDATA pData = NULL;

	LISTFUNC::const_iterator iter = m_listFunc.begin();
	for (;iter != m_listFunc.end();iter++)
	{
		pData = *iter;
		if (pData->strname == strName)
		{
			break;
		}
	}

	return pData;
}

CString CFuncComboBox::GetSelectedstrMsg()
{
	PFUNCDATA pData = GetSelectedData();

	return pData->strMsg;
}