/*
* File: ServiceConfig.h
* Author: trung.la
* Date: 06-16-2025
* Description: This file is declaration of ServiceConfig class.
*/

#ifndef SERVICE_CONFIG_H
#define SERVICE_CONFIG_H

#include <string>
#include <memory>
#include <unordered_map>
#include <optional>

class TopicConfig;

class ServiceConfig
{
private:
    /// @brief Kafka configuration
    std::string mKafkaBroker;
    std::string mKafkaGroupId;
    std::string mKafkaClientId;

    /// @brief  Database configuration
    std::string databaseUrl;
    std::string databaseType;
    int maxDatabaseConnections;
    int databaseConnectionTimeout;

    /// @brief Service Configuration
    std::string mServiceName;
    std::string mServiceVersion;
    int mServicePort;

    std::unique_ptr<TopicConfig> mTopicConfig;

    /// @brief kafka specific settings
    std::unordered_map<std::string, std::string> mKafkaConsumerConfig;
    std::unordered_map<std::string, std::string> mKafkaProducerConfig;

    /// @brief performance settings
    int mProducerBatchSize;
    int mConsumerPollTimeout;
    int mEventHandlerThreads;
    bool mEnableIdempotence;

public:
    ServiceConfig();
    ~ServiceConfig();

    /**
     * @brief Load configuration from file (JSON format)
     */
    static std::unique_ptr<ServiceConfig> loadFromFile(const std::string& filename);

    /**
     * @brief Load configuration from environment variables
     */
    static std::unique_ptr<ServiceConfig> loadFromEnvironment();

    /**
     * @brief Validate the entire configuration
     */
    bool validate() const;

    // Kafka getters
    const std::string& getKafkaBrokers() const;
    const std::string& getKafkaGroupId() const;
    const std::string& getKafkaClientId() const;

    // Kafka setters
    void setKafkaBrokers(const std::string& brokers);
    void setKafkaGroupId(const std::string& groupId);
    void setKafkaClientId(const std::string& clientId);

    // Service getters
    const std::string& getServiceName() const;
    const std::string& getServiceVersion() const;
    int getServicePort() const;
    const std::string& getLogLevel() const;

    // Service setters
    void setServiceName(const std::string& name);
    void setServiceVersion(const std::string& version);
    void setServicePort(int port);
    void setLogLevel(const std::string& level);

    // Topic configuration
    TopicConfig& getTopicConfig();
    const TopicConfig& getTopicConfig() const;
    void setTopicConfig(std::unique_ptr<TopicConfig> config);

    void setKafkaProducerConfig(const std::string& key, const std::string& value);
    void setKafkaConsumerConfig(const std::string& key, const std::string& value);
    std::optional<std::string> getKafkaProducerConfig(const std::string& key) const;
    std::optional<std::string> getKafkaConsumerConfig(const std::string& key) const;

    const std::unordered_map<std::string, std::string>& getAllKafkaProducerConfig() const;
    const std::unordered_map<std::string, std::string>& getAllKafkaConsumerConfig() const;

    /// @brief Performance settings
    int getProducerBatchSize() const;
    int getConsumerPollTimeout() const;
    int getEventHandlerThreads() const;
    bool isIdempotenceEnabled() const;

    void setProducerBatchSize(int batchSize);
    void setConsumerPollTimeout(int timeout);
    void setEventHandlerThreads(int threads);
    void setIdempotenceEnabled(bool enabled);
};

#endif // SERVICE_CONFIG_H