

/************************************************************
** 文件名 uLinxTypes.h
** 创建人：Nephalem<zg250610346@163.com>
** 日  期：2018-06-06
** 修改人：无
** 日  期：无
** 描  述：uLinxTypes头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _ULINXDATATYPE_H_INCLUDE_
#define _ULINXDATATYPE_H_INCLUDE_

#include <string>
#include <iostream>
using namespace std;

typedef char					ULINX_INT8;
typedef signed short			ULINX_INT16;
typedef signed int				ULINX_INT32;
typedef long long				ULINX_INT64;
typedef unsigned char			ULINX_UINT8;
typedef unsigned short			ULINX_UINT16;
typedef unsigned int			ULINX_UINT32;
typedef unsigned long long		ULINX_UINT64;
typedef float					ULINX_FLOAT32;
typedef double					ULINX_DOUBLE64;
typedef double					ULINX_LONGDOUBLE64;
typedef signed int				ULINX_RETURNCODE_T;


typedef unsigned char Octet;
typedef unsigned char octet;

const ULINX_RETURNCODE_T ULINX_RETURNCODE_ERROR			= -1;
const ULINX_RETURNCODE_T ULINX_RETURNCODE_SEM_WAIT_TIMEOUT = -100;


 
#if (defined( ULINX_WIN) ||  defined(_WIN32)) 
	# pragma warning (disable:4819)

#ifndef	ULINX_WIN
#define ULINX_WIN
#endif
	#include <winsock.h>
	#include <Windows.h>
	#include <process.h>
	#include <io.h>
	#include <direct.h>
	//#define DDS_DLL					_declspec(dllexport)

	
	typedef SOCKET                  ULINX_SOCKET;
	typedef HANDLE                  ULINX_APHORE;                               // 信号量对象

	typedef HANDLE                  ULINX_MAPFILE;                              // 共享内存对象
	typedef HANDLE                  ULINX_THREAD;                               // 线程对象
	typedef HANDLE                  ULINX_MUTEX;                                // 互斥锁对象
	typedef ULINX_UINT32            ULINX_TIME;

	typedef unsigned (__stdcall* _beginthreadex_proc_type)(void*);

#elif defined ULINX_LINUX
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <signal.h>
	#include <time.h>
	#include <semaphore.h>	
	#include <net/if.h>
	#include <pthread.h>
	#include <string.h>
	#include <stdlib.h>
    #include <errno.h>
	#include <fcntl.h>
    #include <iostream>
    #include <sys/time.h>
    #include <sys/mman.h>
    #include <sys/ipc.h>
    #include <sys/shm.h>
    #include <sys/stat.h>
    #include <sys/ioctl.h>
    #include <sys/types.h>
    #include <sys/times.h>
        #define __stdcall
        #define CALLBACK
	#define WINAPI
        #define DWORD           ULINX_UINT32
	#define FALSE            false
	#define TRUE             true
	#define ERROR            -1
	//Timer
	#define START_TIMER_MSG WM_USER+1
	//wparam为Timer id
	#define END_TIMER_MSG	WM_USER+2
	//最大等待时间
	#define MAX_WAIT_TIME	2000

	typedef ULINX_INT32                ULINX_SOCKET;
	typedef ULINX_UINT32               ULINX_HANDLE;
	typedef __timer_t                  ULINX_TIME;

	typedef pthread_mutex_t            ULINX_MUTEX;              // 互斥锁对象
	typedef pthread_t                  ULINX_THREAD;             // 线程对象
	typedef sem_t*                     ULINX_APHORE;             // 信号量对象
	typedef ULINX_INT32                ULINX_MAPFILE;            // 共享内存对象


#elif defined ULINX_LINUX_64
	
	#define DDS_DLL_FILE
	#define WINAPI

#elif defined ULINX_VXWORKS
	
	#include <sdLibCommon.h>
	#include <semLibCommon.h>
	#include <sdLib.h>
	#include <taskLib.h>
	#include <errno.h>
	#include <unistd.h>
	#include <time.h>
#include <semLib.h>
#include <VxWorks.h>
#include <taskLib.h>
#include <sockLib.h>
#include <selectLib.h>
#include <inetLib.h>
//#include <inet.h>
//#include <stdioLib.h>
#include <sysLib.h>
#include <ioLib.h>
//#include <routeLib.h>
#include <timers.h>
//#include <logLib.h>
#include <hostLib.h>
#include <netdb.h>
#include <string.h>
#include <ctype.h>
//#include <types.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <sys/times.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <hostLib.h>
//#include <routeLib.h> //for vx5

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/ioctl.h>
#include  <net/if.h>	
#include  <net/if_arp.h>
#include <taskLib.h>
#include <selectLib.h>//for vx6
#include <ioLib.h>
#include <ioctl.h>
#include <strings.h>
#include <memLib.h>
	
    #define CALLBACK
	#define __stdcall
    #define DDS_DLL
	#define DDS_DLL_FILE                                 
	#define WINAPI
	#define DWORD           ULINX_UINT32
	
	typedef SEM_ID      ULINX_MUTEX;                            // 互斥锁对象
	typedef SEM_ID      ULINX_APHORE;                           // 信号量对象
	typedef SD_ID       ULINX_MAPFILE;                          // 共享内存对象
	//typedef int         ULINX_THREAD;                           // 线程对象
	typedef ULINX_INT32 ULINX_SOCKET;
	
	typedef ULINX_INT32                ULINX_SOCKET;
	typedef ULINX_UINT32               ULINX_HANDLE;
	//typedef __timer_t                  ULINX_TIME;

	typedef pthread_t                  ULINX_THREAD;             // 线程对象


    typedef ULINX_INT32 Handle;
    
#endif
#endif

