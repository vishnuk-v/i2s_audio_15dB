#include <Arduino.h>
#include <SPIFFS.h>
#include "WAVFileReader.h"
#include "SinWaveGenerator.h"
#include "I2SOutput.h"

// i2s pins
i2s_pin_config_t i2sPins = {
    .bck_io_num = GPIO_NUM_5,
    .ws_io_num = GPIO_NUM_4,
    .data_out_num = GPIO_NUM_15,
  
    .data_in_num = -1};

I2SOutput *output;
SampleSource *sampleSource;

void setup()
{
  Serial.begin(115200);

  Serial.println("Starting up");

  SPIFFS.begin();

  Serial.println("Created sample source");
  
  delay(2000);

  // sampleSource = new SinWaveGenerator(40000, 10000, 0.75);

  sampleSource = new WAVFileReader("/food_ready_16k.wav");

  Serial.println("Starting I2S Output");
  output = new I2SOutput();
  output->start(I2S_NUM_1, i2sPins, sampleSource);
}

void loop()
{
  // nothing to do here - everything is taken care of by tasks
  SPIFFS.remove("/food_ready.wav");
}