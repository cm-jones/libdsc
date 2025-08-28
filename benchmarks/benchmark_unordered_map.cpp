#include <benchmark/benchmark.h>

#include <random>
#include <string>
#include <unordered_map>

#include "libdsc/unordered_map.h"

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
static void BM_UnorderedMapInsert(benchmark::State &state) {
    dsc_unordered_map *map = unordered_map_create(sizeof(char *), sizeof(int),
                                                  string_hash, string_compare);

    for (auto _ : state) {
        std::string key = random_string(10);
        int value = 42;
        benchmark::DoNotOptimize(unordered_map_insert(map, &key, &value));
    }

    unordered_map_destroy(map);
}
BENCHMARK(BM_UnorderedMapInsert)->Range(1, 1 << 20);

// Benchmark std::unordered_map insertion
static void BM_StdUnorderedMapInsert(benchmark::State &state) {
    std::unordered_map<std::string, int> map;

    for (auto _ : state) {
        std::string key = random_string(10);
        benchmark::DoNotOptimize(map[key] = 42);
    }
}
BENCHMARK(BM_StdUnorderedMapInsert)->Range(1, 1 << 20);

// Benchmark find
static void BM_UnorderedMapFind(benchmark::State &state) {
    dsc_unordered_map *map = unordered_map_create(sizeof(char *), sizeof(int),
                                                  string_hash, string_compare);

    // Pre-populate map
    std::vector<std::string> keys;
    for (size_t i = 0; i < 1000; ++i) {
        std::string key = random_string(10);
        int value = i;
        unordered_map_insert(map, &key, &value);
        keys.push_back(key);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, keys.size() - 1);

    for (auto _ : state) {
        std::string key = keys[dis(gen)];
        benchmark::DoNotOptimize(unordered_map_find(map, &key));
    }

    unordered_map_destroy(map);
}
BENCHMARK(BM_UnorderedMapFind)->Range(1 << 10, 1 << 20);

// Benchmark std::unordered_map find
static void BM_StdUnorderedMapFind(benchmark::State &state) {
    std::unordered_map<std::string, int> map;

    // Pre-populate map
    std::vector<std::string> keys;
    for (size_t i = 0; i < 1000; ++i) {
        std::string key = random_string(10);
        map[key] = i;
        keys.push_back(key);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, keys.size() - 1);

    for (auto _ : state) {
        std::string key = keys[dis(gen)];
        benchmark::DoNotOptimize(map.find(key));
    }
}
BENCHMARK(BM_StdUnorderedMapFind)->Range(1 << 10, 1 << 20);

// Benchmark size operation
static void BM_UnorderedMapSize(benchmark::State &state) {
    dsc_unordered_map *map = unordered_map_create(sizeof(char *), sizeof(int),
                                                  string_hash, string_compare);

    // Pre-populate map
    for (size_t i = 0; i < 1000; ++i) {
        std::string key = random_string(10);
        int value = i;
        unordered_map_insert(map, &key, &value);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(unordered_map_size(map));
    }

    unordered_map_destroy(map);
}
BENCHMARK(BM_UnorderedMapSize)->Range(1 << 10, 1 << 20);

// Benchmark std::unordered_map size
static void BM_StdUnorderedMapSize(benchmark::State &state) {
    std::unordered_map<std::string, int> map;

    // Pre-populate map
    for (size_t i = 0; i < 1000; ++i) {
        map[random_string(10)] = i;
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(map.size());
    }
}
BENCHMARK(BM_StdUnorderedMapSize)->Range(1 << 10, 1 << 20);

// Benchmark empty check
static void BM_UnorderedMapEmpty(benchmark::State &state) {
    dsc_unordered_map *map = unordered_map_create(sizeof(char *), sizeof(int),
                                                  string_hash, string_compare);

    for (auto _ : state) {
        benchmark::DoNotOptimize(unordered_map_empty(map));
    }

    unordered_map_destroy(map);
}
BENCHMARK(BM_UnorderedMapEmpty)->Range(1 << 10, 1 << 20);

// Benchmark std::unordered_map empty
static void BM_StdUnorderedMapEmpty(benchmark::State &state) {
    std::unordered_map<std::string, int> map;

    for (auto _ : state) {
        benchmark::DoNotOptimize(map.empty());
    }
}
BENCHMARK(BM_StdUnorderedMapEmpty)->Range(1 << 10, 1 << 20);

// Benchmark clear operation
static void BM_UnorderedMapClear(benchmark::State &state) {
    dsc_unordered_map *map = unordered_map_create(sizeof(char *), sizeof(int),
                                                  string_hash, string_compare);

    for (auto _ : state) {
        state.PauseTiming();
        // Fill map
        for (size_t i = 0; i < state.range(0); ++i) {
            std::string key = random_string(10);
            int value = i;
            unordered_map_insert(map, &key, &value);
        }
        state.ResumeTiming();

        unordered_map_clear(map);
    }

    unordered_map_destroy(map);
}
BENCHMARK(BM_UnorderedMapClear)->Range(1 << 10, 1 << 20);

