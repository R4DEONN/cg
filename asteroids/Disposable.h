#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>

template<typename... Args>
class EventDispatcher
{
public:
	using Handler = std::function<void(Args...)>;

	std::shared_ptr<Handler> AddHandler(Handler handler)
	{
		auto wrapper = std::make_shared<Handler>(std::move(handler));
		handlers.push_back(wrapper);
		return wrapper;
	}

	void RemoveHandler(const std::shared_ptr<Handler>& handler)
	{
		handlers.erase(
			std::remove(handlers.begin(), handlers.end(), handler),
			handlers.end()
		);
	}

	void Dispatch(Args... args)
	{
		for (const auto& handler: handlers)
		{
			(*handler)(std::forward<Args>(args)...);
		}
	}

private:
	std::vector<std::shared_ptr<Handler>> handlers;
};

class Disposable
{
public:
	~Disposable()
	{
		for (auto& cleanup: cleanups)
		{
			cleanup();
		}
	}

	template<typename... Args>
	void AddHandler(EventDispatcher<Args...>& dispatcher, typename EventDispatcher<Args...>::Handler handler)
	{
		auto handlerPtr = dispatcher.AddHandler(std::move(handler));
		cleanups.push_back([dispatcher = &dispatcher, handlerPtr]
		{
			dispatcher->RemoveHandler(handlerPtr);
		});
	}

private:
	std::vector<std::function<void()>> cleanups;
};