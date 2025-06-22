/*
* File: ServiceConfig.cpp
* Author: trung.la
* Date: 06-16-2025
* Description: This class is definition of ServiceConfig class.
*/

#include "ServiceConfig.h"

ServiceConfig::ServiceConfig()
{
}

ServiceConfig::~ServiceConfig()
{
}

std::unique_ptr<ServiceConfig> ServiceConfig::loadFromFile(const std::string& filename)
{
    // Implementation to load configuration from a JSON file
    // This is a placeholder; actual implementation would parse the file and populate the ServiceConfig object
    return std::make_unique<ServiceConfig>();
}

std::unique_ptr<ServiceConfig> ServiceConfig::loadFromEnvironment()
{
    // Implementation to load configuration from environment variables
    // This is a placeholder; actual implementation would read environment variables and populate the ServiceConfig object
    return std::make_unique<ServiceConfig>();
}

bool ServiceConfig::isValid() const
{
    // Validate the configuration
    // This is a placeholder; actual implementation would check if all required fields are set correctly
    return true;
}

const std::string& ServiceConfig::getKafkaBroker() const
{
    return mKafkaBroker;
}

const std::string& ServiceConfig::getKafkaGroupId() const
{
    return mKafkaGroupId;
}

const std::string& ServiceConfig::getKafkaClientId() const
{
    return mKafkaClientId;
}

void ServiceConfig::setKafkaBroker(const std::string& broker)
{
    mKafkaBroker = broker;
}

void ServiceConfig::setKafkaGroupId(const std::string& groupId)
{
    mKafkaGroupId = groupId;
}

void ServiceConfig::setKafkaClientId(const std::string& clientId)
{
    mKafkaClientId = clientId;
}

void ServiceConfig::setServiceName(const std::string& serviceName)
{
    if (serviceName.empty()) {
        throw std::invalid_argument("Service name cannot be empty");
    }

    if (serviceName != mServiceName) {
        mServiceName = serviceName;
    } else {
        // TODO: Log a warning if the service name is unchanged
    }
}

void ServiceConfig::setServiceVersion(const std::string& serviceVersion)
{
    if (serviceVersion.empty()) {
        throw std::invalid_argument("Service version cannot be empty");
    }

    if (serviceVersion != mServiceVersion) {
        mServiceVersion = serviceVersion;
    } else {
        // TODO: Log a warning if the service version is unchanged
    }
}

void ServiceConfig::setServicePort(int servicePort)
{
    if (servicePort <= 0 || servicePort > 65535) {
        throw std::out_of_range("Service port must be between 1 and 65535");
    }

    if (servicePort != mServicePort) {
        mServicePort = servicePort;
    } else {
        // TODO: Log a warning if the service port is unchanged
    }
}

void ServiceConfig::setLogLevel(const std::string& logLevel)
{
    if (logLevel.empty()) {
        throw std::invalid_argument("Log level cannot be empty");
    }
    // TODO: Add validation for log level (e.g., check against a list of valid log levels)
}

TopicConfig& ServiceConfig::getTopicConfig()
{
    return mTopicConfig;
}

void ServiceConfig::setKafkaProducerConfig(const std::string& key, const std::string& value)
{
    if (key.empty() || value.empty()) {
        throw std::invalid_argument("Key and value for Kafka producer config cannot be empty");
    }
    mKafkaProducerConfig[key] = value;
}

void ServiceConfig::setKafkaConsumerConfig(const std::string& key, const std::string& value)
{
    if (key.empty() || value.empty()) {
        throw std::invalid_argument("Key and value for Kafka consumer config cannot be empty");
    }
    mKafkaConsumerConfig[key] = value;
}

const std::unordered_map<std::string, std::string>& ServiceConfig::getAllKafkaProducerConfig() const
{
    return mKafkaProducerConfig;
}

const std::unordered_map<std::string, std::string>& ServiceConfig::getAllKafkaConsumerConfig() const
{
    return mKafkaConsumerConfig;
}

std::optional<std::string> ServiceConfig::getKafkaProducerConfig(const std::string& key) const
{
    auto it = mKafkaProducerConfig.find(key);
    if (it != mKafkaProducerConfig.end()) {
        return it->second;
    } else {
        return std::nullopt; // Return empty optional if key not found
    }
}

std::optional<std::string> ServiceConfig::getKafkaConsumerConfig(const std::string& key) const
{
    auto it = mKafkaConsumerConfig.find(key);
    if (it != mKafkaConsumerConfig.end()) {
        return it->second;
    } else {
        return std::nullopt; // Return empty optional if key not found
    }
}
