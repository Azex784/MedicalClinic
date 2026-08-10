#include <boost/test/unit_test.hpp>
#include "enums/Specialisation.h"
#include "enums/Equipment.h"
#include "enums/Title.h"
#include "enums/Status.h"

using namespace MedicalClinic;

BOOST_AUTO_TEST_SUITE(EnumsTests)

//Testy funkcji enumów
BOOST_AUTO_TEST_CASE(SpecialisationToStringTest)
{
	BOOST_TEST(specialisationToString(Specialisation::CARDIOLOGIST) == "Kardiolog");
	BOOST_TEST(specialisationToString(Specialisation::NEUROLOGIST) == "Neurolog");
	BOOST_TEST(specialisationToString(Specialisation::ONCOLOGIST) == "Onkolog");
	BOOST_TEST(specialisationToString(Specialisation::PEDIATRICIAN) == "Pediatra");
	BOOST_TEST(specialisationToString(Specialisation::GENERAL_SURGEON) == "Chirurg ogólny");
	BOOST_TEST(specialisationToString(Specialisation::ANESTHESIOLOGIST) == "Anestezjolog");
	BOOST_TEST(specialisationToString(Specialisation::RADIOLOGIST) == "Radiolog");
	BOOST_TEST(specialisationToString(Specialisation::OPHTHALMOLOGIST) == "Okulista");
	BOOST_TEST(specialisationToString(Specialisation::GYNECOLOGIST) == "Ginekolog");
	BOOST_TEST(specialisationToString(Specialisation::UROLOGIST) == "Urolog");
	BOOST_TEST(specialisationToString(Specialisation::PULMONOLOGIST) == "Pulmonolog");
	BOOST_TEST(specialisationToString(Specialisation::GASTROENTEROLOGIST) == "Gastroenterolog");
	BOOST_TEST(specialisationToString(Specialisation::ENDOCRINOLOGIST) == "Endokrynolog");
	BOOST_TEST(specialisationToString(Specialisation::NEPHROLOGIST) == "Nefrolog");
	BOOST_TEST(specialisationToString(Specialisation::HEMATOLOGIST) == "Hematolog");
	BOOST_TEST(specialisationToString(Specialisation::ORTHOPEDIST) == "Ortopeda");
	BOOST_TEST(specialisationToString(Specialisation::DERMATOLOGIST) == "Dermatolog");
	BOOST_TEST(specialisationToString(Specialisation::PSYCHIATRIST) == "Psychiatra");
	BOOST_TEST(specialisationToString(Specialisation::INTERNIST) == "Internista");
	BOOST_TEST(specialisationToString(Specialisation::EMERGENCY_PHYSICIAN) == "Lekarz medycyny ratunkowej");
	BOOST_TEST(specialisationToString(Specialisation::LARYNGOLOGIST) == "Laryngolog");
}

BOOST_AUTO_TEST_CASE(EquipmentToStringTest)
{
	BOOST_TEST(equipmentToString(Equipment::NONE) == "Brak");
	BOOST_TEST(equipmentToString(Equipment::DEFIBRILLATOR) == "Defibrylator");
	BOOST_TEST(equipmentToString(Equipment::ECG_MACHINE) == "Aparat EKG");
	BOOST_TEST(equipmentToString(Equipment::PATIENT_MONITOR) == "Monitor pacjenta");
	BOOST_TEST(equipmentToString(Equipment::VENTILATOR) == "Respirator");
	BOOST_TEST(equipmentToString(Equipment::INFUSION_PUMP) == "Pompa infuzyjna");
	BOOST_TEST(equipmentToString(Equipment::ULTRASOUND_MACHINE) == "Aparat USG");
	BOOST_TEST(equipmentToString(Equipment::X_RAY_MACHINE) == "Aparat RTG");
	BOOST_TEST(equipmentToString(Equipment::CT_SCANNER) == "Tomograf komputerowy");
	BOOST_TEST(equipmentToString(Equipment::MRI_SCANNER) == "Rezonans magnetyczny");
	BOOST_TEST(equipmentToString(Equipment::ANESTHESIA_MACHINE) == "Aparat do znieczulenia");
	BOOST_TEST(equipmentToString(Equipment::SURGICAL_TABLE) == "Stół operacyjny");
	BOOST_TEST(equipmentToString(Equipment::INCUBATOR) == "Inkubator");
}

BOOST_AUTO_TEST_CASE(TitleToStringTest)
{
	BOOST_TEST(titleToString(Title::MD) == "Lekarz");
	BOOST_TEST(titleToString(Title::DR_MED) == "Doktor");
	BOOST_TEST(titleToString(Title::DR_HAB_MED) == "Doktor habilitowany");
	BOOST_TEST(titleToString(Title::PROF) == "Profesor");
}

BOOST_AUTO_TEST_CASE(StatusToStringTest)
{
	BOOST_TEST(statusToString(Status::AVAILABLE) == "Dostępny");
	BOOST_TEST(statusToString(Status::UNAVAILABLE) == "Niedostępny");
	BOOST_TEST(statusToString(Status::ARCHIVED) == "Archiwalny");
}

BOOST_AUTO_TEST_SUITE_END()