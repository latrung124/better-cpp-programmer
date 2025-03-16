/*
* File: Factory.cpp
* Author: trung.la
* Date: 03-15-2025
* Description: This is Factory Design Pattern implementation.
*/

/**
 * What is Factory Design Pattern?
 * 
 * Factory Design Pattern is a creational design pattern that provides
 * an interface for creating objects without specifying their concrete classes.
 * There are alot of implementations, however, we only focus to Modern Registration-based Factory.
 * 
 * Why Modern Registraion-based Factory?
 * 
 * Highly flexible and extensible.
 * No need to modify existing code to add new type, avoid re-compile, re-test,... -> OCP
 * Runtime registration capability
 */

#include <iostream>
#include <typeindex>
#include <functional>
#include <unordered_map>
#include <memory>

class ServiceMessage 
{
public:
    virtual ~ServiceMessage() = default;
    virtual void operation() const = 0;
};

class ConcreteServiceMessageA : public ServiceMessage
{
public:
    void operation() const override { std::cout << "ConcreteServiceMessageA operation()!" << std::endl; }
};

class ConcreteServiceMessageB : public ServiceMessage
{
public:
    void operation() const override { std::cout << "ConcreteServiceMessageB operation()!" << std::endl; }
};

class Producer
{
public:
    virtual ~Producer() = default;
    virtual std::unique_ptr<ServiceMessage> createServiceMessage() const = 0;
};

class ConcreteProducerA : public Producer
{
public:
    std::unique_ptr<ServiceMessage> createServiceMessage() const override {
        return std::make_unique<ConcreteServiceMessageA>();
    }
};

class ConcreteProducerB : public Producer
{
public:
    std::unique_ptr<ServiceMessage> createServiceMessage() const override {
        return std::make_unique<ConcreteServiceMessageB>();
    }
};

class ModernFactory
{
private:
    using CreationFunc = std::function<std::unique_ptr<Producer>()>;
    std::unordered_map<std::type_index, CreationFunc> m_creators;

public:
    template <typename ConcreteProducer>
    void registerServiceMessage() {
        std::type_index type = std::type_index(typeid(ConcreteProducer));
        m_creators[type] = []() { return std::make_unique<ConcreteProducer>(); };
    }

    template <typename ConcreteProducer>
    std::unique_ptr<ServiceMessage> createServiceMessage() const {
        std::type_index type = std::type_index(typeid(ConcreteProducer));
        auto it = m_creators.find(type);
        if (it != m_creators.end()) {
            return it->second()->createServiceMessage();
        }
        return nullptr;
    }
};

int main() {
    std::cout << "======Factory Design Pattern======" << std::endl;
    ModernFactory modernFactory;
    modernFactory.registerServiceMessage<ConcreteProducerA>();
    modernFactory.registerServiceMessage<ConcreteProducerB>();

    auto const messageA = modernFactory.createServiceMessage<ConcreteProducerA>();
    messageA->operation();

    auto const messageB = modernFactory.createServiceMessage<ConcreteProducerB>();
    messageB->operation();

    return EXIT_SUCCESS;
}