//
// Created by root on 25.03.20.
//

#include "../../include/HCI_LE_MetaEvents/HCI_LE_AdvertisingReportEvent.h"

// Created by root on 26.02.20.
//

#include "../../include/HCI_LE_MetaEvents/LEMetaEvent.h"
#include "../../include/HCI_LE_MetaEvents/GAPCodesList.h"
#include <stdio.h>
#include <algorithm>
#include <iostream>


using namespace hcicore;

///------------------------------------------------------------------------------------------------------------------///
/// --- ASSIGN FUNCTIONS --- ///
int HCI_LE_AdvertisingReportEvent::assignSubeventCode(uint8_t &buf){

    // First Assign the Subevent Code
    _subevent_code.code = buf;

    // Check if the subevent code is matching 0x02
    if(_subevent_code.code != 0x02)
        throw std::invalid_argument("Aborting: Given subevent code did not match.");

    switch (_subevent_code.code){
        case 0x02:  _subevent_code.descripton = "HCI LE Advertising Report";
            break;
        default: _subevent_code.descripton = "Unknown/Other Report";
            break;
    }

    /*
    std::cout << "SUBEVENT CODE: " << (int)_subevent_code.code
              << " (" << _subevent_code.descripton << ")" <<std::endl;
    */
    return 0;
}

int HCI_LE_AdvertisingReportEvent::assignTotalNumberOfReports(uint8_t &buf){

    _num_reports = (int)buf;
    /*std::cout  << std::dec << "NUM OF REPORTS: " << (int)_num_reports << std::endl;*/
    return 0;
}

int HCI_LE_AdvertisingReportEvent::assignEventTypes(uint8_t *buf){

    int pos = 0;
    // 0x00 Connectable and scannable undirected advertising (ADV_IND)
    // 0x01 Connectable directed advertising (ADV_DIRECT_IND)
    // 0x02 Scannable undirected advertising (ADV_SCAN_IND)
    // 0x03 Non connectable undirected advertising (ADV_NONCONN_IND)
    for (pos = 0; pos < _num_reports; ++pos) {
        // Get the event code
        eventType tmp_event_type;

        tmp_event_type.code = buf[pos];
        // Assign the event descripton
        switch (tmp_event_type.code){
            case 0x00: tmp_event_type.descripton = "Connectable and scannable undirected advertising (ADV_IND)";
                break;
            case 0x01: tmp_event_type.descripton = "Connectable directed advertising (ADV_DIRECT_IND)";
                break;
            case 0x02: tmp_event_type.descripton = "Scannable undirected advertising (ADV_SCAN_IND)";
                break;
            case 0x03: tmp_event_type.descripton = "Non connectable undirected advertising (ADV_NONCONN_IND)";
                break;
            case 0x04: tmp_event_type.descripton = "Scan Response (SCAN_RSP)";
                break;
            default: tmp_event_type.descripton = "Unknown (ADV_UNKNOWN)";
                break;
        }
        _event_types.push_back(tmp_event_type);

    }


    /*
    // DEBUG PRINTING
    // Just printing out some information about the found event types
    if (_event_types.size() == _num_reports) {
        // Print out the event types
        for (int i = 0; i < _event_types.size(); ++i) {
            std::cout << std::dec << "[" << i << "] Event Type: 0x"
                      << int(_event_types[i].code) <<
                      " (" << _event_types[i].descripton << ")" << std::endl;
        }
    }
    else {
        std::cout << "Event Type: Sanity check error!" << std::endl;
    }
    */

    return pos;
}

