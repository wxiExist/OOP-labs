#include "npc.hpp"

class Observer {
public:
    virtual void on_fight(const std::shared_ptr<NPC>, const std::shared_ptr<NPC>, bool) = 0;
};


class TextObserver : public Observer {
public:
    static std::shared_ptr<Observer> get() {
        static TextObserver instance;
        return std::shared_ptr<Observer>(&instance, [](Observer*){});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::cout << *attacker << "kill" << *defender << "\n";
        }
    }
};


class FileObserver : public Observer {
private:
    FileObserver() {};

public:
    static std::shared_ptr<Observer> get() {
        static FileObserver instance;
        return std::shared_ptr<Observer>(&instance, [](Observer*) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::ofstream lg("log.txt", std::ios::app);
            lg << *attacker << "kill" << *defender << "\n";
            lg.close();
        }
    }
};
