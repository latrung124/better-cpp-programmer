/*
* File: Factory.cpp
* Author: trung.la
* Date: 03-15-2025
* Description: This is Factory Design Pattern implementation with parameter support.
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
#include <string>
#include <any>
#include <vector>

// Message base class
class ServiceMessage 
{
public:
    virtual ~ServiceMessage() = default;
    virtual void operation() const = 0;
};

// Concrete message types with parameterized constructors
class ConcreteServiceMessageA : public ServiceMessage
{
private:
    std::string m_data;
    int m_value;

public:
    // Default constructor
    ConcreteServiceMessageA() : m_data("Default"), m_value(0) {}
    
    // Parameterized constructor
    ConcreteServiceMessageA(const std::string& data, int value) 
        : m_data(data), m_value(value) {}

    void operation() const override { 
        std::cout << "ConcreteServiceMessageA operation! Data: " << m_data 
                  << ", Value: " << m_value << std::endl; 
    }
};

class ConcreteServiceMessageB : public ServiceMessage
{
private:
    double m_rate;
    std::string m_name;

public:
    // Default constructor
    ConcreteServiceMessageB() : m_rate(1.0), m_name("Unknown") {}
    
    // Parameterized constructor
    ConcreteServiceMessageB(double rate, const std::string& name) 
        : m_rate(rate), m_name(name) {}

    void operation() const override { 
        std::cout << "ConcreteServiceMessageB operation! Rate: " << m_rate 
                  << ", Name: " << m_name << std::endl; 
    }
};

// Base parameter container for type erasure
class ParamContainerBase {
public:
    virtual ~ParamContainerBase() = default;
};

// Type-specific parameter container
template<typename... Args>
class ParamContainer : public ParamContainerBase {
public:
    std::tuple<Args...> params;
    
    ParamContainer(Args... args) : params(args...) {}
};

// Improved Producer base class with parameter support
class Producer
{
public:
    virtual ~Producer() = default;
    virtual std::unique_ptr<ServiceMessage> createServiceMessage(ParamContainerBase* params = nullptr) const = 0;
};

// Helper function to extract parameters from a container
template<typename T, typename... Args>
std::unique_ptr<T> createWithParams(const ParamContainer<Args...>* container) {
    return std::apply(
        [](auto&&... args) { return std::make_unique<T>(std::forward<decltype(args)>(args)...); },
        container->params
    );
}

// Concrete producer for ConcreteServiceMessageA
class ConcreteProducerA : public Producer
{
public:
    std::unique_ptr<ServiceMessage> createServiceMessage(ParamContainerBase* params = nullptr) const override {
        if (!params) {
            return std::make_unique<ConcreteServiceMessageA>();
        }
        
        if (auto* container = dynamic_cast<ParamContainer<std::string, int>*>(params)) {
            return createWithParams<ConcreteServiceMessageA>(container);
        }
        
        // Fallback to default constructor if parameters don't match
        return std::make_unique<ConcreteServiceMessageA>();
    }
};

// Concrete producer for ConcreteServiceMessageB
class ConcreteProducerB : public Producer
{
public:
    std::unique_ptr<ServiceMessage> createServiceMessage(ParamContainerBase* params = nullptr) const override {
        if (!params) {
            return std::make_unique<ConcreteServiceMessageB>();
        }
        
        if (auto* container = dynamic_cast<ParamContainer<double, std::string>*>(params)) {
            return createWithParams<ConcreteServiceMessageB>(container);
        }
        
        // Fallback to default constructor if parameters don't match
        return std::make_unique<ConcreteServiceMessageB>();
    }
};

// Improved ModernFactory with parameter support
class ModernFactory
{
private:
    using CreationFunc = std::function<std::unique_ptr<Producer>()>;
    std::unordered_map<std::type_index, CreationFunc> m_creators;

public:
    // Register a message type with its producer
    template <typename ConcreteProducer>
    void registerServiceMessage() {
        std::type_index type = std::type_index(typeid(ConcreteProducer));
        m_creators[type] = []() { return std::make_unique<ConcreteProducer>(); };
    }
    
    // Create a message with no parameters
    template <typename ConcreteProducer>
    std::unique_ptr<ServiceMessage> createServiceMessage() const {
        std::type_index type = std::type_index(typeid(ConcreteProducer));
        auto it = m_creators.find(type);
        if (it != m_creators.end()) {
            return it->second()->createServiceMessage();
        }
        return nullptr;
    }
    
    // Create a message with parameters
    template <typename ConcreteProducer, typename... Args>
    std::unique_ptr<ServiceMessage> createServiceMessage(Args&&... args) const {
        std::type_index type = std::type_index(typeid(ConcreteProducer));
        auto it = m_creators.find(type);
        if (it != m_creators.end()) {
            auto params = std::make_unique<ParamContainer<Args...>>(std::forward<Args>(args)...);
            return it->second()->createServiceMessage(params.get());
        }
        return nullptr;
    }
};

int main() {
    std::cout << "======Factory Design Pattern with Parameters======" << std::endl;
    
    ModernFactory modernFactory;
    modernFactory.registerServiceMessage<ConcreteProducerA>();
    modernFactory.registerServiceMessage<ConcreteProducerB>();
    
    // Create messages with default constructors
    std::cout << "\n--- Creating with default constructors ---" << std::endl;
    auto const defaultMessageA = modernFactory.createServiceMessage<ConcreteProducerA>();
    defaultMessageA->operation();
    
    auto const defaultMessageB = modernFactory.createServiceMessage<ConcreteProducerB>();
    defaultMessageB->operation();
    
    // Create messages with parameters
    std::cout << "\n--- Creating with parameters ---" << std::endl;
    auto const messageA = modernFactory.createServiceMessage<ConcreteProducerA>("Custom Data", 42);
    messageA->operation();
    
    auto const messageB = modernFactory.createServiceMessage<ConcreteProducerB>(3.14, "ProductB");
    messageB->operation();
    
    return EXIT_SUCCESS;
}