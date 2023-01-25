#include <iostream>
#include <chrono>
#include <thread>

struct Timer
{
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<float> duration;

    Timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;

        float ms = duration.count() * 1000;
        std::cout << ms << "ms" << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    using namespace std::chrono_literals;

    Timer t;
    std::this_thread::sleep_for(1s);

    return 0;
}
