# SSD Team Project - Double Checker Team

## 📖 프로젝트 개요
가상 SSD 디바이스를 소프트웨어로 구현하고, 이를 검증하기 위한 **Test Shell** 및 **Script Runner** 프로젝트입니다.  
- **SSDInterface**: SSD 동작 인터페이스
    * **MockSSD**: 메모리 기반 더블(Mock) SSD
    * **RealSSD**: 외부 `ssd.exe` 호출을 통한 실제 SSD 시뮬레이션
- **TestShell**: 대화형 커맨드 셸 (write/read/help/exit/fullwrite/fullread + Test Script)  
- **ScriptRunner**: 스크립트(.txt)를 받아 TestScript1~4를 자동 실행

TDD(Test-Driven Development) 방식으로 구현되었으며, GoogleTest/GMock 단위 테스트가 포함되어 있습니다.

## ⚙️ 개발 환경 및 요구사항
- **언어**: C++17
- **빌드 도구**: Visual Studio 2022
- **테스트 프레임워크**: GoogleTest & GoogleMock

## 🚀 주요 기능 (Features)

- **Interactive Test Shell**  
  SSD 동작을 하나씩 실행해 보고 결과를 즉시 확인할 수 있는 대화형 셸

- **Script Runner**  
  미리 작성한 `.txt` 스크립트 파일을 인자로 전달하면  
  각 명령을 순차적으로 자동 실행하고 “Run…Pass/FAIL!” 을 실시간 출력

- **Logger**  
  수행된 모든 명령과 결과를 별도 로그 파일에 기록

- **Command Buffer & Flush**  
  여러 명령을 버퍼에 쌓아 두었다가 `flush` 명령으로 한꺼번에 커밋


## 🔧 지원 명령어 리스트

- `write [LBA] [VALUE]`  
  지정된 LBA에 0x00000000~0xFFFFFFFF 값을 기록

- `read [LBA]`  
  지정된 LBA에서 값을 읽어 화면/출력 파일에 표시

- `erase [LBA]`  
  단일 LBA를 초기값(0x00000000)으로 지움

- `erase_range [START_LBA] [SIZE]`  
  START_LBA부터 SIZE 개수만큼 연속된 LBA를 초기값으로 지움

- `flush`  
  내부에 버퍼링된 모든 `write`/`erase` 명령을 실제 SSD에 커밋

- `fullwrite [VALUE]`  
  LBA 0~99 전체에 동일한 VALUE를 기록

- `fullread`  
  LBA 0~99 전체를 차례로 읽어 화면에 출력

- `help`  
  제작자 정보 및 모든 명령어 사용 방법 출력

- `exit`  
  Test Shell 종료

- **Test Script 명령**  
  - `1_FullWriteAndReadCompare` (또는 `1_`)  
  - `2_PartialLBAWrite` (또는 `2_`)  
  - `3_WriteReadAging` (또는 `3_`)  
  - `4_EraseAndWriteAging` (또는 `4_`)

## 🛠️ 추가 기능

- **Logger**:  
  로그 파일에 명령어, 실행 시간, 결과 상태(Pass/Fail) 등을 기록

- **Runner**:  
  `.txt` 스크립트만으로 반복 테스트 자동화 지원

- **Command Buffer**:  
  `write`/`erase` 명령을 메모리 버퍼에 보관하고,  
  `flush` 명령 시점에만 실제 SSD(`ssd_nand.txt`)에 반영하여 성능 최적화  



## 🚀 사용법

### 실행 파일 배치

`Shell.exe` 와 `SSD.exe` 를 **동일한 디렉토리**에 복사하세요.

### Interactive 모드

터미널(또는 커맨드 프롬프트)에서 Shell.exe을 실행해주세요.
```bash
./Shell.exe
```

Shell을 실행하면 CLI처럼 아래 명령들을 직접 입력할 수 있습니다:
```bash
Shell> write 3 0xABCDEF01
Shell> read 3
Shell> fullwrite 0xFFFFFFFF
Shell> fullread
Shell> help
Shell> exit
```

### Script 모드

미리 작성해 둔 텍스트 파일(예: runner_script.txt)을 인자로 넘기면 파일에 적힌 명령을 순차적으로 실행합니다:
```bash
./Shell.exe runner_script.txt
```

runner_script.txt 예시:
```txt
1_FullWriteAndReadCompare
2_PartialLBAWrite
3_WriteReadAging
4_EraseAndWriteAging
```

이 경우, 실행을 하면 다음과 같은 결과가 실시간으로 출력됩니다.
```bash
1_FullWriteAndReadCompare --- Run...Pass
2_PartialLBAWrite       --- Run...Pass
3_WriteReadAging        --- Run...Pass
```

