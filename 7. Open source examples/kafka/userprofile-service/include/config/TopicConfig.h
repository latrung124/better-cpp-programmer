/*
* File: TopicConfig.h
* Author: trung.la
* Date: 06-16-2025
* Description: This file is declaration of TopicConfig class
*/

#ifndef TOPIC_CONFIG_H
#define TOPIC_CONFIG_H

#include <string>
#include <unordered_map>
#include <optional>

/**
 * @brief TopicConfig class
 * This class is used to manage topic configurations for Kafka.
 * It can be extended to include topic-specific settings such as partition count,
 * replication factor, and other topic-level configurations.
 */
class TopicConfig
{
public:
    TopicConfig();
    ~TopicConfig();

    /**
     * @brief Get the topic name for user events
     * @return The topic name for user events
     */
    [[nodiscard]] const std::string& getUserEvents() const;

    /**
     * @brief Get the topic name for order events
     * @return The topic name for order events
     */
    [[nodiscard]] const std::string& getOrderEvents() const;

    /**
     * @brief Get the topic name for notification events
     * @return The topic name for notification events
     */
    [[nodiscard]] const std::string& getNotificationEvents() const;

    /**
     * @brief Get the topic name for audit events
     * @return The topic name for audit events
     */
    [[nodiscard]] const std::string& getAuditEvents() const;

    /**
     * @brief Set the topic name for user events
     * @param topic The topic name for user events
     */
    void setUserEvents(const std::string& topic);

    /**
     * @brief Set the topic name for order events
     * @param topic The topic name for order events
     */
    void setOrderEvents(const std::string& topic);

    /**
     * @brief Set the topic name for notification events
     * @param topic The topic name for notification events
     */
    void setNotificationEvents(const std::string& topic);

    /**
     * @brief Set the topic name for audit events
     * @param topic The topic name for audit events
     */
    void setAuditEvents(const std::string& topic);

private:
    /// @brief Topic names
    std::string mUserEvents;
    std::string mOrderEvents;
    std::string mNotificationEvents;
    std::string mAuditEvents;
};

#endif // TOPIC_CONFIG_H