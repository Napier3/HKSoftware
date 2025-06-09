#if !defined(RadRDLibrary_H)
#define RadRDLibrary_H

#pragma comment (lib,"RadRRKit.lib")
//-----------------------------------------------------------------------------
// RD-Kit Library Interface
//  Radian Research, Inc.
//  Copyright  2000-2005.  All Rights Reserved.
//
//   FILE:    RDKitLibrary.h
//   AUTHOR:  Brent Rardin 7/03/00
//                 Mike Henderson 2/11/2005
//
//   OVERVIEW
//   ========
//   Radian RD-xx communications interface libray functions.
//
//   REVISIONS
//   =========
//   9/4/03  JAS - Add RD3x commands and update other APIs for true RD-3x
//
//    v3.00.00
//     2/11/05 MWH - Completed RD-3x commands, updates and additions.
//-----------------------------------------------------------------------------

// The following ifdef block is the standard way of creating macros which make 
// exporting from a DLL simpler. All files within this DLL are compiled with 
// the RADRD1COMM_EXPORTS symbol defined on the command line. This symbol 
// should NOT be defined on any project that uses this DLL. This way any other 
// project whose source files include this file see RADRDKIT_API functions as 
// being imported from a DLL, wheras this DLL sees symbols defined with this 
// macro as being exported.

#define RADRDKIT_API2 __stdcall
#ifdef RADRDKIT_EXPORTS
   #define RADRDKIT_API1 extern "C" __declspec(dllexport)
#else
   #define RADRDKIT_API1 extern "C" __declspec(dllimport)
#endif

// Data type definitions
//-----------------------------------------------------------------------------
typedef unsigned char  byte;
typedef unsigned short uint16;
typedef unsigned long  RADDEVICEID;
typedef signed long    ERRORCODE;

// Minimum size for data strings to use in functions that return data.
#define RAD_SIZE_MODEL      10            // RadRDModel()
#define RAD_SIZE_SERIAL      8            // RadRDSerial()
#define RAD_SIZE_NAME       16            // RadRDName()
#define RAD_SIZE_VERSION     8            // RadRDVersion()
#define RAD_SIZE_MESSAGE   256            // RadRDMessage()
#define RAD_INVALID_DATA   3.402823E+38    // Invalid Number (Used when reading metrics)

// RD-30 Phase Definitions
#define RAD_PHASE_NONE      0  // Use this for single phase devices (RD-2x)
#define RAD_PHASE_NET       0
#define RAD_PHASE_A         1
#define RAD_PHASE_B         2
#define RAD_PHASE_C         3
#define RAD_PHASE_N         4

// RD-2x/3x Auto-Calibration Definitions (RadRDAutocalSet and RadRDAutocalStatus)
#define RAD_FULL_AUTOCAL     0
#define RAD_PARTIAL_AUTOCAL  1

// RD-2x/3x Measurement Mode Definitions (RadRDModeSet)
#define RAD_MODE_AC_RMS        0
#define RAD_MODE_AC_AVG        1    //Only valid for RD-2X-4XX
#define RAD_MODE_DC_RMS        2    //Only valid for RD-22-XXX
#define RAD_MODE_DC_AVG        3    //Only valid for RD-22-4XX

// RD-2x/3x System Status Flag Definitions (RadRDSystemStatus)
#define RAD_STATUS_AUTOCAL          0x000001    //RD-2x Autocalibration Failure
#define RAD_STATUS_AUTOCAL_A        0x000002    //RD-3x Phase A Autocalibration Failure 
#define RAD_STATUS_AUTOCAL_B        0x000004    //RD-3x Phase B Autocalibration Failure
#define RAD_STATUS_AUTOCAL_C        0x000008    //RD-3x Phase C Autocalibration Failure
#define RAD_STATUS_MEMORY           0x000010    //RD-2x Memory Error or RD-3x Master Memory Error
#define RAD_STATUS_MEMORY_A         0x000020    //RD-3x Phase A Memory Error
#define RAD_STATUS_MEMORY_B         0x000040    //RD-3x Phase B Memory Error
#define RAD_STATUS_MEMORY_C         0x000080    //RD-3x Phase C Memory Error
#define RAD_STATUS_TDM_A            0x000200    //RD-3x Phase A TDM Error
#define RAD_STATUS_TDM_B            0x000400    //RD-3x Phase B TDM Error
#define RAD_STATUS_TDM_C            0x000800    //RD-3x Phase C TDM Error
#define RAD_STATUS_EBOARD           0x001000    //RD-2x E-Board Communication Error 
#define RAD_STATUS_EBOARD_A         0x002000    //RD-3x Phase A E-Board Communication Error
#define RAD_STATUS_EBOARD_B         0x004000    //RD-3x Phase B E-Board Communication Error
#define RAD_STATUS_EBOARD_C         0x008000    //RD-3x Phase C E-Board Communication Error
#define RAD_STATUS_PULSEEXCEED      0x010000    //RD-2x Pulse Output Exceeded Max Limits 
#define RAD_STATUS_PULSEEXCEED_A    0x020000    //RD-3x Phase A Pulse Output Exceeded Max Limits 
#define RAD_STATUS_PULSEEXCEED_B    0x040000    //RD-3x Phase B Pulse Output Exceeded Max Limits 
#define RAD_STATUS_PULSEEXCEED_C    0x080000    //RD-3x Phase C Pulse Output Exceeded Max Limits 

// Defines for the Instantaneous Metrics data (RadRDInstMetrics)
#define RAD_INST_V                     0  // Volts
#define RAD_INST_A                     1  // Amps
#define RAD_INST_W                     2  // Watts
#define RAD_INST_VA                    3  // VA
#define RAD_INST_VAR                   4  // VAR
#define RAD_INST_FREQ                  5  // Frequency
#define RAD_INST_PHASE                 6  // Phase Angle (between Volts & Amps)
#define RAD_INST_PF                    7  // Power Factor
#define RAD_INST_ANS                   8  // Analog Sense
#define RAD_INST_DPHASE                9  // Delta Phase( Volts A & phase read )
#define RAD_INST_V_DELTA              10  // Volts Delta mode
#define RAD_INST_W_DELTA              11  // Watts Delta mode
#define RAD_INST_VA_DELTA             12  // VA Delta mode
#define RAD_INST_VAR_DELTA            13  // VAR Delta mode
#define RAD_INST_VAR_WYE_XCONNECTED   14  // VAR WYE Cross-connected
#define RAD_INST_VAR_DELTA_XCONNECTED 15  // VAR DELTA Cross-connected


