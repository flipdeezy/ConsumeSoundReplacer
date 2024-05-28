#include "Events.h"
#include "Logging.h"

EventProcessor::EventProcessor() = default; 
EventProcessor::~EventProcessor() = default;

EventProcessor& EventProcessor::GetInstance() {
    static EventProcessor instance;
    return instance;
}

RE::BSEventNotifyControl EventProcessor::ProcessEvent(const RE::TESEquipEvent* event, RE::BSTEventSource<RE::TESEquipEvent>*) {

        return RE::BSEventNotifyControl::kContinue;
}

void EventProcessor::RegisterEventHandlers() {
    auto& eventProcessor = EventProcessor::GetInstance();
    RE::ScriptEventSourceHolder::GetSingleton()->AddEventSink<RE::TESEquipEvent>(&eventProcessor);
    logger::info("EventProcessor - Event Handlers Registered");
}