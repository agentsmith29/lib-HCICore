//
// Created by root on 26.02.20.
//

#ifndef HCICORE_BDADDRESS_H
#define HCICORE_BDADDRESS_H

#include "string"
#include <cstdint>
#include "list"
#include <vector>
#include <array>

static constexpr int PublicDeviceAddress = 0x00;
static constexpr int RandomDeviceAddress = 0x01;
static constexpr int PublicIdentityAddress = 0x02;
static constexpr int RandomStaticIdentityAddress = 0x03;

class BDAddress {

public:

    /// --- Constructors --- ///
    BDAddress(std::array<uint8_t, 6> bd_address, int address_type);

    explicit BDAddress(std::vector<uint8_t> &buffer);


    /// --- Getter --- ///
    /// Getter: Returns the adress as a list of uint8_t
    /// \return BD-Address
    std::vector<uint8_t> address();

    /// Getter: Returns the address as a string formatted as "00:00:00:00:00:00"
    /// \return Address string
    std::string address_tostring();

    /// Getter: Returns the address type as uint8_t 0x00
    /// \return Address-Type
    int addresstype();

    /// Getter: Returns the address descriptor, e. g. "Public Device Address (0x00)"
    /// \return Address-Descriptor
    std::string addresstype_descriptor();



private:
    /// --- Variables for raw information storage --- ///
    // Stores the raw address information, these are filled when calling the constructor
    // Holdes the 6 octets
    std::vector<uint8_t> _bd_address;
    // Holds the address type information
    int _address_type = 0x00;

    /// --- variable with descriptive purpose ---///
    // These variables do not contain now information, they just hold information which may be useful for printing
    // The string of the corresponding  list of octets (_bd_address)
    std::string _bd_address_str = "00:00:00:00:00:00";

    // The description of the corresponding address type (_address_type)
    std::string _address_type_descriptor = "Unknown Address Type";




};


#endif //HCICORE_BDADDRESS_H
