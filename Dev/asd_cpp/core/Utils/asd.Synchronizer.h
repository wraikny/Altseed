﻿#pragma once
#include <functional>
#include <mutex>
#include "IAsyncResource.h"

namespace asd
{
	typedef std::function<void()> Continuation;

	class SyncInfo
	{
	private:
		IAsyncResource * resource;
		Continuation continuation;
		int id;

	public:
		typedef std::shared_ptr<SyncInfo> Ptr;

		SyncInfo(IAsyncResource* resource, Continuation continuation, int id);
		~SyncInfo();

		IAsyncResource* GetResource() { return resource; }
		Continuation GetContinuation() { return continuation; }

		bool operator==(const SyncInfo& right) const
		{
			return id == right.id;
		}
	};

	class Synchronizer
	{
	private:
		std::list<SyncInfo::Ptr> requests;
		std::mutex listMutex;
		int finalId = -1;

	public:
		typedef std::shared_ptr<Synchronizer> Ptr;

		Synchronizer();

		void Update();
		void Start(IAsyncResource* resource, Continuation continuation);
	};
}