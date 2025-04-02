/*
* File: Message.h
* Author: trung.la
* Date: 04-02-2025
* Description: This is Message class.
* This class is used to represent a message in the message queue.
*/

#ifndef MESSAGE_H
#define MESSAGE_H

#include <memory>
#include <functional>

class MessageHandler;

/**
 * A message class.
 * This class is used to represent a message in the message queue.
 */
class Message
{
public:
    using MessageUPtr = std::unique_ptr<Message>;
    using MessageHandlerPtr = std::shared_ptr<MessageHandler>;
    /**
     * Creates a new message.
     */
    static MessageUPtr obtain();

    /**
     * Creates a new message with a callback.
     * @param callback The callback to be called when the message is processed.
     */
    static MessageUPtr obtain(std::function<void()> callback);

    /**
     * Returns a message to the global pool.
     */
    void recycle();

    void setWhat(int what);
    void getWhat(int &what) const;

    void setArg1(int arg1);
    void getArg1(int &arg1) const;

    void setArg2(int arg2);
    void getArg2(int &arg2) const;

    void setData(void* data);
    void* getData() const;

    void setCallback(std::function<void()> callback);
    void getCallback(std::function<void()>& callback) const;

    void setWhen(long when);
    void getWhen(long &when) const;
private:
    // Private constructor
    Message();

    int64_t m_when;
    int m_what;
    int m_arg1;
    int m_arg2;
    void* m_data;
    std::function<void()> m_callback;
    MessageHandlerPtr m_handler;
};

#endif // MESSAGE_H