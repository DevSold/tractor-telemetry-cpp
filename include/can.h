#pragma once
#include <cstdint>
#include <vector>

namespace tractor {

struct CanFrame {
  std::uint32_t id;
  std::vector<std::uint8_t> data;
};

constexpr std::uint32_t CAN_ID_SENSOR_SAMPLE = 0x180; 
constexpr std::uint32_t CAN_ID_CMD_RESET     = 0x200;

} // namespace tractor
