# interview-150

Solutions to the leetcode top interview 150: https://leetcode.com/studyplan/top-interview-150/

## Setup
1. `nix-shell`
2. `cmake -S . -B build -G Ninja`
3. `cd build`
4. `ninja && ctest --output_on_failure -R <problem-number>`

To run only unit tests add:
`-E Property`

To run only the property tests:
`-R <problem-number>Property`

To avoid having to add the --output-on-failure flag when manually testing, add
this environment variable:
export CTEST_OUTPUT_ON_FAILURE=1
