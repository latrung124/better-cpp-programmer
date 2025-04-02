/*
* File: Looper.h
* Author: trung.la
* Date: 04-02-2025
* Description: This is Looper class.
* This class is a message loop for a thread handling the dispatching of message to handlers.
*/

#include <memory>
#include <functional>
#include <thread>
#include <atomic>
#include <map>
#include <queue>
#include <mutex>
#include <condition_variable>

// #include <uv.h>

class Message;

/**
 * A Message loop for a thread.
 * Handles the dispatching of messages to handlers.
 */
class Looper
{
public:
    using MessageUPtr = std::unique_ptr<Message>;

    /**
     * Creates a new looper for the current thread.
     * @return A shared pointer to the new looper.
     * nullptr if the looper could not be created or called prepare() method.
     */
    static std::shared_ptr<Looper> getForThread();

    /**
     * Prepares the looper for the current thread.
     * Call before using the looper.
     */
    static void prepare();

    /**
     * Enters the looper's message loop.
     */
    void loop();

    /**
     * Exits the looper's message loop.
     */
    void quit();

    /**
     * Posts a message to the looper.
     * @param message The message to be posted.
     */
    void postMessage(MessageUPtr message);

    /**
     * Adds a file descriptor to be monitored.
     * @param fd The file descriptor to be monitored.
     * @param events The events to be monitored.
     * @param callback The callback to be called when the events occur.
     * @param data The data to be passed to the callback.
     * @return true if the file descriptor was added successfully, false otherwise.
     */
    bool addFd(int fd, int events, std::function<void(int, int)> callback, void* data);

    /**
     * Waits for messages or events. Returns after the timeout or processing a message.
     * @param timeout The timeout in milliseconds.
     * return POLL_WAKE if wake() was called, POLL_TIMEOUT if timeout occurred, or POLL_ERROR if an error occurred.
     * and POLL_CALLBACK if a callback was called.
     */
    int pollOnce(int timeoutMillis = -1);

    /**
     * Wakes up the looper.
     */
    void wake();

    /**
     * Get identifier of the thread associated with the looper.
     * @return The identifier of the thread associated with the looper.
     */
    std::thread::id getThreadId() const;

    /**
     * Destructor.
     */
    ~Looper();

private:
    enum PollResult
    {
        POLL_WAKE = 1,
        POLL_TIMEOUT = 2,
        POLL_ERROR = -1,
        POLL_CALLBACK = 3
    };

    // Maximum number of file descriptors that can be monitored.
    static constexpr int EPOLL_MAX_EVENTS = 1024;

    // File descriptor callback information
    struct Request
    {
        int fd;
        int events;
        std::function<void(int, int, void*)> callback;
        void* data;
    };

    //Private constructor
    Looper();

    // Process next message
    void processNextMessage(int timeoutMillis);

    // static void onAsync(uv_async_t* handle, int status);
    // static void onPoll(uv_poll_t* handle, int status, int events);

    static void initTLSKey();

    std::thread m_thread;
    int m_epollFd;
    bool m_isPolling;
    std::atomic<bool> m_isQuiting;
    std::map<int, Request> m_requests;
    std::queue<MessageUPtr> m_messageQueue;
    std::mutex m_mutex;
    std::condition_variable m_condition;
    bool m_isMessageAvailable;
};