// Defines for the Accumulating Metrics data (RadRDAccumMetrics and
// RadRDSetPulseRate )
#define RAD_ACCUM_WH                               0   // Watt Hours
#define RAD_ACCUM_VARH                             1   // VAR Hours
#define RAD_ACCUM_QH                               2   // Q Hours
#define RAD_ACCUM_VAH                              3   // VA Hours
#define RAD_ACCUM_VH                               4   // Volt Hours
#define RAD_ACCUM_AH                               5   // Amp Hours
#define RAD_ACCUM_V2H                              6   // Volts Squared Hours
#define RAD_ACCUM_A2H                              7   // Amps Squared Hours
#define RAD_ACCUM_WHP                              8   // Positive Watt Hours
#define RAD_ACCUM_WHN                              9   // Negative Watt Hours
#define RAD_ACCUM_VARHP                           10   // Positive VAR Hours
#define RAD_ACCUM_VARHN                           11   // Negative VAR Hours
#define RAD_ACCUM_WH_DELTA                        12   // Watt hours Delta
#define RAD_ACCUM_TIME                            13   // Accumulated Time
#define RAD_ACCUM_VAH_DELTA                       14   // VA Hours Delta
#define RAD_ACCUM_VARH_DELTA                      15   // VAR Hours Delta 
#define RAD_ACCUM_VARH_DELTA_XCONNECTED           16   // VAR Hours Delta X
#define RAD_ACCUM_VARH_WYE_XCONNECTED             17   // VAR Hours WYE X
#define RAD_ACCUM_WH_DELTA_POSITIVE               18   // Watt Hours Delta +
#define RAD_ACCUM_WH_DELTA_NEGATIVE               19   // Watt Hours Delta -
#define RAD_ACCUM_VARH_DELTA_POSITIVE             20   // VAR Hours Delta +
#define RAD_ACCUM_VARH_DELTA_NEGATIVE             21   // VAR Hours Delta -
#define RAD_ACCUM_VARH_DELTA_XCONNECTED_POSITIVE  22   // VAR Hours Delta X +
#define RAD_ACCUM_VARH_DELTA_XCONNECTED_NEGATIVE  23   // VAR Hours Delta X -
#define RAD_ACCUM_VARH_WYE_XCONNECTED_POSITIVE    24   // Var Hours WYE X +
#define RAD_ACCUM_VARH_WYE_XCONNECTED_NEGATIVE    25   // Var Hours WYE X -


// Defines for the RadRDAccumPulse modes
#define PULSE_MANUAL_MODE 0
#define PULSE_SENSOR_MODE 1

// Valid values for the Pulse Output setting (RadRDGetPulseOutput and 
// for RadRDSetPulseOutput)
#define RAD_PO_RD3x_PORT1           1    //Pulse Output Port 1 on RD-3x
#define RAD_PO_RD3x_PORT2           2    //Pulse Output Port 2 on RD-3x
#define RAD_PO_RD3x_PORT3           3    //Pulse Output Port 3 on RD-3x
#define RAD_PO_RD2x                 0    //Pulse Output on RD-2x (BNC 2)
#define RAD_PO_WH                               0   // Watt Hours
#define RAD_PO_VARH                             1   // VAR Hours
#define RAD_PO_QH                               2   // Q Hours
#define RAD_PO_VAH                              3   // VA Hours
#define RAD_PO_VH                               4   // Volt Hours
#define RAD_PO_AH                               5   // Amp Hours
#define RAD_PO_V2H                              6   // Volts Squared Hours
#define RAD_PO_A2H                              7   // Amps Squared Hours
#define RAD_PO_WHP                              8   // Positive Watt Hours
#define RAD_PO_WHN                              9   // Negative Watt Hours
#define RAD_PO_VARHP                           10   // Positive VAR Hours
#define RAD_PO_VARHN                           11   // Negative VAR Hours
#define RAD_PO_WH_DELTA                        12   // Watt hours Delta
#define RAD_PO_VAH_DELTA                       14   // VA Hours Delta
#define RAD_PO_VARH_DELTA                      15   // VAR Hours Delta 
#define RAD_PO_VARH_DELTA_XCONNECTED           16   // VAR Hours Delta X
#define RAD_PO_VARH_WYE_XCONNECTED             17   // VAR Hours WYE X
#define RAD_PO_WH_DELTA_POSITIVE               18   // Watt Hours Delta +
#define RAD_PO_WH_DELTA_NEGATIVE               19   // Watt Hours Delta -
#define RAD_PO_VARH_DELTA_POSITIVE             20   // VAR Hours Delta +
#define RAD_PO_VARH_DELTA_NEGATIVE             21   // VAR Hours Delta -
#define RAD_PO_VARH_DELTA_XCONNECTED_POSITIVE  22   // VAR Hours Delta X +
#define RAD_PO_VARH_DELTA_XCONNECTED_NEGATIVE  23   // VAR Hours Delta X -
#define RAD_PO_VARH_WYE_XCONNECTED_POSITIVE    24   // Var Hours WYE X +
#define RAD_PO_VARH_WYE_XCONNECTED_NEGATIVE    25   // Var Hours WYE X -

#define RAD_PULSEOUT_POSITIVE 0
#define RAD_PULSEOUT_NEGATIVE 1

//Defines for setting BNC input mode (RadRDInputControl)
#define RAD_INPUT_SSC_MANUAL    0    // Start/Stop/Clear Gating (Manual Type)
#define RAD_INPUT_CSS_MANUAL    1    // Clear+Start/Stop Gating (Manual Type)
#define RAD_INPUT_NEGATIVE      2    // Negative Pulses Out       (RD-2x Only)
#define RAD_INPUT_SSC_SENSOR    8    // Start/Stop/Clear Gating (Sensor Type)
#define RAD_INPUT_CSS_SENSOR    9    // Clear+Start/Stop Gating (Sensor Type)
#define RAD_INPUT_STATUS        0xFF // Get status of pulse input mode

// Valid values for the Voltage and Current tap settings (from RadRDGetTaps and 
// for RadRDSetTaps).  The Voltage axis uses taps 1 through 3.  The Current axis
// uses taps 1 through 13.  
#define RAD_TAP_UNLOCK    0
#define RAD_TAP_LOCK      1
#define RAD_TAP_UNLOCKED  0
#define RAD_TAP_LOCKED    1
#define RAD_TAP_OPEN      0
#define RAD_TAP_1         1
#define RAD_TAP_2         2
#define RAD_TAP_3         3
#define RAD_TAP_4         4
#define RAD_TAP_5         5
#define RAD_TAP_6         6
#define RAD_TAP_7         7
#define RAD_TAP_8         8
#define RAD_TAP_9         9
#define RAD_TAP_10        10
#define RAD_TAP_11        11
#define RAD_TAP_12        12
#define RAD_TAP_13        13

//Harmonic Analysis Trigger Control (RadRDHarmonicTrigger)
#define RAD_HARMONIC_STATUS     0    //Return status of harmonic analysis
#define RAD_HARMONIC_RESTART    1    //Return status of harmonic analysis  
                                     //Restart analysis if completed
#define RAD_HARMONIC_VOLTAGE    2    //Trigger to start voltage harmonic analysis 
                                     //on the requested harmonic number.  
                                     //If the harmonic number is 0 then stop analysis.
