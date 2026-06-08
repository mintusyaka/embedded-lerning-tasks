#include "big_endian_rw.hpp"

struct SensorPacket {
    uint16_t device_id;    // bytes [0:1], big-endian
    uint32_t timestamp;    // bytes [2:5], big-endian
    int16_t  temperature;  // bytes [6:7], big-endian, одиниці: 0.01°C
    uint16_t checksum;     // bytes [8:9], big-endian
};

bool parse_packet(const uint8_t* buf,
                  size_t len,
                  SensorPacket& out) {
    if (len < 10)
        return false; // недостатньо даних для повного пакету
    uint16_t final_checksum = 0;
    
    uint16_t device_id = be::read_be<uint16_t>(buf, (size_t)0);
    uint32_t timestamp = be::read_be<uint32_t>(buf, (size_t)2);
    int16_t temperature = be::read_be<int16_t>(buf, (size_t)6);
    uint16_t checksum = be::read_be<uint16_t>(buf, (size_t)8);

    final_checksum = device_id + timestamp + temperature; // простий контрольний сум
    if (final_checksum != checksum)
        return false; // контрольний сум не збігається

    out.device_id = device_id;
    out.timestamp = timestamp;
    out.temperature = temperature;
    out.checksum = checksum;

    return true;
}


bool serialize_packet(uint8_t* buf,
                  size_t len,
                  SensorPacket& out) {
    if (len < 10)
        return false; // недостатньо місця для запису повного пакету
    uint16_t final_checksum = out.device_id + out.timestamp + out.temperature; // простий контрольний сум
    be::write_be<uint16_t>(buf, (size_t)0, out.device_id);
    be::write_be<uint32_t>(buf, (size_t)2, out.timestamp);
    be::write_be<int16_t>(buf, (size_t)6, out.temperature);
    be::write_be<uint16_t>(buf, (size_t)8, final_checksum);

    return true;
}