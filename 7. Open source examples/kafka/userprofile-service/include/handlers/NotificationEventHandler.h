/**
 * File: NotificationEventHandler.h
 * Author: trung.la
 * Date: 06-26-2025
 * Description: This file is declaration of NotificationEventHandler class
 */

#ifndef NOTIFICATION_EVENT_HANDLER_H
#define NOTIFICATION_EVENT_HANDLER_H

#include "Handler.h"

/**
 * @brief NotificationEventHandler class
 * This class is responsible for handling notification events.
 * It inherits from the Handler class and overrides the handleEvent method.
 */
class NotificationEventHandler : public Handler
{
public:
    /**
     * @brief Default constructor for NotificationEventHandler class
     */
    NotificationEventHandler() = default;

    /**
     * @brief Default destructor for NotificationEventHandler class
     */
    virtual ~NotificationEventHandler() = default;

    /**
     * @brief Handle event
     * This method is intended to be overridden by derived classes to handle specific events.
     * @param event The event to handle
     * @return true if the event was handled successfully, false otherwise
     */
    virtual bool handleEvent(const Event& event) override;
};

#endif // NOTIFICATION_EVENT_HANDLER_H