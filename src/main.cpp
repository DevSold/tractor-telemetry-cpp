#include "can.h"
#include "sensors.h"
#include "state_machine.h"
#include <iomanip>
#include <iostream>

using namespace tractor;

int main() {
  SensorSimulator sim;
  Machine fsm(
      Thresholds{.max_coolant_c = 100.0,
                 .max_rpm = 2100.0}); 

  std::cout << "Tractor Telemetry (sim)\n";
  for (int i = 0; i < 20; ++i) {
    auto s = sim.next();
    fsm.on_sample(s);

    std::cout << std::fixed << std::setprecision(1) << "Step " << i
              << " | v=" << s.speed_kph << " kph"
              << " rpm=" << s.rpm << " temp=" << s.coolant_c << " C"
              << " | state="
              << (fsm.state() == State::Idle        ? "Idle"
                  : fsm.state() == State::Operating ? "Operating"
                                                    : "Alert")
              << "\n";

    if (i == 5) {
      fsm.on_can(CanFrame{CAN_ID_CMD_RESET, {}});
      std::cout << "CAN: RESET -> Idle\n";
    }
  }
  return 0;
}
