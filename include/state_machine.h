#pragma once
#include "sensors.h"
#include "can.h"

namespace tractor {

enum class State { Idle, Operating, Alert };

struct Thresholds {
  double max_coolant_c{105.0};
  double max_rpm{2200.0};
};

class Machine {
 public:
  explicit Machine(Thresholds t = {}) : t_(t) {}

  State state() const noexcept { return st_; }

  void on_can(const CanFrame& f) {
    if (f.id == CAN_ID_CMD_RESET) {
      st_ = State::Idle;
      stable_count_ = 0;
    }
  }

  void on_sample(const Sample& s) {
    const bool dangerous = (s.coolant_c > t_.max_coolant_c) || (s.rpm > t_.max_rpm);
    switch (st_) {
      case State::Idle:
        if (s.speed_kph > 0.5) st_ = State::Operating;
        break;
      case State::Operating:
        if (dangerous) { st_ = State::Alert; stable_count_ = 0; }
        break;
      case State::Alert:
        if (!dangerous) {
          if (++stable_count_ >= 3) { st_ = State::Operating; stable_count_ = 0; }
        } else {
          stable_count_ = 0;
        }
        break;
    }
  }

 private:
  State st_{State::Idle};
  Thresholds t_{};
  int stable_count_{0};
};

} // namespace tractor
