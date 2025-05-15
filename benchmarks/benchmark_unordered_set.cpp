#include <benchmark/benchmark.h>

#include <random>
#include <string>
#include <unordered_set>

#include "libdsc/unordered_set.h"

// Hash function for strings
static size_t string_hash(void const *key) {
    char const *str = static_cast<char const *>(key);
    size_t hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// Compare function for strings
static int string_compare(void const *a, void const *b) {
    return strcmp(static_cast<char const *>(a), static_cast<char const *>(b));
}

// Generate random string
static std::string random_string(size_t length) {
    static char const charset[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, sizeof(charset) - 2);

    std::string str;
    str.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        str += charset[dis(gen)];
    }
    return str;
}

// Benchmark insertion
static void BM_UnorderedSetInsert(benchmark::State &state) {
    dsc_unordered_set *set =
        unordered_set_create(sizeof(char *), string_hash, string_compare);

    for (auto _ : state) {
        std::string element = random_string(10);
        benchmark::DoNotOptimize(unordered_set_insert(set, &element));
    }

    unordered_set_destroy(set);
}
BENCHMARK(BM_UnorderedSetInsert)->Range(1, 1 << 20);

// Benchmark std::unordered_set insertion
static void BM_StdUnorderedSetInsert(benchmark::State &state) {
    std::unordered_set<std::string> set;

    for (auto _ : state) {
        std::string element = random_string(10);
        benchmark::DoNotOptimize(set.insert(element));
    }
}
BENCHMARK(BM_StdUnorderedSetInsert)->Range(1, 1 << 20);

// Benchmark find
static void BM_UnorderedSetFind(benchmark::State &state) {
    dsc_unordered_set *set =
        unordered_set_create(sizeof(char *), string_hash, string_compare);

    // Pre-populate set
    std::vector<std::string> elements;
    for (size_t i = 0; i < 1000; ++i) {
        std::string element = random_string(10);
        unordered_set_insert(set, &element);
        elements.push_back(element);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, elements.size() - 1);

    for (auto _ : state) {
        std::string element = elements[dis(gen)];
        benchmark::DoNotOptimize(unordered_set_find(set, &element));
    }

    unordered_set_destroy(set);
}
BENCHMARK(BM_UnorderedSetFind)->Range(1 << 10, 1 << 20);

// Benchmark std::unordered_set find
static void BM_StdUnorderedSetFind(benchmark::State &state) {
    std::unordered_set<std::string> set;

    // Pre-populate set
    std::vector<std::string> elements;
    for (size_t i = 0; i < 1000; ++i) {
        std::string element = random_string(10);
        set.insert(element);
        elements.push_back(element);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, elements.size() - 1);

    for (auto _ : state) {
        std::string element = elements[dis(gen)];
        benchmark::DoNotOptimize(set.find(element));
    }
}
BENCHMARK(BM_StdUnorderedSetFind)->Range(1 << 10, 1 << 20);

// Benchmark size operation
static void BM_UnorderedSetSize(benchmark::State &state) {
    dsc_unordered_set *set =
        unordered_set_create(sizeof(char *), string_hash, string_compare);

    // Pre-populate set
    for (size_t i = 0; i < 1000; ++i) {
        std::string element = random_string(10);
        unordered_set_insert(set, &element);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(unordered_set_size(set));
    }

    unordered_set_destroy(set);
}
BENCHMARK(BM_UnorderedSetSize)->Range(1 << 10, 1 << 20);

// Benchmark std::unordered_set size
static void BM_StdUnorderedSetSize(benchmark::State &state) {
    std::unordered_set<std::string> set;

    // Pre-populate set
    for (size_t i = 0; i < 1000; ++i) {
        set.insert(random_string(10));
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(set.size());
    }
}
BENCHMARK(BM_StdUnorderedSetSize)->Range(1 << 10, 1 << 20);

// Benchmark empty check
static void BM_UnorderedSetEmpty(benchmark::State &state) {
    dsc_unordered_set *set =
        unordered_set_create(sizeof(char *), string_hash, string_compare);

    for (auto _ : state) {
        benchmark::DoNotOptimize(unordered_set_empty(set));
    }

    unordered_set_destroy(set);
}
BENCHMARK(BM_UnorderedSetEmpty)->Range(1 << 10, 1 << 20);

// Benchmark std::unordered_set empty
static void BM_StdUnorderedSetEmpty(benchmark::State &state) {
    std::unordered_set<std::string> set;

    for (auto _ : state) {
        benchmark::DoNotOptimize(set.empty());
    }
}
BENCHMARK(BM_StdUnorderedSetEmpty)->Range(1 << 10, 1 << 20);

// Benchmark clear operation
static void BM_UnorderedSetClear(benchmark::State &state) {
    dsc_unordered_set *set =
        unordered_set_create(sizeof(char *), string_hash, string_compare);

    for (auto _ : state) {
        state.PauseTiming();
        // Fill set
        for (size_t i = 0; i < state.range(0); ++i) {
            std::string element = random_string(10);
            unordered_set_insert(set, &element);
        }
        state.ResumeTiming();

        unordered_set_clear(set);
    }

    unordered_set_destroy(set);
}
BENCHMARK(BM_UnorderedSetClear)->Range(1 << 10, 1 << 20);

