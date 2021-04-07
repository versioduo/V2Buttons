#pragma once

#include <Arduino.h>

class V2Buttons {
public:
  // No config or zero values will not count clicks and not detect long-presses.
  struct Config {
    // Time to wait count multiple clicks, usually ~150 milliseconds.
    unsigned long click_usec;

    // Time to detect a long-press, usually ~300 milliseconds.
    unsigned long hold_usec;
  };

  class Button {
  public:
    constexpr Button(const Config *config, uint8_t pin, bool high = false) : _config(config), _pin(pin), _high{high} {}

    void begin();
    bool loop();

  protected:
    virtual void handleDown() {}
    virtual void handleUp() {}

    // The button was pressed and is released, a click; 'count' indicates the
    // number of clicks immedeately before. A single click is 0, double-click
    // is 1.
    virtual void handleClick(uint8_t count) {}

    // The button is pressed and held, a long-press; 'count' indicates the
    // number of clicks immedeately before. Just pressing and holding the button
    // is 0.
    virtual void handleHold(uint8_t count) {}
    virtual void handleRelease() {}

    // Return event number to match Down/Up/Click/Hold/Release calls.
    uint32_t getEvent() {
      return _event;
    }

  private:
    friend class V2Buttons;
    const Config *_config;
    const uint8_t _pin;
    bool _high;
    Button *_next{};
    enum class State { Idle, WaitDown, Down, Hold, Up, Reset } _state{State::Idle};
    uint8_t _clicks{};
    unsigned long _usec{};

    // Event number assigned when we wake up from idle. All calls for the same
    // sequence will have the same event number.
    uint32_t _event{};

    // Are we processing or wait for a new interrupt.
    bool _busy{};
  };

  // Check all registered buttons.
  //
  // The pins of the buttons needs to support external interrupts to trigger
  // the measurement.
  static void loop();
};
