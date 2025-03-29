/*
* File: Adapter.cpp
* Author: trung.la
* Date: 03-29-2025
* Description: This file is implementation of adapter design pattern.
*/

#include <iostream>
#include <string>
#include <memory>

/**
 * What is Adapter Design Pattern
 * 
 * Adapter design pattern is applied to adapt the new format of interface
 * to it callers but do not modifies the caller code.
 * 
 * When we use it?
 * 
 * When we are facing incompatibility between interfaces but need to work together
 * When we want to use the third-party or legacy code but we do not want to modify it.
 * 
 * How it works?
 * 
 * 1. Target Interface - The interface that clients expects to use
 * 2. Adaptee (Existing class) - The existing class that has an incompatible interface
 * 3. Adapter (Wrapper class) - Convert the adaptee's interface to match target interface
 * 4. Client - Uses the adapter to interact with the adaptee.
 */

class IFirebaseBackend
{
public:
    virtual ~IFirebaseBackend() = default;
    virtual std::string getName() const = 0;
};

class FirebaseBackend : public IFirebaseBackend
{
public:
    ~FirebaseBackend() = default;
    std::string getName() const override {
        return m_name;
    } 

private:
    std::string m_name = "La Trung";
};

class IAwsBackend
{
public:
    virtual ~IAwsBackend() = default;
    virtual std::string getFirstName() const = 0;
    virtual std::string getLastName() const = 0;
};

class AwsBackend : public IAwsBackend
{
public:
    virtual ~AwsBackend() = default;

    virtual std::string getFirstName() const override
    {
        return m_firstName;
    }

    virtual std::string getLastName() const override
    {
        return m_lastName;
    }

private:
    std::string m_firstName = "Trung";
    std::string m_lastName = "La";
};

class IAdapter
{
public:
    virtual ~IAdapter() = default;
    virtual std::string getName() const = 0;
};

class FirebaseAdapter : public IAdapter
{
public:
    using IFirebaseBackendUPtr = std::unique_ptr<IFirebaseBackend>;
    FirebaseAdapter(IFirebaseBackendUPtr backend) : m_backend(std::move(backend)) {}
    ~FirebaseAdapter() = default;

    std::string getName() const override
    {
        return m_backend->getName();
    }

private:
    IFirebaseBackendUPtr m_backend;
};

class AwsAdapter : public IAdapter
{
public:
    using IAwsBackendUPtr = std::unique_ptr<IAwsBackend>;
    AwsAdapter(IAwsBackendUPtr backend) : m_backend(std::move(backend)) {}
    ~AwsAdapter() = default;

    std::string getName() const override
    {
        return m_backend->getLastName() + " " + m_backend->getFirstName();
    }

private:
    IAwsBackendUPtr m_backend;
};

class User
{
public:
    using IAdapterUPtr = std::unique_ptr<IAdapter>;
    User(IAdapterUPtr adapter) : m_adapter(std::move(adapter)) {}
    ~User() = default;

    void setAdapter(IAdapterUPtr adapter)
    {
        m_adapter.reset();
        m_adapter = std::move(adapter);
    }

    std::string getName() const
    {
        return m_adapter->getName();
    }

private:
    IAdapterUPtr m_adapter;
};

int main()
{
    User user(std::make_unique<AwsAdapter>(std::make_unique<AwsBackend>()));
    std::cout << user.getName() << "\n";

    // In case we have to change the aws backend to another backend like firebase
    // We just need to change the adapter.

    user.setAdapter(std::make_unique<FirebaseAdapter>(std::make_unique<FirebaseBackend>()));
    std::cout << user.getName() << "\n";

    return EXIT_SUCCESS;
}