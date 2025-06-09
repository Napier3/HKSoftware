//Volt
#ifdef _MainBoard_PI_
    #include "./Volt/PI/SttPowerCtrl_PI_V130.h"
    #include "./Volt/PI/SttPowerCtrl_PI_V270.h"
    #include "./Volt/PI/SttPowerCtrl_PI_V300.h"
    #include "./UI/PI/SttPowerCtrl_PI_V130C20.h"
#elif _MainBoard_PTU_
    #include "./Volt/PTU/SttPowerCtrl_PTU_V270.h"
    #include "./Volt/PTU/SttPowerCtrl_PTU_V300.h"
#elif _MainBoard_PN_
    #include "./Volt/PN/SttPowerCtrl_PN_V130.h"
    #include "./Volt/PN/SttPowerCtrl_PN_V248.h"
    #include "./Volt/PN/SttPowerCtrl_PN_V270.h"
    #include "./Volt/PN/SttPowerCtrl_PN_V300.h"
    #include "./UI/PN/SttPowerCtrl_PN_V130C20.h"
    #include "./UI/PN/SttPowerCtrl_PN_V310C60.h"
	#include "./Volt/PTU200L/SttPowerCtrl_V270_PTU200L.h"
#else
    #include "SttPowerCtrlBase.h"
#endif

//Current
#if defined(_MainBoard_PI_)||defined(_MainBoard_PTU_)||defined(_MainBoard_PN_)
    #include "./Current/SttPowerCtrl_C12_5.h"
    #include "./Current/SttPowerCtrl_C20.h"
    #include "./Current/SttPowerCtrl_C32.h"
#endif
