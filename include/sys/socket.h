/* sys/socket.h
*/

#ifndef _SYS_SOCKET_H
#define _SYS_SOCKET_H

#ifdef __cplusplus
extern "C"
{
#endif				/* __cplusplus */

#include <sys/types.h>
#include <stdint.h>
#include <sys/uio.h>

#ifndef socklen_t
#ifdef __socklen_t
  typedef __socklen_t socklen_t;
#else
  typedef int socklen_t;	/* socklen_t all compiler support */
#endif
#define socklen_t socklen_t
#endif

#ifdef __sa_family_t
  typedef __sa_family_t sa_family_t;
#else
  typedef short sa_family_t;	/* sa_family_t all compiler support */
#endif

  struct sockaddr
  {
    sa_family_t sa_family;	/* address family, AF_xxx */
    char sa_data[14];		/* 14 bytes of protocol address */
  };

/* Definition of sockaddr_storage according to SUSv3. */
#define _SS_MAXSIZE 128		/* Maximum size. */
#define _SS_ALIGNSIZE (sizeof (int64_t))	/* Desired alignment. */
#define _SS_PAD1SIZE (_SS_ALIGNSIZE - sizeof (sa_family_t))
#define _SS_PAD2SIZE (_SS_MAXSIZE - (sizeof (sa_family_t) \
 + _SS_PAD1SIZE + _SS_ALIGNSIZE))

  struct sockaddr_storage
  {
    sa_family_t ss_family;
    char _ss_pad1[_SS_PAD1SIZE];
    int64_t __ss_align;
    char _ss_pad2[_SS_PAD2SIZE];
  };

/* Standard interface flags. */
#define IFF_UP 0x1		/* interface is up */
#define IFF_BROADCAST 0x2	/* broadcast address valid */
#define IFF_LOOPBACK 0x8	/* is a loopback net */
#define IFF_POINTOPOINT 0x10	/* is a point-to-point interface */
#define IFF_NOTRAILERS 0x20	/* avoid use of trailers */
#define IFF_RUNNING 0x40	/* resources allocated */
#define IFF_NOARP 0x80		/* no ARP protocol */
#define IFF_PROMISC 0x100	/* receive all packets */
#define IFF_MULTICAST 0x1000	/* Supports multicast */
#define IFF_LOWER_UP 0x10000	/* driver signals L1 up */
#define IFF_DORMANT 0x20000	/* driver signals dormant */

  struct if_nameindex
  {
    unsigned if_index;
    char *if_name;
  };

#define IFRF_FRIENDLYNAMESIZ 260

  struct ifreq_frndlyname
  {
    int ifrf_len;
    char ifrf_friendlyname[IFRF_FRIENDLYNAMESIZ];
  };

#define IFNAMSIZ 44
#define IF_NAMESIZE IFNAMSIZ
#define IFHWADDRLEN 6

  struct ifreq
  {
    union
    {
      char ifrn_name[IFNAMSIZ];
    } ifr_ifrn;

    union
    {
      struct sockaddr ifru_addr;
      struct sockaddr ifru_broadaddr;
      struct sockaddr ifru_dstaddr;
      struct sockaddr ifru_netmask;
      struct sockaddr ifru_hwaddr;
      int ifru_flags;
      int ifru_metric;
      int ifru_mtu;
      int ifru_ifindex;
      /* The space must be preallocated by the application. */
      void *ifru_data;
      /* Pad to sizeof sockaddr_in6 for further extensions. */
      char __ifru_pad[28];
    } ifr_ifru;
  };

#define ifr_name ifr_ifrn.ifrn_name	/* interface name */
#define ifr_addr ifr_ifru.ifru_addr	/* address */
#define ifr_broadaddr ifr_ifru.ifru_broadaddr	/* broadcast address */
#define ifr_dstaddr ifr_ifru.ifru_dstaddr	/* destination address */
#define ifr_netmask ifr_ifru.ifru_netmask	/* interface net mask */
#define ifr_flags ifr_ifru.ifru_flags	/* flags */
#define ifr_hwaddr ifr_ifru.ifru_hwaddr	/* MAC address */
#define ifr_metric ifr_ifru.ifru_metric	/* metric */
#define ifr_mtu ifr_ifru.ifru_mtu	/* mtu */
#define ifr_ifindex ifr_ifru.ifru_ifindex	/* interface index */
#define ifr_data ifr_ifru.ifru_data	/* for use by interface */
#define ifr_frndlyname ifr_ifru.ifru_data	/* Windows friendly if name */

  struct ifconf
  {
    int ifc_len;		/* size of buffer */
    union
    {
      char *ifcu_buf;
      struct ifreq *ifcu_req;
    } ifc_ifcu;
  };

