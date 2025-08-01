#include "CommandBuffer.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<Interval> CommandBuffer::Optimize(const std::vector<Interval>& in_cmds) {
    std::vector<Interval> cmds = in_cmds;

  unsigned long long orderMask = INIT_ORDER_MASK;
  for (int i = 0; i < cmds.size(); i++) {
    if (cmds[i].data == 0) {
      cmds[i].cmdType = CmdType::ERASE;  // Write 0은 전부 Erase로 취급
    }
    if (cmds[i].cmdType == CmdType::WRITE) {
      cmds[i].data |= orderMask;
      orderMask = (orderMask << 1) | orderMask;
    }
  }
  std::unordered_map<LBA, DATA> lba_data_udic;

  // 1. 최종 메모리 상태 만들기
  for (int i = 0; i < cmds.size(); i++) {
    for (int lba = cmds[i].s; lba <= cmds[i].e; lba++) {
      lba_data_udic[lba] = cmds[i].data;
    }
  }

  // 2. DATA별 LBA 추출 (최종 상태 기준)
  std::unordered_map<DATA, std::vector<bool>> data_lbaChk_udic;
  for (auto it = lba_data_udic.begin(); it != lba_data_udic.end(); it++) {
    LBA lba = it->first;
    DATA data = it->second;

    if (data_lbaChk_udic[data].empty()) {
      data_lbaChk_udic[data].resize(STORAGE_SIZE, false);
    }

    data_lbaChk_udic[data][lba] = true;
  }

  // 3. CommandBuffer에 존재하는 data들을 중복 제거하여 list로 만듦.
  std::vector<DATA> data_list;
  for (int i = 0; i < cmds.size(); i++) {
    data_list.push_back(cmds[i].data);
  }
  std::sort(data_list.begin(), data_list.end());
  data_list.erase(std::unique(data_list.begin(), data_list.end()),
                  data_list.end());

  // 4. 어떤 DATA부터 써야 덮어쓰기로 명령개수를 최소화 할 수 있는지
  //    next_permutation()으로 모든 경우의 수를 다 해봄.
  std::vector<int> covered(STORAGE_SIZE, -1);
  std::vector<Interval> result, ansResult;
  int mnResultCnt = INF;
  do {
    result.clear();
    covered.clear();
    covered.resize(STORAGE_SIZE, -1);

    for (int i = 0; i < data_list.size(); ++i) {
      DATA data = data_list[i];
      std::vector<bool>& lbaChk = data_lbaChk_udic[data];
      if (lbaChk.empty()) continue;

      LBA mnLba = INF, mxLba = 0;
      for (LBA lba = 0; lba < STORAGE_SIZE; lba++) {
        if (lbaChk[lba]) {
          mnLba = std::min(mnLba, lba);
          mxLba = std::max(mxLba, lba);
        }
      }

      LBA s = NA, e = mnLba;
      for (LBA lba = mnLba; lba <= mxLba; lba++) {
        if (lbaChk[lba]) {
          if (s == NA) s = lba;
          e = lba;
          covered[lba] = data;
        } else {
          // 다른 값(val)이 해당 lba를 cover한적이 있다면,
          if (covered[lba] >= 0) {
            e = lba;  // 그냥 cover해도 됨.
          } else {
            // 새로운 구간 생성
            result.push_back(Interval(s, e, data));
            s = NA;  // start지점 초기화
          }
        }
      }
      if (s != NA) {
        result.push_back(Interval(s, e, data));
      }
    }

    // 1번째 후처리: 구간 값 줄이기
    int mnTotalIntvLength = INF;
    int totalIntvLength = 0;
    for (int i = 0; i < result.size(); i++) {
      int sLba = result[i].s;
      for (int j = sLba; j <= result[i].e; j++) {
        if (lba_data_udic.count(j) == 0 ||
            lba_data_udic.at(j) != result[i].data)
          sLba++;
        else
          break;
      }
      int eLba = result[i].e;
      for (int j = eLba; j >= sLba; j--) {
        if (lba_data_udic.count(j) == 0 ||
            lba_data_udic.at(j) != result[i].data)
          eLba--;
        else
          break;
      }
      result[i].s = sLba;
      result[i].e = eLba;
      totalIntvLength += result[i].Length();
    }

    // 2번째 후처리: 처음에 붙였던 Mask bit를 data에서 떼어준다.
    for (int i = 0; i < result.size(); i++) {
      result[i].data &= REAL_DATA_MASK;
      if (result[i].data == 0) result[i].cmdType = CmdType::ERASE;
    }

    // 3번째 후처리: ERASE가 10개 넘어가면 끊어준다.
    std::vector<Interval> newResult;
    for (int i = 0; i < result.size(); i++) {
      // if (result[i].cmdType == CmdType::ERASE) { //-> WRITE도 그냥
      // 끊어주자.
      while (result[i].Length() > 0) {
        int ne = std::min(result[i].s + 10 - 1, result[i].e);
        Interval newInterval(result[i].s, ne, result[i].data,
                             result[i].cmdType);
        newResult.push_back(newInterval);
        result[i].s = ne + 1;
      }
      //}
    }

    if (mnResultCnt > newResult.size()) {
      mnResultCnt = newResult.size();
      ansResult = newResult;
      std::reverse(ansResult.begin(), ansResult.end());
      // ans_writeOrder = writeOrder;
    }
  } while (std::next_permutation(data_list.begin(), data_list.end()));
  return ansResult;
}
