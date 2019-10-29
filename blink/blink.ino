bool state = true;
void setup() {
 pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
 digitalWrite(LED_BUILTIN, state);
 delay(500);
 state = !state;

}
