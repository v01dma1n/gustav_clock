#include "gustav_app.h"
#include <ESP32NTPClock.h>

SemaphoreHandle_t serialMutex = NULL;
AppLogLevel g_appLogLevel = APP_LOG_INFO;
GustavClockApp& app = GustavClockApp::getInstance();

// Queue to signal the display task
QueueHandle_t displayTriggerQueue;

/**
 * @brief High-priority task to handle display multiplexing.
 *
 * This task is the *only* thing that calls the blocking writeDisplay()
 * function. It waits indefinitely for a trigger from the DisplayManager.
 */
void displayTask(void *pvParameters) {
  int dummy; // We just need a signal, the data doesn't matter
  GustavClockApp& app_ref = GustavClockApp::getInstance();

  for (;;) {
    // Wait indefinitely for a trigger
    if (xQueueReceive(displayTriggerQueue, &dummy, portMAX_DELAY)) {
      // Once triggered, call the app's blocking display function
      app_ref.getDisplay().writeDisplay();
    }
  }
}

void setup() {
  delay(300);
  Serial.begin(115200);
  unsigned long startTime = millis();
  while (!Serial && (millis() - startTime < 2000)) {
    ; // Wait for serial port to connect, with a 2-second timeout
  }
  Serial.println("\n>>> Starting Gustav VFD Clock...");
  
  serialMutex = xSemaphoreCreateMutex();

  // Create the trigger queue
  displayTriggerQueue = xQueueCreate(
    1,          // Queue depth of 1 (acts as a "mailbox")
    sizeof(int) // Simple integer trigger
  );

  if (displayTriggerQueue == NULL) {
    Serial.println("Error creating the display trigger queue");
    while (1); // Halt
  }

  // Run the original application setup
  app.setup();

  // Create the high-priority display task on Core 1
  xTaskCreatePinnedToCore(
      displayTask,      // Task function
      "DisplayTask",    // Name for debugging
      4096,             // Stack size
      NULL,             // Task input parameter
      10,               // Priority (high)
      NULL,             // Task handle
      1);               // Core ID

  Serial.println("\n>>> ... setup complete");
}

void loop() {
  // This remains unchanged. The app.loop() contains the FSM,
  // SceneManager, and DisplayManager updates.
  app.loop();
}