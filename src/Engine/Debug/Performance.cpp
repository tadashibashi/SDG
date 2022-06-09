#include "Performance.h"
#include <chrono>
#include <iostream>
#include <map>
#include <utility>

using std::chrono::duration_cast;
using std::chrono::system_clock;
using std::chrono::microseconds;
using std::chrono::time_point;
using std::string;
using std::map;
using std::cout;

static map<string, time_point<system_clock>> tests;

void SDG::Performance::Start(const string &testName)
{

}

SDG::PerformanceResult
SDG::Performance::End(const std::string &testName)
{
    auto end = system_clock::now();
    auto it = tests.find(testName);
    if (it == tests.end())
    {
        cout << "SDG::Performance: error: Could not find test \"" << testName << "\"\n";
        return SDG::PerformanceResult();
    }
    else
    {
        double total = duration_cast<microseconds>(end - it->second).count();
        tests.erase(it);
        return SDG::PerformanceResult(testName, total);
    }
}

SDG::PerformanceResult::PerformanceResult(std::string taskName, double microseconds)
    : taskName(std::move(taskName)), microseconds(microseconds)
{

}

void SDG::PerformanceResult::Log()
{
    cout << "[" << taskName << "] took " << Milliseconds() << " ms" << '\n';
}
