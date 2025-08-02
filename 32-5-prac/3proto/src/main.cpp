#include <iostream>
#include <string>

struct Enterprise {
    int32_t foundation_year;          
    std::string legal_address;        
    std::string name;                 

    bool has_activity_type = false;
    std::string activity_type;        
    bool has_foreign_economic_activity = false;
    bool foreign_economic_activity;   
};

int main() {
    Enterprise ent;

    ent.foundation_year = 2001;
    ent.legal_address = "456 Example Avenue, Big City";
    ent.name = "Tech Solutions";

    ent.has_activity_type = true;
    ent.activity_type = "Software Development";

    ent.has_foreign_economic_activity = true;
    ent.foreign_economic_activity = false;

    std::cout << "Enterprise info:" << std::endl;
    std::cout << "Foundation year: " << ent.foundation_year << std::endl;
    std::cout << "Legal address: " << ent.legal_address << std::endl;
    std::cout << "Name: " << ent.name << std::endl;
    if (ent.has_activity_type)
        std::cout << "Activity type: " << ent.activity_type << std::endl;
    else
        std::cout << "Activity type: (not set)" << std::endl;
    if (ent.has_foreign_economic_activity)
        std::cout << "Foreign economic activity: "
        << (ent.foreign_economic_activity ? "Yes" : "No") << std::endl;
    else
        std::cout << "Foreign economic activity: (not set)" << std::endl;

}
