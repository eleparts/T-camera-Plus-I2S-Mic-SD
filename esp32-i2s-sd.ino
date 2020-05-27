#include <SD.h>
#include <SPI.h>
#include <driver/gpio.h>
#include <driver/i2s.h>

#define SPI_MOSI_PIN 19
#define SPI_MISO_PIN 22
#define SPI_SCLK_PIN 21
#define SD_CS 0

#define MIC_SCK 14 // LCLK
#define MIC_WS  32 // SCLK
#define MIC_SD  33 // DOUT

static const int bytesToRead = 1024 * 1000;
File f;

void setup()
{
	Serial.begin(115200);
  SPI.begin(SPI_SCLK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN);

	i2s_config_t i2s_config;
	i2s_config.mode = (i2s_mode_t) (I2S_MODE_MASTER | I2S_MODE_RX);
	i2s_config.sample_rate = 16000;
	i2s_config.bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT;
	i2s_config.channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT;
	i2s_config.communication_format = (i2s_comm_format_t) (I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB);
	i2s_config.dma_buf_count = 32;
	i2s_config.dma_buf_len = 32 * 2;
	i2s_config.intr_alloc_flags = ESP_INTR_FLAG_LEVEL1;

	i2s_pin_config_t pin_config;
	pin_config.bck_io_num = MIC_SCK;
	pin_config.ws_io_num = MIC_WS;
	pin_config.data_out_num = I2S_PIN_NO_CHANGE;
	pin_config.data_in_num = MIC_SD;

	i2s_driver_install(I2S_NUM_1, &i2s_config, 0, NULL);
	i2s_set_pin(I2S_NUM_1, &pin_config);
	i2s_stop(I2S_NUM_1);

	i2s_start(I2S_NUM_1);

  if(!SD.begin(SD_CS)){
    Serial.println("SD init Fail");  
    return;
  }
  
  Serial.println("SD init Success");
  f = SD.open("/track.pcm", FILE_WRITE);
  // PCM file 
  // ffmpeg -f s32le -ar 16000 -ac 1 -i track.pcm track.wav
  
  Serial.println("file OPEN, Start record (16s)");
}

void loop()
{
	static int totalBytesRead = 0;
	if (totalBytesRead >= bytesToRead) {
		return;
	}
	uint8_t buf[64];
	memset(buf, 0, 64);
	int bytes_read = 0;  
	while(bytes_read == 0) {
		bytes_read = i2s_read_bytes(I2S_NUM_1, (char*) buf, 64, 0);
	}
	f.write(buf, 64);
	totalBytesRead += 64;
	if (totalBytesRead >= bytesToRead) {
		f.close();
		Serial.println("DONE WRITING");
		return;
	}
}
