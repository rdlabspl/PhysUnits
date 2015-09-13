/*
Copyright 2015 Adam Rudzinski (adam.rudzinski@rdlabs.pl)

File:
PhysUnits_Base.hpp

This file is part of PhysUnits.

PhysUnits is free software: you can redistribute it and/or modify
it under the terms of the MIT License.

PhysUnits is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/


#ifndef __PHYSUNITS_BASE_HPP
#define __PHYSUNITS_BASE_HPP


#include <iostream>


#define PHYSUNITS_NAMESPACE	namespace PhysUnits


#ifdef PHYSUNITS_NAMESPACE
PHYSUNITS_NAMESPACE {
#endif


class Numeric_Value {

    double x;

public:

    Numeric_Value(const double _x = 0) : x(_x) {}
    double operator()() const { return x; }

};


template<typename T, int PR_NUM = 1, int PR_DEN = 1, int PR_EXP = 0, int OF_NUM = 0, int OF_DEN = 1, int OF_EXP = 0>
class __Unit {

    double x;

    static constexpr double pow10u(const unsigned int n)
    {
	return ( n == 0 ) ? 1 : (10 * pow10u(n-1));
    }

    static constexpr double pow10(const int n)
    {
	return ( n >= 0 ) ? pow10u(n) : (1 / pow10u(-n));
    }

    static double constexpr PROP = pow10(PR_EXP) * PR_NUM / PR_DEN;		//units per base unit
    static double constexpr OFFSET = pow10(OF_EXP) * double(OF_NUM) / OF_DEN;	//offset in base units for x = 0

public:

    double numeric_value() const { return x; }
    double to_base_unit() const { return x / PROP + OFFSET; }
    static double from_base_unit(const double xbu) { return PROP * (xbu - OFFSET); }

    operator Numeric_Value() const { return numeric_value(); }

    __Unit(const double _x = 0) : x(_x) {}
    __Unit(const typename T::Unit::Base_Unit& u) : x(from_base_unit(u.numeric_value())) {}

    operator typename T::Unit::Base_Unit() const { return to_base_unit(); }
    operator T() const { return operator typename T::Unit::Base_Unit(); }

    __Unit operator-() const { return -x; }

    typename T::Unit::Base_Unit operator+(const typename T::Unit::Base_Unit& u) const { return to_base_unit() + u.to_base_unit(); }
    typename T::Unit::Base_Unit operator-(const typename T::Unit::Base_Unit& u) const { return to_base_unit() - u.to_base_unit(); }

    __Unit operator*(const double a) const { return a * x; }
    __Unit operator/(const double d) const { return x / d; }

    double operator/(const typename T::Unit::Base_Unit& u) const { return to_base_unit() / u.to_base_unit(); }

    bool operator==(const typename T::Unit::Base_Unit& u) const { return to_base_unit() == u.to_base_unit(); }
    bool operator!=(const typename T::Unit::Base_Unit& u) const { return !operator==(u); }
    bool operator<(const typename T::Unit::Base_Unit& u) const { return to_base_unit() < u.to_base_unit(); }
    bool operator<=(const typename T::Unit::Base_Unit& u) const { return to_base_unit() <= u.to_base_unit(); }
    bool operator>(const typename T::Unit::Base_Unit& u) const { return to_base_unit() > u.to_base_unit(); }
    bool operator>=(const typename T::Unit::Base_Unit& u) const { return to_base_unit() >= u.to_base_unit(); }

};


template<typename T>
struct __Base {

protected:

    struct Unit {
	typedef __Unit<T> Base_Unit;
    };

private:

    double x;

protected:

    __Base(const typename Unit::Base_Unit& u) : x(u.to_base_unit()) {}

public:

    operator typename Unit::Base_Unit() const { return x; }

    T operator-() const { return typename T::Unit::Base_Unit(-x); }

    T operator+(const T& t) const { return typename T::Unit::Base_Unit(x + t.x); }
    T operator-(const T& t) const { return typename T::Unit::Base_Unit(x - t.x); }

    T operator*(const double a) const { return typename T::Unit::Base_Unit(a * x); }
    T operator/(const double d) const { return typename T::Unit::Base_Unit(x / d); }

    T& operator+=(const T& t) { x += t.x; return *(T*)this; }
    T& operator-=(const T& t) { x -= t.x; return *(T*)this; }

    double operator/(const T& t) const { return x / t.x; }

    bool operator==(const T& t) const { return x == t.x; }
    bool operator!=(const T& t) const { return !operator==(t); }
    bool operator<(const T& t) const { return x < t.x; }
    bool operator<=(const T& t) const { return x <= t.x; }
    bool operator>(const T& t) const { return x > t.x; }
    bool operator>=(const T& t) const { return x >= t.x; }

};


template<typename T>
inline T operator*(const double a, const T& t)
{
    return t * a;
}


inline std::ostream& operator<<(std::ostream& os, const Numeric_Value& nv)
{
    return os << nv();
}


#ifdef PHYSUNITS_NAMESPACE
}	// PHYSUNITS_NAMESPACE
#endif


#endif
