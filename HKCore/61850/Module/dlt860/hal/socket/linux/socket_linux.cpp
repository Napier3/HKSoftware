/*
 *  socket_linux.c
 *  socket 封装
 */

#include "gsp_hal_socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <netinet/tcp.h> /* required for TCP keepalive */
#include <linux/version.h>
#define _GNU_SOURCE
#include <signal.h>
#include <poll.h>
#include "gsp_linked_list.h"
#include "gsp_hal_thread.h"
#include "gsp_lib_memory.h"

#ifndef DEBUG_SOCKET
#define DEBUG_SOCKET 0
#endif

#define TCP_USER_TIMEOUT   5000 //zhouhj 20230101

struct sSocket {
    int fd;
    uint32_t connectTimeout;
};

struct sGspServerSocket {
    int fd;
    int backLog;
};

struct sHandleSet {
    GSP::GspLinkedList sockets;
    bool pollfdIsUpdated;
    struct pollfd* fds;
    int nfds;
};

GspHandleSet GspHandleset_new(void)
{
    GspHandleSet self = (GspHandleSet) GLOBAL_MALLOC(sizeof(struct sHandleSet));

    if (self) {
        self->sockets = GSP::GspLinkedList_create();
        self->pollfdIsUpdated = false;
        self->fds = nullptr;
        self->nfds = 0;
    }

    return self;
}

void GspHandleset_reset(GspHandleSet self)
{
    if (self) {
        if (self->sockets) {
            GSP::GspLinkedList_destroyStatic(self->sockets);
            self->sockets = GSP::GspLinkedList_create();
            self->pollfdIsUpdated = false;
        }
    }
}

void GspHandleset_addSocket(GspHandleSet self, const GspSocket sock)
{
    if (self != nullptr && sock != nullptr && sock->fd != -1) {

        GSP::GspLinkedList_add(self->sockets, sock);
        self->pollfdIsUpdated = false;
    }
}

void GspHandleset_removeSocket(GspHandleSet self, const GspSocket sock)
{
    if (self && self->sockets && sock) {
        GSP::GspLinkedList_remove(self->sockets, sock);
        self->pollfdIsUpdated = false;
    }
}

int GspHandleset_waitReady(GspHandleSet self, unsigned int timeoutMs)
{
    /* check if pollfd array is updated */
    if (self->pollfdIsUpdated == false) {
        if (self->fds) {
            GLOBAL_FREEMEM(self->fds);
            self->fds = nullptr;
        }

        self->nfds = GSP::GspLinkedList_size(self->sockets);

        self->fds = (pollfd*)GLOBAL_CALLOC(self->nfds, sizeof(struct pollfd));

        int i;

        for (i = 0; i < self->nfds; i++) {
            GspSocket sock = (GspSocket) GSP::GspLinkedList_get(self->sockets, i);
            if (sock) {
                self->fds[i].fd = sock->fd;
                self->fds[i].events = POLL_IN;
            }
        }

        self->pollfdIsUpdated = true;
    }

    if (self->fds && self->nfds > 0) {
        int result = poll(self->fds, self->nfds, timeoutMs);

        if (result == -1) {
            if (DEBUG_SOCKET)
                printf("SOCKET: poll error (errno: %i)\n", errno);
        }

        return result;
    }
    else {
        /* there is no socket to wait for */
        return 0;
    }
}

void GspHandleset_destroy(GspHandleSet self)
{
    if (self) {
        if (self->sockets)
            GSP::GspLinkedList_destroyStatic(self->sockets);

        if (self->fds)
            GLOBAL_FREEMEM(self->fds);

        GLOBAL_FREEMEM(self);
    }
}

