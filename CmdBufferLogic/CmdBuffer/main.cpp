#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;
typedef unsigned int uint;

constexpr int INF = 0x3f3f3f3f;
constexpr int NA = -1;

struct Interval {
  int start;
  int end;
  unsigned int val;
  Interval(int start, int end, int val) : start(start), end(end), val(val) {}

  void print() const { printf("[%d,%d]->val:%d\n", start, end, val); }
};

std::vector<Interval> Optimize(const std::vector<Interval>& cmds) {
  std::unordered_map<int, unsigned int> val_by_lba;

  // 1. 최종 메모리 상태 만들기
  for (int i = 0; i < cmds.size(); ++i) {
    for (int lba = cmds[i].start; lba <= cmds[i].end; ++lba) {
      val_by_lba[lba] = cmds[i].val;
    }
  }

  // 2. 값별 LBA 추출 (최종 상태 기준)

  std::unordered_map<unsigned int, std::vector<bool>> lbaChk_by_val;
  for (auto it = val_by_lba.begin(); it != val_by_lba.end(); ++it) {
    int lba = it->first;
    unsigned int val = it->second;

    if (lbaChk_by_val[val].empty()) {
      lbaChk_by_val[val].resize(100, false);
    }

    lbaChk_by_val[val][lba] = true;
  }

  // 3. 덮는 순서 보존: 가장 나중에 쓴 값부터 되감기 처리
  std::vector<unsigned int> writeOrder;  // 값 순서
  std::unordered_map<unsigned int, bool> seen;
  for (int i = cmds.size() - 1; i >= 0; --i) {
    unsigned int v = cmds[i].val;
    if (!seen[v]) {
      writeOrder.push_back(v);
      seen[v] = true;
    }
  }

  std::reverse(writeOrder.begin(), writeOrder.end());
  // 4. 덮어쓰기 재현용 명령 생성
  int covered[100];
  std::vector<Interval> result, ans_result;
  int mnResultCnt = INF;
  do {
    result.clear();
    memset(covered, -1, sizeof(covered));

    for (int i = 0; i < writeOrder.size(); ++i) {
      unsigned int val = writeOrder[i];
      std::vector<bool>& lbaChk = lbaChk_by_val[val];

      int mn = INF, mx = -1;
      for (int j = 0; j < 100; j++) {
        if (lbaChk[j]) {
          mn = min(mn, j);
          mx = max(mx, j);
        }
      }

      int s = NA, e = mn;
      for (int j = mn; j <= mx; j++) {
        if (lbaChk[j]) {
          if (s == NA) s = j;
          e = j;
          covered[j] = val;
        } else {
          if (covered[j] >=
              0) {  // 다른 값(val)이 해당 lba를 cover한적이 있다면,
            e = j;  // 그냥 cover해도 됨.
          } else {
            // 새로운 구간 생성
            result.push_back(Interval(s, e, val));
            s = NA;  // start지점 초기화
          }
        }
      }
      if (s != NA) {
        result.push_back(Interval(s, e, val));
      }
    }

    if (mnResultCnt > result.size()) {
      mnResultCnt = result.size();
      ans_result = result;
      std::reverse(ans_result.begin(), ans_result.end());
      // ans_writeOrder = writeOrder;
    }
  } while (next_permutation(writeOrder.begin(), writeOrder.end()));
  return ans_result;
}

int main() {
  // vector<Interval> cmds = {{1, 10, 1}, {9, 13, 2}, {12, 17, 1}};
  vector<Interval> cmds = {{1, 10, 1}, {9, 13, 2}, {15, 17, 1}, {2, 7, 2}};
  // vector<Interval> cmds = {{1, 10, 1}, {9, 13, 2}, {12, 17, 1}};
  // vector<Interval> cmds = {{1, 10, 1}, {9, 13, 2}, {12, 17, 1}};
  // vector<Interval> cmds = {{1, 10, 1}, {9, 13, 2}, {12, 17, 1}};
  // vector<Interval> cmds = {{1, 10, 1}, {9, 13, 2}, {12, 17, 1}};

  puts("Cmds:");
  for (const Interval& cmd : cmds) {
    cmd.print();
  }
  puts("\nOutput");
  std::vector<Interval> ret = Optimize(cmds);
  for (const Interval& intv : ret) {
    intv.print();
  }

  return 0;
}
