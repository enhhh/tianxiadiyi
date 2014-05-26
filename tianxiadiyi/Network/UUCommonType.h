/*
**������������׼�������Ͷ���
**�ļ�˵����
**��    �ߣ�uutc
**����ʱ�䣺
**��    �ģ�2013-05-06
**�Ͻ�ʹ��bool��׼����
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _UUCOMMON_TYPE_
#define _UUCOMMON_TYPE_



///////////////////////
// boolֵ����
///////////////////////
//#define true 1		// - ��
//#define false 0		// - ��

#define UUINVALID (-1)  // ��ЧID,��ŵ�

#define	PACKET_HEADER_LEN (4) //��ͷ����


///////////////////////
// ָ��/�ڴ���ض���
///////////////////////
//#define UBI---_NULL 0		// - ��

//����ָ��ֵɾ���ڴ�(malloc����ռ�)
#ifndef SAFE_FREE
#define SAFE_FREE(x)	if( (x)!=NULL ) { free (x); (x)=NULL; }
#endif

//����ָ��ֵɾ���ڴ�(new����ռ�)
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)	if( (x)!=NULL ) { delete (x); (x)=NULL; }
#endif

//����ָ��ֵɾ�����������ڴ�(new�����ռ�)
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