void GspSocket_activateTcpKeepAlive(GspSocket self, int idleTime, int interval, int count)
{
#if defined SO_KEEPALIVE
    int optval;
    socklen_t optlen = sizeof(optval);

    optval = 1;

    if (setsockopt(self->fd, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen)) {
        if (DEBUG_SOCKET)
            printf("Failed to enable TCP keepalive\n");
    }

#if defined TCP_KEEPCNT
    optval = idleTime;
    if (setsockopt(self->fd, IPPROTO_TCP, TCP_KEEPIDLE, &optval, optlen)) {
        if (DEBUG_SOCKET)
            printf("Failed to set TCP keepalive TCP_KEEPIDLE parameter\n");
    }

    optval = interval;
    if (setsockopt(self->fd, IPPROTO_TCP, TCP_KEEPINTVL, &optval, optlen)) {
        if (DEBUG_SOCKET)
            printf("Failed to set TCP keepalive TCP_KEEPINTVL parameter\n");
    }

    optval = count;
    if (setsockopt(self->fd, IPPROTO_TCP, TCP_KEEPCNT, &optval, optlen)) {
        if (DEBUG_SOCKET)
            printf("Failed to set TCP keepalive TCP_KEEPCNT parameter\n");
    }
#endif /* TCP_KEEPCNT */

#endif /* SO_KEEPALIVE */
}

static bool prepareServerAddress(const char* address, int port, struct sockaddr_in* sockaddr)
{
    bool retVal = true;

    memset((char *) sockaddr, 0, sizeof(struct sockaddr_in));

    if (address != nullptr) {
        struct addrinfo addressHints;
        struct addrinfo *lookupResult;
        int result;

        memset(&addressHints, 0, sizeof(struct addrinfo));
        addressHints.ai_family = AF_INET;
        result = getaddrinfo(address, nullptr, &addressHints, &lookupResult);

        if (result != 0) {
            retVal = false;
            goto exit_function;
        }

        memcpy(sockaddr, lookupResult->ai_addr, sizeof(struct sockaddr_in));
        freeaddrinfo(lookupResult);
    }
    else
        sockaddr->sin_addr.s_addr = htonl(INADDR_ANY);

    sockaddr->sin_family = AF_INET;
    sockaddr->sin_port = htons(port);

exit_function:
    return retVal;
}

static void setSocketNonBlocking(GspSocket self)
{
    int flags = fcntl(self->fd, F_GETFL, 0);
    fcntl(self->fd, F_SETFL, flags | O_NONBLOCK);
}

static void activateTcpNoDelay(GspSocket self)
{
    /* activate TCP_NODELAY option - packets will be sent immediately */
    int flag = 1;
    setsockopt(self->fd, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int));
}

GspServerSocket GspTcpServerSocket_create(const char* address, int port)
{
    GspServerSocket serverSocket = nullptr;

    int fd;

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) >= 0) {
        struct sockaddr_in serverAddress;

        if (!prepareServerAddress(address, port, &serverAddress)) {
            close(fd);
            return nullptr;
        }

        int optionReuseAddr = 1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *) &optionReuseAddr, sizeof(int));

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 37)
        int tcpUserTimeout = 10000;
        int result = setsockopt(fd, SOL_TCP,  TCP_USER_TIMEOUT, &tcpUserTimeout, sizeof(tcpUserTimeout));

        if (result < 0) {
            if (DEBUG_SOCKET)
                printf("SOCKET: failed to set TCP_USER_TIMEOUT\n");
        }
#else
#warning "TCP_USER_TIMEOUT not supported by linux kernel"
#endif

        if (bind(fd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) >= 0) {
            serverSocket = (GspServerSocket) GLOBAL_MALLOC(sizeof(struct sGspServerSocket));
            serverSocket->fd = fd;
            serverSocket->backLog = 2;

            setSocketNonBlocking((GspSocket) serverSocket);
        }
        else {
            close(fd);
            return nullptr ;
        }
    }

    return serverSocket;
}

void GspServerSocket_listen(GspServerSocket self)
{
    listen(self->fd, self->backLog);
}

/* CHANGED TO MAKE NON-BLOCKING --> RETURNS NULL IF NO CONNECTION IS PENDING */
GspSocket GspServerSocket_accept(GspServerSocket self)
{
    int fd;

    GspSocket conSocket = nullptr;

    fd = accept(self->fd, nullptr, nullptr );

    if (fd >= 0) {
        conSocket = (GspSocket) GLOBAL_CALLOC(1, sizeof(struct sSocket));
        conSocket->fd = fd;

        activateTcpNoDelay(conSocket);
    }

    return conSocket;
}

void GspServerSocket_setBacklog(GspServerSocket self, int backlog)
{
    self->backLog = backlog;
}

static void closeAndShutdownSocket(int socketFd)
{
    if (socketFd != -1) {

        if (DEBUG_SOCKET)
            printf("socket_linux.c: call shutdown for %i!\n", socketFd);

        /* shutdown is required to unblock read or accept in another thread! */
        shutdown(socketFd, SHUT_RDWR);

        close(socketFd);
    }
}

