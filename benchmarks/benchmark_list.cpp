#include <benchmark/benchmark.h>

#include <list>

#include "libdsc/list.h"

// Benchmark push_front
static void BM_ListPushFront(benchmark::State &state) {
    dsc_list_t *list = list_create(sizeof(int));

    for (auto _ : state) {
        int value = 42;
        benchmark::DoNotOptimize(list_push_front(list, &value));
    }

    list_destroy(list);
}
BENCHMARK(BM_ListPushFront)->Range(1, 1 << 20);

// Benchmark std::list push_front
static void BM_StdListPushFront(benchmark::State &state) {
    std::list<int> list;

    for (auto _ : state) {
        list.push_front(42);
        benchmark::DoNotOptimize(list);
    }
}
BENCHMARK(BM_StdListPushFront)->Range(1, 1 << 20);

// Benchmark push_back
static void BM_ListPushBack(benchmark::State &state) {
    dsc_list_t *list = list_create(sizeof(int));

    for (auto _ : state) {
        int value = 42;
        benchmark::DoNotOptimize(list_push_back(list, &value));
    }

    list_destroy(list);
}
BENCHMARK(BM_ListPushBack)->Range(1, 1 << 20);

// Benchmark std::list push_back
static void BM_StdListPushBack(benchmark::State &state) {
    std::list<int> list;

    for (auto _ : state) {
        list.push_back(42);
        benchmark::DoNotOptimize(list);
    }
}
BENCHMARK(BM_StdListPushBack)->Range(1, 1 << 20);

// Benchmark push_front and pop_front
static void BM_ListPushPopFront(benchmark::State &state) {
    dsc_list_t *list = list_create(sizeof(int));

    for (auto _ : state) {
        int value = 42;
        list_push_front(list, &value);
        list_pop_front(list);
    }

    list_destroy(list);
}
BENCHMARK(BM_ListPushPopFront)->Range(1, 1 << 20);

// Benchmark std::list push_front and pop_front
static void BM_StdListPushPopFront(benchmark::State &state) {
    std::list<int> list;

    for (auto _ : state) {
        list.push_front(42);
        list.pop_front();
    }
}
BENCHMARK(BM_StdListPushPopFront)->Range(1, 1 << 20);

// Benchmark push_back and pop_back
static void BM_ListPushPopBack(benchmark::State &state) {
    dsc_list_t *list = list_create(sizeof(int));

    for (auto _ : state) {
        int value = 42;
        list_push_back(list, &value);
        list_pop_back(list);
    }

    list_destroy(list);
}
BENCHMARK(BM_ListPushPopBack)->Range(1, 1 << 20);

// Benchmark std::list push_back and pop_back
static void BM_StdListPushPopBack(benchmark::State &state) {
    std::list<int> list;

    for (auto _ : state) {
        list.push_back(42);
        list.pop_back();
    }
}
BENCHMARK(BM_StdListPushPopBack)->Range(1, 1 << 20);

// Benchmark front access
static void BM_ListFront(benchmark::State &state) {
    dsc_list_t *list = list_create(sizeof(int));
    int value = 42;
    list_push_front(list, &value);

    for (auto _ : state) {
        benchmark::DoNotOptimize(list_front(list));
    }

    list_destroy(list);
}
BENCHMARK(BM_ListFront)->Range(1 << 10, 1 << 20);

// Benchmark std::list front access
static void BM_StdListFront(benchmark::State &state) {
    std::list<int> list;
    list.push_front(42);

    for (auto _ : state) {
        benchmark::DoNotOptimize(list.front());
    }
}
BENCHMARK(BM_StdListFront)->Range(1 << 10, 1 << 20);

// Benchmark back access
static void BM_ListBack(benchmark::State &state) {
    dsc_list_t *list = list_create(sizeof(int));
    int value = 42;
    list_push_back(list, &value);

    for (auto _ : state) {
        benchmark::DoNotOptimize(list_back(list));
    }

    list_destroy(list);
}
BENCHMARK(BM_ListBack)->Range(1 << 10, 1 << 20);

// Benchmark std::list back access
static void BM_StdListBack(benchmark::State &state) {
    std::list<int> list;
    list.push_back(42);

    for (auto _ : state) {
        benchmark::DoNotOptimize(list.back());
    }
}
BENCHMARK(BM_StdListBack)->Range(1 << 10, 1 << 20);

// Benchmark size operation
static void BM_ListSize(benchmark::State &state) {
    dsc_list_t *list = list_create(sizeof(int));
    int value = 42;
    for (size_t i = 0; i < 1000; ++i) {
        list_push_front(list, &value);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(list_size(list));
    }

    list_destroy(list);
}
BENCHMARK(BM_ListSize)->Range(1 << 10, 1 << 20);

// Benchmark std::list size
static void BM_StdListSize(benchmark::State &state) {
    std::list<int> list;
    for (size_t i = 0; i < 1000; ++i) {
        list.push_front(42);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(list.size());
    }
}
BENCHMARK(BM_StdListSize)->Range(1 << 10, 1 << 20);

// Benchmark empty check
static void BM_ListEmpty(benchmark::State &state) {
    dsc_list_t *list = list_create(sizeof(int));

    for (auto _ : state) {
        benchmark::DoNotOptimize(list_empty(list));
    }

    list_destroy(list);
}
BENCHMARK(BM_ListEmpty)->Range(1 << 10, 1 << 20);

