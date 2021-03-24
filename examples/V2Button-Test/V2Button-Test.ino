#include <V2Buttons.h>

static class Button : public V2Buttons::Button {
public:
  Button() : V2Buttons::Button(PIN_BUTTON) {}

private:
  void handleDown() override {
    Serial.println("down");
  }

  void handleUp() override {
    Serial.println("up");
    Serial.println("---");
  }

  void click(uint8_t count) override {
    Serial.print("clicks: ");
    Serial.println(count);
  }

  void hold(uint8_t count) override {
    Serial.print("long-press: ");
    Serial.println(count);
  }

  void release() override {
    Serial.println("released");
  }
} Button;

void setup() {
  Serial.begin(9600);
  Button.begin();
}

void loop() {
  V2Buttons::loop();
}
