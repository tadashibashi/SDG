/*
 * ClassMacros.h
 * SDG_Engine
 *
 * This file contains macros that change a class or struct's
 * attributes.
 *
 * Usage:
 * Place these attributes as the first members of the class
 * without any semicolon afterward.
 *
 * Example:
 * class Game {
 *      SDG_NOCOPY(Game)
 * public:
 * ... rest of class
 *
 * };
 */
#pragma once



/// Makes a class non-copyable by deleting the copy
/// constructor & copy assignment operator
#define SDG_NOCOPY(classname) public: \
    classname(const classname &) = delete; \
    classname &operator=(const classname &) = delete;
