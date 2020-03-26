//
// Created by developer on 13.02.20.
//

#include "../include/BLEScan.h"



#include <string>
#include <memory>
#include <exception>
// Files for Logging

#include <csignal>

#include "../include/HCI_LE_MetaEvents/LEMetaEvent.h"
#include "../include/HCI_LE_MetaEvents/HCI_LE_AdvertisingReportEvent.h"
#include "../include/HCI_LE_MetaEvents/GAPDataFrame.h"

using namespace hcicore;
using std::exception;
using std::cout;
using std::endl;

volatile int signal_received = 0;

int BLEScan::createLogger(){

    _logger_name = "LE Scan " + std::to_string(_device_id);
    // Create the logger
    try {
        // Creating loggers with multiple sinks
        // see: https://github.com/gabime/spdlog/wiki/2.-Creating-loggers
        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_mt>("/tmp/serverlog.txt", 23, 59));
        _logger = std::make_shared<spdlog::logger>(_logger_name, begin(sinks), end(sinks));
        //register it if you need to access it globally
        spdlog::register_logger(_logger);
        _logger->set_level(spdlog::level::debug); // Set global log level to debug
        spdlog::set_pattern("[%H:%M:%S] [%n] [%^%l%$] %v");
    }
    catch(exception &ex){
        cout << ex.what() << endl;
    }
    return 0;
}

int BLEScan::setupScan() {
    createLogger();

    if (geteuid()) {
        _logger->error("Checking root permission failed. Did you run the program as root?");
        return -1;
    }
    else {
        _logger->debug("You are root! Continue now!");
    }






    // First open the device (raw socket)
    _device_descriptor = hci_open_dev(_device_id);
    _logger->info("Opening device {0}", _device_id);
    if (_device_descriptor < 0) {
        _logger->error("Could not open device {0}: {1}. Code {2}", _device_id,  strerror(errno), errno);
        return -1;
    }



    int err = hci_le_set_scan_parameters(_device_descriptor, _scan_type, _interval, _window,
                                         _own_type, _filter_policy, 10000);
    _logger->info("Setting scan parameter of device {0}.", _device_id);
    if (err < 0) {
        _logger->error("Set scan parameters failed in device {0}: {1}. Code {2}", _device_id,  strerror(errno), errno);
        return -2;
    }

    _logger->info("Enabeling scan of device {0}.", _device_id);
    err = hci_le_set_scan_enable(_device_descriptor, 0x01, _filter_dup, 10000);
    if (err < 0) {
        _logger->error("Enabling scan on device {0} failed: {1}. Code {2}", _device_id,  strerror(errno), errno);
        return -3;
    }

    err = print_advertising_devices(_device_descriptor, _filter_type);
    if (err < 0) {
        _logger->error("Could not receive advertising events on device {0} failed: {1}. Code {2}", _device_id,  strerror(errno), errno);
        return -1;
    }

    err = print_advertising_devices(_device_descriptor, _filter_type);
    if (err < 0) {
        _logger->error("Could not receive advertising events.");
        exit(1);
    }
    return 0;

}

void BLEScan::sigint_handler(int sig)
{
    signal_received = sig;
}

void BLEScan::ouch(int sig) {
    signal_received = sig;
}

