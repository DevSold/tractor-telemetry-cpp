#include <gtest/gtest.h>
#include "state_machine.h"
#include "can.h"

using namespace tractor;

TEST(FSM, IdleToOperating) {
  Machine fsm;
  Sample s{}; s.speed_kph = 1.0;
  fsm.on_sample(s);
  EXPECT_EQ(fsm.state(), State::Operating);
}

TEST(FSM, OperatingToAlertByTemp) {
  Machine fsm(Thresholds{.max_coolant_c=90.0, .max_rpm=3000.0});
  Sample s{}; s.speed_kph = 2.0; fsm.on_sample(s);
  s.coolant_c = 95.0;
  fsm.on_sample(s);
  EXPECT_EQ(fsm.state(), State::Alert);
}