#define RAD_HARMONIC_CURRENT    3    //Trigger to start current harmonic analysis 
                                     //on the requested harmonic number.  
                                     //If the harmonic number is 0 then stop analysis.

//Return status (RadRDHarmonicTrigger)
#define RAD_HARMONIC_NOTRUNNING    0    //No harmonic analysis is being preformed
#define RAD_HARMONIC_INPROGRESS    1    //Harmonic Analysis in progress
#define RAD_HARMONIC_VREADY        2    //Voltage harmonic analysis ready
#define RAD_HARMONIC_IREADY        3    //Current(I) harmonic analysis ready

//HarmonicTrigger Structure
typedef struct _HARMONIC_STRUC {
    byte harmonic;        //Harmonic to read
    byte status;          //Control/Status register
    byte zoom;            //Subharmonic zoom factor
    byte base;            //Base Harmonic
    float magnitude;      //Magnitude measured
    float phase;          //Phase measured
    float distortion;     //Distortion measured
} HARMONIC_STRUC, *PHARMONIC_STRUC;

//Meter Test Control Defines (RadRDMeterTest)
#define RAD_METERTEST_STATUS    0    //Request status of running Meter Test
#define RAD_METERTEST_STARTTEST 1    //Start Meter Test
#define RAD_METERTEST_PULSE     0    //Pulse Based Sensor Test
#define RAD_METERTEST_TIMED     2    //Timed Based Sensor Test
#define RAD_METERTEST_MANUAL    4    //Pulse Based Manual Test
#define RAD_METERTEST_DEMAND    6    //Demand Meter Test
#define RAD_METERTEST_TOTALIZED 8    //Totalized test on RD-3x devices

//Meter Test Element Defines (RadRDMeterTest)
#define RAD_METERTEST_3          0    //3 Element meter
#define RAD_METERTEST_2_5        1    //2.5 Element meter
#define RAD_METERTEST_2          2    //2 Element meter
#define RAD_METERTEST_1          3    //1 Element meter

//Meter Test Structure
typedef struct _METER_TEST_STRUCT {
    byte function;      //Use RAD_ACCUM_XXXX defines for function desired
    byte control;       //Control and Status. Use RAD_METERTEST_XXX definitions
    float duration;     //duration of test in seconds if Timed and Demand Test
    float factor;       //kH factor for pulse and times tests or 
                        //demand register for demand testing
    byte elements;      //Number of meter elements. 
                        //Use RAD_METERTEST_XXX definitions
    byte c_elements;    //Number of Current elements. 1,2 and 3 are supported.
    uint16 revs;        //The number of revolutions for the Meter during the test.
                        //Only Sensor and Manual Tests.
    uint16 pulses_rev;  //The number of pulses per revolution for the Meter 
                        //during the test.  Only Sensor and Manual Tests.
    float percent_error;  //Percent error when test is complete.
    float registration;   //Percent Registration when test is complete.
    unsigned long pulses; //Number of pulses counted by the RD
    float metric;         //Accumulated metric value
} METER_TEST_STRUCT, *PMETER_TEST_STRUCT;

//Standard Test Control Defines (RadRDStandardTest)
#define RAD_STDTEST_STATUS    0    //Request status of running Meter Test
#define RAD_STDTEST_STARTTEST 1    //Start a Standard Test
#define RAD_STDTEST_NONRADIAN 0    //Non-Radian Standard
#define RAD_STDTEST_RADIAN    2    //Radian Standard
#define RAD_STDTEST_TIMED     0    //Time based standard test
#define RAD_STDTEST_PULSE     4    //Pulse based standard test
#define RAD_STDTEST_TOTALIZED 8    //Totalized test on RD-3x devices

//Standard Test Structure
typedef struct _STD_TEST_STRUCT {
    byte function;           //Use RAD_ACCUM_XXXX defines for function desired
    byte control;            //Control and Status. Use RAD_STDTEST_XXX definitions
    float duration;          //duration of test in seconds/pulses
    float constant;          //Pulse constant
    float percent_error;     //Percent error when test is complete.
    float registration;      //Percent Registration when test is complete.
    unsigned long pulses;    //Number of pulses counted by the RD
    float metric;            //Accumulated metric value
} STD_TEST_STRUCT, *PSTD_TEST_STRUCT;
//-----------------------------------------------------------------------------
// RadRDAssignDevice
//   uint16 commPort    Standard RS232 comm port identifier.  
//                       Comm1 = 1, Comm2 = 2, etc.
//   RADDEVICE *id      Handle to the attached RD-xx device.  This function 
//                       sets the handle to be used for the other RadRDxxx 
//                       function calls.  
//
// Returns ERRORCODE    A return value of 
//                      0 (zero) indicates the function was executed properly 
//                      and the RD-xx device accepted the command.  A non-zero 
//                      return usually indicates either a communication error.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   This function opens the RS-232 comm port and identifies the RD-xx device 
//   connected.  If a RD-xx device is found the DEVICEID handle is returned 
//   that ise to be used with the other function calls to read and set data on 
//   the RD-xx.  If the DEVICEID handle returned is zero or ERRORCODE is 
//   non-zero then the RD-xx assign function was not successful.  
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDAssignDevice( uint16 commPort,  
                                                             RADDEVICEID &id );


//-----------------------------------------------------------------------------
// RadRDReleaseDevice
//   RADDEVICEID id    Handle to the connected device for RadRDAssignDevice()
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Use this function to release the device from the Radian shared port.  Any
//    other Radian application will be uneffected.  If this application is the
//    last using the device, the port will be made available to the 
//    operating system.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDReleaseDevice( RADDEVICEID id );


//-----------------------------------------------------------------------------
// RadRDClosePort
//   uint16 commPort    Standard RS232 comm port identifier.  Comm1 = 1, 
//                       Comm2 = 2, etc.
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Use this function to close the comm port so that it can be used by other 
//    applications.  This also invalidates any RADDEVICEID handle used by this 
//    port.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDClosePort( uint16 commPort );


//-----------------------------------------------------------------------------
// RadRDPhaseCount
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 *count      Returned phase count.  For single phase device this will
//                       be 1.  For 3-phase devices this will be 4 or 5 (for 
//                       phases A, B, C, Net and N(neutral) if supported).
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//  Returns the number of phases supported by the device.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDPhaseCount( RADDEVICEID id,  
                                                               uint16 *count );


//-----------------------------------------------------------------------------
// RadRDModel
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   char *data         Buffer for the returned data.  Be sure the buffer is 
//                       at least the minimum size defined in RAD_SIZE_MODEL.
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//  Returns the model number for the RD-xx device.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDModel( RADDEVICEID id, char *data );


//-----------------------------------------------------------------------------
// RadRDSerial
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   char *data         Buffer for the returned data.  Be sure the buffer is 
//                       at least the minimum size defined in RAD_SIZE_SERIAL.
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//  Returns the serial number for the RD-xx device.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDSerial( RADDEVICEID id, char *data );


