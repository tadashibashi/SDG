//
// Created by Aaron Ishibashi on 4/26/22.
//
#pragma once
#include <string>

namespace SDG
{
    class PerformanceResult
    {
    public:
        PerformanceResult(std::string taskName, double microSeconds);

        /// Creates a null result
        PerformanceResult() : taskName(), microseconds(-1) { }

        std::string TaskName() const { return taskName; }
        double Microseconds() const { return microseconds; }
        double Milliseconds() const { return microseconds * 0.001; }
        double Seconds() const { return microseconds * 0.000001; }
        bool IsValid() const { return microseconds >= 0; }
        void Log();
    private:
        std::string taskName;
        double microseconds;
    };

    class Performance
    {
    public:
        static void Start(const std::string &testName);
        static PerformanceResult End(const std::string &testName);
    };
}

