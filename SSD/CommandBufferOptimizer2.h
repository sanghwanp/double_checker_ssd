
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "CommandBufferEntry.h"
#include "CommandBufferConfig.h"

typedef unsigned int uint;
typedef unsigned long long ull;


class CommandOpt2
{
public:
    std::vector<CommandBufferEntry> Optimize(
        const std::vector<CommandBufferEntry>& in_cmds) {
        std::vector<CommandBufferEntry> victimed_Cmd;
        std::vector<CommandBufferEntry> result;
        // victim
        victimed_Cmd = _victim(in_cmds);

        // merge
        result = _merge(victimed_Cmd);
    }

    bool TryFastRead(
        const std::vector<CommandBufferEntry>& in_cmds,
        unsigned int lba,
        unsigned int& out_value) const {

        // try FastRead search
        // last에서 하나씩 lba에 해당하면 erase냐 write냐에 따라 data set. 0 or data

        out_value = static_cast<unsigned int>(CommandBufferConfig::NOT_AVAILABLE);
        return false;
    }
private:
    std::vector<CommandBufferEntry> _victim(
        const std::vector<CommandBufferEntry>& in_cmds) {
        // write victim
        // erase victim
    }
    std::vector<CommandBufferEntry> _merge(
        const std::vector<CommandBufferEntry>& in_cmds) {
        std::vector<CommandBufferEntry> ret;
        std::vector<CommandBufferEntry> copied_cmd(in_cmds.begin(), in_cmds.end() - 1);
        CommandBufferEntry iter_cmd = *in_cmds.rbegin(); // 마지막 들어온 command.
        int index = 0;
        // 현재 들어온 command가 entry 내려가면서 merge 할 수 있는지 확인하고 merge
        for (auto& it = copied_cmd.rbegin(); it != copied_cmd.rend(); ++it) {
            if (_IsContinous(*it, iter_cmd)) {
                *it = _MergeEraseCmd(*it, iter_cmd);
                // 사실 여기서 iter_Cmd로 it를 만들어서 처음부터 다시 시도.
            }
            else {
                ret.push_back(*it);
            }
        }
        std::reverse(ret.begin(), ret.end());
    }

    bool _IsContinous(CommandBufferEntry cmdA, CommandBufferEntry cmdB)
    {
        // [   A   ]
        //      [  B   ]
        if (cmdA.endLba >= cmdB.startLba) { return true; }
        // [   A   ][  B   ]
        if (cmdA.endLba == cmdB.startLba + 1) { return true; }
        //      [   A   ]
        //  [  B   ]
        if (cmdB.endLba >= cmdA.startLba) { return true; }
        // [  B   ][   A   ]
        if (cmdB.endLba == cmdA.startLba+1) { return true; }
    }

    CommandBufferEntry _MergeEraseCmd(CommandBufferEntry cmdA, CommandBufferEntry cmdB)
    {
        CommandBufferEntry ret;
        // 작은쪽으로
        ret.startLba = (cmdA.startLba > cmdB.startLba) ? (cmdB.startLba) : cmdA.startLba;

        // 큰쪽으로
        ret.endLba = (cmdA.endLba > cmdB.endLba) ? (cmdA.endLba) : cmdB.endLba;
        ret.cmdType = eEraseCmd;

        return ret;
    }
};