//-----------------------------------------------------------------------------
// RadRDName
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   char *data         Buffer for the returned data.  Be sure the buffer is 
//                       at least the minimum size defined in RAD_SIZE_NAME.
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//  Returns the device name for the RD-xx device.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDName( RADDEVICEID id, char *data );


//-----------------------------------------------------------------------------
// RadRDSetUnitName
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   LPCSTR name        String of the name to change the device to. 
//                       -16 characters will be used from sent buffer
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//  Changes the user defined name of the device.  The does not effect any 
//   parameters of the device, but allows the customer to name units as they
//   wish.  Be sure to size buffer to routine to 16 characters.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDSetUnitName(RADDEVICEID id, LPCSTR name);


//-----------------------------------------------------------------------------
// RadRDVersion
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   char *data         Buffer for the returned data.  Be sure the buffer is 
//                       at least the minimum size defined in RAD_SIZE_VERSION.
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//  Returns the version number for the RD-xx device.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDVersion( RADDEVICEID id, 
                                                                  char *data );


//-----------------------------------------------------------------------------
// RadRDStatus
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 *status     Returns status of RD-xx device.  Status codes are 
//                       defined in the documentation.
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//  Returns the last errorcode that was received by the device selected.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDStatus( RADDEVICEID id, 
                                                                long *status );


//-----------------------------------------------------------------------------
// RadRDMessage
//   long code        Error or status code.  Codes are defined in the 
//                     documentation.
//   char *data       Buffer for the returned data.  Be sure the buffer is 
//                     at least the minimum size defined in RAD_SIZE_MESSAGE.
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//  Returns a message for the errocode requested.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDMessage( long code, char *data );


//-----------------------------------------------------------------------------
// RadRDNOOP
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Sends a NOOP to the device connected.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDNOOP( RADDEVICEID id );


//-----------------------------------------------------------------------------
// RadRDInstMetric
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 phase       Phase to use (Phase A, B, C, NET or NONE)
//   uint16 function    Instantaneous metric function to read.  Use the 
//                       RAD_INST_xxx defines 
//   float *value       Returned metric value
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   This reads the requested Instananeous Metrics data.  
//    If an invalid number (RAD_INVALID_DATA) is returned, the device does not 
//    support the metric requested.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDInstMetric( RADDEVICEID id, 
                                 uint16 phase, uint16 function, float *value );


//-----------------------------------------------------------------------------
// RadRDInstMetricAll
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 function    Instantaneous metric function to read.  Use the 
//                       RAD_INST_xxx defines 
//   float *phaseA      Returned metric value for phase A
//   float *phaseB      Returned metric value for phase B
//   float *phaseC      Returned metric value for phase C
//   float *phaseN      Returned metric value for phase Neutral
//   float *phaseNet    Returned metric value for Net 
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   This reads all phases of Instananeous Metrics data in one command  
//    If an invalid number (RAD_INVALID_DATA) is returned, the device does not 
//    support the metric requested.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDInstMetricAll( RADDEVICEID id, 
                                               uint16 function, float *phaseA, 
                                               float *phaseB, float *phaseC, 
                                               float *phaseN, float *phaseNet );


//-----------------------------------------------------------------------------
// RadRDInstMetricTable
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 phase       Phase to use (Phase A, B, C, NET or NONE)
//   float *metrics     Returned metric values in float array
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   This reads the all Instananeous Metrics for phase selected.  
//    If an invalid number (RAD_INVALID_DATA) is returned, the device does not 
//    support the metric requested.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDInstMetricTable( RADDEVICEID id, 
                                   uint16 phase, LPSAFEARRAY FAR *metricdata );


//-----------------------------------------------------------------------------
// RadRDMaxMetric
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 phase       Phase to use (Phase A, B, C, NET or NONE)
//   uint16 function    Maximum metric function to read.  Use the 
//                       RAD_INST_xxx defines 
//   float *value       Returned metric value
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   This reads the requested Maximum Metrics data.  
//    If an invalid number (RAD_INVALID_DATA) is returned, the device does not 
//    support the metric requested.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDMaxMetric( RADDEVICEID id, 
                                 uint16 phase, uint16 function, float *value );


//-----------------------------------------------------------------------------
// RadRDMaxMetricAll
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 function    Maximum metric function to read.  Use the 
//                       RAD_INST_xxx defines 
//   float *phaseA      Returned metric value for phase A
//   float *phaseB      Returned metric value for phase B
//   float *phaseC      Returned metric value for phase C
//   float *phaseN      Returned metric value for phase Neutral
//   float *phaseNet    Returned metric value for Net 
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   This reads all phases of Maximum Metrics data in one command  
//    If an invalid number (RAD_INVALID_DATA) is returned, the device does not 
//    support the metric requested.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDMaxMetricAll( RADDEVICEID id, 
                                               uint16 function, float *phaseA, 
                                               float *phaseB, float *phaseC, 
                                               float *phaseN, float *phaseNet );


//-----------------------------------------------------------------------------
// RadRDMaxMetricTable
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 phase       Phase to use (Phase A, B, C, NET or NONE)
//   float *metrics     Returned metric values in float array
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   This reads the all Maximum Metrics for phase selected.  
//    If an invalid number (RAD_INVALID_DATA) is returned, the device does not 
//    support the metric requested.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDMaxMetricTable( RADDEVICEID id, 
                                   uint16 phase, LPSAFEARRAY FAR *metricdata );


//-----------------------------------------------------------------------------
// RadRDMinMetric
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 phase       Phase to use (Phase A, B, C, NET or NONE)
//   uint16 function    Minimum metric function to read.  Use the 
//                       RAD_INST_xxx defines 
//   float *value       Returned metric value
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   This reads the requested Minimum Metrics data.  
//    If an invalid number (RAD_INVALID_DATA) is returned, the device does not 
//    support the metric requested.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDMinMetric( RADDEVICEID id, 
                                 uint16 phase, uint16 function, float *value );


//-----------------------------------------------------------------------------
// RadRDMinMetricAll
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 function    Minimum metric function to read.  Use the 
//                       RAD_INST_xxx defines 
//   float *phaseA      Returned metric value for phase A
//   float *phaseB      Returned metric value for phase B
//   float *phaseC      Returned metric value for phase C
//   float *phaseN      Returned metric value for phase Neutral
//   float *phaseNet    Returned metric value for Net 
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   This reads all phases of Minimum Metrics data in one command  
//    If an invalid number (RAD_INVALID_DATA) is returned, the device does not 
//    support the metric requested.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDMinMetricAll( RADDEVICEID id, 
                                              uint16 function, float *phaseA, 
                                              float *phaseB, float *phaseC, 
                                              float *phaseN, float *phaseNet );


