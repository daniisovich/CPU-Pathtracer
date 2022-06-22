#include "thread_pool.h"


void ThreadPool::threadfunc() {

	while (true) {
		std::function<void()> job;
		{
			std::unique_lock<std::mutex> lock{ queue_mutex };
			mutex_condition.wait(lock, [this]() { return !jobs.empty() || terminate; });
			if (terminate) return;
			job = jobs.front();
			jobs.pop();
		}
		job();
	}

}

void ThreadPool::start(int num_threads) {

	threads.resize(num_threads);
	for (int i{ 0 }; i < num_threads; ++i) {
		threads[i] = std::thread{ [this]() { this->threadfunc(); } };
	}

}

void ThreadPool::queueJob(const ThreadJob& job, int x, int y, int num_samples, int num_bounces, const Scene& scene, Image& img) {

	{
		std::unique_lock<std::mutex> lock{ queue_mutex };
		jobs.push([job, x, y, num_samples, num_bounces, &scene, &img]() { job(x, y, num_samples, num_bounces, scene, img); });
	}
	mutex_condition.notify_one();

}

bool ThreadPool::complete() {

	bool complete;
	{
		std::unique_lock<std::mutex> lock{ queue_mutex };
		complete = jobs.empty();
	}
	return complete;

}

void ThreadPool::stop() {

	{
		std::unique_lock<std::mutex> lock{ queue_mutex };
		terminate = true;
	}
	mutex_condition.notify_all();

	for (std::thread& thread : threads) {
		thread.join();
	}
	threads.clear();

}