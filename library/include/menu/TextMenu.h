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
public:

	TerminalMenu();
	~TerminalMenu() = default;

	void start() const;
	void patient() const;
	void appointment() const;
	void room() const;
	void service() const;
	void personnel() const;
	bool isAmount(const std::string& tmp, const int &amount) const;
	int isDigit(const char &znak,const char &max) const;
};


#endif //REHABILITATIONCENTRE_TERMINALMENU_H