//-----------------------------------------------------------------------------
// RadRDMinMetricTable
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 phase       Phase to use (Phase A, B, C, NET or NONE)
//   float *metrics     Returned metric values in float array
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   This reads the all Minimum Metrics for phase selected.  
//    If an invalid number (RAD_INVALID_DATA) is returned, the device does not 
//    support the metric requested.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDMinMetricTable( RADDEVICEID id, 
                                   uint16 phase, LPSAFEARRAY FAR *metricdata );


//-----------------------------------------------------------------------------
// RadRDAccumMetric
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 phase       Phase to use (Phase A, B, C, NET or NONE)
//   uint16 function    Accumulating metric function to read.  Use the 
//                       RAD_ACCUM_xxx defines 
//   float *value       Returned metric value
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   This reads the requested Accumulating Metrics data.  
//    If an invalid number (RAD_INVALID_DATA) is returned, the device does not 
//    support the metric requested.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDAccumMetric( RADDEVICEID id, 
                                  uint16 phase, uint16 function, float *value);


//-----------------------------------------------------------------------------
// RadRDAccumMetricAll
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 function    Accumulating metric function to read.  Use the 
//                       RAD_ACCUM_xxx defines 
//   float *phaseA      Returned metric value for phase A
//   float *phaseB      Returned metric value for phase B
//   float *phaseC      Returned metric value for phase C
//   float *phaseN      Returned metric value for phase Neutral
//   float *phaseNet    Returned metric value for Net 
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   This reads the requested Accumulating Metrics data.  
//    If an invalid number (RAD_INVALID_DATA) is returned, the device does not 
//    support the metric requested.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDAccumMetricAll( RADDEVICEID id, 
                                              uint16 function, float *phaseA, 
                                              float *phaseB, float *phaseC, 
                                              float *phaseN, float *phaseNet );


//-----------------------------------------------------------------------------
// RadRDAccumMetricTable
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 phase       Phase to use (Phase A, B, C, NET or NONE)
//   float *metrics     Returned metric values in float array
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   This reads the all Accumulated Metrics for phase selected.  
//    If an invalid number (RAD_INVALID_DATA) is returned, the device does not 
//    support the metric requested.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDAccumMetricTable( RADDEVICEID id, 
                                   uint16 phase, LPSAFEARRAY FAR *metricdata );


//-----------------------------------------------------------------------------
// RadRDInstReset
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 phase       Phase to use (Phase A, B, C, NET or NONE)
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Resets int minimum and maximum values for all instantaneous metrics data.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDInstReset( RADDEVICEID id, 
                                                                 uint16 phase);


//-----------------------------------------------------------------------------
// RadRDAccumReset
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 phase        Phase to use (Phase A, B, C, NET or NONE)
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Resets accumulator values for all accumulating metrics data.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDAccumReset( RADDEVICEID id,
                                                                 uint16 phase);


//-----------------------------------------------------------------------------
// RadRDAccumStart
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Enables the accumulating metrics to start counting.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDAccumStart( RADDEVICEID id );


//-----------------------------------------------------------------------------
// RadRDAccumStop
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Stops the accumulating metrics.  Use the function RadRDAccumReset() to 
//    clear the accumulators.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDAccumStop( RADDEVICEID id );


//-----------------------------------------------------------------------------
// RadRDAccumPulse
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 *pulses     Number of pulses
//   uint16 mode        Manual or Senser mode
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   This will begin an accumlution test that will run for x pulses.  When 
//    called with pulses set to greater than zero the accumulators will be 
//    stopped, then cleared.  On the next pulse input the accumulators will 
//    start to run and continue until the specified number of pulses have 
//    occurred.  The accumulators will automatically stop on the last pulse.  
//    To get the status (the number of pulses remaining in the test) send 
//    this command with the number of pulses set to zero.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDAccumPulse( RADDEVICEID id,
                                                 uint16 *pulses, uint16 mode );


//-----------------------------------------------------------------------------
// RadRDAccumTime
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   float *seconds     Number of seconds to run the accumulator timed test.
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   This will begin a timed accumlution test.  When called the accumulators 
//    will be stopped, then cleared, then started to run for the specified 
//    seconds.  The accumulators will automatically stop when the test is 
//    finished.  Use the function with seconds set to zero to determine how much
//    time is left in the test.  
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDAccumTime( RADDEVICEID id, 
                                                              float *seconds );


//-----------------------------------------------------------------------------
// RadRDGetPulseOutput
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 port        Output port on RD-3x to get pulse output function
//                       For RD-2x Devices, this parameter is ignored.
//   uint16 *function   Current pulse output function assigned to pulse output 
//                       port selected  (RAD_PO_xxx defines)  
//   uint16 *phase      Current phase suppling the data for the pulse output. 
//                       (RAD_PHASE_xxx defines)
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Use this function to get the current function bindings used for the pulse 
//    output on pulse output port specified.  The function will be one of the 
//    values from the RAD_PO_xxx defines.  
//        EXAMPLE:    function=8 phase=0    --> Net of Wh+ on selected port
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDGetPulseOutput( RADDEVICEID id, 
                                                 uint16 port, uint16 *function,
                                                 uint16 *phase );


//-----------------------------------------------------------------------------
// RadRDSetPulseOutput
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 port        Output port on RD-3x to set pulse output function
//                       For RD-2x Devices, this parameter is ignored.
//   uint16 function    Pulse output funtion to assign to BNC2
//                       Phase to supply the data for the pulse output. 
//                       (RAD_PHASE_xxx defines)
//   uint16 phase       Phase to supply the data for the pulse output. 
//                       (RAD_PHASE_xxx defines)
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Set which function to use for the pulse output specified.  The function 
//    value must be set to one of the RAD_PO_xxx define values.  The phase selects
//    which metric (Phase A, Phase B ... Totalized (Net)) to pulse out.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDSetPulseOutput( RADDEVICEID id, 
                                                  uint16 port, uint16 function,
                                                  uint16 phase );


//-----------------------------------------------------------------------------
// RadRD3PhaseSync
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 *sync       3 phase sync control 0=Sync pulse out else Sync pulse in
//                       Sending a 255 (0xFF) will return the status of the
//                       3 phase sync.
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//  This routine will read or change the state of the RD-2x 3 phase sync (BNC 3)
//   This command only works on RD-2x units without analog sense.    
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRD3PhaseSync( RADDEVICEID id, 
                                                                uint16 *sync );


//-----------------------------------------------------------------------------
// RadRDGetPulseRate
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 function    Pulse output funtion to set
//   float *value       Pulse output rate
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                        successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Sets the pulse output rate for the specified function.  The function 
//    value must be set to one of the RAD_PO_xxx define values.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDGetPulseRate( RADDEVICEID id, 
                                               uint16 function, float *value );


//-----------------------------------------------------------------------------
// RadRDSetPulseRate
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 function    Pulse output funtion to set
//   float value        Pulse output rate to set
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Sets the pulse output rate for the specified function.  The function 
//    value must be set to one of the RAD_PO_xxx define values.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDSetPulseRate( RADDEVICEID id, 
                                                uint16 function, float value );


