/*
Copyright 2015 Adam Rudzinski (adam.rudzinski@rdlabs.pl)

File:
Area.hpp

This file is part of PhysUnits.

PhysUnits is free software: you can redistribute it and/or modify
it under the terms of the MIT License.

PhysUnits is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/


#ifndef __AREA_HPP
#define __AREA_HPP


#include "Length.hpp"
#include <cmath>


#ifdef PHYSUNITS_NAMESPACE
PHYSUNITS_NAMESPACE {
#endif


struct Area : public __Base<Area> {

//mandatory contents
    struct Unit : public __Base<Area>::Unit {
	typedef Base_Unit m2;
	typedef __Unit<Area, 1, 1, 4> cm2;
	typedef __Unit<Area, 1, 1, 6> mm2;
    };

    Area(const Unit::Base_Unit& v) : __Base<Area>(v) {}

//optional contents
    double m2() const { return Unit::m2(operator Unit::Base_Unit()).numeric_value(); }
    double cm2() const { return Unit::cm2(operator Unit::Base_Unit()).numeric_value(); }
    double mm2() const { return Unit::mm2(operator Unit::Base_Unit()).numeric_value(); }

};


inline Area operator*(const Length::Unit::Base_Unit& l1, const Length::Unit::Base_Unit& l2) { return Area::Unit::Base_Unit(l1.numeric_value() * l2.numeric_value()); }

inline Length::Unit::Base_Unit operator/(const Area::Unit::Base_Unit& a, const Length::Unit::Base_Unit& l) { return a.numeric_value() / l.numeric_value(); }
inline Length::Unit::Base_Unit sqrt(const Area::Unit::Base_Unit& a) { return std::sqrt(a.numeric_value()); }


#ifdef PHYSUNITS_NAMESPACE
}	// PHYSUNITS_NAMESPACE
#endif

#endif
