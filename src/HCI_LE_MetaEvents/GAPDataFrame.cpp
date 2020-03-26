//
// Created by root on 25.03.20.
//

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <sstream>

#include "../../include/HCI_LE_MetaEvents/GATTServices.h"
#include "../../include/HCI_LE_MetaEvents/GAPDataFrame.h"
#include "../../include/HCI_LE_MetaEvents/GAPCodesList.h"

using namespace hcicore;





int GAPDataFrame::assignVectorStructs(std::vector<GAPDataFrame::GAPCodeList> &gap_code_list){
    gap_code_list = {
            {0x01, "Flags",  &GAPDataFrame::parseFlags},
            {0x02, "IncompleteListof16bitServiceClassUUIDs",  nullptr},
            {0x03, "CompleteListof16bitServiceClassUUIDs",  &GAPDataFrame::parseCompleteListof16bitServiceClassUUIDs},
            {0x04, "IncompleteListof32bitServiceClassUUIDs",  nullptr},
            {0x05, "CompleteListof32bitServiceClassUUIDs",  nullptr},
            {0x06, "IncompleteListof128bitServiceClassUUIDs",  nullptr},
            {0x07, "CompleteListof128bitServiceClassUUIDs",  nullptr},
            {0x08, "ShortenedLocalName",  nullptr},
            {0x09, "CompleteLocalName",  &GAPDataFrame::parseCompleteLocalName},
            {0x0A, "TxPowerLevel",  nullptr},
            {0x0D, "ClassofDevice",  nullptr},
            {0x0E, "SimplePairingHashC",  nullptr},
            {0x0E, "SimplePairingHashC192",  nullptr},
            {0x0F, "SimplePairingRandomizerR",  nullptr},
            {0x0F, "SimplePairingRandomizerR192",  nullptr},
            {0x10, "DeviceID",  nullptr},
            {0x10, "SecurityManagerTKValue",  nullptr},
            {0x11, "SecurityManagerOutofBandFlags",  nullptr},
            {0x12, "SlaveConnectionIntervalRange",  nullptr},
            {0x14, "Listof16bitServiceSolicitationUUIDs",  nullptr},
            {0x15, "Listof128bitServiceSolicitationUUIDs",  nullptr},
            {0x16, "ServiceData",  nullptr},
            {0x16, "ServiceData16bitUUID",  nullptr},
            {0x17, "PublicTargetAddress",  nullptr},
            {0x18, "RandomTargetAddress",  nullptr},
            {0x19, "Appearance",  nullptr},
            {0x1A, "AdvertisingInterval",  nullptr},
            {0x1B, "LEBluetoothDeviceAddress",  nullptr},
            {0x1C, "LERole",  nullptr},
            {0x1D, "SimplePairingHashC256",  nullptr},
            {0x1E, "SimplePairingRandomizerR256",  nullptr},
            {0x1F, "Listof32bitServiceSolicitationUUIDs",  nullptr},
            {0x20, "ServiceData32bitUUID",  nullptr},
            {0x21, "ServiceData128bitUUID",  nullptr},
            {0x22, "LESecureConnectionsConfirmationValue",  nullptr},
            {0x23, "LESecureConnectionsRandomValue",  nullptr},
            {0x24, "URI",  nullptr},
            {0x25, "IndoorPositioning",  nullptr},
            {0x26, "TransportDiscoveryData",  nullptr},
            {0x27, "LESupportedFeatures",  nullptr},
            {0x28, "ChannelMapUpdateIndication",  nullptr},
            {0x29, "PBADV",  nullptr},
            {0x2A, "MeshMessage",  nullptr},
            {0x2B, "MeshBeacon",  nullptr},
            {0x2C, "BIGInfo",  nullptr},
            {0x2D, "Broadcast_Code",  nullptr},
            {0x3D, "3DInformationData",  nullptr},
            {0xFF, "ManufacturerSpecificData",  nullptr},

    };
}
GAPDataFrame::GAPDataFrame(std::vector<uint8_t> &raw_data) {

    unsigned int pos = 0;
    std::vector<GAPCodeList> gap_code_list;
    // This is for population the struct
    assignVectorStructs(gap_code_list);


    while(pos < raw_data.size()) {

        // First position is length
        int length = raw_data[pos++];

        // Second position is the type
        uint8_t eir_type = raw_data[pos++];

        // Extract the desired field
        std::vector<uint8_t> extracted_data(raw_data.begin() + pos, raw_data.begin() + (pos - 1) + length);

        /*
        // DEBUG PRINTING
        std::cout << "LENGTH: " << std::dec << length << " TYPE 0x" << std::hex << (int) eir_type << ": ";
        for (int j = 0; j < extracted_data.size(); ++j) {
            std::cout << std::hex << (int)extracted_data[j] << std::dec  << " - ";
        }
        std::cout << std::endl;
        */


        //Just for printing
        std::stringstream ss;

        bool found = false;
        for (int i = 0; i < gap_code_list.size(); ++i) {
            if(eir_type == gap_code_list[i].datatype_value) {
                if(gap_code_list[i].fun_ptr == NULL){
                    std::cout << "  --> Function pointer for Code 0x" << std::hex << (int)eir_type << std::dec
                    << " (" <<gap_code_list[i].datatype_name << ") not implemented." << std::endl;
                    found = true;
                }
                else {
                    (this->*gap_code_list[i].fun_ptr)(extracted_data);
                }
                found = true;
                break;
            }
        }

        if(!found){
            std::cout << "Function Parser 0x" << std::hex << (int)eir_type << std::dec << "not found." << std::endl;
        }
        pos += length - 1;
    }

}