//-----------------------------------------------------------------------------
// RadRDInputControl
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 *setup      BNC input setup.  Use RAD_INPUT_XXX defines
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   This will set the gating mode of the BNC input port(s).
//    Sending setup=0xFF will request status from the command.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDInputControl( RADDEVICEID id, 
                                                               uint16 *setup );


//-----------------------------------------------------------------------------
// RadRDBeepControl
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 *beep       Beep control 0=Beeper disabled else beeper enabled
//                       Sending a 255 (0xFF) will return the status of beeper.
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   This routine will turn on/off the gate beeper.  If beep is set to 0 then
//    the beeper will be disabled else the beeper will be enabled.  Sending a 
//    255 (0xFF) will return the status of beeper.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDBeepControl( RADDEVICEID id, 
                                                                uint16 *beep );


//-----------------------------------------------------------------------------
// RadRDLockTap
//   RADDEVICEID id    Handle to the connected device from RadRDAssignDevice()
//   uint16 phase      Phase to use (Phase A, B, C, NET or NONE)
//   uint16 axis       0 = Voltage Axis,  1 = Current Axis
//   uint16 tap        Tap setting.  Use the defines RAD_TAP_xx
//
// Returns ERRORCODE   A return value of 0 (zero) indicates the function was 
//                     successful.
//                     Use RadRDMessage to determine meaning of the errorcode. 
//
//   This will lock the specified axis to the specified tap.  The Voltage axis 
//    uses taps 1 through 3.  The Current axis uses taps 1 through 13.  Note if 
//    the voltage/current measured exceeds the limit of the locked tap 
//    setting, the RD will auto range to higher taps.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDLockTap( RADDEVICEID id, 
                                                     uint16 phase, uint16 axis,
                                                     uint16 tap );


//-----------------------------------------------------------------------------
// RadRDUnlockTap
//   RADDEVICEID id    Handle to the connected device from RadRDAssignDevice()
//   uint16 phase      Phase to use (Phase A, B, C, Net or NONE)
//   uint16 axis       0 = Voltage Axis,  1 = Current Axis
//
// Returns ERRORCODE   A return value of 0 (zero) indicates the function was 
//                     successful.
//                     Use RadRDMessage to determine meaning of the errorcode. 
//
//   Unlocks the tap setting for the specified axis.  This allows the RD to 
//    auto range to the appropriate tap.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDUnlockTap( RADDEVICEID id, 
                                                   uint16 phase, uint16 axis );


//-----------------------------------------------------------------------------
// RadRDGetTaps
//   RADDEVICEID id   Handle to the connected device from RadRDAssignDevice()
//   uint16 phase     Phase to use (Phase A, B, C or NONE)
//   uint16 *vLock    Returns whether the voltage Tap is locked or not. 
//                     RAD_TAP_LOCKED or RAD_TAP_UNLOCKED
//   uint16 *vTap     Returns voltage Tap setting.  Uses the defines RAD_TAP_xx
//   uint16 *iLock    Returns whether the current Tap is locked or not. 
//                     RAD_TAP_LOCKED or RAD_TAP_UNLOCKED
//   uint16 *iTap     Returns current Tap setting.  Uses the define RAD_TAP_xx
//
// Returns ERRORCODE   A return value of 0 (zero) indicates the function was 
//                     successful.
//                     Use RadRDMessage to determine meaning of the errorcode. 
//
//   Returns the Voltage and Current tap settings
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDGetTaps( RADDEVICEID id, 
                                     uint16 phase, uint16 *vLock, uint16 *vTap,
                                     uint16 *iLock, uint16 *iTap );


//-----------------------------------------------------------------------------
// RadRDResetDevice
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Resets the device.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDResetDevice( RADDEVICEID id );


//-----------------------------------------------------------------------------
// RadRDPotentialGating
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//     uint16 state     Set this to 0x01 to turn on-potential gating.
//                       Set this to 0x00 to turn off potential gating.
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//  Turns on potential gating, Potential gating is only available to units 
//   with 07.02.10 and higher.  Turning off potential gating is only
//   available in 07.04.60 and higher.  Potential gating will be disabled on 
//   reset or power cycle.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDPotentialGating( RADDEVICEID id,
                                                                uint16 state );


//-----------------------------------------------------------------------------
// RadRDAutoCalStatus
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 *acal_state Status of auto-calibration state of unit connected.
//                       Use the RAD_XXXXXXX_AUTOCAL defines
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Returns the status of auto-calibration of the unit.
//    Use the RAD_XXXXXXX_AUTOCAL defines
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDAutoCalStatus( RADDEVICEID id,
                                                          uint16 *acal_state );


//-----------------------------------------------------------------------------
// RadRDAutoCalSet
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 acal_state  State of auto-calibration to set the unit connected.
//                       Use the RAD_XXXXXXX_AUTOCAL defines
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Sets the state of auto-calibration of the unit.  
//    Use the RAD_XXXXXXX_AUTOCAL defines
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDAutoCalSet( RADDEVICEID id,
                                                           uint16 acal_state );


//-----------------------------------------------------------------------------
// RadRDModeSet
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 mode        Mode to set the connected device to RMS/AVG/DC/AC.
//                       Use the RAD_MODE_XX_XXX defines
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Sets the mode of the device connected.  Changing the mode is static and
//    the unit will stay in the mode selected unit changed, reguardless of
//    power cycling or reseting.  Use the RAD_MODE_XX_XXX defines
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDModeSet( RADDEVICEID id, 
                                                                 uint16 mode );


//-----------------------------------------------------------------------------
// RadRDModeStatus
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   uint16 *mode       Mode to get the connected device mode RMS/AVG/DC/AC.
//                       Use the RAD_MODE_XX_XXX defines
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//  Gets the mode of the device connected.  
//   Use the RAD_MODE_XX_XXX defines
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDModeStatus( RADDEVICEID id, 
                                                                uint16 *mode );


//-----------------------------------------------------------------------------
// RadRDSystemStatus
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   long *status       System Status flags for RD-XX.
//                       Use the RAD_STATUS_XXX_X defines
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
// Reads the devices system status flags and reports any errors found.
//  Error bits are defined using RAD_STATUS_XXX_X defines.
//  If status returns 0 then no error were found.
//  Sending anything other than a 0 for the status will attempt to clear any
//  errors that were discovered.  If the error repeats, it is unclearable, and
//  a power cycle/reset may be required.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDSystemStatus( RADDEVICEID id,
                                                                long *status );


//-----------------------------------------------------------------------------
// RadRDIntegrationTime
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   float *value       Time in seconds for integration time of Instantaneous 
//                       Metrics.  Valid time is in multiples of 0.5 seconds.
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Sets the integration time for the Instantaneous metrics in 0.5 second
//    intervals.  i.e. value=4.5, intergation time will be 4.5 Seconds.
//    This command is valid only for units with firmware 07.02.10 and higher.
//    Entering a 0 for Value will return the current integration time in seconds.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDIntegrationTime( RADDEVICEID id,
                                                                float *value );


