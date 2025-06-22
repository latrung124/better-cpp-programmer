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

#include "TopicConfig.h"

/**
 * @brief ServiceConfig class
 * This class is used to manage the configuration of the service, including Kafka settings,
 * database settings, and other service-specific configurations.
 * It can load configurations from a file or environment variables and validate them.
 */
class ServiceConfig
{
private:
    /// @brief Kafka configuration
    std::string mKafkaBroker;
    std::string mKafkaGroupId;
    std::string mKafkaClientId;

    /// @brief  Database configuration
    std::string mDatabaseUrl;
    std::string mDatabaseType;
    int mMaxDatabaseConnections;
    int mDatabaseConnectionTimeout;

    /// @brief Service Configuration
    std::string mServiceName;
    std::string mServiceVersion;
    int mServicePort;

    /// @brief Topic configuration
    TopicConfig mTopicConfig;

    /// @brief kafka specific settings
    std::unordered_map<std::string, std::string> mKafkaConsumerConfig;
    std::unordered_map<std::string, std::string> mKafkaProducerConfig;

    /// @brief performance settings
    int mProducerBatchSize;
    int mConsumerPollTimeout;
    int mEventHandlerThreads;
    bool mEnableIdempotence;

public:
    /// @brief Constructor and Destructor
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
    bool isValid() const;

    // Kafka getters
    [[nodiscard]] const std::string& getKafkaBroker() const;
    [[nodiscard]] const std::string& getKafkaGroupId() const;
    [[nodiscard]] const std::string& getKafkaClientId() const;

    // Kafka setters
    void setKafkaBroker(const std::string& broker);
    void setKafkaGroupId(const std::string& groupId);
    void setKafkaClientId(const std::string& clientId);

    // Service getters
    [[nodiscard]] const std::string& getServiceName() const;
    [[nodiscard]] const std::string& getServiceVersion() const;
    [[nodiscard]] int getServicePort() const;
    [[nodiscard]] const std::string& getLogLevel() const;

    /**
     * @brief Set the service name
     * @param name Service name
     */
    void setServiceName(const std::string& name);

    /**
     * @brief Set the service version
     * @param version Service version
     */
    void setServiceVersion(const std::string& version);

    /**
     * @brief Set the service port
     * @param port Service port
     */
    void setServicePort(int port);

    /**
     * @brief Set the log level
     * @param level Log level (e.g., "DEBUG", "INFO", "WARN", "ERROR")
     */
    void setLogLevel(const std::string& level);

    /**
     * @brief Get the topic configuration
     * @return Reference to the TopicConfig object
     */
    TopicConfig& getTopicConfig();

    /**
     * @brief Set Kafka producer and consumer configurations
     * @param key Configuration key
     * @param value Configuration value
     */
    void setKafkaProducerConfig(const std::string& key, const std::string& value);

    /**
     * @brief Get Kafka producer and consumer configurations
     * @param key Configuration key
     */
    void setKafkaConsumerConfig(const std::string& key, const std::string& value);

    /**
     * @brief Get Kafka producer and consumer configurations
     * @param key Configuration key
     * @return Optional string containing the configuration value if it exists
     */
    std::optional<std::string> getKafkaProducerConfig(const std::string& key) const;
    
    /**
     * @brief Get Kafka consumer configurations
     * @param key Configuration key
     * @return Optional string containing the configuration value if it exists
     */
    std::optional<std::string> getKafkaConsumerConfig(const std::string& key) const;

    /**
     * @brief Get all Kafka producer and consumer configurations
     * @return Unordered map containing all configurations
     */
    const std::unordered_map<std::string, std::string>& getAllKafkaProducerConfig() const;
    
    /**
     * @brief Get all Kafka consumer configurations
     * @return Unordered map containing all configurations
     */
    const std::unordered_map<std::string, std::string>& getAllKafkaConsumerConfig() const;
};

#endif // SERVICE_CONFIG_H