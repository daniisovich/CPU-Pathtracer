#pragma once

#include <thread>
#include <mutex>
#include <functional>
#include <queue>
#include <vector>

#include "image.h"
#include "../scene/scene.h"


using ThreadJob = std::function<void(int, int, int, int, const Scene&, Image&)>;


class ThreadPool {

public:

	void queueJob(const ThreadJob& job, int x, int y, int num_samples, int num_bounces, const Scene& scene, Image& img);
	void start(int num_threads = std::thread::hardware_concurrency());
	bool complete();
	void stop();

private:

	void threadfunc();

	bool m_terminate{ false };
	std::mutex m_queue_mutex;
	std::condition_variable m_mutex_condition;

	std::vector<std::thread> m_threads;
	std::queue<std::function<void()>> m_jobs;

};