# T-camera-Plus I2S Mic recording & save SDcard  
  
T-camera-Plus 개발보드의 MSM261S4030H0 MEMS 마이크 모듈 음성 녹음 및 SD카드 저장 예제입니다.  
  
<img src="https://raw.githubusercontent.com/eleparts/T-camera-Plus-I2S-Mic-SD/master/img/T-camera-Plus.jpg" width="50%"></img>

## Mic Schematic  
  
MSM261S4030H0 MEMS 마이크 모듈 GPIO  
  
|MSM261S4030H0|ESP32/I2S|
|-------------|---------|
|WS           |IO 32    |
|SD           |IO 33    |
|SCK          |IO 14    |

## SD card Schematic  

SD카드 GPIO  

|SDcard|ESP32/SPI|
|--------|-------|
|MISO    |IO 22  |
|MOSI    |IO 19  |
|SCLK    |IO 21  |
|CS      |IO 0   |

## Usage  

예제 실행 시 Start record 메시지 이후로 약 16초간 녹음됩니다.  
녹음된 파일은 SD카드에 track.pcm로 저장되며(PCM 데이터 파일), PC환경에서 재생을 해야하는 경우 컨버팅을 해 주어야 합니다.  

ffmpeg를 설치 후 아래 명령어로 wav파일로 변환 가능합니다.  
  
```
ffmpeg -f s32le -ar 16000 -ac 1 -i track.pcm track.wav
```
  
