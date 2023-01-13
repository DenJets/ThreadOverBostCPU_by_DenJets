#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <windows.h>

void proc()
{
    using namespace std::chrono_literals;
    while (true);
    std::this_thread::sleep_for(5s);
}

int main()
{
    std::vector<std::thread> thr;
    for (unsigned int i = 0; i < std::thread::hardware_concurrency(); ++i) 
    {
        std::cout << "CPU Over Bust - ID: " << i << "\n";
        thr.emplace_back(proc);
        if (SetThreadAffinityMask(thr.back().native_handle(), DWORD_PTR(1) << i) == 0)
            std::cerr << "Error: " << GetLastError() << '\n';
    }
    for (auto& OverBoost : thr)
        OverBoost.join();
}