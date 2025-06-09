## Main Components:

**User Profile Service Package:**

* `UserProfileService` - Main service class that orchestrates user operations
* `User` and `UserData` - Domain models for user data
* `UserRepository` - Data access layer
* Event classes (`UserCreatedEvent`, `UserUpdatedEvent`, `UserDeletedEvent`)

**Kafka Integration Package:**

* `KafkaMessageProducer` - Wraps cppkafka producer for publishing events
* `KafkaMessageConsumer` - Wraps cppkafka consumer for receiving messages
* `MessageHandler` interface for processing incoming messages
* `Message` class representing Kafka messages

**Event Handlers Package:**

* `EventHandler` interface for processing user events
* Specific handlers for different services (Order, Notification, Audit)
* Shows how other microservices can react to user profile changes

**Configuration:**

* `ServiceConfig` and `TopicConfig` for managing Kafka and service settings

## Key Design Patterns:

1. **Event-Driven Architecture** - User operations trigger events published to Kafka
2. **Handler Pattern** - Different event handlers for different business concerns
3. **Repository Pattern** - Clean separation of data access
4. **Publisher-Subscriber** - Services communicate via Kafka topics
