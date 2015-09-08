/*
Copyright 2015 Adam Rudzinski (adam.rudzinski@rdlabs.pl)

File:
Length.hpp

This file is part of PhysUnits.

PhysUnits is free software: you can redistribute it and/or modify
it under the terms of the MIT License.

PhysUnits is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/


#ifndef __LENGTH_HPP
#define __LENGTH_HPP


#include "PhysUnits_Base.hpp"


#ifdef PHYSUNITS_NAMESPACE
PHYSUNITS_NAMESPACE {
#endif


struct Length : public __Base<Length> {

//mandatory contents
    struct Unit : public __Base<Length>::Unit {
	typedef Base_Unit m;
	typedef __Unit<Length, 100> cm;
	typedef __Unit<Length, 1000> mm;
	typedef __Unit<Length, 1, 1, 6> um;
	typedef __Unit<Length, 10, 254, 6> mils;
    };

    Length(const Unit::Base_Unit& v = Unit::Base_Unit(0)) : __Base<Length>(v) {}

//optional contents
    double m() const { return Unit::m(operator Unit::Base_Unit()).numeric_value(); }
    double cm() const { return Unit::cm(operator Unit::Base_Unit()).numeric_value(); }
    double mm() const { return Unit::mm(operator Unit::Base_Unit()).numeric_value(); }
    double um() const { return Unit::um(operator Unit::Base_Unit()).numeric_value(); }
    double mils() const { return Unit::mils(operator Unit::Base_Unit()).numeric_value(); }

};


#ifdef PHYSUNITS_NAMESPACE
}	// PHYSUNITS_NAMESPACE
#endif

#endif