// Benchmark std::unordered_set clear
static void BM_StdUnorderedSetClear(benchmark::State &state) {
    std::unordered_set<std::string> set;

    for (auto _ : state) {
        state.PauseTiming();
        // Fill set
        for (size_t i = 0; i < state.range(0); ++i) {
            set.insert(random_string(10));
        }
        state.ResumeTiming();

        set.clear();
    }
}
BENCHMARK(BM_StdUnorderedSetClear)->Range(1 << 10, 1 << 20);

// Benchmark reserve operation
static void BM_UnorderedSetReserve(benchmark::State &state) {
    dsc_unordered_set *set =
        unordered_set_create(sizeof(char *), string_hash, string_compare);

    for (auto _ : state) {
        benchmark::DoNotOptimize(unordered_set_reserve(set, state.range(0)));
    }

    unordered_set_destroy(set);
}
BENCHMARK(BM_UnorderedSetReserve)->Range(1 << 10, 1 << 20);

// Benchmark std::unordered_set reserve
static void BM_StdUnorderedSetReserve(benchmark::State &state) {
    std::unordered_set<std::string> set;

    for (auto _ : state) {
        set.reserve(state.range(0));
        benchmark::DoNotOptimize(set);
    }
}
BENCHMARK(BM_StdUnorderedSetReserve)->Range(1 << 10, 1 << 20);

// Benchmark erase operation
static void BM_UnorderedSetErase(benchmark::State &state) {
    dsc_unordered_set *set =
        unordered_set_create(sizeof(char *), string_hash, string_compare);
    std::vector<std::string> elements;

    // Pre-populate set and keep track of elements
    for (size_t i = 0; i < state.range(0); ++i) {
        std::string element = random_string(10);
        unordered_set_insert(set, &element);
        elements.push_back(element);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, elements.size() - 1);

    for (auto _ : state) {
        state.PauseTiming();
        size_t idx = dis(gen);
        std::string element = elements[idx];
        state.ResumeTiming();

        benchmark::DoNotOptimize(unordered_set_erase(set, &element));
    }

    unordered_set_destroy(set);
}
BENCHMARK(BM_UnorderedSetErase)->Range(1 << 10, 1 << 20);

// Benchmark std::unordered_set erase
static void BM_StdUnorderedSetErase(benchmark::State &state) {
    std::unordered_set<std::string> set;
    std::vector<std::string> elements;

    // Pre-populate set and keep track of elements
    for (size_t i = 0; i < state.range(0); ++i) {
        std::string element = random_string(10);
        set.insert(element);
        elements.push_back(element);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, elements.size() - 1);

    for (auto _ : state) {
        state.PauseTiming();
        size_t idx = dis(gen);
        std::string element = elements[idx];
        state.ResumeTiming();

        benchmark::DoNotOptimize(set.erase(element));
    }
}
BENCHMARK(BM_StdUnorderedSetErase)->Range(1 << 10, 1 << 20);

// Benchmark insert with pre-reserved capacity
static void BM_UnorderedSetInsertReserved(benchmark::State &state) {
    dsc_unordered_set *set =
        unordered_set_create(sizeof(char *), string_hash, string_compare);
    unordered_set_reserve(set, state.range(0));

    for (auto _ : state) {
        state.PauseTiming();
        unordered_set_clear(set);
        state.ResumeTiming();

        for (size_t i = 0; i < state.range(0); ++i) {
            std::string element = random_string(10);
            unordered_set_insert(set, &element);
        }
    }

    unordered_set_destroy(set);
}
BENCHMARK(BM_UnorderedSetInsertReserved)->Range(1 << 10, 1 << 20);

// Benchmark std::unordered_set insert with pre-reserved capacity
static void BM_StdUnorderedSetInsertReserved(benchmark::State &state) {
    std::unordered_set<std::string> set;
    set.reserve(state.range(0));

    for (auto _ : state) {
        state.PauseTiming();
        set.clear();
        state.ResumeTiming();

        for (size_t i = 0; i < state.range(0); ++i) {
            set.insert(random_string(10));
        }
    }
}
BENCHMARK(BM_StdUnorderedSetInsertReserved)->Range(1 << 10, 1 << 20);

