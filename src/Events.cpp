#include "Events.h"
#include "Logging.h"

EventProcessor::EventProcessor() = default; 
EventProcessor::~EventProcessor() = default;

EventProcessor& EventProcessor::GetInstance() {
    static EventProcessor instance;
    return instance;
}

// Process equip events
// std::unordered_map<RE::FormID, RE::BGSSoundDescriptorForm*> originalSoundsMap;
RE::BSEventNotifyControl EventProcessor::ProcessEvent(const RE::TESEquipEvent* event, RE::BSTEventSource<RE::TESEquipEvent>*) {
//     if (!event) {
//         return RE::BSEventNotifyControl::kContinue;
//     }

//     auto a_object = RE::TESForm::LookupByID<RE::TESBoundObject>(event->baseObject);
//     if (!a_object) {
//         return RE::BSEventNotifyControl::kContinue;
//     }

//     auto a_actor = RE::TESForm::LookupByID<RE::Actor>(event->actor->formID);
//     if (!a_actor) {
//         return RE::BSEventNotifyControl::kContinue;
//     }

//     if (a_object->Is(RE::FormType::AlchemyItem)) { 
//         auto bPlayEquipSound = GetAnimationVariableBool(a_actor, "bPlayEquipSound");
//         auto alchemyItem = static_cast<RE::AlchemyItem*>(a_object);
//         auto customSound = RE::TESForm::LookupByID<RE::BGSSoundDescriptorForm>(0x03C7BA);
//         if (customSound) {
//             logger::info("Custom sound: {}", customSound->GetFormID());
//             if (alchemyItem->data.consumptionSound) {
//                 logger::info("Alchemy item sound: {}", alchemyItem->data.consumptionSound->GetFormID()); 

//                 // Store the original sound in the map if not already stored
//                 if (originalSoundsMap.find(alchemyItem->GetFormID()) == originalSoundsMap.end()) {
//                     originalSoundsMap[alchemyItem->GetFormID()] = alchemyItem->data.consumptionSound;
//                 }

//                 // Change the sound to the custom sound
//                 alchemyItem->data.consumptionSound = customSound;
//             } else {
//                 logger::warn("Alchemy item has no consumption sound!");
//             }

//             // Revert the sound if bPlayEquipSound is true
//             if (bPlayEquipSound) {
//                 auto originalSoundIt = originalSoundsMap.find(alchemyItem->GetFormID());
//                 if (originalSoundIt != originalSoundsMap.end()) {
//                     alchemyItem->data.consumptionSound = originalSoundIt->second;
//                     logger::info("Reverted alchemy item sound to original: {}", originalSoundIt->second->GetFormID());
//                     originalSoundsMap.erase(originalSoundIt);
//                 }
//             }
//         } else {
//             logger::warn("Custom sound not found!");
//         }
//     }

        return RE::BSEventNotifyControl::kContinue;
}

void EventProcessor::RegisterEventHandlers() {
    auto& eventProcessor = EventProcessor::GetInstance();
    RE::ScriptEventSourceHolder::GetSingleton()->AddEventSink<RE::TESEquipEvent>(&eventProcessor);
    logger::info("EventProcessor - Event Handlers Registered");
}