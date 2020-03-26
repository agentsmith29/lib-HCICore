//
// Created by developer on 13.02.20.
//

#ifndef LIB_HCICORE_BLESCAN_H
#define LIB_HCICORE_BLESCAN_H

#include <string>
#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <netinet/in.h>
#include <memory>

#include "lib/bluetooth.h"
#include "lib/hci.h"
#include "lib/hci_lib.h"


#include "spdlog/spdlog.h"
#include "spdlog/async.h"
// import the sinks
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h" // support for basic file logging
#include "spdlog/sinks/daily_file_sink.h" // support for daily file logging

namespace hcicore {
    class BLEScan {


    public:
       // BLEScan();


        int setupScan();
        int createLogger();

        ~BLEScan();
    private:



        int _device_id = 0;

        int _device_descriptor = 0;

        std::string _logger_name = "Generic Logger";

        std::shared_ptr<spdlog::logger> _logger;

        int print_advertising_devices(int dd, uint8_t filter_type);

        static void sigint_handler(int sig);

        static void ouch(int sig);

        uint8_t _own_type = LE_PUBLIC_ADDRESS;
        uint8_t _scan_type = 0x01; // TODO: Meaning of this values? (From bluez, hcitool.c)
        uint8_t _filter_type = 0;  // TODO: Meaning of this values? (From bluez, hcitool.c)
        uint8_t _filter_policy = 0x00;  // TODO: Meaning of this values? (From bluez, hcitool.c)
        uint16_t _interval = htobs(0x0010);  // TODO: Meaning of this values? (From bluez, hcitool.c)
        uint16_t _window = htobs(0x0010);  // TODO: Meaning of this values? (From bluez, hcitool.c)
        uint8_t _filter_dup = 0x00; // TODO: Meaning of this values? (From bluez, hcitool.c)

    };
}

#endif //LIB_HCICORE_BLESCAN_H
