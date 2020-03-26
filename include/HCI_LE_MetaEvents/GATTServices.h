//
// Created by root on 25.03.20.
//

#include <string>
#include <vector>

#ifndef HCICORE_GATTSERVICES_H
#define HCICORE_GATTSERVICES_H

namespace hcicore {
 // From https://www.bluetooth.com/specifications/gatt/services/
// 25.03.2020
        struct GattService {
            std::string name;
            std::string uniform_type_identifier;
            uint16_t code;
        };

        std::vector<GattService> gatt_services = {
            { "Generic Access", "org.bluetooth.service.generic_access", 0x1800 },
            { "Alert Notification Service", "org.bluetooth.service.alert_notification", 0x1811 },
            { "Automation IO", "org.bluetooth.service.automation_io", 0x1815 },
            { "Battery Service", "org.bluetooth.service.battery_service", 0x180F },
            { "Binary Sensor", "GATT Service UUID", 0x183B },
            { "Blood Pressure", "org.bluetooth.service.blood_pressure", 0x1810 },
            { "Body Composition", "org.bluetooth.service.body_composition", 0x181B },
            { "Bond Management Service", "org.bluetooth.service.bond_management", 0x181E },
            { "Continuous Glucose Monitoring", "org.bluetooth.service.continuous_glucose_monitoring", 0x181F },
            { "Current Time Service", "org.bluetooth.service.current_time", 0x1805 },
            { "Cycling Power", "org.bluetooth.service.cycling_power", 0x1818 },
            { "Cycling Speed and Cadence", "org.bluetooth.service.cycling_speed_and_cadence", 0x1816 },
            { "Device Information", "org.bluetooth.service.device_information", 0x180A },
            { "Emergency Configuration", "GATT Service UUID", 0x183C },
            { "Environmental Sensing", "org.bluetooth.service.environmental_sensing", 0x181A },
            { "Fitness Machine", "org.bluetooth.service.fitness_machine", 0x1826 },
            { "Generic Attribute", "org.bluetooth.service.generic_attribute", 0x1801 },
            { "Glucose", "org.bluetooth.service.glucose", 0x1808 },
            { "Health Thermometer", "org.bluetooth.service.health_thermometer", 0x1809 },
            { "Heart Rate", "org.bluetooth.service.heart_rate", 0x180D },
            { "HTTP Proxy", "org.bluetooth.service.http_proxy", 0x1823 },
            { "Human Interface Device", "org.bluetooth.service.human_interface_device", 0x1812 },
            { "Immediate Alert", "org.bluetooth.service.immediate_alert", 0x1802 },
            { "Indoor Positioning", "org.bluetooth.service.indoor_positioning", 0x1821 },
            { "Insulin Delivery", "org.bluetooth.service.insulin_delivery", 0x183A },
            { "Internet Protocol Support Service", "org.bluetooth.service.internet_protocol_support", 0x1820 },
            { "Link Loss", "org.bluetooth.service.link_loss", 0x1803 },
            { "Location and Navigation", "org.bluetooth.service.location_and_navigation", 0x1819 },
            { "Mesh Provisioning Service", "org.bluetooth.service.mesh_provisioning", 0x1827 },
            { "Mesh Proxy Service", "org.bluetooth.service.mesh_proxy", 0x1828 },
            { "Next DST Change Service", "org.bluetooth.service.next_dst_change", 0x1807 },
            { "Object Transfer Service", "org.bluetooth.service.object_transfer", 0x1825 },
            { "Phone Alert Status Service", "org.bluetooth.service.phone_alert_status", 0x180E },
            { "Pulse Oximeter Service", "org.bluetooth.service.pulse_oximeter", 0x1822 },
            { "Reconnection Configuration", "org.bluetooth.service.reconnection_configuration", 0x1829 },
            { "Reference Time Update Service", "org.bluetooth.service.reference_time_update", 0x1806 },
            { "Running Speed and Cadence", "org.bluetooth.service.running_speed_and_cadence", 0x1814 },
            { "Scan Parameters", "org.bluetooth.service.scan_parameters", 0x1813 },
            { "Transport Discovery", "org.bluetooth.service.transport_discovery", 0x1824 },
            { "Tx Power", "org.bluetooth.service.tx_power", 0x1804 },
            { "User Data", "org.bluetooth.service.user_data", 0x181C },
            { "Weight Scale", "org.bluetooth.service.weight_scale", 0x181D }
        };
}
#endif //HCICORE_GATTSERVICES_H
