#ifndef REHABILITATIONCENTRE_EXCEPTIONS_H
#define REHABILITATIONCENTRE_EXCEPTIONS_H

#include <string>
#include <stdexcept>

/**
 * Wyjątki, gdy nie ma dostępności danej rzeczy
 */
class ActivityException : public std::logic_error {
public:
	explicit ActivityException(const std::string& thing) : std::logic_error(thing + " nie jest obecnie dostępny") {};
};

/**
 * Wyjątki gdy daty kolidują
 */
class DateException : public std::logic_error {
public:
	explicit DateException(const std::string& thing) : std::logic_error(thing + " ma spotkanie w podanym terminie") {};
};

/**
 * Wyjątki ogólne
 */
class LogicException : public std::logic_error {
public:
	explicit LogicException(const std::string& msg) : std::logic_error(msg) {}
};

/**
 * Wyjątki, gdy przekazywany argument to nullptr
 */
class NullPointerException : public std::logic_error {
public:
	explicit NullPointerException(const std::string& pointerName) : std::logic_error("Wskaźnik " + pointerName + " ma wartość null.") {};
};

/**
 * Wyjątki, gdy coś nie istnieje
 */
class NoExistException : public std::logic_error {
public:
	explicit NoExistException(const std::string& name,const std::string& uniqueParametr) : std::logic_error("Nie istnieje " + name + " o takim paramtrze: " + uniqueParametr +  ".") {};
};



/**
 * Wyjątki, gdy coś istnieje
 */
class ExistException : public std::logic_error {
public:
	explicit ExistException(const std::string& name,const std::string& uniqueParametr) : std::logic_error("Istnieje " + name + " o takim paramtrze: " + uniqueParametr +  ".") {};
};

#endif //REHABILITATIONCENTRE_EXCEPTIONS_H