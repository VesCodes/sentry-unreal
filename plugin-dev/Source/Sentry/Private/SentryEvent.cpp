// Copyright (c) 2022 Sentry. All Rights Reserved.

#include "SentryEvent.h"

#include "Interface/SentryEventInterface.h"

#if PLATFORM_ANDROID
#include "Android/SentryEventAndroid.h"
#elif PLATFORM_IOS || PLATFORM_MAC
#include "Apple/SentryEventApple.h"
#elif PLATFORM_WINDOWS || PLATFORM_LINUX
#include "Desktop/SentryEventDesktop.h"
#endif

USentryEvent::USentryEvent()
{
	if (USentryEvent::StaticClass()->GetDefaultObject() != this)
	{
#if PLATFORM_ANDROID
		EventNativeImpl = MakeShareable(new SentryEventAndroid());
#elif PLATFORM_IOS || PLATFORM_MAC
		EventNativeImpl = MakeShareable(new SentryEventApple());
#elif PLATFORM_WINDOWS || PLATFORM_LINUX
		EventNativeImpl = MakeShareable(new SentryEventDesktop());
#endif
	}
}

void USentryEvent::SetMessage(const FString& Message)
{
	if (!EventNativeImpl)
		return;

	EventNativeImpl->SetMessage(Message);
}

FString USentryEvent::GetMessage() const
{
	if(!EventNativeImpl)
		return FString();

	return EventNativeImpl->GetMessage();
}

void USentryEvent::SetLevel(ESentryLevel Level)
{
	if (!EventNativeImpl)
		return;

	EventNativeImpl->SetLevel(Level);
}

ESentryLevel USentryEvent::GetLevel() const
{
	if(!EventNativeImpl)
		return ESentryLevel::Debug;

	return EventNativeImpl->GetLevel();
}

void USentryEvent::InitWithNativeImpl(TSharedPtr<ISentryEvent> eventImpl)
{
	if (!EventNativeImpl)
		return;

	EventNativeImpl = eventImpl;
}

TSharedPtr<ISentryEvent> USentryEvent::GetNativeImpl()
{
	return EventNativeImpl;
}
