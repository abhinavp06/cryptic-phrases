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
 *     output: [], -1
 *
 *   Case 8 — input string too short (invalid input):
 *     x="a", y="b", input="ab"
 *     output: [], -1
 *
 * FUTURE ENHANCEMENTS:
 *   - report all valid patterns irrespective of length, not just the longest
 *   - generalise x and y from single characters to k-mers (e.g. x="CGG")
 *   - support wildcard pivot: y = any character that is not x
 *   - DNA mode: ACGT alphabet, seeded random sequence generation
 *   - visualiser: render matches as arcs over the input sequence
 ***/