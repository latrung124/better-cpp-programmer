/**
 * @file Event.h
 * @author trung.la
 * @date 06-26-2025
 * @brief This file is declaration of Event class
*/

#ifndef EVENT_H
#define EVENT_H

#include <string>

#include "utils.h"

/**
 * @class Event
 * @brief The Event class represents a generic event with a payload.
 *
 * This class provides a way to encapsulate an event with a string payload.
 * It includes methods to set the payload and a default constructor and destructor.
 */
class Event
{
public:
    using EventType = user_profile::utils::event::EventType; ///< Alias for EventType from utils

    /**
     * @brief Default constructor for Event class
     */
    Event() = default;

    /**
     * @brief Constructor with event type
     * @param type The type of the event
     */
    Event(EventType type);

    /**
     * @brief Default destructor for Event class
     */
    virtual ~Event() = default;

    /**
     * @brief Set payload of the event
     * @param payload The payload to set
     */
    void setPayload(std::string const &payload);

    /**
     * @brief Get payload of the event
     * @return The payload of the event
     */
    std::string const &getPayload() const;

    /**
     * @brief Get the type of the event
     * @return The type of the event
     */
    EventType getType() const;

    /**
     * @brief Set the type of the event
     * @param type The type to set
     */
    void setType(EventType type);

private:
    std::string mPayload; ///< The payload of the event
    EventType mType = EventType::eUnknown;      ///< The type of the event
};

#endif // EVENT_H