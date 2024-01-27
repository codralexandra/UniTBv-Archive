#include "Visitor.h"

#include <sstream>

Visitor::Visitor(const std::string& name, bool hasPets, int age) :
    m_name(name),
    m_hasPets(hasPets),
    m_age(age)
{}

const std::string& Visitor::name() const noexcept
{
    return m_name;
}

bool Visitor::hasPets() const noexcept
{
    return m_hasPets;
}

int Visitor::age() const noexcept
{
    return m_age;
}

std::string Visitor::toString() const noexcept
{
    static std::ostringstream stringStream;
    stringStream.clear();
    stringStream.str("");

    stringStream << m_name << " | " << m_age << " | " << std::boolalpha << m_hasPets;
    return stringStream.str();
}
