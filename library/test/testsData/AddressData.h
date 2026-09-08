//
// Created by azex on 9/7/26.
//

#ifndef MEDICALCLINIC_ADDRESSDATA_H
#define MEDICALCLINIC_ADDRESSDATA_H
#include <string>
#include <vector>

namespace data
{
    const std::vector<std::string> cities = {
        "Warszawa",
        "Kraków",
        "Wrocław",
        "Poznań",
        "Gdańsk",
        "Łódź",
        "Szczecin",
        "Katowice",
        "Lublin",
        "Toruń"
    };

    const std::vector<std::string> streets = {
        "Marszałkowska",
        "Floriańska",
        "Świdnicka",
        "Półwiejska",
        "Długi Targ",
        "Piotrkowska",
        "Aleja Wojska Polskiego",
        "Mariacka",
        "Krakowskie Przedmieście",
        "Szeroka"
    };

    const std::vector<std::string> numbers = {
        "10/15",
        "22",
        "5",
        "42",
        "39",
        "104",
        "15",
        "7",
        "34",
        "12"
    };
}


#endif //MEDICALCLINIC_ADDRESSDATA_H
