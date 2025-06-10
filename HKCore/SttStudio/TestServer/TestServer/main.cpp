#include"../../Module/SttTest/SttTestServerApp_QT/SttTestServerApp.h"
#include "../../Module/SttTest/PNS330/SttTestFactoryPNS330.h"
#include "../../Module/SttDevice/PNS330/SttDevicePNS330.h"
#include "../../Module/OSInterface/QT/CDateTime_QT.h"
#include "../../Module/RecordTest/RingMemBufShm.h"
#include "QProcess"
#include "../../Module/API/GlobalConfigApi.h"

//2022-4-7  lijunqing ��ͬ�Ĳ�Ʒ��ʹ�õķ�ʽ�ǲ�ͬ�ģ����磺AT02Dʹ�÷����ڴ淽ʽ
//330ʹ�ù����ڴ淽ʽ�����Ի������ڸ����̵�Main�д������Ա�֤ͨ����
extern CRingMemBuf *g_pSttRcdSndRingBuf;

int main(int argc, char *argv[])
{
    //g_strDrvName = "SttDriver_PNS330";
    //g_strAppName = "SttTestServer_PNS330";
    qDebug() << ">>>>>>start!";
    qDebug() << ">>>>>>main!!";
	CDateTime::CreateClientDataTime();
	CSttTestFactoryPNS330::Create();
	CSttDevicePNS330::Create();
	CSttTestServerApp  a(argc, argv);
    _P_InitSystemPath();

#ifdef SVR_DEBUG_MODE
    drv_reg_debug_create_file();
#endif


    CRingMemBufShm *pShmMemBuf = new CRingMemBufShm;
    pShmMemBuf->ShmCreateServer();
    g_pSttRcdSndRingBuf = pShmMemBuf;    
	a.InitSttTestServerBaseApp();
	stt_test_new_base_manualtest_buff();
    stt_test_new_base_harmtest_buff();
	stt_test_new_base_statetest_buff();
	stt_test_new_ex_ImpBase_buff();
	stt_test_new_synparas_buff();



    int nRet = a.exec();                //�¼�ѭ�����������������С�
	a.ExitSttTestServerBaseApp();

    stt_test_free_base_manualtest_buff();
    stt_test_free_base_harmtest_buff();
    stt_test_free_base_statetest_buff();
	stt_test_free_ex_ImpBase_buff();
    stt_test_free_synparas_buff();
	CSttDevicePNS330::Release();
	CSttTestFactoryPNS330::Release();
	CDateTime::ReleaseClientDataTime();
    delete g_pSttRcdSndRingBuf;

#ifdef SVR_DEBUG_MODE
    drv_reg_debug_Release_file();
#endif

	return nRet;
}

