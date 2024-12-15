#pragma once
#include "npc.hpp"
#include "observer.hpp"

class NPCFactory {
public:
    static std::shared_ptr<NPC> CreateNPC(const NPCType& type, const std::string& name, int x, int y) {
        std::shared_ptr<NPC> res;    

        if (type == NPCType::PrincessType) {
            res = std::static_pointer_cast<NPC>(std::make_shared<Princess>(name, x, y));
        } else if (type == NPCType::DragonType) {
            res = std::static_pointer_cast<NPC>(std::make_shared<Dragon>(name, x, y));
        } else if (type == NPCType::KnightType) {
            res = std::static_pointer_cast<NPC>(std::make_shared<Knight>(name, x, y));
        }

        if (res) {
            res->subscribe(TextObserver::get());
            res->subscribe(FileObserver::get());
        }

        return res;
    }

    static std::shared_ptr<NPC> CreateNPC(std::istream& is) {
        std::shared_ptr<NPC> res;
        int type = 0;
        if (is >> type) {
            if (type == NPCType::PrincessType) {
                res = std::static_pointer_cast<NPC>(std::make_shared<Princess>(is));
            } else if (type == NPCType::DragonType) {
                res = std::static_pointer_cast<NPC>(std::make_shared<Dragon>(is));
            } else if (type == NPCType::KnightType) {
                res = std::static_pointer_cast<NPC>(std::make_shared<Knight>(is));
            }
        }

        if (res) {
            res->subscribe(TextObserver::get());
            res->subscribe(FileObserver::get());
        }

        return res;
    }
};