//-----------------------------------------------------------------------------
// RadRDGetTemperature
//   RADDEVICEID id     Handle to the connected device from RadRDAssignDevice()
//   float *temperature Temperature in degrees Celsius.
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
// This reads the a temperature sensor built into the device.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDGetTemperature( RADDEVICEID id, 
                                                          float *temperature );


//-----------------------------------------------------------------------------
// RadRDHarmonicAnalysis
//   RADDEVICEID id    Handle to the connected device from RadRDAssignDevice()
//   uint16 phase      Phase to use (Phase A, B, C, Net or NONE)
//   PHARMONIC_STRUC harmonic    Structure of harmonic data/status
//
//  HARMONIC_STRUC {
//    byte harmonic;     Harmonic number requested     (Input/Output)
//    byte status;       Status of Trigger             (Input/Output)
//    byte zoom;         Zoom for subharmonics         (Input)
//    byte base;         Base harmonic                 (Input)
//    float magnitude;   Magnitude                     (Output)
//    float phase;       Phase                         (Output)
//    float distortion;  Distortion                    (Output)
//  } 
//                                    
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//  Starts or reads status of harmonic analysis in RD-2x/3x devices with
//   firmware 07.03.70 or higher.  Harmonic status is defined with 
//   RAD_HARMONIC_XXX Harmonic number is the harmonic requested i.e. 
//   fundamental=1. Magnitude, phase and distortion are floating point numbers
//   from the unit when the status register shows that the harmonic analysis 
//   is complete. Zoom factor and base harmonic should normally be set to 1.
//   To do sub harmonic content measurement, the zoom factor can be a value of
//   1 to 10.  The base harmonic can be changed to modify the start point of 
//   the harmonic measurement.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDHarmonicAnalysis( RADDEVICEID id,
                                                    uint16 phase,
                                                    PHARMONIC_STRUC harmonic );


//-----------------------------------------------------------------------------
// RadRDHarmonicData
//   RADDEVICEID id    Handle to the connected device from RadRDAssignDevice()
//   uint16 phase      Phase to use (Phase A, B, C or NONE)
//   float *harmonicdata Harmonic data returned        
//                                    
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Read the harmonic data from the RD-2x/3x device with firmware 07.03.70 or
//    higher.  The RadRDHarmonicAnalysis must be run and ready before the 
//    data is available for this command.  
//   Reserved memory size for harmonic data should be 150 floats (600 bytes)
//      The returned array order is:
//        First float:    Harmonic 1 Magnitude
//        Second float:    Harmonic 1 Phase
//        Third float:    Total THD
//        Fourth float:    Harmonic 2 Magnitude
//        Fifth float:    Harmonic 2 Phase
//        Sixth float:    Harmonic 2 Distortion
//            o                    o
//            o                    o    
//            o                    o
//        148th float:    Harmonic 50 Magnitude
//        149th float:    Harmonic 50 Phase
//        150th float:    Harmonic 50 Distortion
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDHarmonicData( RADDEVICEID id,
                                               uint16 phase,
                                               LPSAFEARRAY FAR *harmonicdata );


//-----------------------------------------------------------------------------
// RadRDMeterTest
//   RADDEVICEID id      Handle to the connected device from RadRDAssignDevice()
//   uint16 phase        Phase to use (Phase A, B, C or NONE)
//   PMETER_TEST_STRUCT meter_test    Structure of Meter Test data
//
//   METER_TEST_STRUCT {
//    byte function;         //Use RAD_ACCUM_XXXX defines
//    byte control;          //Control and Status. 
//                              Use RAD_METERTEST_XXX definitions
//    float duration;        //Time in seconds if Timed or Demand Test
//    float factor;          //kH factor for pulse and times tests, or
//                              demand register for demand testing
//    byte elements;         //Number of meter elements. 
//                              Use RAD_METERTEST_XXX definitions
//    byte c_elements;       //Number of Current elements. 
//                              1,2 and 3 are supported.
//    uint16 revs;           //Revolutions for the Meter during the test.
//                              Only Sensor and Manual Tests.
//    uint16 pulses_rev;     //Pulses per revolution for the Meter.
//                              Only Sensor and Manual Tests.
//    float percent_error;   //Percent error when test is complete.
//    float registration;    //Percent Registration when test is complete.
//    unsigned long pulses;  //Number of pulses counted by the RD
//    float metric           //Accumulated Metric value
//    } 
//                                    
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Starts or reads status of meter test in RD-2x/3x devices with
//      firmware 07.03.20 or higher.  When requesting status, you must
//      enter all of the same parameters that were used to start the test.
//
//meter_test structure:
//    INPUTS:
//    function      - Accumulated metric to use for test.  
//                     Defined by RAD_ACCUM_XXXX
//    control       - Defined by RAD_METERTEST_XXX. 
//                     OR respective test definitions for test desired.
//    duration      - Used in timed and demand testing.  
//                     Length of test in seconds.
//    factor        - kH or Demand Meter Register
//    elements      - Number of meter elements
//    c_elements    - Number of current elements in meter (1,2 or 3)
//    revs          - Revolutions of meter during the test
//                     (Sensor and Manual tests only)
//    pulses_rev    - Pulse per revolution for the meter.
//                     (Sensor and Manual tests only)
//    OUTPUTS:
//    function      - Accumulated metric used for test. 
//                     Defined by RAD_ACCUM_XXXX
//    control       - Status of test.  Defined by RAD_METERTEST_XXX.
//    duration      - Number of pulses/seconds remaining in the test
//    percent_error - Percent error when test is complete
//    registration  - Percent Registration when test is complete
//    pulses        - Number of pulses counted by the RD
//    metric        - Accumulated metric value the test is running
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDMeterTest( RADDEVICEID id,
                                               uint16 phase,
                                               PMETER_TEST_STRUCT meter_test );


//-----------------------------------------------------------------------------
// RadRDStandardTest
//   RADDEVICEID id    Handle to the connected device from RadRDAssignDevice()
//   uint16 phase      Phase to use (Phase A, B, C or NONE)
//     PSTD_TEST_STRUCT std_test    Structure of Standard Test data
//
//  STD_TEST_STRUCT {
//    byte function;        //Use RAD_ACCUM_XXXX defines for function
//    byte control;         //Control and Status. 
//                             Use RAD_STDTEST_XXX definitions
//    float duration;       //duration of test in seconds/pulses
//    float constant;       //Pulse constant
//    float percent_error;  //Percent error when test is complete.
//    float registration;   //Percent Registration when test is complete.
//    unsigned long pulses; //Number of pulses counted by the RD
//    float metric          //Accumulated Metric value
//    } 
//                                    
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Starts or reads status of standard test in RD-2x/3x devices with
//      firmware 07.01.10 or higher.  When requesting status, you must
//      enter all of the same parameters that was used to start the test.
//
//Standard Test structure:
//    INPUTS:
//      function      - Accumulated metric to use for test.  
//                       Defined by RAD_ACCUM_XXXX
//      control       - Defined by RAD_STDTEST_XXX. 
//                       OR respective test definitions for test desired.
//      duration      - Length of test in seconds/pulses.
//      constant      - Pulse constant to use for test
//    OUTPUTS:
//      function      - Accumulated metric used for test.  
//                       Defined by RAD_ACCUM_XXXX
//      control       - Status of test.  Defined by RAD_STDTEST_XXX.
//      duration      - Number of seconds/pulses remaining in the test
//      percent_error - Percent error when test is complete
//      registration  - Percent Registration when test is complete
//      pulses        - Number of pulses counted by the RD
//      metric        - Accumulated metric value the test is running
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDStandardTest( RADDEVICEID id,
                                                   uint16 phase,
                                                   PSTD_TEST_STRUCT std_test );