int HCI_LE_AdvertisingReportEvent::assignAddress(uint8_t *buf){

    int pos = 0;
    std::vector<uint8_t> tmp_addr_type; // Stores temporary the address type
    std::vector<std::array<uint8_t, 6>> tmp_addr; // Stores temporary the address type

    // Assign the Address Type
    for (pos = 0; pos < _num_reports; ++pos) {
        tmp_addr_type.push_back(buf[pos]);
    }


    // Assign the BD Address
    for (int i = 0; i < _num_reports; ++i) {
        // Assign the six octets of the address
        std::array<uint8_t, 6> addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        for (int j = 0; j < addr.size(); j++) {
            addr[j] = buf[pos++];
        }
        // Now reverse the assigned octets since the byte order is not correct.
        std::reverse(std::begin(addr), std::end(addr));
        tmp_addr.push_back(addr);
    }



    // Now we got two array, merge them and assign it to the _bd_address vector
    if(tmp_addr.size() == tmp_addr_type.size()) {
        for (int k = 0; k < _num_reports; ++k) {
            BDAddress tmp_bd_addr = BDAddress(tmp_addr[k], tmp_addr_type[k]);
            _bd_address.push_back(tmp_bd_addr);
        }
    }



    if(_bd_address.size() != _num_reports)
        std::cout << "Address assignment: Sanity check error" << std::endl;


    /*
    // DEBUG PRINTING
    // Now we ant to display the information we stored
    for (int l = 0; l < _bd_address.size(); ++l) {
        std::cout << std::dec << "[" << l << "] ADDRESS: "
                  << _bd_address[l].address_tostring()
                  << ", Type: " << _bd_address[l].addresstype_descriptor()
                  << " (0x" << std::hex << _bd_address[l].addresstype() << std::dec << ")" << std::endl;
    }
    */
    return pos;
}

int HCI_LE_AdvertisingReportEvent::assignDataLength(uint8_t *buf){

    int pos = 0;
    // Assign the Address Type
    for (pos = 0; pos < _num_reports; ++pos) {
       _data_length.push_back(buf[pos]);
    }

    /*
    // DEBUG PRINTING
    // Just printing out the stored information
    if(_num_reports == _data_length.size()) {
        for (int i = 0; i < _num_reports; ++i) {
            std::cout << std::dec << "[" << i << "] DATA LENGTH: " << int (_data_length[i]) << std::endl;
        }
    }
    else{
        std::cout << "Data Length: Sanity check error. Length did not match with given number of reports" << std::endl;
    }
    */
    return pos;
}

int HCI_LE_AdvertisingReportEvent::assignRawData(uint8_t *buf){

    int pos = 0;
    std::vector<uint8_t> tmp_data;

    for (int i = 0; i < _num_reports; ++i) {
        tmp_data.clear();

        for (int j = 0; j < _data_length[i]; ++j) {
            tmp_data.push_back(buf[j]);
            pos++;
        }
        _raw_data.push_back(tmp_data);
    }

    return pos;
}

int HCI_LE_AdvertisingReportEvent::parseDataframe(){


    for (int i = 0; i < _raw_data.size(); ++i) {
        GAPDataFrame frame = GAPDataFrame(_raw_data[i]);
        _gap_dataframes.push_back(frame);
    }

    return 0;
}
///------------------------------------------------------------------------------------------------------------------///



HCI_LE_AdvertisingReportEvent::HCI_LE_AdvertisingReportEvent(unsigned char buf[260], int buf_len) {

    int pos = 0;

    // Get the subevent code (See S. 2382f. 24.03.2020)
    // 1 Octet
    assignSubeventCode(buf[pos++]);

    // Retrieve number of reports (usually 1)
    // 1 Octet
    assignTotalNumberOfReports(buf[pos++]);


    if(_num_reports > 0){

        // Assign the event types
        pos += assignEventTypes(buf + pos);

        // Assign the address
        pos +=  assignAddress(buf + pos);

        // Assign the DataLength
        pos += assignDataLength(buf + pos);

        // Parse the data
        pos += assignRawData(buf + pos);

        parseDataframe();
    }
    createFinalReport();
}

int HCI_LE_AdvertisingReportEvent::createFinalReport() {
    // Make a check
    bool check_passed = true;

    if(_event_types.size() != _num_reports)
        check_passed = false;
    if(_bd_address.size() != _num_reports)
        check_passed = false;
    if(_gap_dataframes.size() != _num_reports)
        check_passed = false;


    for (int i = 0; i < _num_reports; ++i) {

        AdvertisingReport tmp_report = {_event_types[i], _bd_address[i], _gap_dataframes[i]};
        _reports.push_back(tmp_report);
    }
}