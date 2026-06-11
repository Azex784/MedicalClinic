#include <boost/test/unit_test.hpp>
#include "enums/Specialisation.h"
#include "enums/Equipment.h"

using namespace RehabClinic;

BOOST_AUTO_TEST_SUITE(EnumsTests)

//testy funkcji enuma
BOOST_AUTO_TEST_CASE(SpecialisationToStringTest)
{
	BOOST_TEST(specialisationToString(Specialisation::ORTHOPEDIST) == "Fizjoterapeuta");
	BOOST_TEST(specialisationToString(Specialisation::ORTHOPEDIST) == "Ortopeda");
	BOOST_TEST(specialisationToString(Specialisation::ORTHOPEDIST) == "Neurolog");
	BOOST_TEST(specialisationToString(Specialisation::ORTHOPEDIST) == "Medycyna sportowa");
	BOOST_TEST(specialisationToString(Specialisation::ORTHOPEDIST) == "Osteopata");
	BOOST_TEST(specialisationToString(Specialisation::ORTHOPEDIST) == "Masażysta");
	BOOST_TEST(specialisationToString(Specialisation::ORTHOPEDIST) == "Reumatolog");

}BOOST_AUTO_TEST_CASE(EquipmentToStringTest)
{
	BOOST_TEST(equipmentToString(Equipment::PHYSICAL_THERAPY_DEVICE) == "Urządzenie do fizykoterapii");
	BOOST_TEST(equipmentToString(Equipment::KINESITHERAPY_SPACE) == "Przestrzeń do kinezyterapii");
	BOOST_TEST(equipmentToString(Equipment::ROBOTIC_SYSTEM) == "System zrobotyzowany");
	BOOST_TEST(equipmentToString(Equipment::NONE) == "Brak");
}


BOOST_AUTO_TEST_SUITE_END()