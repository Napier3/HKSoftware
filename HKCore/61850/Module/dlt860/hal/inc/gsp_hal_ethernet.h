/*
 *  ethernet_hal.h
 *  以太网层的封装
 */

#ifndef GSP_ETHERNET_HAL_H_
#define GSP_ETHERNET_HAL_H_

#include "gsp_hal_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief 以太网的数据操作接口.
 */
typedef struct sGspEthernetSocket* GspEthernetSocket;

/** 以太网数据集的操作接口 */
typedef struct sGspEthernetHandleSet* GspEthernetHandleSet;

/**
 * \brief 创建数据处理对象
 *
 * \return new EthernetHandleSet instance
 */
PAL_API GspEthernetHandleSet EthernetHandleSet_new(void);

/**
 * \brief 增加数据到待处理的数据集合
 * \param self 处理数据集合
 * \param sock socket数据
 */
PAL_API void GspEthernetHandleSet_addSocket(GspEthernetHandleSet self, const GspEthernetSocket sock);

/**
 * \brief 从待处理的数据集合中移除数据
 * \param self 数据集处理集合
 * \param sock 需要移除的数据集合
 */
PAL_API void GspEthernetHandleSet_removeSocket(GspEthernetHandleSet self, const GspEthernetSocket sock);

/**
 * \brief 等待socket数据(poll 原型)
 *
 * 这是一个poll模型的封装,用来获取指定socket的数据,当等待指定毫秒后没有数据到来,则返回 -1
 *
 * \param self 待处理的数据套接字
 * \param timeout 等待超市时间
 * \return 有数据时返回具体的数据尺寸,没有数据时返回0,有错误时返回-1
 */
PAL_API int GspEthernetHandleSet_waitReady(GspEthernetHandleSet self, unsigned int timeoutMs);

/**
 * \brief 销毁数据实例
 *
 * \param self 需要销毁的数据实例
 */
PAL_API void GspEthernetHandleSet_destroy(GspEthernetHandleSet self);

/**
 * \brief 获取以太网口的 MAC地址
 *
 * 返回指定网口的6字节的MAC地址
 *
 * \param interfaceId 以太网口的ID
 * \param addr 传出的地址信息
 */
PAL_API void GspEthernet_getInterfaceMACAddress(const char* interfaceId, uint8_t* addr);

/**
 * \brief 使用指定的网口ID 和 目标MAC地址创建一个以太网层的链接
 *
 * \param interfaceId 以太网接口ID
 * \param destAddress 目标设备的MAC地址
 */
PAL_API GspEthernetSocket GspEthernet_createSocket(const char* interfaceId, uint8_t* destAddress);

/**
 * \brief 销毁以太网接口处理链接
 *
 * \param 以太网链接
 */
PAL_API void GspEthernet_destroySocket(GspEthernetSocket ethSocket);


/**
 * @brief Ethernet_sendPacket 在以太网链接上发送数据
 * @param ethSocket 以太网链接
 * @param buffer 待发送的数据缓存
 * @param packetSize 数据大小
 */
PAL_API void GspEthernet_sendPacket(GspEthernetSocket ethSocket, uint8_t* buffer, int packetSize);

/*
 * \brief 为指定的以太网类型设置协议筛选器
 *
 * \param ethSocket 以太网链接
 * \param etherType 要接受的消息类型
 */
PAL_API void GspEthernet_setProtocolFilter(GspEthernetSocket ethSocket, uint16_t etherType);

/**
 * \brief 从以太网链接上接受数据 (非阻塞)
 *
 * \param ethSocket 以太网链接
 * \param buffer 接受到的消息数据
 * \param 接受到的数据大小
 *
 * \return 接受到的数据大小
 */
PAL_API int GspEthernet_receivePacket(GspEthernetSocket ethSocket, uint8_t* buffer, int bufferSize);

/**
 * \brief 是否支持以太网层的数据链接
 *
 * \return 默认支持
 */
PAL_API bool GspEthernet_isSupported(void);


#ifdef __cplusplus
}
#endif

#endif /* GSP_ETHERNET_HAL_H_ */
