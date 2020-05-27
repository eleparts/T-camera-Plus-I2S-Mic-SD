# T-camera-Plus I2S Mic recording & save SDcard  
  
T-camera-Plus 개발보드의 MSM261S4030H0 MEMS 마이크 모듈 음성 녹음 및 SD카드 저장 예제입니다.  
  
## Mic Schematic  
  
MSM261S4030H0 MEMS 마이크 모듈  
  
|MSM261S4030H0|ESP32/I2S|
|-------------|---------|
|WS           |IO25     |
|SD           |IO22     |
|SCK          |IO26     |

## SD card Schematic  

SD카드  

|SDcard|ESP32/SPI|
|--------|-------|
|MISO    |IO22   |
|MOSI    |IO19   |
|SCLK    |IO21   |
|CS      |IO0    |

## Usage  

저장된 파일은 SC카드에 track.pcm로 저장되며, PC환경에서 재생을 해야하는 경우 별도로 컨버팅을 해 주어야 합니다.  

ffmpeg를 설치 후 아래 명령어로 wav파일로 변환 가능합니다.  
  
```
ffmpeg -f s32le -ar 16000 -ac 1 -i track.pcm track.wav
```
  
