/**
 * File: OrderEventHandler.h
 * Author: trung.la
 * Date: 06-26-2025
 * Description: This file is declaration of OrderEventHandler class
 */

#ifndef ORDER_EVENT_HANDLER_H
#define ORDER_EVENT_HANDLER_H

#include "Handler.h"

/**
 * @brief OrderEventHandler class
 * This class is responsible for handling order events.
 * It inherits from the Handler class and overrides the handleEvent method.
 */
class OrderEventHandler : public Handler
{
public:
    /**
     * @brief Default constructor for OrderEventHandler class
     */
    OrderEventHandler() = default;

    /**
     * @brief Default destructor for OrderEventHandler class
     */
    virtual ~OrderEventHandler() = default;

    /**
     * @brief Handle event
     * This method is intended to be overridden by derived classes to handle specific events.
     * @param event The event to handle
     * @return true if the event was handled successfully, false otherwise
     */
    virtual bool handleEvent(const Event& event) override;
};

#endif // ORDER_EVENT_HANDLER_H