// Benchmark std::unordered_map clear
static void BM_StdUnorderedMapClear(benchmark::State &state) {
    std::unordered_map<std::string, int> map;

    for (auto _ : state) {
        state.PauseTiming();
        // Fill map
        for (size_t i = 0; i < state.range(0); ++i) {
            map[random_string(10)] = i;
        }
        state.ResumeTiming();

        map.clear();
    }
}
BENCHMARK(BM_StdUnorderedMapClear)->Range(1 << 10, 1 << 20);

// Benchmark reserve operation
static void BM_UnorderedMapReserve(benchmark::State &state) {
    dsc_unordered_map *map = unordered_map_create(sizeof(char *), sizeof(int),
                                                  string_hash, string_compare);

    for (auto _ : state) {
        benchmark::DoNotOptimize(unordered_map_reserve(map, state.range(0)));
    }

    unordered_map_destroy(map);
}
BENCHMARK(BM_UnorderedMapReserve)->Range(1 << 10, 1 << 20);

// Benchmark std::unordered_map reserve
static void BM_StdUnorderedMapReserve(benchmark::State &state) {
    std::unordered_map<std::string, int> map;

    for (auto _ : state) {
        map.reserve(state.range(0));
        benchmark::DoNotOptimize(map);
    }
}
BENCHMARK(BM_StdUnorderedMapReserve)->Range(1 << 10, 1 << 20);

// Benchmark erase operation
static void BM_UnorderedMapErase(benchmark::State &state) {
    dsc_unordered_map *map = unordered_map_create(sizeof(char *), sizeof(int),
                                                  string_hash, string_compare);
    std::vector<std::string> keys;

    // Pre-populate map and keep track of keys
    for (size_t i = 0; i < state.range(0); ++i) {
        std::string key = random_string(10);
        int value = i;
        unordered_map_insert(map, &key, &value);
        keys.push_back(key);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, keys.size() - 1);

    for (auto _ : state) {
        state.PauseTiming();
        size_t idx = dis(gen);
        std::string key = keys[idx];
        state.ResumeTiming();

        benchmark::DoNotOptimize(unordered_map_erase(map, &key));
    }

    unordered_map_destroy(map);
}
BENCHMARK(BM_UnorderedMapErase)->Range(1 << 10, 1 << 20);

// Benchmark std::unordered_map erase
static void BM_StdUnorderedMapErase(benchmark::State &state) {
    std::unordered_map<std::string, int> map;
    std::vector<std::string> keys;

    // Pre-populate map and keep track of keys
    for (size_t i = 0; i < state.range(0); ++i) {
        std::string key = random_string(10);
        map[key] = i;
        keys.push_back(key);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, keys.size() - 1);

    for (auto _ : state) {
        state.PauseTiming();
        size_t idx = dis(gen);
        std::string key = keys[idx];
        state.ResumeTiming();

        benchmark::DoNotOptimize(map.erase(key));
    }
}
BENCHMARK(BM_StdUnorderedMapErase)->Range(1 << 10, 1 << 20);

// Benchmark insert with pre-reserved capacity
static void BM_UnorderedMapInsertReserved(benchmark::State &state) {
    dsc_unordered_map *map = unordered_map_create(sizeof(char *), sizeof(int),
                                                  string_hash, string_compare);
    unordered_map_reserve(map, state.range(0));

    for (auto _ : state) {
        state.PauseTiming();
        unordered_map_clear(map);
        state.ResumeTiming();

        for (size_t i = 0; i < state.range(0); ++i) {
            std::string key = random_string(10);
            int value = i;
            unordered_map_insert(map, &key, &value);
        }
    }

    unordered_map_destroy(map);
}
BENCHMARK(BM_UnorderedMapInsertReserved)->Range(1 << 10, 1 << 20);

// Benchmark std::unordered_map insert with pre-reserved capacity
static void BM_StdUnorderedMapInsertReserved(benchmark::State &state) {
    std::unordered_map<std::string, int> map;
    map.reserve(state.range(0));

    for (auto _ : state) {
        state.PauseTiming();
        map.clear();
        state.ResumeTiming();

        for (size_t i = 0; i < state.range(0); ++i) {
            map[random_string(10)] = i;
        }
    }
}
BENCHMARK(BM_StdUnorderedMapInsertReserved)->Range(1 << 10, 1 << 20);

// Benchmark mixed operations pattern
static void BM_UnorderedMapMixedOps(benchmark::State &state) {
    dsc_unordered_map *map = unordered_map_create(sizeof(char *), sizeof(int),
                                                  string_hash, string_compare);
    std::vector<std::string> keys;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (auto _ : state) {
        std::string key = random_string(10);
        int value = 42;

        // Randomly choose between insert, find, and erase
        std::uniform_int_distribution<> dis(0, 2);
        int op = dis(gen);

        switch (op) {
            case 0:  // Insert
                benchmark::DoNotOptimize(
                    unordered_map_insert(map, &key, &value));
                keys.push_back(key);
                break;
            case 1:  // Find
                if (!keys.empty()) {
                    size_t idx = gen() % keys.size();
                    benchmark::DoNotOptimize(
                        unordered_map_find(map, &keys[idx]));
                }
                break;
            case 2:  // Erase
                if (!keys.empty()) {
                    size_t idx = gen() % keys.size();
                    benchmark::DoNotOptimize(
                        unordered_map_erase(map, &keys[idx]));
                    keys.erase(keys.begin() + idx);
                }
                break;
        }
    }

    unordered_map_destroy(map);
}
BENCHMARK(BM_UnorderedMapMixedOps)->Range(1 << 10, 1 << 20);

