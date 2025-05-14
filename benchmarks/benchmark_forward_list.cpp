#include <benchmark/benchmark.h>

#include <forward_list>

#include "libdsc/forward_list.h"

// Benchmark push_front
static void BM_ForwardListPushFront(benchmark::State &state) {
    dsc_forward_list_t *list = forward_list_create(sizeof(int));

    for (auto _ : state) {
        int value = 42;
        benchmark::DoNotOptimize(forward_list_push_front(list, &value));
    }

    forward_list_destroy(list);
}
BENCHMARK(BM_ForwardListPushFront)->Range(1, 1 << 20);

// Benchmark std::forward_list push_front
static void BM_StdForwardListPushFront(benchmark::State &state) {
    std::forward_list<int> list;

    for (auto _ : state) {
        list.push_front(42);
        benchmark::DoNotOptimize(list);
    }
}
BENCHMARK(BM_StdForwardListPushFront)->Range(1, 1 << 20);

// Benchmark push_front and pop_front
static void BM_ForwardListPushPopFront(benchmark::State &state) {
    dsc_forward_list_t *list = forward_list_create(sizeof(int));

    for (auto _ : state) {
        int value = 42;
        forward_list_push_front(list, &value);
        forward_list_pop_front(list);
    }

    forward_list_destroy(list);
}
BENCHMARK(BM_ForwardListPushPopFront)->Range(1, 1 << 20);

// Benchmark std::forward_list push_front and pop_front
static void BM_StdForwardListPushPopFront(benchmark::State &state) {
    std::forward_list<int> list;

    for (auto _ : state) {
        list.push_front(42);
        list.pop_front();
    }
}
BENCHMARK(BM_StdForwardListPushPopFront)->Range(1, 1 << 20);

// Benchmark front access
static void BM_ForwardListFront(benchmark::State &state) {
    dsc_forward_list_t *list = forward_list_create(sizeof(int));
    int value = 42;
    forward_list_push_front(list, &value);

    for (auto _ : state) {
        benchmark::DoNotOptimize(forward_list_front(list));
    }

    forward_list_destroy(list);
}
BENCHMARK(BM_ForwardListFront)->Range(1 << 10, 1 << 20);

// Benchmark std::forward_list front access
static void BM_StdForwardListFront(benchmark::State &state) {
    std::forward_list<int> list;
    list.push_front(42);

    for (auto _ : state) {
        benchmark::DoNotOptimize(list.front());
    }
}
BENCHMARK(BM_StdForwardListFront)->Range(1 << 10, 1 << 20);

// Benchmark insert_after
static void BM_ForwardListInsertAfter(benchmark::State &state) {
    dsc_forward_list_t *list = forward_list_create(sizeof(int));
    int value = 42;
    forward_list_push_front(list, &value);
    forward_list_node_t *pos = forward_list_begin(list);

    for (auto _ : state) {
        benchmark::DoNotOptimize(forward_list_insert_after(list, pos, &value));
    }

    forward_list_destroy(list);
}
BENCHMARK(BM_ForwardListInsertAfter)->Range(1, 1 << 20);

// Benchmark std::forward_list insert_after
static void BM_StdForwardListInsertAfter(benchmark::State &state) {
    std::forward_list<int> list;
    list.push_front(42);
    auto pos = list.begin();

    for (auto _ : state) {
        list.insert_after(pos, 42);
        benchmark::DoNotOptimize(list);
    }
}
BENCHMARK(BM_StdForwardListInsertAfter)->Range(1, 1 << 20);

// Benchmark size operation
static void BM_ForwardListSize(benchmark::State &state) {
    dsc_forward_list_t *list = forward_list_create(sizeof(int));
    int value = 42;
    for (size_t i = 0; i < 1000; ++i) {
        forward_list_push_front(list, &value);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(forward_list_size(list));
    }

    forward_list_destroy(list);
}
BENCHMARK(BM_ForwardListSize)->Range(1 << 10, 1 << 20);

// Benchmark std::forward_list size
static void BM_StdForwardListSize(benchmark::State &state) {
    std::forward_list<int> list;
    for (size_t i = 0; i < 1000; ++i) {
        list.push_front(42);
    }

    for (auto _ : state) {
        size_t size = std::distance(list.begin(), list.end());
        benchmark::DoNotOptimize(size);
    }
}
BENCHMARK(BM_StdForwardListSize)->Range(1 << 10, 1 << 20);

