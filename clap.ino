#define SENSOR_PIN 8
#define RELAY_PIN 7
#define LED_PIN 13

int clap = 0;
long detection_start = 0;
long last_detection = 0;
bool light_on = false;

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Relay off
}

void loop() {
  int sound_detected = digitalRead(SENSOR_PIN);

  if (sound_detected == 0) { // Sound detected
    if (clap == 0) {
      detection_start = last_detection = millis();
      clap++;
    } else if (millis() - last_detection >= 50) {
      last_detection = millis();
      clap++;
    }
  }

  if (millis() - detection_start >= 400) {
    if (clap == 2) {
      light_on = !light_on;

      digitalWrite(LED_PIN, light_on ? HIGH : LOW);
      digitalWrite(RELAY_PIN, light_on ? LOW : HIGH); // LOW to turn relay ON
    }
    clap = 0; // Reset clap count
  }
}
