#pragma once

#include "SSDConfig.h"
#include "IParam.h"
#include "FileDriver.h"

#include "CommandBufferHandler.h"

class ICommand {
 public:
  ICommand() { fileDriver = FileDriver::GetInstance(); }
  virtual ~ICommand() {}

  virtual bool Execute(IParam* param) { return false; }
  virtual bool CheckPrecondition() { return false; }

#if (USING_COMMAND_BUFFER == 1)
  CommandBufferHandler cmdBufHandler;
#endif
  FileDriver* fileDriver = FileDriver::GetInstance();
};

#if 0 //refactoring
#pragma once

// 필요한 경우에만 실제 헤더 include
// 현재는 IParam만 사용되므로 전방 선언으로 충분

class IParam;

/**
 * @brief ICommand는 모든 Command 클래스들이 상속받는 순수 인터페이스입니다.
 *
 * 이 인터페이스는 명령 실행과 사전 조건 검사를 정의합니다.
 * 구현체는 Execute()와 CheckPrecondition()을 반드시 구현해야 합니다.
 */
class ICommand {
 public:
  /**
   * @brief 명령을 실행합니다.
   *
   * @param param 명령 실행에 필요한 파라미터 객체 (nullable 가능)
   * @return true 성공적으로 실행됨
   * @return false 실패
   */
  virtual bool Execute(IParam* param) = 0;

  /**
   * @brief 명령 실행 전에 조건을 검사합니다.
   *
   * @return true 조건 만족
   * @return false 조건 불만족
   */
  virtual bool CheckPrecondition() = 0;

  /**
   * @brief 가상 소멸자 — 다형성 삭제를 위함
   */
  virtual ~ICommand() = default;
};


#endif
