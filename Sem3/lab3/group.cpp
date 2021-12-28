#include <iostream>
#include "include/group.h"

std::ostream& Commercial::printInfo(std::ostream& out) {
    out << "\nGroup #" << this->getIndex() << "   Type: Commercial"
    << "\nNumber of students: " << this->getNum()
    << "\nNumber of kaf: " << this->getKaf()
    << "\nTerm of studying: " << this->getTerm()
    << "\nSpecialization: " << this->getSpecialization()
    << "\nNumber of contract: " << m_contract
    << "\nPrice: " << m_price << "rub a semester."
    << std::endl;
    return out;
}

std::ostream& Daytime::printInfo(std::ostream& out) {
    out << "\nGroup #" << this->getIndex() << "   Type: Daytime"
        << "\nNumber of students: " << this->getNum()
        << "\nNumber of kaf: " << this->getKaf()
        << "\nTerm of studying: " << this->getTerm()
        << "\nSpecialization: " << this->getSpecialization()
        << "\nScholarship: " << m_money << "rub a month."
        << "\nScholarship holders: " << m_numMoney << " students."
        << std::endl;
    return out;
}

std::ostream& Evening::printInfo(std::ostream& out) {
    out << "\nGroup #" << this->getIndex() << "   Type: Evening"
        << "\nNumber of students: " << this->getNum()
        << "\nNumber of kaf: " << this->getKaf()
        << "\nTerm of studying: " << this->getTerm()
        << "\nSpecialization: " << this->getSpecialization()
        << "\nAge of students: " << m_age << "+ years old."
        << "\nQualification: " << m_qualification
        << std::endl;
    return out;
}