void GspServerSocket_destroy(GspServerSocket self)
{
    int fd = self->fd;

    self->fd = -1;

    closeAndShutdownSocket(fd);

    GspThread_sleep(10);

    GLOBAL_FREEMEM(self);
}

GspSocket GspTcpSocket_create()
{
    GspSocket self = nullptr;

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock != -1) {
        self = (GspSocket) GLOBAL_MALLOC(sizeof(struct sSocket));
        self->fd = sock;
        self->connectTimeout = 5000;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 37)
        int tcpUserTimeout = 10000;
        int result = setsockopt(sock, SOL_TCP,  TCP_USER_TIMEOUT, &tcpUserTimeout, sizeof(tcpUserTimeout));

        if (result < 0) {
            if (DEBUG_SOCKET)
                printf("SOCKET: failed to set TCP_USER_TIMEOUT\n");
        }
#endif

    }
    else {
        if (DEBUG_SOCKET)
            printf("SOCKET: failed to create socket (errno=%i)\n", errno);
    }

    return self;
}


void GspSocket_setConnectTimeout(GspSocket self, uint32_t timeoutInMs)
{
    self->connectTimeout = timeoutInMs;
}

bool GspSocket_connectAsync(GspSocket self, const char* address, int port,const char* local_address)
{
    struct sockaddr_in serverAddress;

    if (DEBUG_SOCKET)
        printf("SOCKET: connect: %s:%i\n", address, port);

    if (!prepareServerAddress(address, port, &serverAddress))
        return false;

    fd_set fdSet;
    FD_ZERO(&fdSet);
    FD_SET(self->fd, &fdSet);

    activateTcpNoDelay(self);

    fcntl(self->fd, F_SETFL, O_NONBLOCK);

    if (connect(self->fd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {

        if (errno != EINPROGRESS) {
            if (close(self->fd) == -1) {
                if (DEBUG_SOCKET)
                    printf("SOCKET: failed to close socket (errno: %i)\n", errno);
            }

            self->fd = -1;
            return false;
        }
    }

    return true; /* is connecting or already connected */
}

GspSocketState GspSocket_checkAsyncConnectState(GspSocket self)
{
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    fd_set fdSet;
    FD_ZERO(&fdSet);
    FD_SET(self->fd, &fdSet);

    int selectVal = select(self->fd + 1, nullptr, &fdSet , nullptr, &timeout);

    if (selectVal == 1) {

        /* Check if connection is established */

        int so_error;
        socklen_t len = sizeof so_error;

        if (getsockopt(self->fd, SOL_SOCKET, SO_ERROR, &so_error, &len) >= 0) {

            if (so_error == 0)
                return GSP_SOCKET_STATE_CONNECTED;
        }

        return GSP_SOCKET_STATE_FAILED;
    } else if (selectVal == 0) {
        return GSP_SOCKET_STATE_CONNECTING;
    } else {
        return GSP_SOCKET_STATE_FAILED;
    }
}

int GspSocket_getId(GspSocket self) {
    return self->fd;
}

bool GspSocket_connect(GspSocket self, const char* address, int port)
{
    if (GspSocket_connectAsync(self, address, port) == false)
        return false;

    struct timeval timeout;
    timeout.tv_sec = self->connectTimeout / 1000;
    timeout.tv_usec = (self->connectTimeout % 1000) * 1000;

    fd_set fdSet;
    FD_ZERO(&fdSet);
    FD_SET(self->fd, &fdSet);

    if (select(self->fd + 1, nullptr, &fdSet , nullptr, &timeout) == 1) {

        /* Check if connection is established */

        int so_error;
        socklen_t len = sizeof so_error;

        if (getsockopt(self->fd, SOL_SOCKET, SO_ERROR, &so_error, &len) >= 0) {

            if (so_error == 0)
                return true;
        }
    }

    close (self->fd);
    self->fd = -1;

    return false;
}


static char* convertAddressToStr(struct sockaddr_storage* addr)
{
    char addrString[INET6_ADDRSTRLEN + 7];
    int port;

    bool isIPv6;

    if (addr->ss_family == AF_INET) {
        struct sockaddr_in* ipv4Addr = (struct sockaddr_in*) addr;
        port = ntohs(ipv4Addr->sin_port);
        inet_ntop(AF_INET, &(ipv4Addr->sin_addr), addrString, INET_ADDRSTRLEN);
        isIPv6 = false;
    } else if (addr->ss_family == AF_INET6) {
        struct sockaddr_in6* ipv6Addr = (struct sockaddr_in6*) addr;
        port = ntohs(ipv6Addr->sin6_port);
        inet_ntop(AF_INET6, &(ipv6Addr->sin6_addr), addrString, INET6_ADDRSTRLEN);
        isIPv6 = true;
    } else {
        return nullptr ;
    }

    char* clientConnection = (char*) GLOBAL_MALLOC(strlen(addrString) + 9);

    if (isIPv6) {
        sprintf(clientConnection, "[%s]:%i", addrString, port);
    } else {
        sprintf(clientConnection, "%s:%i", addrString, port);
    }

    return clientConnection;
}

char* GspSocket_getPeerAddress(GspSocket self)
{
    struct sockaddr_storage addr;
    socklen_t addrLen = sizeof(addr);

    if (getpeername(self->fd, (struct sockaddr*) &addr, &addrLen) == 0) {
        return convertAddressToStr(&addr);
    } else {
        return nullptr;
    }
}

char* GspSocket_getLocalAddress(GspSocket self)
{
    struct sockaddr_storage addr;
    socklen_t addrLen = sizeof(addr);

    if (getsockname(self->fd, (struct sockaddr*) &addr, &addrLen) == 0) {
        return convertAddressToStr(&addr);
    } else {
        return nullptr;
    }
}

char* GspSocket_getPeerAddressStatic(GspSocket self, char* peerAddressString)
{
    struct sockaddr_storage addr;
    socklen_t addrLen = sizeof(addr);

    getpeername(self->fd, (struct sockaddr*) &addr, &addrLen);

    char addrString[INET6_ADDRSTRLEN + 7];
    int port;

    bool isIPv6;

    if (addr.ss_family == AF_INET) {
        struct sockaddr_in* ipv4Addr = (struct sockaddr_in*) &addr;
        port = ntohs(ipv4Addr->sin_port);
        inet_ntop(AF_INET, &(ipv4Addr->sin_addr), addrString, INET_ADDRSTRLEN);
        isIPv6 = false;
    } else if (addr.ss_family == AF_INET6) {
        struct sockaddr_in6* ipv6Addr = (struct sockaddr_in6*) &addr;
        port = ntohs(ipv6Addr->sin6_port);
        inet_ntop(AF_INET6, &(ipv6Addr->sin6_addr), addrString, INET6_ADDRSTRLEN);
        isIPv6 = true;
    } else {
        return nullptr ;
    }

    if (isIPv6) {
        sprintf(peerAddressString, "[%s]:%i", addrString, port);
    } else {
        sprintf(peerAddressString, "%s:%i", addrString, port);
    }

    return peerAddressString;
}

int GspSocket_read(GspSocket self, uint8_t* buf, int size)
{
    if (self->fd == -1)
        return -1;

    int read_bytes = recv(self->fd, buf, size, MSG_DONTWAIT);

    if (read_bytes == 0)
        return -1;

    if (read_bytes == -1) {
        int error = errno;

        switch (error) {

        case EAGAIN:
            return 0;

        default:

            if (DEBUG_SOCKET)
                printf("DEBUG_SOCKET: recv returned error (errno=%i)\n", error);

            return -1;
        }
    }

    return read_bytes;
}

int GspSocket_write(GspSocket self, uint8_t* buf, int size)
{
    if (self->fd == -1)
        return -1;

    /* MSG_NOSIGNAL - prevent send to signal SIGPIPE when peer unexpectedly closed the socket */
    int retVal = send(self->fd, buf, size, MSG_NOSIGNAL);

    if (retVal == -1) {
        if (errno == EAGAIN) {
            return 0;
        }
        else {
            if (DEBUG_SOCKET)
                printf("DEBUG_SOCKET: send returned error (errno=%i)\n", errno);
        }
    }

    return retVal;
}

void GspSocket_destroy(GspSocket self)
{
    int fd = self->fd;

    self->fd = -1;

    closeAndShutdownSocket(fd);

    GspThread_sleep(10);

    GLOBAL_FREEMEM(self);
}
