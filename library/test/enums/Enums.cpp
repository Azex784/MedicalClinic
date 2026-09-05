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
	BOOST_TEST(toString(Specialisation::CARDIOLOGIST) == "Kardiolog");
	BOOST_TEST(toString(Specialisation::NEUROLOGIST) == "Neurolog");
	BOOST_TEST(toString(Specialisation::ONCOLOGIST) == "Onkolog");
	BOOST_TEST(toString(Specialisation::PEDIATRICIAN) == "Pediatra");
	BOOST_TEST(toString(Specialisation::GENERAL_SURGEON) == "Chirurg ogólny");
	BOOST_TEST(toString(Specialisation::ANESTHESIOLOGIST) == "Anestezjolog");
	BOOST_TEST(toString(Specialisation::RADIOLOGIST) == "Radiolog");
	BOOST_TEST(toString(Specialisation::OPHTHALMOLOGIST) == "Okulista");
	BOOST_TEST(toString(Specialisation::GYNECOLOGIST) == "Ginekolog");
	BOOST_TEST(toString(Specialisation::UROLOGIST) == "Urolog");
	BOOST_TEST(toString(Specialisation::PULMONOLOGIST) == "Pulmonolog");
	BOOST_TEST(toString(Specialisation::GASTROENTEROLOGIST) == "Gastroenterolog");
	BOOST_TEST(toString(Specialisation::ENDOCRINOLOGIST) == "Endokrynolog");
	BOOST_TEST(toString(Specialisation::NEPHROLOGIST) == "Nefrolog");
	BOOST_TEST(toString(Specialisation::HEMATOLOGIST) == "Hematolog");
	BOOST_TEST(toString(Specialisation::ORTHOPEDIST) == "Ortopeda");
	BOOST_TEST(toString(Specialisation::DERMATOLOGIST) == "Dermatolog");
	BOOST_TEST(toString(Specialisation::PSYCHIATRIST) == "Psychiatra");
	BOOST_TEST(toString(Specialisation::INTERNIST) == "Internista");
	BOOST_TEST(toString(Specialisation::EMERGENCY_PHYSICIAN) == "Lekarz medycyny ratunkowej");
	BOOST_TEST(toString(Specialisation::LARYNGOLOGIST) == "Laryngolog");
}

BOOST_AUTO_TEST_CASE(EquipmentToStringTest)
{
	BOOST_TEST(toString(Equipment::NONE) == "Brak");
	BOOST_TEST(toString(Equipment::DEFIBRILLATOR) == "Defibrylator");
	BOOST_TEST(toString(Equipment::ECG_MACHINE) == "Aparat EKG");
	BOOST_TEST(toString(Equipment::PATIENT_MONITOR) == "Monitor pacjenta");
	BOOST_TEST(toString(Equipment::VENTILATOR) == "Respirator");
	BOOST_TEST(toString(Equipment::INFUSION_PUMP) == "Pompa infuzyjna");
	BOOST_TEST(toString(Equipment::ULTRASOUND_MACHINE) == "Aparat USG");
	BOOST_TEST(toString(Equipment::X_RAY_MACHINE) == "Aparat RTG");
	BOOST_TEST(toString(Equipment::CT_SCANNER) == "Tomograf komputerowy");
	BOOST_TEST(toString(Equipment::MRI_SCANNER) == "Rezonans magnetyczny");
	BOOST_TEST(toString(Equipment::ANESTHESIA_MACHINE) == "Aparat do znieczulenia");
	BOOST_TEST(toString(Equipment::SURGICAL_TABLE) == "Stół operacyjny");
	BOOST_TEST(toString(Equipment::INCUBATOR) == "Inkubator");
}

BOOST_AUTO_TEST_CASE(TitleToStringTest)
{
	BOOST_TEST(toString(Title::MD) == "Lekarz");
	BOOST_TEST(toString(Title::DR_MED) == "Doktor");
	BOOST_TEST(toString(Title::DR_HAB_MED) == "Doktor habilitowany");
	BOOST_TEST(toString(Title::PROF) == "Profesor");
}

BOOST_AUTO_TEST_CASE(StatusToStringTest)
{
	BOOST_TEST(toString(Status::AVAILABLE) == "Dostępny");
	BOOST_TEST(toString(Status::UNAVAILABLE) == "Niedostępny");
	BOOST_TEST(toString(Status::ARCHIVED) == "Archiwalny");
}

BOOST_AUTO_TEST_CASE(EnumsOverloadTest)
{
	std::ostringstream os;
	os << Specialisation::LARYNGOLOGIST;

	BOOST_TEST(os.str() == "Laryngolog");

	os.str("");
	os.clear();
	os << Equipment::INCUBATOR;

	BOOST_TEST(os.str() == "Inkubator");

	os.str("");
	os.clear();
	os << Title::PROF;

	BOOST_TEST(os.str() == "Profesor");

	os.str("");
	os.clear();
	os << Status::ARCHIVED;

	BOOST_TEST(os.str() == "Archiwalny");
}


BOOST_AUTO_TEST_SUITE_END()