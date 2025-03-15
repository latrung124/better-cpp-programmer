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
#include <functional>
#include <map>
#include <memory>

class ServiceMessage 
{
public:
    virtual ~ServiceMessage() = default;
    virtual void operation() const = 0;
};

class ConcreateServiceMessageA : public ServiceMessage
{
public:
    void operation() const override { std::cout << "ConcreateServiceMessageA operation()!" << std::endl; }
};

class ConcreateServiceMessageB : public ServiceMessage
{
public:
    void operation() const override { std::cout << "ConcreateServiceMessageB operation()!" << std::endl; }
};

class ModernFactory
{
private:
    using CreationFunc = std::function<std::unique_ptr<ServiceMessage>()>;
    std::unordered_map<std::string, CreationFunc> m_creators;

public:
    template <typename ServiceMessageType>
    void registerServiceMessage(std::string const &type) {
        m_creators[type] = []() { return std::make_unique<ServiceMessageType>(); };
    }

    std::unique_ptr<ServiceMessage> createServiceMessage(std::string const &type) const {
        auto it = m_creators.find(type);
        if (it != m_creators.end()) {
            return it->second();
        }
        return nullptr;
    }
};

int main() {
    std::cout << "======Factory Design Pattern======" << std::endl;
    ModernFactory modernFactory;
    modernFactory.registerServiceMessage<ConcreateServiceMessageA>("A");
    modernFactory.registerServiceMessage<ConcreateServiceMessageB>("B");

    auto const messageA = modernFactory.createServiceMessage("A");
    messageA->operation();

    auto const messageB = modernFactory.createServiceMessage("B");
    messageB->operation();

    return EXIT_SUCCESS;
}