// Benchmark std::list empty
static void BM_StdListEmpty(benchmark::State &state) {
    std::list<int> list;

    for (auto _ : state) {
        benchmark::DoNotOptimize(list.empty());
    }
}
BENCHMARK(BM_StdListEmpty)->Range(1 << 10, 1 << 20);

// Benchmark insert operation
static void BM_ListInsert(benchmark::State &state) {
    dsc_list_t *list = list_create(sizeof(int));
    int value = 42;
    
    for (auto _ : state) {
        state.PauseTiming();
        list_clear(list);  // Clear any previous nodes
        list_push_back(list, &value);  // Add initial node
        list_node_t *pos = list_begin(list);  // Get fresh position
        state.ResumeTiming();
        
        benchmark::DoNotOptimize(list_insert(list, pos, &value));
    }
    
    list_destroy(list);
}
BENCHMARK(BM_ListInsert)->Range(1 << 10, 1 << 20);

// Benchmark std::list insert
static void BM_StdListInsert(benchmark::State &state) {
    std::list<int> list;
    list.push_back(42);
    auto pos = list.begin();

    for (auto _ : state) {
        auto inserted = list.insert(pos, 42);
        benchmark::DoNotOptimize(list);
        state.PauseTiming();
        list.erase(inserted);
        state.ResumeTiming();
    }
}
BENCHMARK(BM_StdListInsert)->Range(1 << 10, 1 << 20);

// Benchmark erase operation
static void BM_ListErase(benchmark::State &state) {
    dsc_list_t *list = list_create(sizeof(int));
    int value = 42;
    list_push_back(list, &value);
    list_push_back(list, &value);
    list_node_t *pos = list_begin(list)->next;

    for (auto _ : state) {
        benchmark::DoNotOptimize(list_erase(list, pos));
        state.PauseTiming();
        list_insert(list, list_begin(list), &value);  // Restore the erased node
        state.ResumeTiming();
    }

    list_destroy(list);
}
BENCHMARK(BM_ListErase)->Range(1 << 10, 1 << 20);

// Benchmark std::list erase
static void BM_StdListErase(benchmark::State &state) {
    std::list<int> list;
    list.push_back(42);
    list.push_back(42);
    auto pos = ++list.begin();

    for (auto _ : state) {
        auto next = list.erase(pos);
        benchmark::DoNotOptimize(list);
        state.PauseTiming();
        pos = list.insert(next, 42);
        state.ResumeTiming();
    }
}
BENCHMARK(BM_StdListErase)->Range(1 << 10, 1 << 20);

// Benchmark clear operation
static void BM_ListClear(benchmark::State &state) {
    dsc_list_t *list = list_create(sizeof(int));
    int value = 42;

    for (auto _ : state) {
        state.PauseTiming();
        // Fill list
        for (size_t i = 0; i < state.range(0); ++i) {
            list_push_back(list, &value);
        }
        state.ResumeTiming();

        list_clear(list);
    }

    list_destroy(list);
}
BENCHMARK(BM_ListClear)->Range(1 << 10, 1 << 20);

// Benchmark std::list clear
static void BM_StdListClear(benchmark::State &state) {
    std::list<int> list;

    for (auto _ : state) {
        state.PauseTiming();
        // Fill list
        for (size_t i = 0; i < state.range(0); ++i) {
            list.push_back(42);
        }
        state.ResumeTiming();

        list.clear();
    }
}
BENCHMARK(BM_StdListClear)->Range(1 << 10, 1 << 20);

// Benchmark forward iterator traversal
static void BM_ListForwardTraversal(benchmark::State &state) {
    dsc_list_t *list = list_create(sizeof(int));
    int value = 42;
    for (size_t i = 0; i < 1000; ++i) {
        list_push_back(list, &value);
    }

    for (auto _ : state) {
        list_node_t *it = list_begin(list);
        while (it != list_end(list)) {
            benchmark::DoNotOptimize(it);
            it = it->next;
        }
    }

    list_destroy(list);
}
BENCHMARK(BM_ListForwardTraversal)->Range(1 << 10, 1 << 20);

// Benchmark std::list forward traversal
static void BM_StdListForwardTraversal(benchmark::State &state) {
    std::list<int> list;
    for (size_t i = 0; i < 1000; ++i) {
        list.push_back(42);
    }

    for (auto _ : state) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            benchmark::DoNotOptimize(*it);
        }
    }
}
BENCHMARK(BM_StdListForwardTraversal)->Range(1 << 10, 1 << 20);

// Benchmark reverse iterator traversal
static void BM_ListReverseTraversal(benchmark::State &state) {
    dsc_list_t *list = list_create(sizeof(int));
    int value = 42;
    for (size_t i = 0; i < 1000; ++i) {
        list_push_back(list, &value);
    }

    for (auto _ : state) {
        list_node_t *it = list_rbegin(list);
        while (it != list_rend(list)) {
            benchmark::DoNotOptimize(it);
            it = it->prev;
        }
    }

    list_destroy(list);
}
BENCHMARK(BM_ListReverseTraversal)->Range(1 << 10, 1 << 20);

// Benchmark std::list reverse traversal
static void BM_StdListReverseTraversal(benchmark::State &state) {
    std::list<int> list;
    for (size_t i = 0; i < 1000; ++i) {
        list.push_back(42);
    }

    for (auto _ : state) {
        for (auto it = list.rbegin(); it != list.rend(); ++it) {
            benchmark::DoNotOptimize(*it);
        }
    }
}
BENCHMARK(BM_StdListReverseTraversal)->Range(1 << 10, 1 << 20);

BENCHMARK_MAIN();
