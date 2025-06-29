/**
 * @file KafkaConst.h
 * @author trung.la
 * @date 06-29-2025
 * @brief This file contains constants related to Kafka integration.
 */

#ifndef KAFKA_CONST_H
#define KAFKA_CONST_H

#include <map>

namespace kafka_const 
{
    // Kafka brokers list
    const std::map<std::string, std::string> kBrokers = {
        {"broker1", "localhost:9092"},
        {"broker2", "localhost:9093"},
        {"broker3", "localhost:9094"}
    };
};

#endif // KAFKA_CONST_H
