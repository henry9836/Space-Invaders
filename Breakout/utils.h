///
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: utils.h
// Description	: holds the utils info
// Author		: Henry Oliver
// Mail			: henry.oliver@mediadesign.school.nz
//


#pragma once

#if !defined(__UTILS_H__)
#define __UTILS_H__

// Library Includes
#include <strstream>

// Local Includes

// Types

// Constants

// Prototypes

#define VALIDATE(a) if (!a) return (false)

template<typename T>
std::string ToString(const T& _value)
{
    std::strstream theStream;
    theStream << _value << std::ends;
    return (theStream.str());
}


#endif    // __UTILS_H__

