#include <string>
#include <map>
#include <vector>
#include <iostream>


class IPublisher {
public: virtual  void publish(std::string data) {};
};

class ISubscriber {
public: virtual void notify(std::string data) {};
};

class IEventChannel {
public:
	virtual void publish(std::string topic, std::string data) {};
	virtual void subscribe(std::string topic, ISubscriber* subscriber) {};
};

class EventChannel : public IEventChannel {
public: 
	void publish(std::string topic, std::string data) {
		auto findIter = topics.find(topic);
		if (findIter != topics.end()) {
			// if topics exist => notify all its subscribers
			for (auto subscriber : findIter->second) {
				subscriber->notify(data);
			}
		}
	}

	void subscribe(std::string topic, ISubscriber* subscriber) {
		auto findIter = topics.find(topic);
		if (findIter != topics.end()) {
			// add in existed topic new subscriber
			findIter->second.push_back(subscriber);
		}
		else {
			// add new topic with new subscriber
			topics.insert({ topic, std::vector<ISubscriber*>(1, subscriber) });
		}
	}

private: 
	std::map < std::string, std::vector<ISubscriber*>> topics;
};

class Publisher : public  IPublisher {
public:
	Publisher(std::string _topic, IEventChannel* _channel) {
		topic = _topic;
		channel = _channel;
	}

	void publish(std::string data) {
		channel->publish(topic, data);
	}

private:
	std::string topic;
	IEventChannel* channel;
};

class Subscriber : public  ISubscriber {
public: 
	Subscriber(std::string _name) {
		name = _name;
	}

	void notify(std::string data) {
		std::cout << "Subscriber " << name << " notify: " << data << std::endl;
	}

private:
	std::string name;
};

void main2() {
	IEventChannel* eventChannel = new EventChannel();
	IPublisher* publisherA = new Publisher("topic_A", eventChannel);
	IPublisher* publisherB = new Publisher("topic_B", eventChannel);
	ISubscriber* subscriber1 = new Subscriber("Subscriber1");
	ISubscriber* subscriber2 = new Subscriber("Subscriber2");

	eventChannel->subscribe("topic_A", subscriber1);
	eventChannel->subscribe("topic_A", subscriber2);
	eventChannel->subscribe("topic_B", subscriber2);

	publisherA->publish("Hello from publisherA");
	// Subscriber Subscriber1 notify: Hello from publisherA

	publisherB->publish("Hello from publisherB");
	//Subscriber Subscriber2 notify: Hello from publisherA
	//Subscriber Subscriber2 notify: Hello from publisherB
}