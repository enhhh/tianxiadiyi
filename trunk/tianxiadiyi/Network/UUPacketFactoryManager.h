#ifndef __UUPACKET_FACTORY_MANAGER_H__ 
#define __UUPACKET_FACTORY_MANAGER_H__

#include "UUPacket.h"
#include "UUPacketEXT.h"
#include "UUPacketFactory.h"

#define PACKET_HEARTBEAT  1
#define PACKET_GENERAL  2

#define PACKET_CG_HEARTBEAT  1

#define PACKET_CG_STUDY_FORMATION  5
#define PACKET_CG_LEVEL_UP_FORMATION  5
#define PACKET_CG_FORMATION_LIST  12
#define PACKET_CG_GENERAL_LIST  5
#define PACKET_CG_SELECT_FORMATION  12
#define PACKET_CG_FIX_FORMATION  12
#define PACKET_CG_MODIFY_FORMATION  12

#define PACKET_MAX 65535

class UUPacketFactoryManager 
{
public :
	UUPacketFactoryManager( ) ;

	~UUPacketFactoryManager( ) ;

	void				AddFactory( UUPacketFactory* pFactory ) ;

	// ��ʼ���ӿ�
	void				Init( ) ;

	// ������Ϣ���ʹ��ڴ��������Ϣʵ�����ݣ���������߳�ͬʱ���ã�
	UUPacketEXT*		CreatePacket( unsigned short packetID ) ;
	
	//ɾ����Ϣʵ�壨������߳�ͬʱ���ã�
	void				RemovePacket( UUPacketEXT* pPacket ) ;

	UUPacketFactory **	m_Factories ;

	unsigned short   	m_Size ;

	unsigned int*		m_pPacketAllocCount ;
};

extern UUPacketFactoryManager* g_pPacketFactoryManager;

#endif