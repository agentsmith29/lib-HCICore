//
// Created by root on 25.03.20.
//

#ifndef HCICORE_GAPDATAFRAME_H
#define HCICORE_GAPDATAFRAME_H

#include <vector>
#include <cstdint>
#include <string>
namespace hcicore {

    /// --- FLAGS --- ///
    struct flag{
        uint8_t code;
        std::string description;
    };

    /// --- COMPLETE LIST OF 16 BIT SERVICE CLASS UUID --- ///
    struct complete_list_of_16_bit_service_class_uuid{
        std::string name;
        std::string uniform_type_identifier;
        uint16_t code;
    };




    class GAPDataFrame {
    public:
        ///----------------------------------------------------------------------------------------------------------///
        // --- CONSTRUCTOR --- ///
        ///----------------------------------------------------------------------------------------------------------///
        GAPDataFrame(std::vector<uint8_t> &raw_data);


        ///----------------------------------------------------------------------------------------------------------///
        /// --- GETTER --- ///
        ///----------------------------------------------------------------------------------------------------------///
        // Make sure to implement the parsing function before writing a getter!

        /// Getter: Return a reference to the flag field!
        /// \return A reference to the flag field
        flag &Flags(){
            return flags;
        };

        /// Getter: Returns a vector of complete_list_of_16_bit_service_class_uuid of 16 bit Service Class UUIDs
        /// \return std::vector<complete_list_of_16_bit_service_class_uuid> of 16 bit Service Class UUIDs
        std::vector<complete_list_of_16_bit_service_class_uuid> &CompleteListOf16BitServiceClassUuid() {
            return complete_list_of_16_bit_service_class_uuids;
        };

        /// Getter: Returns the Complete Local Name as a string
        /// \return string of Complete Local Name
        std::string CompleteLocalName() {
            return complete_local_name;
        };


    private:

        //std::stringstream _report_out;

        // The struct. It holds the code, a description and the pointer to the corresponding parsing function.
        // Get's populated in the assignVectorStructs function
        struct GAPCodeList{
            uint8_t datatype_value;
            std::string datatype_name;
            int (GAPDataFrame::*fun_ptr)(std::vector<uint8_t>&);
        };

        int assignVectorStructs(std::vector<GAPDataFrame::GAPCodeList> &gap_code_list);


        ///----------------------------------------------------------------------------------------------------------///
        /// --- MEMBER VARIABLES --- ///
        ///----------------------------------------------------------------------------------------------------------///
        // Holds the found flags of the dataframe
        flag flags;

        // Holds the found complete local name of the dataframe. Of no name was found it's set to unknown
        std::string complete_local_name = "unknown";

        // Holds a list of found 16-bit UUIDs
        std::vector<complete_list_of_16_bit_service_class_uuid> complete_list_of_16_bit_service_class_uuids;

        // TODO: The fields are missing
        // Since we many parsing functions are missing, these vector's aren't populated. Feel free to write a parsing
        // function and populate the vectors with the correct values
        std::vector<uint16_t> incomplete_list_of_16_bit_service_class_uuids;
        std::vector<uint32_t> incomplete_list_of_32_bit_service_class_uuids;
        std::vector<uint32_t> complete_list_of_32_bit_service_class_uuids;
        //std::vector<uint128_t> incomplete_list_of_128_bit_service_class_uuids;
        //std::vector<uint8_t> complete_list_of_128_bit_service_class_uuids;
        std::vector<uint8_t> shortened_local_name;
        std::vector<uint8_t> tx_power_level;
        std::vector<uint8_t> class_of_device;
        std::vector<uint8_t> simple_pairing_hash_c;
        std::vector<uint8_t> simple_pairing_randomizer_r;
        std::vector<uint8_t> device_id;
        std::vector<uint8_t> security_manager_tk_value;
        std::vector<uint8_t> security_manager_out_of_band_flags;
        std::vector<uint8_t> slave_connection_interval_range;
        std::vector<uint8_t> list_of_16_bit_service_solicitation_uuids;
        std::vector<uint8_t> list_of_128_bit_service_solicitation_uuids;
        std::vector<uint8_t> service_data;
        std::vector<uint8_t> public_target_address;
        std::vector<uint8_t> random_target_address;
        std::vector<uint8_t> appearance;
        std::vector<uint8_t> advertising_interval;
        std::vector<uint8_t> le_bluetooth_device_address;
        std::vector<uint8_t> le_role;
        std::vector<uint8_t> simple_pairing_hash_c_256;
        std::vector<uint8_t> simple_pairing_randomizer_r_256;
        std::vector<uint8_t> list_of_32_bit_service_solicitation_uuids;
        std::vector<uint8_t> service_data_32_bit_uuid;
        std::vector<uint8_t> service_data_128_bit_uuid;
        std::vector<uint8_t> le_secure_connections_confirmation_value;
        std::vector<uint8_t> le_secure_connections_random_value;
        std::vector<uint8_t> uri;
        std::vector<uint8_t> indoor_positioning;
        std::vector<uint8_t> transport_discovery_data;
        std::vector<uint8_t> le_supported_features;
        std::vector<uint8_t> channel_map_update_indication;
        std::vector<uint8_t> pb_adv;
        std::vector<uint8_t> mesh_message;
        std::vector<uint8_t> mesh_beacon;
        std::vector<uint8_t> biginfo;
        std::vector<uint8_t> broadcast_code;
        std::vector<uint8_t> three_d_information_data;
        std::vector<uint8_t> manufacturer_specific_data;



