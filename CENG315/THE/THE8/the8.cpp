#include "the8.h"

// DO NOT ADD OTHER LIBRARIES

const int NUM_SYMBOLS = 128;

int transitionFunc(const std::string &pattern, int M, int state, int index, const std::pair<std::string, std::string> mapping) {
    if (((state < M) && (index == pattern[state])) || ((index == mapping.first[0]) && (pattern[state] == mapping.second[0])) || ((index == mapping.second[0]) && (pattern[state] == mapping.first[0]))) {
        return state + 1;
    }

    int i;
    for (int ns = state; ns > 0; ns--) {
        if (pattern[ns - 1] == index) {
            for (i = 0; i < ns - 1; i++) {
                if (pattern[i] != pattern[state - ns + 1 + i])
                    break;
            }

            if (i == ns - 1) {
                return ns;
            }
        }
    }
    return 0;
}

void matchPattern(const std::string &sequence, const std::pair<std::string, std::string> mapping, const std::string &pattern) {
    bool print = false;
    std::string result;

    int patternSize = pattern.size();
    int sequenceSize = sequence.size();

    int transition[patternSize + 1][NUM_SYMBOLS];

    for (int state = 0; state <= patternSize; ++state) {
        for (int index = 0; index < NUM_SYMBOLS; ++index) {
            transition[state][index] = transitionFunc(pattern, patternSize, state, index, mapping);
        }
    }

    int state = 0;
    for (int i = 0; i < sequenceSize; i++) {
        int index = int(sequence[i]);
        state = transition[state][index];
        if (state == patternSize) {
            result.append(std::to_string(i - patternSize + 1));
            result.append(" ");
            print = true;
        }
    }

    if (!print)
        std::cout << "NONE" << std::endl;

    else {
        result.pop_back();
        std::cout << result << std::endl;
    }
}