#define ifc_buf ifc_ifcu.ifcu_buf	/* buffer address */
#define ifc_req ifc_ifcu.ifcu_req	/* array of structures */

  extern unsigned if_nametoindex (const char *);
  extern char *if_indextoname (unsigned, char *);
  extern struct if_nameindex *if_nameindex (void);
  extern void if_freenameindex (struct if_nameindex *);

#define IOCPARM_MASK 0x7f	/* parameters must be < 128 bytes */
#define IOC_VOID 0x20000000	/* no parameters */
#define IOC_OUT 0x40000000	/* copy out parameters */
#define IOC_IN 0x80000000	/* copy in parameters */

#define _IO(x,y) (IOC_VOID|(x<<8)|y)
#define _IOR(x,y,t) (IOC_OUT|(((long)sizeof(t)&IOCPARM_MASK)<<16)|(x<<8)|y)
#define _IOW(x,y,t) (IOC_IN|(((long)sizeof(t)&IOCPARM_MASK)<<16)|(x<<8)|y)

#define SIOCATMARK _IOR('s', 7, long)	/* at oob mark? */
#define FIONREAD _IOR('f', 127, long)	/* get # bytes to read */
#define SIOCINQ FIONREAD
/* Compatible with termios.h */
#define FIONBIO 0x8004667e	/* set/clear non-blocking i/o */
#define FIOASYNC _IOW('f', 125, long)	/* set/clear async i/o */
#define SIOCSHIWAT _IOW('s', 0, long)	/* set high watermark */
#define SIOCGHIWAT _IOR('s', 1, long)	/* get high watermark */
#define SIOCSLOWAT _IOW('s', 2, long)	/* set low watermark */
#define SIOCGLOWAT _IOR('s', 3, long)	/* get low watermark */

/* Needed for if queries */
#define SIOCGIFCONF _IOW('s', 100, struct ifconf)	/* get if list */
#define SIOCGIFFLAGS _IOW('s', 101, struct ifreq)	/* Get if flags */
#define SIOCGIFADDR _IOW('s', 102, struct ifreq)	/* Get if addr */
#define SIOCGIFBRDADDR _IOW('s', 103, struct ifreq)	/* Get if broadcastaddr */
#define SIOCGIFNETMASK _IOW('s', 104, struct ifreq)	/* Get if netmask */
#define SIOCGIFHWADDR _IOW('s', 105, struct ifreq)	/* Get hw addr */
#define SIOCGIFMETRIC _IOW('s', 106, struct ifreq)	/* get metric */
#define SIOCGIFMTU _IOW('s', 107, struct ifreq)	/* get MTU size */
#define SIOCGIFINDEX _IOW('s', 108, struct ifreq)	/* get if index */
#define SIOGIFINDEX SIOCGIFINDEX	/* backward compatibility w/ Linux typo. */
#define SIOCGIFFRNDLYNAM _IOW('s', 109, struct ifreq)	/* get friendly if name */
#define SIOCGIFDSTADDR _IOW('s', 110, struct ifreq)	/* Get if dstaddr */

#define SOL_SOCKET 0xffff	/* options for socket level */

#define SO_DEBUG 0x0001		/* turn on debugging info recording */
#define SO_ACCEPTCONN 0x0002	/* socket has had listen() */
#define SO_REUSEADDR 0x0004	/* allow local address reuse */
#define SO_KEEPALIVE 0x0008	/* keep connections alive */
#define SO_DONTROUTE 0x0010	/* just use interface addresses */
#define SO_BROADCAST 0x0020	/* permit sending of broadcast msgs */
#define SO_USELOOPBACK 0x0040	/* bypass hardware when possible */
#define SO_LINGER 0x0080	/* linger on close if data present */
#define SO_OOBINLINE 0x0100	/* leave received OOB data in line */
#define SO_DONTLINGER (unsigned int)(~SO_LINGER)
#define SO_PEERCRED 0x0200	/* same as getpeereid */
#define SO_PASSCRED 0x0400	/* enable receiving of credentials */

/*
 * Additional options.
 */
