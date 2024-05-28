#pragma once
#
class EventProcessor : public RE::BSTEventSink<RE::TESEquipEvent>
{
public:
    static EventProcessor& GetInstance();
    RE::BSEventNotifyControl ProcessEvent(const RE::TESEquipEvent* event, RE::BSTEventSource<RE::TESEquipEvent>*) override;
    static void RegisterEventHandlers();

private:
    EventProcessor();  
    ~EventProcessor(); 
};