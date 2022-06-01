/*!
 * @file ClassMacros.h
 * @abstract
 * This file contains macros that change a class or struct's attributes.
 * These attributes should be placed as the first members of the class
 *
 * @example
 * class Game {
 *      SDG_NOCOPY(Game);
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
    classname &operator=(const classname &) = delete
