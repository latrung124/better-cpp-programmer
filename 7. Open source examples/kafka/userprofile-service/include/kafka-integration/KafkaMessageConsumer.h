/**
 * @file KafkaMessageConsumer.h
 * @author trung.la
 * @date 08-07-2025
 * @brief This file is declaration of KafkaMessageConsumer class
 */

#ifndef KAFKA_MESSAGE_CONSUMER_H
#define KAFKA_MESSAGE_CONSUMER_H

#include <kafka/KafkaConsumer.h>

#include <memory>

class KafkaMessageConsumer
{
public:
    using KafkaConsumer = KAFKA_API::clients::consumer::KafkaConsumer; // Alias for Kafka consumer

    /**
     * @brief Constructor for KafkaMessageConsumer class
     */
    KafkaMessageConsumer();

    /**
     * @brief Destructor for KafkaMessageConsumer class
     */
    ~KafkaMessageConsumer();

    /**
     * @brief Initialize the Kafka consumer
     * This method sets up the Kafka consumer with the necessary configurations.
     * @return true if initialization is successful, false otherwise
     */
    bool initialize();

    /**
     * @brief Consume messages from a specified topic
     * This method consumes messages.
     */
    void consume();

private:
    std::unique_ptr<KafkaConsumer> mConsumer;
    bool mRunning = true; // Flag to control the consumer loop
};

#endif // KAFKA_MESSAGE_CONSUMER_H