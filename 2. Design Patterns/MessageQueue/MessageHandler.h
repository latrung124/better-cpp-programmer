/*
* File: MessageHandler.h
* Author: trung.la
* Date: 04-02-2025
* Description: This is Message Handler class.
* This class is used to handle messages in a message queue.
*/

#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <memory>
#include <functional>

class Message;
class Looper;

class MessageHandler
{
public:
    using MessageUPtr = std::unique_ptr<Message>;
    using LooperPtr = std::shared_ptr<Looper>;
    using LooperWPtr = std::weak_ptr<Looper>;

    /**
     * Default constructor
     * The Handler will be associated with a looper of current thread.
     */
    MessageHandler();

    /**
     * Constructor with looper
     * The Handler will be associated with a looper of the given thread.
     */
    explicit MessageHandler(LooperPtr looper);

    /**
     * Virtual destructor
     */
    virtual ~MessageHandler();

    /**
     * Sends a message to the handler.
     * @param message The message to be sent.
     */
    void sendMessage(MessageUPtr message);

    /**
     * Sends a message to the handler with a delay.
     * @param message The message to be sent.
     * @param delay The delay in milliseconds.
     */
    void sendMessageDelayed(MessageUPtr message, int delay);

    /**
     * Post a runnable to the handler.
     * @param runnable The runnable to be posted.
     */
    void postRunnable(std::function<void()> runnable);

    /**
     * Post a runnable to the handler with a delay.
     * @param runnable The runnable to be posted.
     * @param delay The delay in milliseconds.
     */
    void postRunnableDelayed(std::function<void()> runnable, int delay);

    /**
     * Call when the message is received.
     * @param message The received message.
     */
    virtual void handleMessage(MessageUPtr message) = 0;

    LooperWPtr getLooper() const;

private:
    LooperPtr m_looper; // The looper associated with this handler.
};

#endif // MESSAGE_HANDLER_H