        ///----------------------------------------------------------------------------------------------------------///
        /// --- PARSING FUNCTIONS --- ///
        ///----------------------------------------------------------------------------------------------------------///
        // These functions are required for parsing. We are working woth function pointer.
        // How do you implement a new function?
        // First take a Function definition from the list (see 'Implement these') and write the corresponding
        // function. Now add the function to the list'gap_code_list' For this, replace the nullptr wit a pointer to the
        // correct function. The list get's automatically initilaized by invoking the function 'assignVectorStructs'

        // See: Supplement to Bluetooth Core Specification | CSS v9, Part A
        // 1.3 FLAGS (S. 12f)
        int parseFlags(std::vector<uint8_t> &data_holder);

        // See: Supplement to Bluetooth Core Specification | CSS v9, Part A
        // 1.2 LOCAL NAME (S. 11f)
        int parseCompleteLocalName(std::vector<uint8_t> &data_holder);

        // See: Supplement to Bluetooth Core Specification | CSS v9, Part A
        // 1.1 SERVICE UUID (S. 10f)
        int parseCompleteListof16bitServiceClassUUIDs(std::vector<uint8_t> &data_holder);


        // TODO: Implement these
        // These are function that are not implemented yet. Feel free to implement one of those
        int parseIncompleteListof16bitServiceClassUUIDs(std::vector<uint8_t> &data_holder);
        int parseIncompleteListof32bitServiceClassUUIDs(std::vector<uint8_t> &data_holder);
        int parseCompleteListof32bitServiceClassUUIDs(std::vector<uint8_t> &data_holder);
        int parseIncompleteListof128bitServiceClassUUIDs(std::vector<uint8_t> &data_holder);
        int parseCompleteListof128bitServiceClassUUIDs(std::vector<uint8_t> &data_holder);
        int parseShortenedLocalName(std::vector<uint8_t> &data_holder);
        int parseTxPowerLevel(std::vector<uint8_t> &data_holder);
        int parseClassofDevice(std::vector<uint8_t> &data_holder);
        int parseSimplePairingHashC(std::vector<uint8_t> &data_holder);
        int parseSimplePairingHashC192(std::vector<uint8_t> &data_holder);
        int parseSimplePairingRandomizerR(std::vector<uint8_t> &data_holder);
        int parseSimplePairingRandomizerR192(std::vector<uint8_t> &data_holder);
        int parseDeviceID(std::vector<uint8_t> &data_holder);
        int parseSecurityManagerTKValue(std::vector<uint8_t> &data_holder);
        int parseSecurityManagerOutofBandFlags(std::vector<uint8_t> &data_holder);
        int parseSlaveConnectionIntervalRange(std::vector<uint8_t> &data_holder);
        int parseListof16bitServiceSolicitationUUIDs(std::vector<uint8_t> &data_holder);
        int parseListof128bitServiceSolicitationUUIDs(std::vector<uint8_t> &data_holder);
        int parseServiceData(std::vector<uint8_t> &data_holder);
        int parseServiceData16bitUUID(std::vector<uint8_t> &data_holder);
        int parsePublicTargetAddress(std::vector<uint8_t> &data_holder);
        int parseRandomTargetAddress(std::vector<uint8_t> &data_holder);
        int parseAppearance(std::vector<uint8_t> &data_holder);
        int parseAdvertisingInterval(std::vector<uint8_t> &data_holder);
        int parseLEBluetoothDeviceAddress(std::vector<uint8_t> &data_holder);
        int parseLERole(std::vector<uint8_t> &data_holder);
        int parseSimplePairingHashC256(std::vector<uint8_t> &data_holder);
        int parseSimplePairingRandomizerR256(std::vector<uint8_t> &data_holder);
        int parseListof32bitServiceSolicitationUUIDs(std::vector<uint8_t> &data_holder);
        int parseServiceData32bitUUID(std::vector<uint8_t> &data_holder);
        int parseServiceData128bitUUID(std::vector<uint8_t> &data_holder);
        int parseLESecureConnectionsConfirmationValue(std::vector<uint8_t> &data_holder);
        int parseLESecureConnectionsRandomValue(std::vector<uint8_t> &data_holder);
        int parseURI(std::vector<uint8_t> &data_holder);
        int parseIndoorPositioning(std::vector<uint8_t> &data_holder);
        int parseTransportDiscoveryData(std::vector<uint8_t> &data_holder);
        int parseLESupportedFeatures(std::vector<uint8_t> &data_holder);
        int parseChannelMapUpdateIndication(std::vector<uint8_t> &data_holder);
        int parsePBADV(std::vector<uint8_t> &data_holder);
        int parseMeshMessage(std::vector<uint8_t> &data_holder);
        int parseMeshBeacon(std::vector<uint8_t> &data_holder);
        int parseBIGInfo(std::vector<uint8_t> &data_holder);
        int parseBroadcast_Code(std::vector<uint8_t> &data_holder);
        int parse3DInformationData(std::vector<uint8_t> &data_holder);
        int parseManufacturerSpecificData(std::vector<uint8_t> &data_holder);
    };
}
#endif //HCICORE_GAPDATAFRAME_H
