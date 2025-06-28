#pragma once
#include <iostream>
#include <cmath>

enum operations_e
{
    none = 1,
    scalpel_e = 1 << 1,
    hemostat_e = 1 << 2,
    tweezers_e = 1 << 3,
    suture_e = 1 << 4,
};

struct scalpel_st
{
    double x = 0;
    double y = 0;
};

struct hemostat_st
{
    double p = 0;
};

struct tweezers_st
{
    double p = 0;
};

struct suture_st
{
    double x = 0;
    double y = 0;
};

bool cut_off(double& x, double& y, const int& factor)
{
    x = std::round(x * factor) / factor;
    y = std::round(y * factor) / factor;
    if (x == y)
    {
        std::cerr << "\n**ERROR MATCH VALUES**\n\n";
        return false;
    }
    if (x > y)
        std::swap(x, y);
    std::cout << "\nCut off from " << x << " to " << y << std::endl << std::endl;
    return true;
}

bool clamped(double& x, double& y, double& p, const int& factor)
{
    p = std::round(p * factor) / factor;
    if (p < x || p > y)
    {
        std::cerr << "\n**OUT OF CUT**\n\n";
        return false;
    }
    std::cout << "\nClamped in " << p << std::endl << std::endl;
    return true;
}

bool pincers_f(double& x, double& y, double& p, const int& factor)
{
    p = std::round(p * factor) / factor;
    if (p < x || p > y)
    {
        std::cerr << "\n**OUT OF CUT**\n\n";
        return false;
    }
    std::cout << "\nTweezers in " << p << std::endl << std::endl;
    return true;
}

bool sutured(double& x_s, double& y_s, double& x, double& y, const int& factor)
{
    x = std::round(x * factor) / factor;
    y = std::round(y * factor) / factor;
    if (x > y)
        std::swap(x, y);
    if (x != x_s || y != y_s)
    {
        std::cerr << "\n**SUTURE MUST MATCH CUT**\n\n";
        return false;
    }
    std::cout << "\nSutured from " << x << " to " << y << std::endl << std::endl;
    return true;
}
