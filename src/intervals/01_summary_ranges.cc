#include "01_summary_ranges.h"
#include <algorithm>
#include <format>
#include <iterator>

struct Range {
  int start;
  int end;

  static Range from(int num) { return Range{num, num}; }
};

std::vector<Range> buildRanges(std::vector<int> &nums) {
  std::vector<Range> ranges;

  auto extendsLatestRange = [&](int num) {
    return !ranges.empty() && num == ranges.back().end + 1;
  };

  for (int num : nums) {
    if (extendsLatestRange(num)) {
      ranges.back().end += 1;
    } else {
      ranges.push_back(Range::from(num));
    }
  }

  return ranges;
}

std::vector<std::string> convertRangesToStrings(std::vector<Range> &ranges) {
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

std::vector<std::string> SummaryRanges::summaryRanges(std::vector<int> &nums) {
  if (nums.empty())
    return {};
  std::vector<Range> ranges = buildRanges(nums);
  return convertRangesToStrings(ranges);
}