#define SO_SNDBUF 0x1001	/* send buffer size */
#define SO_RCVBUF 0x1002	/* receive buffer size */
#define SO_SNDLOWAT 0x1003	/* send low-water mark */
#define SO_RCVLOWAT 0x1004	/* receive low-water mark */
#define SO_SNDTIMEO 0x1005	/* send timeout */
#define SO_RCVTIMEO 0x1006	/* receive timeout */
#define SO_ERROR 0x1007		/* get error status and clear */
#define SO_TYPE 0x1008		/* get socket type */

#ifndef uid_t
  typedef int uid_t;
#endif

#ifndef gid_t
  typedef int gid_t;
#endif

  struct ucred
  {
    pid_t pid;
    uid_t uid;
    gid_t gid;
  };

  struct linger
  {
    unsigned short l_onoff;	/* Linger active */
    unsigned short l_linger;	/* How long to linger for */
  };

  struct msghdr
  {
    void *msg_name;		/* Socket name */
    socklen_t msg_namelen;	/* Length of name */
    struct iovec *msg_iov;	/* Data blocks */
    int msg_iovlen;		/* Number of blocks */
    void *msg_control;		/* Ancillary data */
    socklen_t msg_controllen;	/* Ancillary data buffer length */
    int msg_flags;		/* Received flags on recvmsg */
  };

  struct cmsghdr
  {
    size_t cmsg_len;		/* Length of cmsghdr + data */
    int cmsg_level;		/* Protocol */
    int cmsg_type;		/* Protocol type */
  };

#define CMSG_ALIGN(len) \
 (((len) + __alignof__ (struct cmsghdr) - 1) \
 & ~(__alignof__ (struct cmsghdr) - 1))
#define CMSG_LEN(len) \
 (CMSG_ALIGN (sizeof (struct cmsghdr)) + (len))
#define CMSG_SPACE(len) \
 (CMSG_ALIGN (sizeof (struct cmsghdr)) + CMSG_ALIGN(len))
#define CMSG_FIRSTHDR(mhdr) \
 ({ \
 struct msghdr *_m = (struct msghdr *) mhdr; \
 (unsigned) (_m)->msg_controllen >= sizeof (struct cmsghdr) \
 ? (struct cmsghdr *) (_m)->msg_control \
 : (struct cmsghdr *) NULL; \
 })
#define CMSG_NXTHDR(mhdr,cmsg) \
 ({ \
 struct msghdr *_m = (struct msghdr *) mhdr; \
 struct cmsghdr *_c = (struct cmsghdr *) cmsg; \
 ((char *) _c + CMSG_SPACE (_c->cmsg_len) \
 > (char *) _m->msg_control + _m->msg_controllen) \
 ? (struct cmsghdr *) NULL \
 : (struct cmsghdr *) ((char *) _c + CMSG_ALIGN (_c->cmsg_len)); \
 })
#define CMSG_DATA(cmsg) \
 ((unsigned char *) ((struct cmsghdr *)(cmsg) + 1))

/* "Socket"-level control message types: */
#define SCM_RIGHTS 0x01		/* descriptor passing (array of int) */
#define SCM_CREDENTIALS 0x02	/* credential passing (struct ucred) */

/* Definition of struct msghdr up to release 1.5.18 */
  struct OLD_msghdr
  {
    void *msg_name;		/* Socket name */
    int msg_namelen;		/* Length of name */
    struct iovec *msg_iov;	/* Data blocks */
    int msg_iovlen;		/* Number of blocks */
    void *msg_accrights;	/* Per protocol magic */
    /* (eg BSD descriptor passing) */
    int msg_accrightslen;	/* Length of rights list */
  };

/* Socket types. */
#define SOCK_STREAM 1		/* stream (connection) socket */
#define SOCK_DGRAM 2		/* datagram (conn.less) socket */
#define SOCK_RAW 3		/* raw socket */
#define SOCK_RDM 4		/* reliably-delivered message */
#define SOCK_SEQPACKET 5	/* sequential packet socket */

#define SOCK_NONBLOCK 0x01000000
#define SOCK_CLOEXEC 0x02000000
#define _SOCK_FLAG_MASK 0xff000000	/* Bits left for more extensions */

