/**
 * @file KafkaMessageConsumer.cpp
 * @author trung.la
 * @date 08-07-2025
 * @brief This file is the implementation of KafkaMessageConsumer class
 */

 #include "KafkaMessageConsumer.h"

 #include "const/KafkaConst.h"

KafkaMessageConsumer::KafkaMessageConsumer()
{
}

KafkaMessageConsumer::~KafkaMessageConsumer()
{
}

bool KafkaMessageConsumer::initialize()
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
    mConsumer = std::make_unique<KAFKA_API::clients::consumer::KafkaConsumer>(properties);
    if (!mConsumer) {
        return false; // Failed to create consumer
    } else {
        return true; // Consumer created successfully
    }

}

void KafkaMessageConsumer::consume()
{
     while (mRunning) {
        // Poll messages from Kafka brokers
        auto records = mConsumer->poll(std::chrono::milliseconds(100));

        for (const auto& record: records) {
            if (!record.error()) {
                // Handle the record
            } else {
                // Handle the error
            }
        }
    }

    // No explicit close is needed, RAII will take care of it
    mConsumer->close();
}