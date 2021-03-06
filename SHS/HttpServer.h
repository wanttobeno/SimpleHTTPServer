#pragma once

#include <iostream>
#include <chrono>
#include <time.h>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <fstream>

#include "Http.h"
#include "HttpUtils.h"
#include "Sockets.h"

namespace Http
{
	class HttpServer
	{
	private:
		sockets::ServerSocket server;

		int threadCount;
		std::vector<std::thread> threadpool;

		std::queue<sockets::ClientConnection> clientQueue;
		std::mutex clientQueueMutex;
		std::condition_variable clientQueueConditionVariable;

		bool stopped = false;

	protected:
		void threadNetworkHandler();
		HttpResponse httpRequestHandler(HttpRequest req) const;

	public:
		HttpServer(int threadCount = 100);

		void start();
		void stop();

		bool isStopped() const;
	};
}
