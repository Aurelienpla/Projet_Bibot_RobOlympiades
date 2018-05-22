#include <VirtualWire.h>

void setup()
{
  pinMode(2, INPUT_PULLUP);
  vw_setup(2000);
  vw_set_tx_pin(3);
}

void loop()
{
  if (digitalRead(2) == HIGH) {
    digitalWrite(9, HIGH);
    const char *msg = "Hello";
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx();
    delay(500);
    digitalWrite(9, LOW);
    while(digitalRead(2) == HIGH);
  }
}
