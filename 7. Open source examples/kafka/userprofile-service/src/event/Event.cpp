/**
 * @file Event.cpp
 * @author trung.la
 * @date 06-29-2025
 * @brief This file is implementation of Event class
 */

#include "Event.h"

Event::Event(EventType type)
    : mType(type)
{
}

void Event::setPayload(std::string const &payload)
{
    mPayload = payload;
}

std::string const &Event::getPayload() const
{
    return mPayload;
}

user_profile::utils::event::EventType Event::getType() const
{
    return mType;
}

void Event::setType(EventType type)
{
    mType = type;
}