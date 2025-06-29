/*
* File: Handler.h
* Author: trung.la
* Date: 06-25-2025
* Description: This file is declaration of Handler class
*/

#ifndef HANDLER_H
#define HANDLER_H

struct Event;

/**
 * @brief Handler class
 * This class is responsible for handling events.
 * It provides a virtual method handleEvent that can be overridden by derived classes.
 */
class Handler
{
public:
    /**
     * @brief Default constructor for Handler class
     */
    Handler() = default;

    /**
     * @brief Default destructor for Handler class
     */
    virtual ~Handler() = default;

    /**
     * @brief Handle event
     * This method is intended to be overridden by derived classes to handle specific events.
     * @param event The event to handle
     * @return true if the event was handled successfully, false otherwise
     */
    virtual bool handleEvent(const Event& event) = 0;
};

#endif // HANDLER_H