// Benchmark std::unordered_map mixed operations
static void BM_StdUnorderedMapMixedOps(benchmark::State &state) {
    std::unordered_map<std::string, int> map;
    std::vector<std::string> keys;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (auto _ : state) {
        std::string key = random_string(10);

        // Randomly choose between insert, find, and erase
        std::uniform_int_distribution<> dis(0, 2);
        int op = dis(gen);

        switch (op) {
            case 0:  // Insert
                benchmark::DoNotOptimize(map[key] = 42);
                keys.push_back(key);
                break;
            case 1:  // Find
                if (!keys.empty()) {
                    size_t idx = gen() % keys.size();
                    benchmark::DoNotOptimize(map.find(keys[idx]));
                }
                break;
            case 2:  // Erase
                if (!keys.empty()) {
                    size_t idx = gen() % keys.size();
                    benchmark::DoNotOptimize(map.erase(keys[idx]));
                    keys.erase(keys.begin() + idx);
                }
                break;
        }
    }
}
BENCHMARK(BM_StdUnorderedMapMixedOps)->Range(1 << 10, 1 << 20);

// Benchmark collision handling (keys with same hash)
static void BM_UnorderedMapCollisions(benchmark::State &state) {
    dsc_unordered_map *map = unordered_map_create(sizeof(char *), sizeof(int),
                                                  string_hash, string_compare);
    std::vector<std::string> colliding_keys;

    // Generate keys that will have hash collisions
    for (size_t i = 0; i < state.range(0); ++i) {
        std::string base = random_string(8);
        colliding_keys.push_back(base + "aa");
        colliding_keys.push_back(
            base + "bb");  // Will likely collide due to similar pattern
    }

    for (auto _ : state) {
        state.PauseTiming();
        unordered_map_clear(map);
        state.ResumeTiming();

        for (size_t i = 0; i < colliding_keys.size(); ++i) {
            benchmark::DoNotOptimize(
                unordered_map_insert(map, &colliding_keys[i], &i));
        }
    }

    unordered_map_destroy(map);
}
BENCHMARK(BM_UnorderedMapCollisions)->Range(1 << 8, 1 << 16);

// Benchmark std::unordered_map collision handling
static void BM_StdUnorderedMapCollisions(benchmark::State &state) {
    std::unordered_map<std::string, int> map;
    std::vector<std::string> colliding_keys;

    // Generate keys that will have hash collisions
    for (size_t i = 0; i < state.range(0); ++i) {
        std::string base = random_string(8);
        colliding_keys.push_back(base + "aa");
        colliding_keys.push_back(
            base + "bb");  // Will likely collide due to similar pattern
    }

    for (auto _ : state) {
        state.PauseTiming();
        map.clear();
        state.ResumeTiming();

        for (size_t i = 0; i < colliding_keys.size(); ++i) {
            benchmark::DoNotOptimize(map[colliding_keys[i]] = i);
        }
    }
}
BENCHMARK(BM_StdUnorderedMapCollisions)->Range(1 << 8, 1 << 16);

// Benchmark load factor performance
static void BM_UnorderedMapLoadFactor(benchmark::State &state) {
    dsc_unordered_map *map = unordered_map_create(sizeof(char *), sizeof(int),
                                                  string_hash, string_compare);
    size_t target_size = state.range(0);
    unordered_map_reserve(map, target_size / 2);  // Force higher load factor

    for (auto _ : state) {
        std::string key = random_string(10);
        int value = 42;
        benchmark::DoNotOptimize(unordered_map_insert(map, &key, &value));

        if (unordered_map_size(map) >= target_size) {
            state.PauseTiming();
            unordered_map_clear(map);
            state.ResumeTiming();
        }
    }

    unordered_map_destroy(map);
}
BENCHMARK(BM_UnorderedMapLoadFactor)->Range(1 << 10, 1 << 20);

// Benchmark std::unordered_map load factor
static void BM_StdUnorderedMapLoadFactor(benchmark::State &state) {
    std::unordered_map<std::string, int> map;
    size_t target_size = state.range(0);
    map.max_load_factor(0.8f);
    map.reserve(target_size / 2);  // Force higher load factor

    for (auto _ : state) {
        std::string key = random_string(10);
        benchmark::DoNotOptimize(map[key] = 42);

        if (map.size() >= target_size) {
            state.PauseTiming();
            map.clear();
            state.ResumeTiming();
        }
    }
}
BENCHMARK(BM_StdUnorderedMapLoadFactor)->Range(1 << 10, 1 << 20);

BENCHMARK_MAIN();
