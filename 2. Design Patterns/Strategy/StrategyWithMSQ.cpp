/*
* File: StrategyWithMSQ.cpp
* Author: trung.la
* Date: 03-15-2025
* Description: This file is implementation of strategy pattern with MSQ
*/

#include <iostream>
#include <string>
#include <memory>
#include <vector>

/**
 * Strategy desgin pattern applies with  Message Service Queue consumer
 * This helps us avoid using enumeration for each message and decoupling the handle message part.
 * Avoid recompile, retest, redeploy the old sources because we don't touch the existence source
 * when we add new type of messages.
 */

class ServiceMessage
{
public:
    virtual ~ServiceMessage() = default;

    virtual void handle() = 0;
};

template <typename T>
class HandleStrategy
{
public:
    virtual ~HandleStrategy() = default;

    virtual void handle(T const &) = 0;
};

class WMediaInfoMessage;
class WPlaybackControlsMessage;

class HandleWMediaInfoStrategy : public HandleStrategy<WMediaInfoMessage>
{
public:
    void handle(WMediaInfoMessage const &message) override
    {
        std::cout << "Handle WMediaInfoMaessage!" << std::endl;
    }
};

class HandleWPlaybackControlsStrategy : public HandleStrategy<WPlaybackControlsMessage>
{
public:
    void handle(WPlaybackControlsMessage const &message) override
    {
        std::cout << "Handle WPlaybackControlsMessage! " << std::endl;
    }
};

class WMediaInfoMessage : public ServiceMessage
{
private:
    std::string m_info;
    std::unique_ptr<HandleStrategy<WMediaInfoMessage>> m_strategy;
public:
    WMediaInfoMessage(const std::string &info, std::unique_ptr<HandleStrategy<WMediaInfoMessage>> strategy)
    : m_info(info)
    , m_strategy(std::move(strategy)) {}

    void handle() override { m_strategy->handle(*this); }
};

class WPlaybackControlsMessage : public ServiceMessage
{
private:
    int m_playback = 0;
    std::unique_ptr<HandleStrategy<WPlaybackControlsMessage>> m_strategy;

public:
    WPlaybackControlsMessage(int playback, std::unique_ptr<HandleStrategy<WPlaybackControlsMessage>> strategy)
    : m_playback(playback)
    , m_strategy(std::move(strategy)) {}

    void handle() override { m_strategy->handle(*this); }
};

int main()
{
    using ServiceMessages = std::vector<std::unique_ptr<ServiceMessage>>;

    ServiceMessages messages{};

    messages.emplace_back(std::make_unique<WMediaInfoMessage>(
        "winfo", std::make_unique<HandleWMediaInfoStrategy>()));

    messages.emplace_back(std::make_unique<WPlaybackControlsMessage>(
        1, std::make_unique<HandleWPlaybackControlsStrategy>()));
    
    for (auto const &message : messages) {
        message->handle();
    }

    return EXIT_SUCCESS;
}