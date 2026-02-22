#include "IP-tm-stepmotor.h"

SuperStepper::SuperStepper(uint8_t stepPin, uint8_t dirPin) {
  _stepPin = stepPin;
  _dirPin = dirPin;

  pinMode(_stepPin, OUTPUT);
  pinMode(_dirPin, OUTPUT);
}

void SuperStepper::stepPulse(int delayUs) {
  digitalWrite(_stepPin, HIGH);
  delayMicroseconds(delayUs);
  digitalWrite(_stepPin, LOW);
  delayMicroseconds(delayUs);
}

// EASY
void SuperStepper::run(long distance, Dir direction) {
  run(distance, STEPS, direction, 500);
}

// PRO
void SuperStepper::run(long distance, Unit unit, Dir direction, int pulseUs) {

  digitalWrite(_dirPin, direction == CW);

  long steps = distance;

  if (unit == CM)
    steps = distance * _stepsPerCM;

  for (long i = 0; i < steps; i++) {
    stepPulse(pulseUs);
    _position++;
    if (_position >= _maxPos) break;
  }
}

// EXPERT
void SuperStepper::run(long distance, Unit unit, Dir direction,
                       int pulseUs, bool enable, bool sleep) {

  // enable/sleep placeholder (user can expand with pins)

  run(distance, unit, direction, pulseUs);
}

// Calibration
void SuperStepper::setStepsPerCM(float value) {
  _stepsPerCM = value;
}

void SuperStepper::setZero() {
  _position = 0;
}

void SuperStepper::setMaxPosition(long pos) {
  _maxPos = pos;
}
