#pragma once

#include "logging.h"

class Utility : public Singleton<Utility>
{
public:
    static bool GetAnimationVariableBool(RE::Actor* a_actor, const std::string& variableName) {
        bool value = false;
        auto animGraphHolder = static_cast<RE::IAnimationGraphManagerHolder*>(a_actor);
        if (animGraphHolder) {
            animGraphHolder->GetGraphVariableBool(variableName.c_str(), value);
            logger::info("variable '{}' for actor '{}': Value = {}", variableName,
                         a_actor->GetName(), value ? "true" : "false");
        } else {
            logger::error("Failed to get animGraphHolder for actor '{}'",
                          a_actor->GetName());
        }
        return value;
    }
};