//
// Created by root on 25.03.20.
//
#include <cstdint>

#ifndef HCICORE_GAPSPECIFICATION_H
#define HCICORE_GAPSPECIFICATION_H

// From https://www.bluetooth.com/specifications/assigned-numbers/generic-access-profile/
static constexpr uint8_t FLAGS = 0x01;
static constexpr uint8_t INCOMPLETE_LIST_OF_16_BIT_SERVICE_CLASS_UUIDS = 0x02;
static constexpr uint8_t COMPLETE_LIST_OF_16_BIT_SERVICE_CLASS_UUIDS = 0x03;
static constexpr uint8_t INCOMPLETE_LIST_OF_32_BIT_SERVICE_CLASS_UUIDS = 0x04;
static constexpr uint8_t COMPLETE_LIST_OF_32_BIT_SERVICE_CLASS_UUIDS = 0x05;
static constexpr uint8_t INCOMPLETE_LIST_OF_128_BIT_SERVICE_CLASS_UUIDS = 0x06;
static constexpr uint8_t COMPLETE_LIST_OF_128_BIT_SERVICE_CLASS_UUIDS = 0x07;
static constexpr uint8_t SHORTENED_LOCAL_NAME = 0x08;
static constexpr uint8_t COMPLETE_LOCAL_NAME = 0x09;
static constexpr uint8_t TX_POWER_LEVEL = 0x0A;
static constexpr uint8_t CLASS_OF_DEVICE = 0x0D;
static constexpr uint8_t SIMPLE_PAIRING_HASH_C = 0x0E;
static constexpr uint8_t SIMPLE_PAIRING_RANDOMIZER_R = 0x0F;
static constexpr uint8_t DEVICE_ID = 0x10;
static constexpr uint8_t SECURITY_MANAGER_OUT_OF_BAND_FLAGS = 0x11;
static constexpr uint8_t SLAVE_CONNECTION_INTERVAL_RANGE = 0x12;
static constexpr uint8_t LIST_OF_16_BIT_SERVICE_SOLICITATION_UUIDS = 0x14;
static constexpr uint8_t LIST_OF_128_BIT_SERVICE_SOLICITATION_UUIDS = 0x15;
static constexpr uint8_t SERVICE_DATA = 0x16;
static constexpr uint8_t PUBLIC_TARGET_ADDRESS = 0x17;
static constexpr uint8_t RANDOM_TARGET_ADDRESS = 0x18;
static constexpr uint8_t APPEARANCE = 0x19;
static constexpr uint8_t ADVERTISING_INTERVAL = 0x1A;
static constexpr uint8_t LE_BLUETOOTH_DEVICE_ADDRESS = 0x1B;
static constexpr uint8_t LE_ROLE = 0x1C;
static constexpr uint8_t SIMPLE_PAIRING_HASH_C_256 = 0x1D;
static constexpr uint8_t SIMPLE_PAIRING_RANDOMIZER_R_256 = 0x1E;
static constexpr uint8_t LIST_OF_32_BIT_SERVICE_SOLICITATION_UUIDS = 0x1F;
static constexpr uint8_t SERVICE_DATA_32_BIT_UUID = 0x20;
static constexpr uint8_t SERVICE_DATA_128_BIT_UUID = 0x21;
static constexpr uint8_t LE_SECURE_CONNECTIONS_CONFIRMATION_VALUE = 0x22;
static constexpr uint8_t LE_SECURE_CONNECTIONS_RANDOM_VALUE = 0x23;
static constexpr uint8_t URI = 0x24;
static constexpr uint8_t INDOOR_POSITIONING = 0x25;
static constexpr uint8_t TRANSPORT_DISCOVERY_DATA = 0x26;
static constexpr uint8_t LE_SUPPORTED_FEATURES = 0x27;
static constexpr uint8_t CHANNEL_MAP_UPDATE_INDICATION = 0x28;
static constexpr uint8_t PB_ADV = 0x29;
static constexpr uint8_t MESH_MESSAGE = 0x2A;
static constexpr uint8_t MESH_BEACON = 0x2B;
static constexpr uint8_t BIGINFO = 0x2C;
static constexpr uint8_t BROADCAST_CODE = 0x2D;
static constexpr uint8_t THREE_D_INFORMATION_DATA = 0x3D;
static constexpr uint8_t MANUFACTURER_SPECIFIC_DATA = 0xFF;


#endif //HCICORE_GAPSPECIFICATION_H
