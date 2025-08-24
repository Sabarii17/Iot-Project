#define SENSOR_PIN 8
#define LED_PIN 13

int clap = 0;
unsigned long detection_start = 0;
unsigned long last_detection = 0;
bool light_on = false;

void setup() {
  pinMode(SENSOR_PIN, INPUT);      // Sound sensor DO (active LOW on clap)
  pinMode(LED_PIN, OUTPUT);        // LED indicator
  digitalWrite(LED_PIN, LOW);      // Start with LED off
}

void loop() {
  int sound_detected = digitalRead(SENSOR_PIN);

  // Sensor outputs LOW on sound pulse
  if (sound_detected == LOW) {
    if (clap == 0) {
      detection_start = last_detection = millis();
      clap = 1;
    } else if (millis() - last_detection >= 50) {  // debounce gap
      last_detection = millis();
      clap++;
    }
  }

  // Evaluate window after 400 ms from first clap
  if (clap > 0 && millis() - detection_start >= 400) {
    if (clap == 2) {
      light_on = !light_on;
      digitalWrite(LED_PIN, light_on ? HIGH : LOW);
    }
    clap = 0;  // reset for next sequence
  }
}

