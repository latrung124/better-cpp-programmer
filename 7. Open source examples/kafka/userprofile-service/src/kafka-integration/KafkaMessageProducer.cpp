/**
 * @file KafkaMessageProducer.cpp
 * @author trung.la
 * @date 06-29-2025
 * @brief This file is implementation of KafkaMessageProducer class
 * * This class is responsible for producing messages to Kafka topics.
 * * It provides methods to initialize the producer, send messages, and handle errors.
 */

#include "KafkaMessageProducer.h"

#include "KafkaConst.h"

KafkaMessageProducer::KafkaMessageProducer()
{
}

KafkaMessageProducer::~KafkaMessageProducer()
{
}

bool KafkaMessageProducer::initialize()
{
    // TODO: implement the actual initialization logic with ServiceConfig and TopicConfig
    // For now, we will use a hardcoded broker for demonstration purposes
    if (kafka_const::kBrokers.empty()) {
        return false; // No brokers configured
    }

    auto broker = kafka_const::kBrokers.find("broker1");
    if (broker == kafka_const::kBrokers.end()) {
        return false; // Broker not found
    }

    const KAFKA_API::Properties properties({{"bootstrap.servers", broker->second}});
    mProducer = std::make_unique<KAFKA_API::clients::producer::KafkaProducer>(properties);
    if (!mProducer) {
        return false; // Failed to create producer
    }

    return true;
}

bool KafkaMessageProducer::sendMessage(const std::string& topic, const std::string& key, const std::string& message)
{
    try {
        if (mProducer == nullptr) {
            // TODO: add logging here
            return false; // Producer is not initialized
        }

        // Create a producer record
        // Note: Add id if we want to track the message later
        KAFKA_API::clients::producer::ProducerRecord record(topic,
             KAFKA_API::Key(key.c_str(), key.size()), KAFKA_API::Value(message.c_str(), message.size()));
        // Note: Add id if we want to track the message later

        // Callback function to handle delivery confirmation
        auto deliveryCallback = [](const KAFKA_API::clients::producer::RecordMetadata& metadata,
                                   const KAFKA_API::Error& error) {
            if (error) {
                // Handle the error (e.g., log it)
            } else {
                // Successfully sent the message
                // You can log the metadata if needed
            }
        };

        // Send message, consider the options to copy the record value
        // or not, read the KafkaProducer::SendOption
        mProducer->send(record, deliveryCallback);
    } catch(const KAFKA_API::KafkaException& e) {
        // Handle Kafka exceptions (e.g., log the error)
        return false;
    }

    return true;
}
