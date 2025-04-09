#ifndef COMPONENT_H
#define COMPONENT_H

#include <Arduino.h>

// An interface for connecting to an Arduino component.
class Component
{
public:
    virtual ~Component() = default;
    // Returns true if the component is initizialized, false otherwise.
    virtual const bool get_is_initialized() = 0;
    // Initializes the component and returns true if successful, false otherwise.
    virtual bool initialize() = 0;
};

#endif // COMPONENT_H
