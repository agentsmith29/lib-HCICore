//
// Created by developer on 13.02.20.
//
#include <iostream>
#include "include/BLEScan.h"

int main() {
    hcicore::BLEScan ble_scan = hcicore::BLEScan();

    ble_scan.setupScan();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

