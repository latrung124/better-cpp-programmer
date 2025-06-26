/**
 * @file NotificationEventHandler.h
 * @author trung.la
 * @date 06-26-2025
 * @brief This file is declaration of NotificationEventHandler class
 */

#ifndef AUDIT_EVENT_HANDLER_H
#define AUDIT_EVENT_HANDLER_H

#include "Handler.h"

/**
 * @brief AuditEventHandler class
 * This class is responsible for handling audit events.
 * It inherits from the Handler class and overrides the handleEvent method.
 */
class AuditEventHandler : public Handler
{
public:
    /**
     * @brief Default constructor for AuditEventHandler class
     */
    AuditEventHandler() = default;

    /**
     * @brief Default destructor for AuditEventHandler class
     */
    virtual ~AuditEventHandler() = default;

    /**
     * @brief Handle event
     * This method is intended to be overridden by derived classes to handle specific events.
     * @param event The event to handle
     * @return true if the event was handled successfully, false otherwise
     */
    virtual bool handleEvent(const Event& event) override;
};

#endif // AUDIT_EVENT_HANDLER_H
