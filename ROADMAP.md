# libdsc Roadmap

## Implement remaining containers

### Sequence containers

- [ ] `std::array`

- [ ] `std::inplace_vector`

- [ ] `std::deque`

### Associative containers

- [ ] `std::set`

- [ ] `std::map`

- [ ] `std::multiset`

- [ ] `std::multimap`

### Unordered associative containers

- [ ] `std::unordered_multimap`

- [ ] `std::unordered_multimap`

### Container adaptors

- [ ] `std::priority_queue`

- [ ] `std::flat_set`

- [ ] `std::flat_map`

- [ ] `std::flat_multiset`

- [ ] `std::flat_multimap`

## Improve test coverage

Ideally, this should be as close to 100% as possible.

[![Codecov](https://codecov.io/gh/cm-jones/libdsc/branch/main/graph/badge.svg)](https://codecov.io/gh/cm-jones/libdsc)

## Create visualizations for benchmarks vs. libc++ over time

We'd like to do this via GitHub Actions (not locally) on a weekly basis per the existing .github/workflows/benchmark.yaml workflow.

## Upload documentation to GitHub Pages

We already generate HTML documentation via Doxygen. Set up https://cm-jones.github.io/libdsc to display this.
