//
// Created by root on 26.02.20.
//

#include <iostream>
#include "../include/BDAddress.h"
#include "sstream"

BDAddress::BDAddress(std::array<uint8_t, 6> bd_address, int address_type) {


    _address_type = address_type;
    switch(_address_type){
        case PublicDeviceAddress :
            _address_type_descriptor = "Public Device Address";
            break;
        case RandomDeviceAddress :
            _address_type_descriptor = "Random Device Address";
            break;
        case PublicIdentityAddress :
            _address_type_descriptor = "Public Identity Address (Corresponds to Resolved Private Address)";
            break;
        case RandomStaticIdentityAddress :
            _address_type_descriptor = "Random (static) Identity Address (Corresponds to Resolved Private Address)";
            break;
        default:
            std::stringstream ss;
            ss << "Unknown address type " << _address_type << " (Reserved for future use)";
            _address_type_descriptor = ss.str();
            break;
    }


    // Now we need to assign the actual address
    std::stringstream bdaddress_stream;

    for (unsigned char bd_addres : bd_address) {
        _bd_address.push_back(bd_addres);
    }
    // Generate a string out of the assigned information
    for (int j = 0; j < _bd_address.size(); ++j) {
        if(j < _bd_address.size() - 1)
            bdaddress_stream << std::hex << std::uppercase << (int)_bd_address[j] << ":" << std::dec;
        else
            bdaddress_stream << std::hex << std::uppercase << (int)bd_address[j] << std::dec;
    }
    _bd_address_str = bdaddress_stream.str();

}




/// -- Getter --- ///
std::string BDAddress::addresstype_descriptor(){
    return _address_type_descriptor;
}

std::string BDAddress::address_tostring(){
    return _bd_address_str;
}

std::vector<uint8_t>  BDAddress::address(){
    return _bd_address;
}

int  BDAddress::addresstype(){
    return _address_type;
}