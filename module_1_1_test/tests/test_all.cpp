#include <cassert>
#include <cstdint>
#include <cstddef>

extern uint32_t set_field(uint32_t reg,
                           uint8_t bit_pos,
                           uint8_t bit_width,
                           uint32_t value);

extern uint32_t reverse_bits(uint32_t value);

struct SensorPacket {
    uint16_t device_id;
    uint32_t timestamp;
    int16_t temperature;
    uint16_t checksum;
};

extern bool parse_packet(const uint8_t* buf,
                         size_t len,
                         SensorPacket& out);

extern bool serialize_packet(uint8_t* buf,
                             size_t len,
                             SensorPacket& out);

extern uint32_t wait_for_flag_safe(volatile uint32_t* reg,
                                   uint32_t bit_mask);

extern uint32_t wait_for_flag_unsafe(uint32_t* reg,
                                     uint32_t bit_mask);

extern int getNextId();

class BitwiseTests {
public:
    static void run() {
        testSetField();
        testReverseBits();
    }

private:
    static void testSetField() {
        uint32_t reg = 0u;
        assert(set_field(reg, 0, 3, 5u) == 5u);

        reg = 0xFFFF0000u;
        assert(set_field(reg, 4, 4, 0xAu) == 0xFFFF00A0u);

        reg = 0xFFu;
        assert(set_field(reg, 0, 4, 1u) == 0xF1u);
    }

    static void testReverseBits() {
        assert(reverse_bits(0x00000001u) == 0x80000000u);
        assert(reverse_bits(0xF0000000u) == 0x0000000Fu);
        assert(reverse_bits(0x12345678u) == 0x1E6A2C48u);
    }
};

// Тест для const та constexpr не потрібен, я описав помилки у самому .cpp файлі

class EndiannessTests {
public:
    static void run() {
        testSerializeAndParse();
        testParseChecksumFailure();
    }

private:
    static void testSerializeAndParse() {
        SensorPacket packet{
            0xABCDu,
            0x12345678u,
            static_cast<int16_t>(2500),
            0u
        };

        uint8_t buffer[10] = {};
        assert(serialize_packet(buffer, sizeof(buffer), packet));

        SensorPacket parsed = {};
        assert(parse_packet(buffer, sizeof(buffer), parsed));

        uint16_t expected_checksum = static_cast<uint16_t>(packet.device_id + packet.timestamp + packet.temperature);
        assert(parsed.device_id == packet.device_id);
        assert(parsed.timestamp == packet.timestamp);
        assert(parsed.temperature == packet.temperature);
        assert(parsed.checksum == expected_checksum);
    }

    static void testParseChecksumFailure() {
        uint8_t bad_buffer[10] = {
            0x00, 0x01, // device_id = 1
            0x00, 0x00, 0x00, 0x02, // timestamp = 2
            0x00, 0x10, // temperature = 16
            0x12, 0x34  // incorrect checksum
        };

        SensorPacket parsed = {};
        assert(!parse_packet(bad_buffer, sizeof(bad_buffer), parsed));
    }
};

// для volatile не бачу сенсу робити тест, оскільки головна мета - порівняти .s файли

int main() {
    BitwiseTests::run();
    EndiannessTests::run();
    return 0;
}
