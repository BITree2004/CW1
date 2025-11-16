#include "../include/quicksort.h"

// the const of the program
constexpr size_t VECTOR_SIZE = 100'000'000;
constexpr size_t NUM_RUNS = 5;
constexpr size_t NUM_THREADS = 4;

void run_benchmark() {
    std::cout << "Vector size: " << VECTOR_SIZE << " elements" << std::endl;
    std::cout << "Number of runs: " << NUM_RUNS << std::endl;
    std::cout << "Number of threads: " << NUM_THREADS << std::endl;

    setenv("PARLAY_NUM_THREADS", std::to_string(NUM_THREADS).c_str(), 1);

    std::vector<long double> seq_times;
    std::vector<long double> par_times;

    for (int i = 1; i <= NUM_RUNS; ++i) {
        std::cout << "Run " << i << " of " << NUM_RUNS << std::endl;

        const auto seed = static_cast<unsigned>(239/*std::time(nullptr)*/ + i * 1000);
        auto arr = generate_random_array<int>(VECTOR_SIZE, seed);

        auto arr_seq = arr;
        auto seq_time = measure_time([&]() {
            sequential_quicksort(arr_seq);
        });
        assert(std::ranges::is_sorted(arr_seq));
        seq_times.push_back(seq_time);
        std::cout << "Sequential time: " << std::fixed << std::setprecision(2) << seq_time << " seconds" << std::endl;

        auto arr_par = arr;
        auto par_time = measure_time([&]() {
            parallel_quicksort(arr_par);
        });
        assert(std::ranges::is_sorted(arr_seq));
        par_times.push_back(par_time);
        std::cout << "Parallel time:   " << std::fixed << std::setprecision(2) << par_time << " seconds" << std::endl;

        // Небольшая пауза для стабилизации системы
        if (i < NUM_RUNS) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

    auto avg_seq_time = static_cast<long double>(0.0);
    auto avg_par_time = static_cast<long double>(0.0);
    for (std::size_t i = 0; i < NUM_RUNS; ++i) {
        avg_seq_time += seq_times[i];
        avg_par_time += par_times[i];
    }
    avg_seq_time /= NUM_RUNS;
    avg_par_time /= NUM_RUNS;

    auto speedup = avg_seq_time / avg_par_time;

    std::cout << std::fixed << std::setprecision(2)
            << "Average seq time: " << avg_seq_time << " seconds\n"
            << "Average par time: " << avg_par_time << " seconds\n"
            << "Speedup: " << speedup << "x" << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    run_benchmark();
    return 0;
}