/* Supported address families. */
#define AF_UNSPEC 0		/* unspecified */
#define AF_UNIX 31
#define AF_LOCAL 1		/* POSIX name for AF_UNIX */
#define AF_INET 2		/* internetwork: UDP, TCP, etc. */
#define AF_IMPLINK 3		/* arpanet imp addresses */
#define AF_PUP 4		/* pup protocols: e.g. BSP */
#define AF_CHAOS 5		/* mit CHAOS protocols */
#define AF_NS 6			/* XEROX NS protocols */
#define AF_ISO 7		/* ISO protocols */
#define AF_OSI AF_ISO		/* OSI is ISO */
#define AF_ECMA 8		/* european computer manufacturers */
#define AF_DATAKIT 9		/* datakit protocols */
#define AF_CCITT 10		/* CCITT protocols, X.25 etc */
#define AF_SNA 11		/* IBM SNA */
#define AF_DECnet 12		/* DECnet */
#define AF_DLI 13		/* Direct data link interface */
#define AF_LAT 14		/* LAT */
#define AF_HYLINK 15		/* NSC Hyperchannel */
#define AF_APPLETALK 16		/* AppleTalk */
#define AF_NETBIOS 17		/* NetBios-style addresses */
#define AF_INET6 23		/* IP version 6 */

#define AF_MAX 32
/* Protocol families, same as address families for now. */
#define PF_UNSPEC AF_UNSPEC
#define PF_UNIX AF_UNIX
#define PF_LOCAL AF_LOCAL
#define PF_INET AF_INET
#define PF_IMPLINK AF_IMPLINK
#define PF_PUP AF_PUP
#define PF_CHAOS AF_CHAOS
#define PF_NS AF_NS
#define PF_ISO AF_ISO
#define PF_OSI AF_OSI
#define PF_ECMA AF_ECMA
#define PF_DATAKIT AF_DATAKIT
#define PF_CCITT AF_CCITT
#define PF_SNA AF_SNA
#define PF_DECnet AF_DECnet
#define PF_DLI AF_DLI
#define PF_LAT AF_LAT
#define PF_HYLINK AF_HYLINK
#define PF_APPLETALK AF_APPLETALK
#define PF_NETBIOS AF_NETBIOS
#define PF_INET6 AF_INET6

#define PF_MAX AF_MAX

#define SOMAXCONN 0x7fffffff

/* Flags we can use with send/ and recv. */
#define MSG_OOB 0x1		/* process out-of-band data */
#define MSG_PEEK 0x2		/* peek at incoming message */
#define MSG_DONTROUTE 0x4	/* send without using routing tables */
#define MSG_WAITALL 0x8		/* wait for all requested bytes */
#define MSG_DONTWAIT 0x10	/* selective non-blocking operation */
#define MSG_NOSIGNAL 0x20	/* Don't raise SIGPIPE */
#define MSG_TRUNC 0x0100	/* Normal data truncated */
#define MSG_CTRUNC 0x0200	/* Control data truncated */

#define MSG_BCAST 0x0400	/* Broadcast datagram */
#define MSG_MCAST 0x0800	/* Multicast datagram */

#define MSG_CMSG_CLOEXEC 0x1000	/* Set O_CLOEXEC on fd's passed via
				   SCM_RIGHTS */

#define MSG_EOR 0x8000		/* Terminates a record */

/* Set Sock options */
#define SOL_IP 0
#define SOL_IPV6 41
#define SOL_IPX 256
#define SOL_AX25 257
#define SOL_ATALK 258
#define SOL_NETROM 259
#define SOL_TCP 6
#define SOL_UDP 17

/* IP options */
#ifndef IPTOS_LOWDELAY
#define IPTOS_LOWDELAY 0x10
#define IPTOS_THROUGHPUT 0x08
#define IPTOS_RELIABILITY 0x04
#endif

#define IP_DEFAULT_MULTICAST_TTL 1
#define IP_DEFAULT_MULTICAST_LOOP 1
#define IP_MAX_MEMBERSHIPS 20

/* IP options for use with getsockopt/setsockopt */
#define IP_OPTIONS 1
#define IP_HDRINCL 2
#define IP_TOS 3
#define IP_TTL 4
#define IP_MULTICAST_IF 9
#define IP_MULTICAST_TTL 10
#define IP_MULTICAST_LOOP 11
#define IP_ADD_MEMBERSHIP 12
#define IP_DROP_MEMBERSHIP 13
#define IP_DONTFRAGMENT 14
#define IP_ADD_SOURCE_MEMBERSHIP 15
#define IP_DROP_SOURCE_MEMBERSHIP 16
#define IP_BLOCK_SOURCE 17
#define IP_UNBLOCK_SOURCE 18
#define IP_PKTINFO 19
#define IP_UNICAST_IF 31

