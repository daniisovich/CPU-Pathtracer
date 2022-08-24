#include "precompiled/pch.h"
#pragma hdrstop

#include "thread_pool.h"


void ThreadPool::threadfunc() {

	while (true) {
		std::function<void()> job;
		{
			std::unique_lock<std::mutex> lock{ m_queue_mutex };
			m_mutex_condition.wait(lock, [this]() { return !m_jobs.empty() || m_terminate; });
			if (m_terminate) return;
			job = m_jobs.front();
			m_jobs.pop();
		}
		job();
	}

}

void ThreadPool::start(int num_threads) {

	m_threads.resize(num_threads);
	for (int i{ 0 }; i < num_threads; ++i) {
		m_threads[i] = std::thread{ [this]() { this->threadfunc(); } };
	}

}

void ThreadPool::queueJob(const ThreadJob& job, int x, int y, int num_samples, int num_bounces, const Scene& scene, Image& img) {
	m_jobs.push([job, x, y, num_samples, num_bounces, &scene, &img]() { job(x, y, num_samples, num_bounces, scene, img); });
}

bool ThreadPool::complete() {

	bool complete;
	{
		std::unique_lock<std::mutex> lock{ m_queue_mutex };
		complete = m_jobs.empty();
	}
	return complete;

}

void ThreadPool::stop() {

	{
		std::unique_lock<std::mutex> lock{ m_queue_mutex };
		m_terminate = true;
	}
	m_mutex_condition.notify_all();

	for (std::thread& thread : m_threads) {
		thread.join();
	}
	m_threads.clear();

}