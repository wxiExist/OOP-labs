#pragma once

#include "npc.hpp"

class NPC;
class Dragon;
class Princess;
class Knight;

enum NPCType {
    UnknownType,
    PrincessType,
    DragonType,
    KnightType,
};

class Visitor {
public:
    virtual bool visit(const std::shared_ptr<Princess>&) const = 0;
    virtual bool visit(const std::shared_ptr<Dragon>&) const = 0;
    virtual bool visit(const std::shared_ptr<Knight>&) const = 0;
};


class PrincessVisitor : public Visitor {
public:
    virtual bool visit(const std::shared_ptr<Princess>&) const override { 
        return false;
    }
    virtual bool visit(const std::shared_ptr<Dragon>&) const override { 
        return false; 
    }
    virtual bool visit(const std::shared_ptr<Knight>&) const override { 
        return false;
    }
};


class DragonVisitor : public Visitor {
    virtual bool visit(const std::shared_ptr<Princess>&) const override { 
        return true; 
    }
    virtual bool visit(const std::shared_ptr<Dragon>&) const override { 
        return false;
    }
    virtual bool visit(const std::shared_ptr<Knight>&) const override { 
        return false;
    }
};


class KnightVisitor : public Visitor {
    virtual bool visit(const std::shared_ptr<Princess>&) const override { 
        return false; 
    }
    virtual bool visit(const std::shared_ptr<Dragon>&) const override { 
        return true; 
    }
    virtual bool visit(const std::shared_ptr<Knight>&) const override { 
        return false;
    }
};


class VisitorFactory {
public:
    static std::shared_ptr<Visitor> CreateVisitor(const NPCType& type) {

        if (type == NPCType::PrincessType) {
            return std::static_pointer_cast<Visitor>(std::make_shared<PrincessVisitor>());
        }

        if (type == NPCType::DragonType) {
            return std::static_pointer_cast<Visitor>(std::make_shared<DragonVisitor>());
        }

        if (type == NPCType::KnightType) {
            return std::static_pointer_cast<Visitor>(std::make_shared<KnightVisitor>());
        }

        return std::shared_ptr<Visitor>(nullptr);
    }
};
