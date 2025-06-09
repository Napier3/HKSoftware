/*
 *  gsp_hal_serial.h
 *
 */

#ifndef GSP_SRC_IEC60870_LINK_LAYER_SERIAL_PORT_H_
#define GSP_SRC_IEC60870_LINK_LAYER_SERIAL_PORT_H_

#include "gsp_hal_base.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sGspSerialPort* GspSerialPort;

typedef enum {
    GSP_SERIAL_PORT_ERROR_NONE = 0,
    GSP_SERIAL_PORT_ERROR_INVALID_ARGUMENT = 1,
    GSP_SERIAL_PORT_ERROR_INVALID_BAUDRATE = 2,
    GSP_SERIAL_PORT_ERROR_OPEN_FAILED = 3,
    GSP_SERIAL_PORT_ERROR_UNKNOWN = 99
} GspSerialPortError;

PAL_API GspSerialPort GspSerialPort_create(const char* interfaceName, int baudRate, uint8_t dataBits, char parity, uint8_t stopBits);

PAL_API void GspSerialPort_destroy(GspSerialPort self);

PAL_API bool GspSerialPort_open(GspSerialPort self);

PAL_API void GspSerialPort_close(GspSerialPort self);

PAL_API int GspSerialPort_getBaudRate(GspSerialPort self);

PAL_API void GspSerialPort_setTimeout(GspSerialPort self, int timeout);

PAL_API void GspSerialPort_discardInBuffer(GspSerialPort self);

PAL_API int GspSerialPort_readByte(GspSerialPort self);

PAL_API int GspSerialPort_write(GspSerialPort self, uint8_t* buffer, int startPos, int numberOfBytes);

PAL_API GspSerialPortError GspSerialPort_getLastError(GspSerialPort self);


#ifdef __cplusplus
}
#endif


#endif /* GSP_SRC_IEC60870_LINK_LAYER_SERIAL_PORT_H_ */
