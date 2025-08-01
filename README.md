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

