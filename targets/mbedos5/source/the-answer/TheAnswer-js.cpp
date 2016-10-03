#include "jerryscript-mbed-util/logging.h"
#include "jerryscript-mbed-library-registry/wrap_tools.h"


// Load the library that we'll wrap
#include "TheAnswer.h"

/**
 * TheAnswer#give (native JavaScript method)
 *
 * @returns 42
 */
DECLARE_CLASS_FUNCTION(TheAnswer, give) {
    CHECK_ARGUMENT_COUNT(TheAnswer, give, (args_count == 0));

    // Extract native TheAnswer pointer
    uintptr_t ptr_val;
    jerry_get_object_native_handle(this_obj, &ptr_val);

    TheAnswer* native_ptr = reinterpret_cast<TheAnswer*>(ptr_val);

    // Get the result from the C++ API
    uint8_t result = native_ptr->give();
    // Cast it back to JavaScript and return
    return jerry_create_number(result);
}

/**
 * TheAnswer#blink42times (native JavaScript method)
 * @param pin DigitalOut pin to blink
 */
DECLARE_CLASS_FUNCTION(TheAnswer, blink42times) {
    // Check that we have 1 argument, and that it's an object
    CHECK_ARGUMENT_COUNT(TheAnswer, blink42times, (args_count == 1));
	CHECK_ARGUMENT_TYPE_ALWAYS(TheAnswer, blink42times, 0, object);

    // Extract native DigitalOut argument (objects are always pointers)
    uintptr_t digitalout_ptr;
    jerry_get_object_native_handle(args[0], &digitalout_ptr);
	DigitalOut* pin = reinterpret_cast<DigitalOut*>(digitalout_ptr);

    // Extract native TheAnswer pointer (from this object)
    uintptr_t ptr_val;
    jerry_get_object_native_handle(this_obj, &ptr_val);

    TheAnswer* native_ptr = reinterpret_cast<TheAnswer*>(ptr_val);

    // Call our native function (C++) with the native argument
    native_ptr->blink42times(*pin);

    // When done, return undefined
    return jerry_create_undefined();
}

/**
 * TheAnswer#destructor
 *
 * Called if/when the TheAnswer is GC'ed.
 */
void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(TheAnswer)(const uintptr_t native_handle) {
    delete reinterpret_cast<TheAnswer*>(native_handle);
}

/**
 * TheAnswer (native JavaScript constructor)
 *
 * @returns a JavaScript object representing TheAnswer.
 */
DECLARE_CLASS_CONSTRUCTOR(TheAnswer) {
    CHECK_ARGUMENT_COUNT(TheAnswer, __constructor, args_count == 0);

    // Create the C++ object
    uintptr_t native_ptr = (uintptr_t) new TheAnswer();

    // create the jerryscript object
    jerry_value_t js_object = jerry_create_object();
    jerry_set_object_native_handle(js_object, native_ptr, NAME_FOR_CLASS_NATIVE_DESTRUCTOR(TheAnswer));

    // attach methods
    ATTACH_CLASS_FUNCTION(js_object, TheAnswer, give);
    ATTACH_CLASS_FUNCTION(js_object, TheAnswer, blink42times);

    return js_object;
}
