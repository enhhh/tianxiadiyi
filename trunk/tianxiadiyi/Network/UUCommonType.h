/*
**功能描述：标准数据类型定义
**文件说明：
**作    者：uutc
**创建时间：
**修    改：2013-05-06
**严禁使用bool标准类型
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _UUCOMMON_TYPE_
#define _UUCOMMON_TYPE_



///////////////////////
// bool值定义
///////////////////////
//#define true 1		// - 真
//#define false 0		// - 假

#define UUINVALID (-1)  // 无效ID,编号等

#define	PACKET_HEADER_LEN (4) //包头长度


///////////////////////
// 指针/内存相关定义
///////////////////////
//#define UBI---_NULL 0		// - 空

//根据指针值删除内存(malloc分配空间)
#ifndef SAFE_FREE
#define SAFE_FREE(x)	if( (x)!=NULL ) { free (x); (x)=NULL; }
#endif

//根据指针值删除内存(new分配空间)
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)	if( (x)!=NULL ) { delete (x); (x)=NULL; }
#endif

//根据指针值删除数组类型内存(new分配块空间)
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if( (x)!=NULL ) { delete[] (x); (x)=NULL; }
#endif

#if defined(_WIN32_)

#define UUSOCKCALL_RETURN(OP,TYPE,FAILVALUE) \
  	 do { TYPE result = (TYPE) OP; \
      	  if (result == FAILVALUE) { int ___ = ::WSAGetLastError (); errno = ___; return (TYPE) FAILVALUE; } else return result; \
  		} while (0)
	#define UUSOCKCALL(OP,TYPE,FAILVALUE,RESULT) \
  	 do { RESULT = (TYPE) OP; \
      	  if (RESULT == FAILVALUE) { int ___ = ::WSAGetLastError (); errno = ___; RESULT = FAILVALUE; } \
  } while (0)
  

#else

extern int errno;

#define UUSOCKCALL_RETURN(OP,TYPE,FAILVALUE) \
  	 do { TYPE result = (TYPE) OP; \
      	  if (result == FAILVALUE) { int ___ = errno ; errno = ___; return (TYPE) FAILVALUE; } else return result; \
  		} while (0)
	#define UUSOCKCALL(OP,TYPE,FAILVALUE,RESULT) \
  	 do { RESULT = (TYPE) OP; \
      	  if (RESULT == FAILVALUE) { int ___ = errno ; errno = ___; RESULT = FAILVALUE; } \
  } while (0)

#endif

#endif
