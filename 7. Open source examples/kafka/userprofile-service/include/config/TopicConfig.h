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
};

#endif // TOPIC_CONFIG_H