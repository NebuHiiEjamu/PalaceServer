#include "hive.hpp"

Hive::Hive():
	workGuard(asio::make_work_guard(ioContext)),
	shutdownSignal(0)
{
}

asio::io_context& Hive::getIOContext()
{
	return ioContext;
}

bool Hive::stopped()
{
	std::uint32_t v1 = 1;
	std::uint32_t v2 = 1;
	return shutdownSignal.compare_exchange_strong(v1, v2);
}

void Hive::poll()
{
	ioContext.poll();
}

void Hive::run()
{
	ioContext.run();
}

void Hive::stop()
{
	std::uint32_t v1 = 1;
	std::uint32_t v2 = 0;

	if (!shutdownSignal.compare_exchange_strong(v1, v2))
	{
		workGuard.reset();
		ioContext.run();
		ioContext.stop();
	}
}

void Hive::reset()
{
	std::uint32_t v1 = 0;
	std::uint32_t v2 = 1;

	if (shutdownSignal.compare_exchange_strong(v1, v2))
	{
		ioContext.reset();
		workGuard.reset(asio::make_work_guard(ioContext)),
	}
}