// Benchmark empty check
static void BM_ForwardListEmpty(benchmark::State &state) {
    dsc_forward_list_t *list = forward_list_create(sizeof(int));

    for (auto _ : state) {
        benchmark::DoNotOptimize(forward_list_empty(list));
    }

    forward_list_destroy(list);
}
BENCHMARK(BM_ForwardListEmpty)->Range(1 << 10, 1 << 20);

// Benchmark std::forward_list empty
static void BM_StdForwardListEmpty(benchmark::State &state) {
    std::forward_list<int> list;

    for (auto _ : state) {
        benchmark::DoNotOptimize(list.empty());
    }
}
BENCHMARK(BM_StdForwardListEmpty)->Range(1 << 10, 1 << 20);

// Benchmark erase_after operation
static void BM_ForwardListEraseAfter(benchmark::State &state) {
    dsc_forward_list_t *list = forward_list_create(sizeof(int));
    int value = 42;
    forward_list_push_front(list, &value);
    forward_list_node_t *pos = forward_list_begin(list);
    forward_list_insert_after(list, pos, &value);  // Add a node to erase

    for (auto _ : state) {
        benchmark::DoNotOptimize(forward_list_erase_after(list, pos));
        state.PauseTiming();
        forward_list_insert_after(list, pos, &value);  // Restore the node
        state.ResumeTiming();
    }

    forward_list_destroy(list);
}
BENCHMARK(BM_ForwardListEraseAfter)->Range(1 << 10, 1 << 20);

// Benchmark std::forward_list erase_after
static void BM_StdForwardListEraseAfter(benchmark::State &state) {
    std::forward_list<int> list;
    list.push_front(42);
    auto pos = list.begin();
    list.insert_after(pos, 42);  // Add a node to erase

    for (auto _ : state) {
        benchmark::DoNotOptimize(list.erase_after(pos));
        state.PauseTiming();
        list.insert_after(pos, 42);  // Restore the node
        state.ResumeTiming();
    }
}
BENCHMARK(BM_StdForwardListEraseAfter)->Range(1 << 10, 1 << 20);

// Benchmark clear operation
static void BM_ForwardListClear(benchmark::State &state) {
    dsc_forward_list_t *list = forward_list_create(sizeof(int));
    int value = 42;

    for (auto _ : state) {
        state.PauseTiming();
        // Fill list
        for (size_t i = 0; i < state.range(0); ++i) {
            forward_list_push_front(list, &value);
        }
        state.ResumeTiming();

        forward_list_clear(list);
    }

    forward_list_destroy(list);
}
BENCHMARK(BM_ForwardListClear)->Range(1 << 10, 1 << 20);

// Benchmark std::forward_list clear
static void BM_StdForwardListClear(benchmark::State &state) {
    std::forward_list<int> list;

    for (auto _ : state) {
        state.PauseTiming();
        // Fill list
        for (size_t i = 0; i < state.range(0); ++i) {
            list.push_front(42);
        }
        state.ResumeTiming();

        list.clear();
    }
}
BENCHMARK(BM_StdForwardListClear)->Range(1 << 10, 1 << 20);

// Benchmark iterator operations (begin/end traversal)
static void BM_ForwardListTraversal(benchmark::State &state) {
    dsc_forward_list_t *list = forward_list_create(sizeof(int));
    int value = 42;
    for (size_t i = 0; i < 1000; ++i) {
        forward_list_push_front(list, &value);
    }

    for (auto _ : state) {
        forward_list_node_t *it = forward_list_begin(list);
        while (it != forward_list_end(list)) {
            benchmark::DoNotOptimize(it);
            it = it->next;
        }
    }

    forward_list_destroy(list);
}
BENCHMARK(BM_ForwardListTraversal)->Range(1 << 10, 1 << 20);

// Benchmark std::forward_list traversal
static void BM_StdForwardListTraversal(benchmark::State &state) {
    std::forward_list<int> list;
    for (size_t i = 0; i < 1000; ++i) {
        list.push_front(42);
    }

    for (auto _ : state) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            benchmark::DoNotOptimize(*it);
        }
    }
}
BENCHMARK(BM_StdForwardListTraversal)->Range(1 << 10, 1 << 20);

BENCHMARK_MAIN();
