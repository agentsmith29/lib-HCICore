//
// Created by root on 25.03.20.
//

#include "LEMetaEvent.h"

#include "../../include/HCI_LE_MetaEvents/GAPDataFrame.h"

#ifndef HCICORE_HCI_LE_ADVERTISINGREPORTEVENT_H
#define HCICORE_HCI_LE_ADVERTISINGREPORTEVENT_H

namespace hcicore {
    ///--------------------------------------------------------------------------------------------------------------///
    /// --- GLOBAL STRUCTS ---///
    ///--------------------------------------------------------------------------------------------------------------///
    // A struct for storing the code and the descriptionf of the subevent
    struct subeventCode{
        uint8_t code;
        std::string descripton;
    } ;
    typedef struct subeventCode SubeventCode;

    // A struct for storing the code and the description of the subevent
    struct eventType{
        uint8_t code;
        std::string descripton;
    } ;
    typedef struct eventType EventType;

    // A struct for the whole AdvertisingReport
    struct report{
        EventType eventType;
        BDAddress address;
        GAPDataFrame data;
    };
    typedef struct report AdvertisingReport;



    ///--------------------------------------------------------------------------------------------------------------///
    /// --- CLASS HCI_LE_AdvertisingReportEvent ---///
    ///--------------------------------------------------------------------------------------------------------------///
    class HCI_LE_AdvertisingReportEvent : LEMetaEvent {
        // See BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 4, Part E
        // 7.7.65.2 LE Advertising Report event
        // S. 2382f. 26.02.2020
    public:



        HCI_LE_AdvertisingReportEvent(unsigned char buf[260], int buf_len);

        std::string eventTypeDescription();

        // Return the Name (if found) of the current AdvertisingReport
        std::string address();

        // Return the Name (if found) of the current AdvertisingReport
        std::string name();

        ///----------------------------------------------------------------------------------------------------------///
        /// --- GETTER --- ///
        ///----------------------------------------------------------------------------------------------------------///

        std::vector<AdvertisingReport> Report(){
            return _reports;
        }

        /// Getter: Return the Subevent Code of the given Advertising Report
        /// First: Code, Second: Description
        /// \return
        /*
        std::pair<uint8_t, std::string> &SubeventCode() {
            return _subevent_code;
        };
        */
        /// Getter: Return the number of Report
        /// \return Integer, returns the number of reports
        int NumberOfReports() {
            return _num_reports;
        };

        /// Getter: Returns the Event Type of the response, selected by parameter 'selector'
        /// \param selector Select the desired response
        /// \return
        /*
        std::pair<uint8_t, std::string> EventType(unsigned int selector) {
            if(selector >= _event_types.size() || selector < 0)
                throw std::out_of_range("Index out of bounds.");

            return _event_types[0];
        }
        */

        /// Getter: Returns the current BD Address of the response, selected by parameter 'selector'
        /// \param selector Select the desired response
        /// \return
        BDAddress &Address(unsigned int selector){
            if(selector >= _event_types.size() || selector < 0)
                throw std::out_of_range("Index out of bounds.");

            return _bd_address[selector];
        };

        /// Getter: Returns the current dataframe of the response, selected by parameter 'selector'
        /// \param selector Select the desired response
        /// \return
       /* GAPDataFrame gapDataFrame(unsigned int selector){
            if(selector >= _event_types.size() || selector < 0)
                throw std::out_of_range("Index out of bounds.");

            return _gap_dataframes[selector];
        }*/




    private:


        int selector = 0;

        // SUBEVENT CODE
        ///
        /// \param buf
        /// \return
        int assignSubeventCode(uint8_t &buf);
        subeventCode _subevent_code;

        // NUMBER OF REPORTS
        ///
        /// \param buf
        /// \return
        int assignTotalNumberOfReports(uint8_t &buf);
        int _num_reports = 0;


        /// Assigns the Event Type
        /// \param buf
        /// \return position of the next frame
        int assignEventTypes(uint8_t *buf);
        std::vector<eventType> _event_types;                  // Array


        /// Assigns the address and the type to the vector _bd_address
        /// \param buf
        /// \return position of the next frame
        int assignAddress(uint8_t *buf);
        std::vector<BDAddress> _bd_address;                 // array


        /// Assigns the length of the following dataframes
        /// \param buf
        /// \return position of the next frame
        int assignDataLength(uint8_t *buf);
        std::vector<int> _data_length;                     // Array


        ///
        /// \param buf
        /// \return
        int assignRawData(uint8_t *buf);
        std::vector<std::vector<uint8_t>> _raw_data;           // Array


        /// Take the data from _raw_data and creates a splitted dataframe
        /// from this.
        /// \return
        int parseDataframe();
        std::vector<GAPDataFrame> _gap_dataframes;


        ///
        /// \param buf
        /// \return
        int assignRSSI(uint8_t *buf) = delete;
        std::vector<uint8_t> _rssi;                        // Array

        std::vector<AdvertisingReport> _reports;                        // Array

        int createFinalReport();

        //std::stringstream _report_out;
    };

}

#endif //HCICORE_HCI_LE_ADVERTISINGREPORTEVENT_H
