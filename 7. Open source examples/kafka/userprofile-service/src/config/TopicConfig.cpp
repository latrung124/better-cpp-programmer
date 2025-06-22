/*
* File: TopicConfig.cpp
* Author: trung.la
* Date: 06-16-2025
* Description: This is definition of TopicConfig class.
*/

#include "TopicConfig.h"

TopicConfig::TopicConfig()
{
}

TopicConfig::~TopicConfig()
{
}

const std::string& TopicConfig::getUserEvents() const
{
    return mUserEvents;
}

const std::string& TopicConfig::getOrderEvents() const
{
    return mOrderEvents;
}

const std::string& TopicConfig::getNotificationEvents() const
{
    return mNotificationEvents;
}

const std::string& TopicConfig::getAuditEvents() const
{
    return mAuditEvents;
}

void TopicConfig::setUserEvents(const std::string& topic)
{
    if (topic.empty())
    {
        throw std::invalid_argument("Topic name cannot be empty");
    } else {
        if (topic != mUserEvents)
        {
            mUserEvents = topic;
        } else {
            // TODO: Log a warning that the topic name is already set
        }
    }
}


void TopicConfig::setOrderEvents(const std::string& topic)
{
    if (topic.empty())
    {
        throw std::invalid_argument("Topic name cannot be empty");
    } else {
        if (topic != mOrderEvents)
        {
            mOrderEvents = topic;
        } else {
            // TODO: Log a warning that the topic name is already set
        }
    }
}

void TopicConfig::setNotificationEvents(const std::string& topic)
{
    if (topic.empty())
    {
        throw std::invalid_argument("Topic name cannot be empty");
    } else {
        if (topic != mNotificationEvents)
        {
            mNotificationEvents = topic;
        } else {
            // TODO: Log a warning that the topic name is already set
        }
    }
}

void TopicConfig::setAuditEvents(const std::string& topic)
{
    if (topic.empty())
    {
        throw std::invalid_argument("Topic name cannot be empty");
    } else {
        if (topic != mAuditEvents)
        {
            mAuditEvents = topic;
        } else {
            // TODO: Log a warning that the topic name is already set
        }
    }
}