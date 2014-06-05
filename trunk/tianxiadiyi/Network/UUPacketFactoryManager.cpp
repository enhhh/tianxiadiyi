#include "UUPacketFactoryManager.h"

#include "Packets\GCHeartBeat.h"

#include "Packets\Starring\GCStarringAttribute.h"
#include "Packets\Starring\GCCulture.h"
#include "Packets\Starring\GCTelentList.h"
#include "Packets\Starring\GCLightUpTelent.h"
#include "Packets\Starring\GCSoulBeadList.h"
#include "Packets\Starring\GCSoulBeadEquipList.h"
#include "Packets\Starring\GCPutOnSoulBead.h"
#include "Packets\Starring\GCTakeOffSoulBead.h"
#include "Packets\Starring\GCSwapSoulBead.h"

UUPacketFactoryManager* g_pPacketFactoryManager = NULL ;

UUPacketFactoryManager::UUPacketFactoryManager()
{
	m_Factories = NULL ;
	m_Size = PACKET_MAX ;
	m_Factories = new UUPacketFactory*[ m_Size ];
	m_pPacketAllocCount = new UINT[m_Size] ;

	for ( int i = 0; i < m_Size; i++ ) 
	{
		m_Factories[i] = NULL ;
		m_pPacketAllocCount[i] = 0 ;
	}
}

UUPacketFactoryManager::~UUPacketFactoryManager()
{
	for ( int i = 0; i < m_Size; i++ ) 
	{
		SAFE_DELETE(m_Factories[i]) ;
	}

	SAFE_DELETE_ARRAY(m_Factories) ;
	SAFE_DELETE_ARRAY(m_pPacketAllocCount) ;
}

void UUPacketFactoryManager::AddFactory( UUPacketFactory* pFactory )
{
	if ( m_Factories[pFactory->GetPacketID()]!=NULL ) 
	{
		return;
	}

	m_Factories[pFactory->GetPacketID()] = pFactory ;
}

void UUPacketFactoryManager::Init()
{
	AddFactory( new GCHeartBeatFactory());

	AddFactory( new GCStarringAttributeFactory());
	AddFactory( new GCCultureFactory());
	AddFactory( new GCTelentListFactory());
	AddFactory( new GCLightUpTelentFactory());
	AddFactory( new GCSoulBeadListFactory());
	AddFactory( new GCSoulBeadEquipListFactory());
	AddFactory( new GCPutOnSoulBeadFactory());
	AddFactory( new GCTakeOffSoulBeadFactory());
	AddFactory( new GCSwapSoulBeadFactory());
}

UUPacketEXT* UUPacketFactoryManager::CreatePacket( unsigned short packetID )
{
	UUPacketEXT* pPacket = m_Factories[packetID]->CreatePacket();
	m_pPacketAllocCount[packetID]++;

	return pPacket ;
}

void UUPacketFactoryManager::RemovePacket( UUPacketEXT* pPacket )
{
	unsigned short packetID = pPacket->GetPacketID() ;
	SAFE_DELETE( pPacket ) ;
	m_pPacketAllocCount[packetID] -- ;
}
