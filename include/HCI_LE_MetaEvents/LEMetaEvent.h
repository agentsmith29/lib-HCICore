//
// Created by root on 26.02.20.
//

#ifndef HCICORE_LEMETAEVENT_H
#define HCICORE_LEMETAEVENT_H

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include "../BDAddress.h"


// From BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 4, Part E
// 7.7.65 LE Meta event, S. 2379f.
static constexpr uint8_t HCILE_ConnectionComplete = 0x01;
static constexpr uint8_t HCILE_AdvertisingReport = 0x02;
static constexpr uint8_t HCILE_ConnectionUpdateComplete = 0x03;
static constexpr uint8_t HCILE_ReadRemoteFeaturesComplete = 0x04;
static constexpr uint8_t HCILE_LongTermKeyRequest = 0x05;
static constexpr uint8_t HCILE_RemoteConnectionParameterRequest = 0x06;
static constexpr uint8_t HCILE_DataLengthChange = 0x07;
static constexpr uint8_t HCILE_ReadLocalP256PublicKeyComplete = 0x08;
static constexpr uint8_t HCILE_GenerateDHKeyComplete = 0x09;
static constexpr uint8_t HCILE_EnhancedConnectionComplete = 0x0A;
static constexpr uint8_t HCILE_DirectedAdvertisingReport = 0x0B;
static constexpr uint8_t HCILE_PHYUpdate_Complete = 0x0C;
static constexpr uint8_t HCILE_ExtendedAdvertisingReport = 0x0D;
static constexpr uint8_t HCILE_PeriodicAdvertisingSyncEstablished = 0x0E;
static constexpr uint8_t HCILE_PeriodicAdvertisingReport = 0x0F;
static constexpr uint8_t HCILE_PeriodicAdvertisingSyncLost = 0x10;
static constexpr uint8_t HCILE_ScanTimeout = 0x11;
static constexpr uint8_t HCILE_AdvertisingSet_Terminated = 0x12;
static constexpr uint8_t HCILE_Scan_RequestReceived = 0x13;
static constexpr uint8_t HCILE_Channel_SelectionAlgorithm = 0x14;
static constexpr uint8_t HCILE_ConnectionlessIQReport = 0x15;
static constexpr uint8_t HCILE_ConnectionIQReport = 0x16;
static constexpr uint8_t HCILE_CTE_RequestFailed = 0x17;
static constexpr uint8_t HCILE_PeriodicAdvertisingSyncTransferReceived = 0x18;
static constexpr uint8_t HCILE_CISEstablished = 0x19;
static constexpr uint8_t HCILE_CISRequest = 0x1A;
static constexpr uint8_t HCILE_CreateBIGComplete = 0x1B;
static constexpr uint8_t HCILE_TerminateBIGComplete = 0x1C;
static constexpr uint8_t HCILE_BIGSyncEstablished = 0x1D;
static constexpr uint8_t HCILE_BIGSyncLost = 0x1E;
static constexpr uint8_t HCILE_RequestPeerSCAComplete = 0x1F;
static constexpr uint8_t HCILE_PathLossThreshold = 0x20;
static constexpr uint8_t HCILE_TransmitPowerReporting = 0x21;
static constexpr uint8_t HCILE_BIGInfoAdvertising_Report = 0x22;


static constexpr uint8_t EIR_FLAGS = 0x01; /* flags */
static constexpr uint8_t EIR_UUID16_SOME = 0x02;  /* 16-bit UUID, more available */
static constexpr uint8_t EIR_UUID16_ALL = 0x03;  /* 16-bit UUID, all listed */
static constexpr uint8_t EIR_UUID32_SOME = 0x04;  /* 32-bit UUID, more available */
static constexpr uint8_t EIR_UUID32_ALL = 0x05;  /* 32-bit UUID, all listed */
static constexpr uint8_t EIR_UUID128_SOME = 0x06;  /* 128-bit UUID, more available */
static constexpr uint8_t EIR_UUID128_ALL = 0x07;  /* 128-bit UUID, all listed */
static constexpr uint8_t EIR_NAME_SHORT = 0x08;  /* shortened local name */
static constexpr uint8_t EIR_NAME_COMPLETE = 0x09;  /* complete local name */
static constexpr uint8_t EIR_TX_POWER = 0x0A;  /* transmit power level */
static constexpr uint8_t EIR_DEVICE_ID = 0x10;  /* device ID */




class LEMetaEvent {

public:

private:

    uint8_t _subevent_code;
};



#endif //HCICORE_LEMETAEVENT_H