int BLEScan::print_advertising_devices(int dd, uint8_t filter_type)
{
    unsigned char buf[HCI_MAX_EVENT_SIZE], *ptr;
    struct hci_filter nf, of;
    struct sigaction sa;
    socklen_t olen;
    int len;

    struct sigaction act;
    act.sa_handler = ouch;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGSEGV, &act, 0);

    olen = sizeof(of);
    if (getsockopt(dd, SOL_HCI, HCI_FILTER, &of, &olen) < 0) {
        _logger->error("Could not get socket options.");
        return -1;
    } else
        _logger->debug("Get socket options.");

    hci_filter_clear(&nf);
    hci_filter_set_ptype(HCI_EVENT_PKT, &nf);
    hci_filter_set_event(EVT_LE_META_EVENT, &nf);

    if (setsockopt(dd, SOL_HCI, HCI_FILTER, &nf, sizeof(nf)) < 0) {
        _logger->error("Could not set socket options.");
        return -2;
    }else
        _logger->debug("Set socket options.");

    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_NOCLDSTOP;
    sa.sa_handler = sigint_handler;
    sigaction(SIGINT, &sa, NULL);


    _logger->info("Start retrieving devices.");

    int i = 0;
    while (i < 10) {
       // i++;
        evt_le_meta_event *meta;
        le_advertising_info *info;
        char addr[18];

        while ((len = read(dd, buf, sizeof(buf))) < 0) {
            if (errno == EINTR && signal_received == SIGINT) {
                _logger->debug("Error or signal received: {0}. Code: {1}", strerror(errno), errno);
                len = 0;
                setsockopt(dd, SOL_HCI, HCI_FILTER, &of, sizeof(of));

                if (len < 0)
                    return -1;

                return 0;
            }

            if (errno == EAGAIN || errno == EINTR)
                continue;


            setsockopt(dd, SOL_HCI, HCI_FILTER, &of, sizeof(of));
            if (len < 0)
                return -1;
            return 0;
        }
        ptr = buf + (1 + HCI_EVENT_HDR_SIZE);
        len -= (1 + HCI_EVENT_HDR_SIZE);


        if(ptr[0] == 0x02) {
            HCI_LE_AdvertisingReportEvent advertising_report_event = HCI_LE_AdvertisingReportEvent(ptr, len);

            std::stringstream ss;

            std::vector<AdvertisingReport> adv_reports = advertising_report_event.Report();

            for (int j = 0; j < adv_reports.size(); ++j) {
                ss << std::endl
                   << "\t EVENT TYPE: 0x" << std::hex << (int) adv_reports[j].eventType.code << std::dec
                   << " (" << adv_reports[j].eventType.descripton << ")";

                ss << std::endl
                   << "\t [" << j << "] ADDRESS: "
                   << adv_reports[j].address.address_tostring() << std::dec
                   << " (" << adv_reports[j].address.addresstype_descriptor() << ")";

                ss << std::endl
                   << "\t [" << j << "] NAME: "<< adv_reports[j].data.CompleteLocalName();

                if(adv_reports[j].data.CompleteListOf16BitServiceClassUuid().size() > 0) {
                    ss  << std::endl
                        << "\t [" << j << "] 16 Bit UUID: ";

                    // Display the UUIDs
                    for (int k = 0; k < adv_reports[j].data.CompleteListOf16BitServiceClassUuid().size(); ++k) {

                        ss << std::endl
                           << "\t\t [" << k << "] 0x"
                           << std::uppercase << std::hex
                           << adv_reports[j].data.CompleteListOf16BitServiceClassUuid()[k].code << std::dec
                           << " ("
                           << adv_reports[j].data.CompleteListOf16BitServiceClassUuid()[k].uniform_type_identifier
                           << ")" ;
                    }
                }
            }
            _logger->info(ss.str());

        }
        else{
            _logger->info("Got event code {0}. Exiting.", ptr[0]);
        }


        //ptr = buf + (1 + HCI_EVENT_HDR_SIZE);
        //len -= (1 + HCI_EVENT_HDR_SIZE);

         meta = (evt_le_meta_event *) ptr;
         // printf("%s %s\n", ptr);

        if (meta->subevent != 0x02) {
            _logger->info("NO LE Meta Subevent 0x02 received. Exiting.");
            setsockopt(dd, SOL_HCI, HCI_FILTER, &of, sizeof(of));

            if (len < 0)
                return -1;

            return 0;
        }

        /*
        // Ignoring multiple reports //
        info = (le_advertising_info *) (meta->data + 1);
        //if (check_report_filter(filter_type, info)) {
            //char name[30];

            //memset(name, 0, sizeof(name));

            ba2str(&info->bdaddr, addr);

        _logger->info("ADDR: {0}", addr);
        //}
        //break;
         */
    }

    return 0;
}





BLEScan::~BLEScan(){

    _logger->debug("Disabling scan on device {0}", _device_id);
    int err = hci_le_set_scan_enable(_device_descriptor, 0x00, _filter_dup, 10000);
    if (err < 0) {
        _logger->error("Disable scan failed on device {0} failed: {1}. Code {2}", _device_id,  strerror(errno), errno);
    }



    hci_close_dev(_device_descriptor);
    _logger->info("Device {0} closed", _device_id);
}