//-----------------------------------------------------------------------------
// RadRDAnalogSenseTest
//   RADDEVICEID id   Handle to the connected device from RadRDAssignDevice()
//   byte function    Instantaneous metric use RAD_INST_XXX definitions
//     float factor   Analog sense factor (factor/1mA) 
//     float *metric  Selected Metric value
//     float *ans     Analog sense measurement (Data in mA)
//     float *diff    Difference between Analog Sense measurement and 
//                     requested instantaneous metric. (Data in mA)
//     float *percent_error    Percent error between analog sense metric and 
//                              instantaneous metric.
//                                    
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Using the analog sense factor and metric to compare, the function
//   returns equivalent metric for the analog input, difference and percent
//   error compared to the metric it is being compared to.  
//   The factor value should be a magnitude of the metric selected compared 
//   to 1mA.  
//    Example:  100V/1mA for function Volts(0) Factor=100
//    Example:  30W/1mA for function Watts(2) Factor=30
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDAnalogSenseTest( RADDEVICEID id,
                                           byte function, float factor,
                                           float *metric, float *ans,
                                           float *diff, float *percent_error );


//-----------------------------------------------------------------------------
// RadRS712SetOutput
//   RADDEVICEID id  Handle to the connected device from RadRDAssignDevice()
//   float value     Value of DC current to source.
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Sets the RS-712 current output current and sets the unit for source mode.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRS712SetOutput( RADDEVICEID id,
                                                                 float value );


//-----------------------------------------------------------------------------
// RadRDWaveformCapture
//   RADDEVICEID id  Handle to the connected device from RadRDAssignDevice()
//   uint16 phase    Phase to use (Phase A, B, C or NONE)
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
// Starts a waveform capture in the device and phase, on the next zero crossing
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDWaveformCapture( RADDEVICEID id,
                                                                uint16 phase );


//-----------------------------------------------------------------------------
// RadRDWaveformData
//   RADDEVICEID id      Handle to the connected device from RadRDAssignDevice()
//   uint16 phase        Phase to use (Phase A, B, C or NONE)
//   float *waveformdata Waveform data returned        
//                                    
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Read the Waveform data from the RD-2x/3x device.
//    The RadRDWaveformCapture must be run before the  data is available.
//    Sample Frequency is 20119.29882 
//    Time between samples is 49.70352 micro Seconds

//   Reserved memory size for waveformdata should be 1600 floats
//     The returned array order is:
//        First float:   Voltage Sample (t)
//        Second float   Voltage Sample (t + 1)
//        Third float    Voltage Sample (t + 2)
//            o                 o          o
//            o                 o          o
//            o                 o          o
//        800th float    Voltage Sample (t + 799)
//        801th float    Current Sample (t)
//        802th float    Current Sample (t + 1)
//        803rd float    Current Sample (t + 2)
//            o                 o          o
//            o                 o          o
//            o                 o          o
//        1600th float    Current Sample (t + 799)
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDWaveformData( RADDEVICEID id,
                                               uint16 phase,
                                               LPSAFEARRAY FAR *waveformdata );


//-----------------------------------------------------------------------------
// RadRDSendPacket
//   RADDEVICEID id    Handle to the connected device from RadRDAssignDevice()
//   uint16 packetLen  Length of data to send
//   byte *snddata     Data to send in byte array
//   byte *rcvdata     Data received from device in byte array
//   long *ReadLength  Length received
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//  Raw Radian communication with commport.  The packet will automatically
//   calculate the required checksum and properly evaluate the return data
//   for checksum and communications errors.
//   This packet should only be needed for new communications that are not 
//   currently supported by this DLL.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDSendPacket(RADDEVICEID id, 
                                              uint16 packetLen, byte *snddata, 
                                              byte *rcvdata, long *ReadLength);


//-----------------------------------------------------------------------------
// RadRDByteToFloat
//   RADDEVICEID id    Handle to the connected device from RadRDAssignDevice()
//   byte *data        4 byte array of TI-Float
//   float *value      Value returned in IEEE float
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Convert 4 bytes from TI-Float to IEEE float.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDByteToFloat(byte *data, 
                                                                 float *value);


//-----------------------------------------------------------------------------
// RadRDFloatToByte
//   RADDEVICEID id    Handle to the connected device from RadRDAssignDevice()
//   float value       Value in IEEE float
//   byte *data        4 byte array data returned in TI-Float
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Convert 4 bytes from IEEE to TI-float.
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDFloatToByte(float value, byte *data);


//-----------------------------------------------------------------------------
// RadRDUserVoltageCalOffset
//   RADDEVICEID id   Handle to the connected device from RadRDAssignDevice()
//   uint16 phase     Phase to use (Phase A, B, C or NONE)
//   uint16 update    If set to 0 then user offset is read into value,
//                     if set to 1 then value is written to device.
//   float value      Value in IEEE float
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Read or Update the user voltage offset calibration in percent.
//    This is the AC gain percent adder (calibrated at 120V).
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDUserVoltageCalOffset(RADDEVICEID id,
                                    uint16 phase, uint16 update, float *value);


//-----------------------------------------------------------------------------
// RadRDUserCurrentCalOffset
//   RADDEVICEID id   Handle to the connected device from RadRDAssignDevice()
//   uint16 phase     Phase to use (Phase A, B, C or NONE)
//   uint16 update    If set to 0 then user offset is read into value,
//                     if set to 1 then value is written to device.
//   float value      Value in IEEE float
//
// Returns ERRORCODE    A return value of 0 (zero) indicates the function was 
//                      successful.
//                      Use RadRDMessage to determine meaning of the errorcode. 
//
//   Read or Update the user current offset calibration in percent.
//    This is the AC gain percent adder (calibrated at 5A).
//-----------------------------------------------------------------------------
RADRDKIT_API1 ERRORCODE RADRDKIT_API2 RadRDUserCurrentCalOffset(RADDEVICEID id,
                                    uint16 phase, uint16 update, float *value);
#endif
