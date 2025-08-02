#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

void findActorMovies(const json& db, const std::string& actor_name) {
    bool found = false;
    for (auto& [movie_title, movie_info] : db.items()) {
        const json& cast = movie_info["main_cast"];
        for (const json& member : cast) {
            std::string actor = member["actor"];
            if (actor.find(actor_name) != std::string::npos) {
                found = true;
                std::cout << "Movie: " << movie_title
                    << ", Role: " << member["character"] << std::endl;
            }
        }
    }
    if (!found) {
        std::cout << "Actor with name or surname \"" << actor_name << "\" not found in the database." << std::endl;
    }
}

int main() {
    json filmDb = {
        {"Inception", {
            {"country", {"USA", "UK"}},
            {"release_date", "2010-07-16"},
            {"production_studios", {"Warner Bros.", "Legendary Entertainment", "Syncopy"}},
            {"screenplay_author", "Christopher Nolan"},
            {"director", "Christopher Nolan"},
            {"producers", {"Emma Thomas", "Christopher Nolan"}},
            {"main_cast", {
                {{"character", "Dom Cobb"}, {"actor", "Leonardo DiCaprio"}},
                {{"character", "Arthur"}, {"actor", "Joseph Gordon-Levitt"}},
                {{"character", "Ariadne"}, {"actor", "Elliot Page"}}
            }}
        }},

        {"The Matrix", {
            {"country", {"USA"}},
            {"release_date", "1999-03-31"},
            {"production_studios", {"Warner Bros."}},
            {"screenplay_author", "The Wachowskis"},
            {"director", "The Wachowskis"},
            {"producers", {"Joel Silver"}},
            {"main_cast", {
                {{"character", "Neo"}, {"actor", "Keanu Reeves"}},
                {{"character", "Morpheus"}, {"actor", "Laurence Fishburne"}},
                {{"character", "Trinity"}, {"actor", "Carrie-Anne Moss"}}
            }}
        }},

        {"The Dark Knight", {
            {"country", {"USA", "UK"}},
            {"release_date", "2008-07-18"},
            {"production_studios", {"Warner Bros.", "Legendary Entertainment"}},
            {"screenplay_author", "Jonathan Nolan"},
            {"director", "Christopher Nolan"},
            {"producers", {"Emma Thomas", "Charles Roven"}},
            {"main_cast", {
                {{"character", "Bruce Wayne / Batman"}, {"actor", "Christian Bale"}},
                {{"character", "Joker"}, {"actor", "Heath Ledger"}},
                {{"character", "Harvey Dent"}, {"actor", "Aaron Eckhart"}}
            }}
        }},

        {"Pulp Fiction", {
            {"country", {"USA"}},
            {"release_date", "1994-10-14"},
            {"production_studios", {"Miramax"}},
            {"screenplay_author", "Quentin Tarantino"},
            {"director", "Quentin Tarantino"},
            {"producers", {"Lawrence Bender"}},
            {"main_cast", {
                {{"character", "Vincent Vega"}, {"actor", "John Travolta"}},
                {{"character", "Jules Winnfield"}, {"actor", "Samuel L. Jackson"}},
                {{"character", "Mia Wallace"}, {"actor", "Uma Thurman"}}
            }}
        }},

        {"Fight Club", {
            {"country", {"USA"}},
            {"release_date", "1999-10-15"},
            {"production_studios", {"20th Century Fox"}},
            {"screenplay_author", "Jim Uhls"},
            {"director", "David Fincher"},
            {"producers", {"Art Linson"}},
            {"main_cast", {
                {{"character", "The Narrator"}, {"actor", "Edward Norton"}},
                {{"character", "Tyler Durden"}, {"actor", "Brad Pitt"}},
                {{"character", "Marla Singer"}, {"actor", "Helena Bonham Carter"}}
            }}
        }}
    };

    std::ofstream file("filmDb.json");
    file << filmDb.dump(4);
    file.close();

    std::cout << "Enter actor's name or surname to search: ";
    std::string query;
    std::getline(std::cin, query);

    findActorMovies(filmDb, query);
}
