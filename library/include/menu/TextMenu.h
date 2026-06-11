#ifndef REHABILITATIONCENTRE_TERMINALMENU_H
#define REHABILITATIONCENTRE_TERMINALMENU_H

#include "managers/LogicManager.h"

/**
 * Klasa zapewniające tekstowe menu do obsługi centrum rehabilitacji
 */
class TerminalMenu
{
private:
	LogicManagerPtr logicManger;

	bool isAmount(const std::string& tmp, const int& amount) const;
	int isDigit(const char& znak, const char& max) const;

	template <typename type>
	bool contains(std::vector<type> vectorOfValues, type value, const std::string& itemName) const;

	bool checkInt(const std::string& tmp, unsigned int& liczba) const;

	template <typename type>
	void displayAll(std::vector<type> wektor) const;

	template <typename type>
	bool displaySpecific(type patient, const std::string& msg) const;

	bool loadEquipment(std::vector<Equipment>& accessibleEquipment) const;

	bool jointLoadService(unsigned int& serviceCost,
	                      unsigned int& requiredDocSize,
	                      unsigned int& serviceId,
	                      unsigned int& serviceDuration,
	                      Specialisation& specjalizacja,
	                      std::string& serviceName) const;

	bool jointLoadPersonnel(std::string& firstName, std::string& lastName,
	                        unsigned int& personnelId) const;

	bool specialisationLoad(Specialisation& spec) const;
	template <typename type, typename ManagerPtr>
	bool findByInt(const std::string &msg, ManagerPtr manage) const;

	template <typename type, typename ManagerPtr>
	bool findByInt(const std::string& msg, ManagerPtr manager, type &returnValue) const;

	bool isContinue() const;

	bool checkDate(const std::string& dateInput, const std::string& timeInput, boost::posix_time::ptime& parsedTime) const;

public:
	TerminalMenu();
	~TerminalMenu() = default;

	void start() const;
	void patient() const;
	void appointment() const;
	void room() const;
	void service() const;
	void personnel() const;
};


#endif //REHABILITATIONCENTRE_TERMINALMENU_H
