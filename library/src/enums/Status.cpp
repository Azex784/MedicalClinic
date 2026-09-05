#include "enums/Status.h"

using namespace std;

namespace MedicalClinic
{
	const std::string toString(Status status)
	{
		switch (status)
		{
			case Status::AVAILABLE: return "Dostępny";
			case Status::UNAVAILABLE: return "Niedostępny";
			case Status::ARCHIVED: return "Archiwalny";
			default: return "Unknown";
		}
	}

	std::ostream& operator<<(std::ostream& os, const Status& status) {
		os << toString(status);
		return os;
	}
}
