#pragma once

#include "../Core/Utils/EventUtils.h"

class CEventManager
{
	friend class CEngine;
private:
	CEventManager() = default;
	~CEventManager() = default;

private:
	inline static CEventManager* mInst;

	// 이벤트 타입별로 등록된 리스너 목록
	using EventCallback = std::function<void(void*)>;
	std::unordered_map<int, std::vector<EventCallback>> mListener;

	// 다음 n 프레임에 처리할 이벤트를 임시로 보관
	struct FPendingEvent { EEventType type; void* data; float timeDelay; };
	std::vector<FPendingEvent> mPendingEvents;

public:
	void AddListener(EEventType type, EventCallback callback)
	{
		mListener[(int)type].emplace_back(callback);
	}
	void EraseListener(EEventType type)
	{
		mListener.erase((int)type);
	}
	void ClearListener()
	{
		mListener.clear();
	}

	void Broadcast(EEventType type, void* data = nullptr, float delaySec = 0.0f)
	{
		if (delaySec <= 0.0f)
		{
			for (auto& callback : mListener[(int)type])
				callback(data);
			return;
		}
		mPendingEvents.emplace_back(FPendingEvent(type, data, delaySec));
	}

private:
	void Update(float deltaTime)
	{
		for (size_t i = mPendingEvents.size(); i > 0; i--)
		{
			FPendingEvent& event = mPendingEvents[i - 1];

			event.timeDelay -= deltaTime;
			if (event.timeDelay <= 0.0f)
			{
				for (auto& callback : mListener[(int)event.type])
					callback(event.data);

				std::swap(mPendingEvents[i - 1], mPendingEvents.back());
				mPendingEvents.pop_back();
			}
		}
	}

public:
	static CEventManager* GetInst()
	{
		if (!mInst)
			mInst = new CEventManager;
		return mInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};