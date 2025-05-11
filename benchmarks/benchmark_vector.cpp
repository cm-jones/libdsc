#include <libdsc/vector.h>
#include <benchmark/benchmark.h>
#include <vector>
#include <random>

// Benchmark size operation
static void BM_VectorSize(benchmark::State& state) {
    dsc_vector_t* vec = vector_create(sizeof(int));
    int value = 42;
    for (int i = 0; i < 1000; ++i) {
        vector_push_back(vec, &value);
    }
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(vector_size(vec));
    }
    
    vector_destroy(vec);
}
BENCHMARK(BM_VectorSize)->Range(1<<10, 1<<20);

// Benchmark std::vector size
static void BM_StdVectorSize(benchmark::State& state) {
    std::vector<int> vec;
    for (int i = 0; i < 1000; ++i) {
        vec.push_back(42);
    }
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(vec.size());
    }
}
BENCHMARK(BM_StdVectorSize)->Range(1<<10, 1<<20);

// Benchmark empty check
static void BM_VectorEmpty(benchmark::State& state) {
    dsc_vector_t* vec = vector_create(sizeof(int));
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(vector_empty(vec));
    }
    
    vector_destroy(vec);
}
BENCHMARK(BM_VectorEmpty)->Range(1<<10, 1<<20);

// Benchmark std::vector empty
static void BM_StdVectorEmpty(benchmark::State& state) {
    std::vector<int> vec;
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(vec.empty());
    }
}
BENCHMARK(BM_StdVectorEmpty)->Range(1<<10, 1<<20);

// Benchmark capacity check
static void BM_VectorCapacity(benchmark::State& state) {
    dsc_vector_t* vec = vector_create(sizeof(int));
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(vector_capacity(vec));
    }
    
    vector_destroy(vec);
}
BENCHMARK(BM_VectorCapacity)->Range(1<<10, 1<<20);

// Benchmark std::vector capacity
static void BM_StdVectorCapacity(benchmark::State& state) {
    std::vector<int> vec;
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(vec.capacity());
    }
}
BENCHMARK(BM_StdVectorCapacity)->Range(1<<10, 1<<20);

// Benchmark clear operation - Improved version that should not hang
static void BM_VectorClear(benchmark::State& state) {
    dsc_vector_t* vec = vector_create(sizeof(int));
    int value = 42;
    const size_t size = state.range(0);
    
    // Pre-fill vector once before starting benchmark loop
    for (size_t i = 0; i < size; ++i) {
        vector_push_back(vec, &value);
    }
    
    for (auto _ : state) {
        vector_clear(vec);  // Removed DoNotOptimize since clear returns void
        
        state.PauseTiming();
        // Refill vector for next iteration
        for (size_t i = 0; i < size; ++i) {
            vector_push_back(vec, &value);
        }
        state.ResumeTiming();
    }
    
    vector_destroy(vec);
}
BENCHMARK(BM_VectorClear)->Range(1<<10, 1<<20);

// Benchmark std::vector clear - Improved version that should not hang
static void BM_StdVectorClear(benchmark::State& state) {
    std::vector<int> vec;
    const size_t size = state.range(0);
    
    // Pre-fill vector once before starting benchmark loop
    for (size_t i = 0; i < size; ++i) {
        vec.push_back(42);
    }
    
    for (auto _ : state) {
        vec.clear();  // Removed DoNotOptimize since clear returns void
        
        state.PauseTiming();
        // Refill vector for next iteration
        for (size_t i = 0; i < size; ++i) {
            vec.push_back(42);
        }
        state.ResumeTiming();
    }
}
BENCHMARK(BM_StdVectorClear)->Range(1<<10, 1<<20);

// Benchmark push_back operation
static void BM_VectorPushBack(benchmark::State& state) {
    dsc_vector_t* vec = vector_create(sizeof(int));
    int value = state.range(0);
    
    for (auto _ : state) {
        vector_push_back(vec, &value);
    }
    
    vector_destroy(vec);
}
BENCHMARK(BM_VectorPushBack)->Range(1, 1<<20);

// Benchmark std::vector push_back
static void BM_StdVectorPushBack(benchmark::State& state) {
    std::vector<int> vec;
    int value = state.range(0);
    
    for (auto _ : state) {
        vec.push_back(value);
    }
}
BENCHMARK(BM_StdVectorPushBack)->Range(1, 1<<20);

BENCHMARK_MAIN();
