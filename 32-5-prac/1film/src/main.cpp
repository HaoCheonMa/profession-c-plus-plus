#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main() {
    json inception = {
        {"title", "Inception"},
        {"original_title", "Inception"},
        {"country", {"USA", "Great Britain"}},
        {"release_date", "2010-07-16"},
        {"production_studios", {"Warner Bros.", "Legendary Entertainment", "Syncopy"}},
        {"screenplay_author", "Christopher Nolan"},
        {"director", "Christopher Nolan"},
        {"producers", {"Emma Thomas", "Christopher Nolan"}},
        {"main_cast", {
            {{"character", "Dom Cobb"}, {"actor", "Leonardo DiCaprio"}},
            {{"character", "Arthur"}, {"actor", "Joseph Gordon-Levitt"}},
            {{"character", "Ariadne"}, {"actor", "Elliot Page"}},
            {{"character", "Mal"}, {"actor", "Marion Cotillard"}},
            {{"character", "Eames"}, {"actor", "Tom Hardy"}},
            {{"character", "Saito"}, {"actor", "Ken Watanabe"}},
            {{"character", "Yusuf"}, {"actor", "Dileep Rao"}},
            {{"character", "Robert Fischer"}, {"actor", "Cillian Murphy"}},
            {{"character", "Peter Browning"}, {"actor", "Tom Berenger"}},
            {{"character", "Professor Miles"}, {"actor", "Michael Caine"}}
        }}
    };

    std::ofstream file("inception.json");
    file << inception.dump(1);
    file.close();
}
