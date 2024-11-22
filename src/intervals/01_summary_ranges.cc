#include "01_summary_ranges.h"
#include <algorithm>
#include <format>
#include <iterator>

struct Range {
  int start;
  int end;
};

std::vector<std::string> SummaryRanges::summaryRanges(std::vector<int> &nums) {
  std::vector<Range> ranges;

  auto inLatestRange = [&](int num) { return num != (ranges.back().end + 1); };

  for (int num : nums) {
    if (ranges.empty() || inLatestRange(num)) {
      ranges.push_back(Range{num, num});
    } else {
      ranges.back().end += 1;
    }
  }

  auto rangeToString = [](Range range) {
    if (range.start == range.end) {
      return std::format("{}", range.start);
    }
    return std::format("{}->{}", range.start, range.end);
  };

  std::vector<std::string> result;
  std::ranges::transform(ranges, std::back_inserter(result), rangeToString);
  return result;
}