// Benchmark mixed operations pattern
static void BM_UnorderedSetMixedOps(benchmark::State &state) {
    dsc_unordered_set *set =
        unordered_set_create(sizeof(char *), string_hash, string_compare);
    std::vector<std::string> elements;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (auto _ : state) {
        std::string element = random_string(10);

        // Randomly choose between insert, find, and erase
        std::uniform_int_distribution<> dis(0, 2);
        int op = dis(gen);

        switch (op) {
            case 0:  // Insert
                benchmark::DoNotOptimize(unordered_set_insert(set, &element));
                elements.push_back(element);
                break;
            case 1:  // Find
                if (!elements.empty()) {
                    size_t idx = gen() % elements.size();
                    benchmark::DoNotOptimize(
                        unordered_set_find(set, &elements[idx]));
                }
                break;
            case 2:  // Erase
                if (!elements.empty()) {
                    size_t idx = gen() % elements.size();
                    benchmark::DoNotOptimize(
                        unordered_set_erase(set, &elements[idx]));
                    elements.erase(elements.begin() + idx);
                }
                break;
        }
    }

    unordered_set_destroy(set);
}
BENCHMARK(BM_UnorderedSetMixedOps)->Range(1 << 10, 1 << 20);

// Benchmark std::unordered_set mixed operations
static void BM_StdUnorderedSetMixedOps(benchmark::State &state) {
    std::unordered_set<std::string> set;
    std::vector<std::string> elements;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (auto _ : state) {
        std::string element = random_string(10);

        // Randomly choose between insert, find, and erase
        std::uniform_int_distribution<> dis(0, 2);
        int op = dis(gen);

        switch (op) {
            case 0:  // Insert
                benchmark::DoNotOptimize(set.insert(element));
                elements.push_back(element);
                break;
            case 1:  // Find
                if (!elements.empty()) {
                    size_t idx = gen() % elements.size();
                    benchmark::DoNotOptimize(set.find(elements[idx]));
                }
                break;
            case 2:  // Erase
                if (!elements.empty()) {
                    size_t idx = gen() % elements.size();
                    benchmark::DoNotOptimize(set.erase(elements[idx]));
                    elements.erase(elements.begin() + idx);
                }
                break;
        }
    }
}
BENCHMARK(BM_StdUnorderedSetMixedOps)->Range(1 << 10, 1 << 20);

// Benchmark collision handling (strings with same hash)
static void BM_UnorderedSetCollisions(benchmark::State &state) {
    dsc_unordered_set *set =
        unordered_set_create(sizeof(char *), string_hash, string_compare);
    std::vector<std::string> colliding_strings;

    // Generate strings that will have hash collisions
    for (size_t i = 0; i < state.range(0); ++i) {
        std::string base = random_string(8);
        colliding_strings.push_back(base + "aa");
        colliding_strings.push_back(
            base + "bb");  // Will likely collide due to similar pattern
    }

    for (auto _ : state) {
        state.PauseTiming();
        unordered_set_clear(set);
        state.ResumeTiming();

        for (auto const &str : colliding_strings) {
            benchmark::DoNotOptimize(unordered_set_insert(set, &str));
        }
    }

    unordered_set_destroy(set);
}
BENCHMARK(BM_UnorderedSetCollisions)->Range(1 << 8, 1 << 16);

// Benchmark std::unordered_set collision handling
static void BM_StdUnorderedSetCollisions(benchmark::State &state) {
    std::unordered_set<std::string> set;
    std::vector<std::string> colliding_strings;

    // Generate strings that will have hash collisions
    for (size_t i = 0; i < state.range(0); ++i) {
        std::string base = random_string(8);
        colliding_strings.push_back(base + "aa");
        colliding_strings.push_back(
            base + "bb");  // Will likely collide due to similar pattern
    }

    for (auto _ : state) {
        state.PauseTiming();
        set.clear();
        state.ResumeTiming();

        for (auto const &str : colliding_strings) {
            benchmark::DoNotOptimize(set.insert(str));
        }
    }
}
BENCHMARK(BM_StdUnorderedSetCollisions)->Range(1 << 8, 1 << 16);

// Benchmark load factor performance
static void BM_UnorderedSetLoadFactor(benchmark::State &state) {
    dsc_unordered_set *set =
        unordered_set_create(sizeof(char *), string_hash, string_compare);
    size_t target_size = state.range(0);
    unordered_set_reserve(set, target_size / 2);  // Force higher load factor

    for (auto _ : state) {
        std::string element = random_string(10);
        benchmark::DoNotOptimize(unordered_set_insert(set, &element));

        if (unordered_set_size(set) >= target_size) {
            state.PauseTiming();
            unordered_set_clear(set);
            state.ResumeTiming();
        }
    }

    unordered_set_destroy(set);
}
BENCHMARK(BM_UnorderedSetLoadFactor)->Range(1 << 10, 1 << 20);

// Benchmark std::unordered_set load factor
static void BM_StdUnorderedSetLoadFactor(benchmark::State &state) {
    std::unordered_set<std::string> set;
    size_t target_size = state.range(0);
    set.max_load_factor(0.8f);
    set.reserve(target_size / 2);  // Force higher load factor

    for (auto _ : state) {
        std::string element = random_string(10);
        benchmark::DoNotOptimize(set.insert(element));

        if (set.size() >= target_size) {
            state.PauseTiming();
            set.clear();
            state.ResumeTiming();
        }
    }
}
BENCHMARK(BM_StdUnorderedSetLoadFactor)->Range(1 << 10, 1 << 20);

BENCHMARK_MAIN();
