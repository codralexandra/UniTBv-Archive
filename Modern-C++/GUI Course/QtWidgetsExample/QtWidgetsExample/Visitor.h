#pragma once
#include <string>

class Visitor
{
public:
    static constexpr int MinimumAge = 18;     // Constexpr: variable can be evaluated/used at compile-time
    static constexpr int MaximumAge = 120;    // we can do complex computation at compile-time to compute some constants
    static constexpr int AttributesCount = 3; // saves on resources used during run-time
public:
	Visitor(const std::string& name, bool hasPets, int age);

    const  std::string& name() const noexcept; // noexcept: function does not throw
    bool  hasPets() const noexcept;            // binary code will be optimized by the compiler
	int age() const noexcept;

	std::string toString() const noexcept;

private:
	std::string  m_name;
	bool m_hasPets;
	int m_age;
};

