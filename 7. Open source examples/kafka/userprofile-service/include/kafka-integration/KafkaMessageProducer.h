/**
 * @file KafkaMessageProducer.h
 * @author trung.la
 * @date 06-29-2025
 * @brief This file is declaration of KafkaMessageProducer class
 * * This class is responsible for producing messages to Kafka topics.
 * * It provides methods to initialize the producer, send messages, and handle errors.
 */

#ifndef KAFKA_MESSAGE_PRODUCER_H
#define KAFKA_MESSAGE_PRODUCER_H

#include <memory>

#include <kafka/KafkaProducer.h>
#include <kafka/KafkaException.h>
#include <kafka/ProducerRecord.h>

class KafkaMessageProducer
{
public:
    using KafkaProducer = KAFKA_API::clients::producer::KafkaProducer; // Alias for Kafka producer

    /**
     * @brief Constructor for KafkaMessageProducer class
     */
    KafkaMessageProducer();

    /**
     * @brief Destructor for KafkaMessageProducer class
     */
    ~KafkaMessageProducer();

    /**
     * @brief Initialize the Kafka producer
     * This method sets up the Kafka producer with the necessary configurations.
     * @return true if initialization is successful, false otherwise
     */
    bool initialize();

    /**
     * @brief Send a message to a specified topic
     * This method sends a message to the given Kafka topic.
     * @param topic The topic to which the message will be sent
     * @param key The key associated with the message
     * @param message The message to send
     * @return true if the message was sent successfully, false otherwise
     */
    bool sendMessage(const std::string& topic, const std::string& key, const std::string& message);

    /**
     * @brief Flush the producer
     * This method flushes the producer, ensuring that all messages are sent.
     * @return true if the flush was successful, false otherwise
     */
    bool flush();

private:
    std::unique_ptr<KafkaProducer> mProducer; // Unique pointer to Kafka producer instance
};

#endif // KAFKA_MESSAGE_PRODUCER_H