cmake_minimum_required(VERSION 3.15)
project(hcicore)

set(CMAKE_CXX_STANDARD 14)
#SET(CMAKE_CXX_FLAGS  "-Wall")
#include_directories(bluez/lib)
#include_directories(bluez/ell)
#include_directories(bluez)
include_directories(/usr/include/glib-2.0)
include_directories(/usr/lib/x86_64-linux-gnu/glib-2.0/include)
include_directories(/usr/lib/dbus-1.0/)
include_directories(/usr/include/dbus-1.0/)
include_directories(/usr/lib/dbus-1.0/include)

include_directories(/usr/lib/)
include_directories(/usr/include/dbus-1.0/)
include_directories(/usr/lib/x86_64-linux-gnu/dbus-1.0/include)
include_directories(/usr/include/glib-2.0)
include_directories(/usr/lib/x86_64-linux-gnu/glib-2.0/include/)



include_directories(bluez)
include_directories(bluez/lib)
include_directories(spdlog/include)

set(BLUETOOT_SRC
        bluez/lib/bluetooth.c
        bluez/lib/bluetooth.h
        bluez/lib/hci.c
        bluez/lib/hci.h src/BDAddress.cpp src/HCI_LE_MetaEvents/HCI_LE_AdvertisingReportEvent.cpp include/HCI_LE_MetaEvents/HCI_LE_AdvertisingReportEvent.h include/HCI_LE_MetaEvents/GAPCodesList.h src/HCI_LE_MetaEvents/GAPDataFrame.cpp include/HCI_LE_MetaEvents/GAPDataFrame.h include/HCI_LE_MetaEvents/GATTServices.h)

add_executable(hcicore
        include/BLEScan.h
        src/BLEScan.cpp
        main.cpp
        ${BLUETOOT_SRC}
        src/HCI_LE_MetaEvents/LEMetaEvent.cpp include/HCI_LE_MetaEvents/LEMetaEvent.h)

target_include_directories(hcicore PRIVATE ${GLIB_INCLUDE_DIRS})
target_link_libraries(hcicore ${GLIB_LDFLAGS} ${LIB_DBUS_1} ${LIB_READLINE})


#add_executable(hcicore
#        src/BLEScan.cpp
#        include/BLEScan.h
#        main.cpp)
#
#