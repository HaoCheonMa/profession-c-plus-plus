#include "operations.h"
#include <string>
#include <limits>
#include <map>
#include <iostream>

int main()
{
    const int factor = 100;
    int operations = none;
    std::cout << "\n**CMDs: scalpel, hemostat, tweezers, suture**\n\n";
    std::string cmd;

    scalpel_st cut;
    hemostat_st clamp;
    tweezers_st pincers;
    suture_st spine;

    std::map<std::string, char> cmds;
    cmds.insert({ "scalpel", '.' });
    cmds.insert({ "hemostat", '.' });
    cmds.insert({ "tweezers", '.' });
    cmds.insert({ "suture", '.' });

    while (true)
    {
        std::cout << "Input tool: ";
        std::cin >> cmd;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        auto it = cmds.find(cmd);
        if (it == cmds.end())
        {
            std::cerr << "\n**UNKNOWN TOOL**\n\n";
            continue;
        }

        if ((operations & none) && cmd == "scalpel")
        {
            while (true)
            {
                std::cout << "Input x y: ";
                std::cin >> cut.x >> cut.y;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (std::cin.fail())
                {
                    std::cerr << "\n**INVALID VALUES**\n\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                if (!cut_off(cut.x, cut.y, factor))
                    continue;
                break;
            }
            operations |= scalpel_e;
            operations &= ~none;
            continue;
        }
        else if ((operations & scalpel_e) && cmd == "hemostat")
        {
            while (true)
            {
                std::cout << "Input point: ";
                std::cin >> clamp.p;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (std::cin.fail())
                {
                    std::cerr << "\n**INVALID VALUE**\n\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                if (!clamped(cut.x, cut.y, clamp.p, factor))
                    continue;
                break;
            }
            operations |= hemostat_e;
        }
        else if ((operations & hemostat_e) && cmd == "tweezers")
        {
            while (true)
            {
                std::cout << "Input point: ";
                std::cin >> pincers.p;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (std::cin.fail())
                {
                    std::cerr << "\n**INVALID VALUE**\n\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                if (pincers.p < cut.x || pincers.p > cut.y)
                {
                    std::cerr << "\n**OUT OFF CUT**\n\n";
                    continue;
                }
                if(!pincers_f(cut.x, cut.y, pincers.p, factor))
                    continue;
                break;
            }
            operations |= tweezers_e;
            continue;
        }
        else if ((operations & tweezers_e) && cmd == "suture")
        {
            while (true)
            {
                std::cout << "Input x y: ";
                std::cin >> spine.x >> spine.y;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (std::cin.fail())
                {
                    std::cerr << "\n**INVALID VALUES**\n\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                if (!sutured(cut.x, cut.y, spine.x, spine.y, factor))
                    continue;
                break;
            }
            operations |= suture_e;
        }
        else
        {
            std::cerr << "\n**WRONG ORDER**\n\n";
            continue;
        }

        if ((operations & scalpel_e) && (operations & hemostat_e) && (operations & tweezers_e) && (operations & suture_e))
            break;
    }
    std::cout << "**SUCCESSFUL OPERATION**\n\n";
}
