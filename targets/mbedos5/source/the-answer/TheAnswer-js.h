#ifndef _THE_ANSWER_JS_H
#define _THE_ANSWER_JS_H

// This file contains all the macros
#include "jerryscript-mbed-library-registry/wrap_tools.h"

// TheAnswer is a class constructor
DECLARE_CLASS_CONSTRUCTOR(TheAnswer);

// Define a wrapper, we can load the wrapper in `main.cpp`.
// This makes it possible to load libraries optionally.
DECLARE_JS_WRAPPER_REGISTRATION (the_answer_library) {
    REGISTER_CLASS_CONSTRUCTOR(TheAnswer);
}

#endif  // _THE_ANSWER_JS_H
