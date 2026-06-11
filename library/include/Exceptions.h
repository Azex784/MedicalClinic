#ifndef REHABILITATIONCENTRE_EXCEPTIONS_H
#define REHABILITATIONCENTRE_EXCEPTIONS_H

#include <string>
#include <stdexcept>

/**
 * Wyjątki, gdy nie ma dostępności danej rzeczy
 */
class ActivityException : public std::logic_error {
public:
	explicit ActivityException(const std::string& thing) : std::logic_error(thing + " nie jest obecnie dostępny.") {};
};

/**
 * Wyjątki gdy daty kolidują
 */
class DateException : public std::logic_error {
public:
	explicit DateException(const std::string& thing) : std::logic_error(thing + " ma spotkanie w podanym terminie.") {};
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
	explicit NullPointerException(const std::string& pointerName) : std::logic_error("Wskaźnik " + pointerName + " ma wartość nullptr.") {};
};

/**
 * Wyjątki, gdy coś nie istnieje
 */
class NoExistException : public std::logic_error {
public:
	explicit NoExistException(const std::string& name,const std::string& uniqueParametr) : std::logic_error("Nie istnieje " + name + " o takim parametrze: " + uniqueParametr) {};
};

/**
 * Wyjątki, gdy coś istnieje
 */
class ExistException : public std::logic_error {
public:
	explicit ExistException(const std::string& name,const std::string& uniqueParametr) : std::logic_error("Istnieje " + name + " o takim parametrze: " + uniqueParametr) {};
};

/**
 * Wyjątki gdy jest nieprawidłowe otwarcie pliku
 */
class OpeningException : public std::logic_error {
public:
	explicit OpeningException(const std::string& fileName) : std::logic_error("Nie udało się otworzyć pliku: " + fileName) {};
};

/**
 * Wyjątki gdy jest nieprawidłowa wielkość wektora
 */
class EmptyRecordException : public std::logic_error {
public:
	explicit EmptyRecordException(const std::string& name) : std::logic_error("Próba zapisu pustego wektora: " + name) {};
};

/**
 * Wyjątki podczas zapisu
 */
class WriteException : public std::logic_error {
public:
	explicit WriteException(const std::string& fileName) : std::logic_error("Błąd strumienia podczas zapisywania do pliku: " + fileName) {};
};

/**
 * Wyjątek gdy pojawia się nieoczkiwany znak
 */
class UnexpectedCharacterException : public std::logic_error {
public:
	explicit UnexpectedCharacterException(const std::string& clas) : std::logic_error(clas + " Wczytano nieoczekiwany znak.") {};
};


/**
 * Wyjątek gdy pojawia jest próba archiwizacji zaarchiwizowanego elementu
 */
class ArchiveArchivedException : public std::logic_error {
public:
	explicit ArchiveArchivedException(const std::string& clas) : logic_error( "Nie można zaarchiwiować zarchiwizowanego " + clas) {};
};


#endif //REHABILITATIONCENTRE_EXCEPTIONS_H