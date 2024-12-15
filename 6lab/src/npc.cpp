#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <cstring>
#include <string>
#include <random>
#include <set>
#include <cmath>

#include "visitor.hpp"

class NPC;
class Observer {
public:
    virtual void on_fight(const std::shared_ptr<NPC>, const std::shared_ptr<NPC>, bool) = 0;
};

class NPC : public std::enable_shared_from_this<NPC> {
public:
    int x = 0;
    int y = 0;
    NPCType type;
    std::string name;

    std::vector<std::shared_ptr<Observer>> observers;

    NPC(NPCType type, const std::string& name, int x, int y);
    NPC(NPCType type, std::istream& is);

    virtual bool accept(const std::shared_ptr<NPC>& attacker) const = 0;

    void subscribe(const std::shared_ptr<Observer>& observer);
    void fight_notify(const std::shared_ptr<NPC> defender, bool win) const;
    virtual bool is_close(const std::shared_ptr<NPC>& other, size_t distance) const;

    virtual void save(std::ostream& os);
    friend std::ostream& operator<<(std::ostream& os, NPC& npc);
};

using set_t = std::set<std::shared_ptr<NPC>>;

NPC::NPC(NPCType type, const std::string& name, int x, int y) : type(type), name(name), x(x), y(y) {
}

NPC::NPC(NPCType type, std::istream& is) : type(type) {
    is >> name;
    is >> x;
    is >> y;
}

void NPC::subscribe(const std::shared_ptr<Observer>& observer) {
    observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC> defender, bool win) const {
    for (auto& i: observers) {
        i->on_fight(std::const_pointer_cast<NPC>(shared_from_this()), defender, win);
    }
}

bool NPC::is_close(const std::shared_ptr<NPC>& other, size_t distance) const {
    return ((std::pow(x - other->x, 2) + std::pow(y - other->y, 2)) <= std::pow(distance, 2));
}

void NPC::save(std::ostream& os) {
    os << name << std::endl;
    os << x << std::endl;
    os << y << std::endl;
}

std::ostream& operator<<(std::ostream& os, NPC& npc) {
    os << npc.name << "(" << npc.x << ", " << npc.y << ") ";
    return os;
}

class Knight : public NPC {
public:
    Knight(const std::string& name, int x, int y);
    Knight(std::istream& is);

    virtual bool accept(const std::shared_ptr<NPC>& attacker) const override;
    void save(std::ostream& os) override;
    friend std::ostream& operator<<(std::ostream& os, Knight& knight);
};


Knight::Knight(const std::string& name, int x, int y) : NPC(KnightType, name, x, y) {
}

Knight::Knight(std::istream& is) : NPC(KnightType, is) {
}

bool Knight::accept(const std::shared_ptr<NPC>& attacker) const {
    
    std::shared_ptr<Visitor> v = VisitorFactory::CreateVisitor(attacker->type);
    std::shared_ptr<Knight> defender = std::dynamic_pointer_cast<Knight>(std::const_pointer_cast<NPC>(shared_from_this()));
    
    bool result = v->visit(defender);
    attacker->fight_notify(defender, result);
    return result;
}

void Knight::save(std::ostream& os) {
    os << KnightType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Knight& knight) {
    os << "knight " << *(static_cast<NPC*>(&knight)) << std::endl;
    return os;
}

class Dragon : public NPC {
public:
    Dragon(const std::string& name, int x, int y);
    Dragon(std::istream& is);

    virtual bool accept(const std::shared_ptr<NPC>& attacker) const override;
    void save(std::ostream& os) override;
    friend std::ostream& operator<<(std::ostream& os, Dragon& dragon);
};

Dragon::Dragon(const std::string& name, int x, int y) : NPC(DragonType, name, x, y) {
}

Dragon::Dragon(std::istream& is) : NPC(DragonType, is) {
}

bool Dragon::accept(const std::shared_ptr<NPC>& attacker) const {
    
    std::shared_ptr<Visitor> v = VisitorFactory::CreateVisitor(attacker->type);
    std::shared_ptr<Dragon> defender = std::dynamic_pointer_cast<Dragon>(std::const_pointer_cast<NPC>(shared_from_this()));
    
    bool result = v->visit(defender);
    attacker->fight_notify(defender, result);
    return result;
}

void Dragon::save(std::ostream& os) {
    os << DragonType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Dragon& dragon) {
    os << "dragon " << *(static_cast<NPC*>(&dragon)) << std::endl;
    return os;
}

class Princess : public NPC {
public:
    Princess(const std::string& name, int x, int y);
    Princess(std::istream& is);

    virtual bool accept(const std::shared_ptr<NPC>& attacker) const override;
    void save(std::ostream& os) override;
    friend std::ostream& operator<<(std::ostream& os, Princess& princess);
};

Princess::Princess(const std::string& name, int x, int y) : NPC(PrincessType, name, x, y) {
}

Princess::Princess(std::istream& is) : NPC(PrincessType, is) {
}

bool Princess::accept(const std::shared_ptr<NPC>& attacker) const {
    
    std::shared_ptr<Visitor> v = VisitorFactory::CreateVisitor(attacker->type);
    std::shared_ptr<Princess> defender = std::dynamic_pointer_cast<Princess>(std::const_pointer_cast<NPC>(shared_from_this()));
    
    bool result = v->visit(defender);
    attacker->fight_notify(defender, result);
    return result;
}

void Princess::save(std::ostream& os) {
    os << PrincessType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Princess& princess) {
    os << "princess " << *(static_cast<NPC*>(&princess)) << std::endl;
    return os;
}