int GAPDataFrame::parseFlags(std::vector<uint8_t> &data_holder){

    if(data_holder.size() != 1){
        flags.code = 0xff;
        flags.description = "Error setting flag";
    } else {
       // int len = data_holder[0];
        flags.code = data_holder[0];

        // See: Supplement to Bluetooth Core Specification | CSS v9, Part A
        // 1.3 FLAGS (S. 12f)
        switch (flags.code){
            case 0x01: flags.description = "LE Limited Discoverable Mode";
                break;
            case 0x02: flags.description = "LE General Discoverable Mode";
                break;
            case 0x04: flags.description = "BR/EDR Not Supported";
                break;
            case 0x08: flags.description = "Simultaneous LE and BR/EDR to Same Device Capable (Controller)";
                break;
            case 0x16: flags.description = "Simultaneous LE and BR/EDR to Same Device Capable (Host)";
                break;
            default: flags.description = "Reserved for future use";
                break;
        }
    }

    /*
    // DEBUG PRINTING
    std::cout << "  --> FLAGS (0x01)" << "[" << data_holder.size() << "]: 0x" << std::hex
              << (int)flags.code << std::dec << " - " << flags.description << std::endl; */
    return 0;
}


int GAPDataFrame::parseCompleteLocalName(std::vector<uint8_t> &data_holder){

    std::stringstream ss;
    if(data_holder.size() == 0){
        ss  << "unknown";
    }else {
        for (unsigned int i = 0; i < data_holder.size(); ++i) {
            ss << (char) data_holder[i];
        }
    }
    complete_local_name = ss.str();

    /*
    std::cout << "  --> COMPLETE_LOCAL_NAME (0x09) " <<
              "[" << data_holder.size() << "]: " << complete_local_name << std::endl;
    */

    return  0;
}


int GAPDataFrame::parseCompleteListof16bitServiceClassUUIDs(std::vector<uint8_t> &data_holder){
    // In case of 16 bit we always need to take 2 octets
    bool found = false;

    if(data_holder.size() == 0){
      //std::cout << "No UUIDs";
    }
    else {
        if(data_holder.size()%2 == 0) {
            for (unsigned int i = 0; i < data_holder.size(); i += 2) {
                // Combine both uint8_t to one uint16_t
               uint16_t wd = ((uint16_t)data_holder[i + 1] << 8) | data_holder[i];
                complete_list_of_16_bit_service_class_uuid tmp_uuid;
                tmp_uuid.code = wd;
                for (unsigned int j = 0; j < gatt_services.size(); ++j) {
                    if (gatt_services[j].code == tmp_uuid.code){
                        tmp_uuid.uniform_type_identifier = gatt_services[j].uniform_type_identifier;
                        tmp_uuid.name = gatt_services[j].name;
                        found = true;
                    }
                }
                if(!found){
                    tmp_uuid.uniform_type_identifier ="unknown";
                    tmp_uuid.name = "unknown";
                }
                complete_list_of_16_bit_service_class_uuids.push_back(tmp_uuid);
            }
        }

    }

    std::stringstream ss;

    /*
    // DEBUG PRINTING
    for (unsigned int i = 0; i < complete_list_of_16_bit_service_class_uuids.size(); ++i) {
        ss << "0x" << std::hex
           << (int)complete_list_of_16_bit_service_class_uuids[i].code << std::dec
           << " (" << complete_list_of_16_bit_service_class_uuids[i].name << ")  |  ";
    }
    std::cout << "  --> COMPLETE_LIST_OF_16_BIT_SERVICE_CLASS_UUIDS (0x03) "
                 << "[" << data_holder.size() << "]: " << ss.str() << std::endl;
    */

    return 0;
}






