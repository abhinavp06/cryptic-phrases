/***
 * nyn — symmetric repeat pattern matcher
 *
 * PATTERN DEFINITION:
 *   x{n} y x{n}   where y ≠ x, n ≥ 1
 *   x and y are user-defined characters
 *   n is the number of consecutive x's on each side of the pivot y
 *   a pattern is fully described by (starting_index, n)
 *
 * RULES:
 *   - user provides x, y, and input string
 *   - x and y must be different characters, else return empty
 *   - input string must be at least 3 characters long, else return empty
 *   - find the maximum value of n across all valid patterns in the string
 *   - return an array of starting indexes of all patterns with that maximum n
 *   - array is in ascending order
 *   - if no valid pattern exists, return empty array and n = -1
 *
 * OVERLAP BEHAVIOR:
 *   - overlapping patterns are allowed
 *   - report the starting index of each, as long as n matches the maximum
 *   - example: "aaabaaabaaab", x="a", y="b" → [0, 4], n=3
 *
 * SAMPLE CASES:
 *
 *   Case 1 — no match:
 *     x="a", y="b", input="abcdefg"
 *     output: [], -1
 *
 *   Case 2 — match at index 0:
 *     x="a", y="b", input="aaabaaac"
 *     output: [0], 3
 *
 *   Case 3 — two pivots, same n, non-overlapping:
 *     x="a", y="b", input="aabaaabbaabaaab"
 *     output: [0, 8], 2
 *
 *   Case 4 — two pivots, different n, report only longest:
 *     x="a", y="b", input="aabaaaaabaaaaaa"
 *     output: [3], 5
 *
 *   Case 5 — overlapping patterns:
 *     x="a", y="b", input="aaabaaabaaab"
 *     output: [0, 4], 3
 *
 *   Case 6 — entire string is the pattern:
 *     x="a", y="b", input="aaabaaaa"
 *     output: [0], 3
 *
 *   Case 7 — x and y are the same character (invalid input):
 *     x="a", y="a", input="aaabaaaa"
 *     output: "invalid input"
 *
 *   Case 8 — input string too short (invalid input):
 *     x="a", y="b", input="ab"
 *     output: "invalid input"
 *
 * FUTURE ENHANCEMENTS:
 *   - report all valid patterns irrespective of length, not just the longest
 *   - generalise x and y from single characters to k-mers (e.g. x="CGG")
 *   - support wildcard pivot: y = any character that is not x
 *   - DNA mode: ACGT alphabet, seeded random sequence generation
 *   - visualiser: render matches as arcs over the input sequence
 ***/

#include <iostream>
#include <string>
#include <vector>

struct Result {
    std::vector<int> indexes;
    int n;
};

struct Run {
    char character;
    int count;
    int start_index;
};

Result find_pattern_run_length_encoding(char x, char y, const std::string& input_string) {
    Result result = { {}, -1 };
    std::string rle_string;
    std::vector<Run> rle_runs;

    for (int i = 0; i < input_string.size(); i++) {
        Run run = {
            input_string[i],
            1,
            i
        };
        rle_string.push_back(input_string[i]);

        while (i < input_string.size() - 1 && input_string[i] == input_string[i + 1]) {
            run.count++;
            i++;
        }

        rle_runs.push_back(run);
        rle_string.append(std::to_string(run.count));
    }

    std::cout << "RLE ENCODED STRING: " << rle_string << std::endl;

    if (rle_runs.size() < 3) {
        return result;
    }

    for (int i = 0; i < rle_runs.size() - 2; i ++) {
        /**
        * 1. middle character must be the pivot and it's count should be 1
        * 2. characters beside the middle character must be the same
        * 3. find std::min() between the counts of both the side characters and if it is greater than or equal to max n, update the result object
        */
        if (rle_runs[i + 1].character == y && rle_runs[i + 1].count == 1 && rle_runs[i].character == x && rle_runs[i].character == rle_runs[i + 2].character) {
            int current_n = std::min(rle_runs[i].count, rle_runs[i + 2].count);
            int start_index = rle_runs[i].count == current_n ? rle_runs[i].start_index : rle_runs[i+1].start_index - current_n;
            if (current_n < result.n) {
                continue;
            } 
            else if (current_n == result.n) {
                result.indexes.push_back(start_index);
            }
            else if (current_n > result.n) {
                result.indexes.clear();
                result.indexes.push_back(start_index);
                result.n = current_n;
            }
        }
    }

    return result;
}

Result find_pattern_naive(char x, char y, const std::string& input_string) {
    Result result = { {}, -1 };
    int max_n = -1;

    for (size_t i = 0; i < input_string.size(); i++) {
        std::cout << "--------" << std::endl;
        std::cout << "i = " << i << " ";
        if (input_string[i] != y) {
            continue;
        }

        int l = i - 1, r = i + 1, current_n = -1;

        while (l >= 0 && r < input_string.size() && input_string[l] == x && input_string[r] == x) {
            std::cout << "l = " << l << " r = " << r << " current_n = " << current_n << " max_n = " << max_n << std::endl;
            l--;
            r++;
        }

        if (l != i-1 && r != i+1) {
            current_n = std::min(i - l, r - i) - 1;
            if (current_n == max_n) {
                result.indexes.push_back(l + 1);
            }
            else if (current_n > max_n) {
                result.indexes.clear();
                result.indexes.push_back(l + 1);
                max_n = current_n;
            }
        }
    }

    result.n = max_n;

    return result;
}

int validate_input(char x, char y, const std::string& input_string) {
    if (x == y) {
        return 1;
    }

    if (input_string.length() < 3) {
        return 1;
    }

    return 0;
}

int main() {
    std::cout << "--- PATTERN RECOGNIZER ---" << std::endl;

    char x, y;
    std::string input_string;

    std::cout << "what's your 'x'?" << std::endl;
    std::cin >> x;

    std::cout << "what's your 'y'?" << std::endl;
    std::cin >> y;

    std::cout << "enter your string:" << std::endl;
    std::cin >> input_string;
    
    if (validate_input(x, y, input_string)) {
        std::cout << "invalid input" << std::endl;
        return 1;
    }

    std::cout << "\n" << std::endl;

    Result result = find_pattern_run_length_encoding(x, y, input_string);

    //Result result = find_pattern_naive(x, y, input_string);
    
    std::cout << "\n--- OUTPUT ---" << std::endl;
    std::cout << "n = " << result.n << std::endl;
    std::cout << "indexes =>" << " ";
    for (int index : result.indexes) {
        if (index == result.indexes.size()) {
            std::cout << index << " ";
        }
        else {
            std::cout << index << ", ";
        }
    }
    std::cout << std::endl;


    return 0;
}