/* IPv6 options for use with getsockopt/setsockopt */
#define IPV6_HOPOPTS 1
#define IPV6_UNICAST_HOPS 4
#define IPV6_MULTICAST_IF 9
#define IPV6_MULTICAST_HOPS 10
#define IPV6_MULTICAST_LOOP 11
#define IPV6_ADD_MEMBERSHIP 12
#define IPV6_DROP_MEMBERSHIP 13
#define IPV6_JOIN_GROUP IPV6_ADD_MEMBERSHIP
#define IPV6_LEAVE_GROUP IPV6_DROP_MEMBERSHIP
#define IPV6_DONTFRAG 14
#define IPV6_PKTINFO 19
#define IPV6_HOPLIMIT 21
#define IPV6_CHECKSUM 26
#define IPV6_V6ONLY 27
#define IPV6_UNICAST_IF 31
#define IPV6_RTHDR 32
#define IPV6_RECVRTHDR 38
#define IPV6_TCLASS 39
#define IPV6_RECVTCLASS 40

/* IP agnostic options for use with getsockopt/setsockopt */
#define MCAST_JOIN_GROUP 41
#define MCAST_LEAVE_GROUP 42
#define MCAST_BLOCK_SOURCE 43
#define MCAST_UNBLOCK_SOURCE 44
#define MCAST_JOIN_SOURCE_GROUP 45
#define MCAST_LEAVE_SOURCE_GROUP 46

#define MCAST_INCLUDE 0
#define MCAST_EXCLUDE 1

#define _WS1_IP_OPTIONS 1
#define _WS1_IP_MULTICAST_IF 2
#define _WS1_IP_MULTICAST_TTL 3
#define _WS1_IP_MULTICAST_LOOP 4
#define _WS1_IP_ADD_MEMBERSHIP 5
#define _WS1_IP_DROP_MEMBERSHIP 6
#define _WS1_IP_TTL 7
#define _WS1_IP_TOS 8
#define _WS1_IP_DONTFRAGMENT 9

/* IPX options */
#define IPX_TYPE 1

/* Symbolic values for the second parm to shutdown(2) */
#define SHUT_RD 0		/* == Win32 SD_RECEIVE */
#define SHUT_WR 1		/* == Win32 SD_SEND */
#define SHUT_RDWR 2		/* == Win32 SD_BOTH */

/* The various priorities. */
#define SOPRI_INTERACTIVE 0
#define SOPRI_NORMAL 1
#define SOPRI_BACKGROUND 2

#ifdef __cplusplus
};
#endif /* __cplusplus */

#ifdef __cplusplus
extern "C"
{
#endif

  int accept (int, struct sockaddr *__peer, socklen_t *);
  int accept4 (int, struct sockaddr *__peer, socklen_t *, int flags);
  int bind (int, const struct sockaddr *__my_addr, socklen_t __addrlen);
  int connect (int, const struct sockaddr *, socklen_t);
  int getpeername (int, struct sockaddr *__peer, socklen_t *);
  int getsockname (int, struct sockaddr *__addr, socklen_t *);
  int listen (int, int __n);
  ssize_t recv (int, void *__buff, size_t __len, int __flags);
  ssize_t recvfrom (int, void *__buff, size_t __len, int __flags,
		    struct sockaddr *__from, socklen_t * __fromlen);
  ssize_t recvmsg (int s, struct msghdr *msg, int flags);
  ssize_t send (int, const void *__buff, size_t __len, int __flags);
  ssize_t sendmsg (int s, const struct msghdr *msg, int flags);
  ssize_t sendto (int, const void *, size_t __len, int __flags,
		  const struct sockaddr *__to, socklen_t __tolen);
  int setsockopt (int __s, int __level, int __optname, const void *optval,
		  socklen_t __optlen);
  int getsockopt (int __s, int __level, int __optname, void *__optval,
		  socklen_t * __optlen);
  int shutdown (int, int);
  int socket (int __family, int __type, int __protocol);
  int sockatmark (int __fd);
  int socketpair (int __domain, int __type, int __protocol, int __fds[2]);

  struct servent *getservbyname (const char *__name, const char *__proto);

#ifdef __cplusplus
};
#endif

#if __SSP_FORTIFY_LEVEL > 0
#include <ssp/socket.h>
#endif

#endif /* _SYS_SOCKET_H */
