#include <iostream>
#include <map>
#include <random>
#include <chrono>
#include <thread>
#include <mutex> 
#include <shared_mutex>
#include <cstdlib>

#include "src/NPCFactory.cpp"

class Game {
public:
    Game() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 99); 
        for (size_t i = 0; i < 500; ++i) {
            int x = distrib(gen);
            int y = distrib(gen);
            NPCType type = (i % 3 == 0) ? NPCType::PrincessType : (i % 3 == 1) ? NPCType::DragonType : NPCType::KnightType;
            characters_.emplace(std::make_pair(x, y), NPCFactory::CreateNPC(type, std::to_string(i), x, y));
        }
    }

    void Battle() {
        std::unique_lock<std::shared_mutex> lock(npcs_mutex); 
        std::map<std::pair<int, int>, std::shared_ptr<NPC>> kills;
        for (auto i : this->characters_) {
            for (auto j : this->characters_) {
                if (i.second->accept(j.second)) kills[std::make_pair(i.second->x, i.second->y)];
            }
        }
        for (auto i : kills) {
            this->characters_[std::make_pair(i.first.first, i.first.second)]->act = false;
        }
    }

    void Move() {
        std::unique_lock<std::shared_mutex> lock(npcs_mutex); 
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 99);
        auto m = this->characters_;
        for (auto i : this->characters_) {
            if (i.second->act) {
                int newX = i.second->x + (distrib(gen) % 3) - 1; 
                int newY = i.second->y + (distrib(gen) % 3) - 1;
                newX = std::max(0, std::min(newX, 99));
                newY = std::max(0, std::min(newY, 99));
                auto t = m[std::make_pair(i.second->x, i.second->y)];
                m.erase(std::make_pair(i.second->x, i.second->y));
                t->x = newX;
                t->y = newY;
                m[std::make_pair(t->x, t->y)] = t;
            }
        }
        this->characters_ = m;
    }

    void Print() {
        std::unique_lock<std::shared_mutex> lock(npcs_mutex); 
        system("clear");
        for (size_t i = 0; i < 100; ++i) {
            for (size_t j = 0; j < 100; ++j) {
                auto it = this->characters_.find(std::make_pair(i, j));
                if (it != this->characters_.end()) {
                    if (this->characters_[std::make_pair(i, j)]->act) {
                        std::cout << "@";
                    } else {
                        std::cout << "x";
                    }
                } else {
                    std::cout << ".";
                }
            }
            std::cout << std::endl;
        }
    }

private:
    std::map<std::pair<int, int>, std::shared_ptr<NPC>> characters_;
    std::mutex cout_mutex;
    std::shared_mutex npcs_mutex;
};


int main() {

    Game g;

    auto start = std::chrono::steady_clock::now();

    std::thread Thread1([&g]() { 
        while (true) {
            g.Move(); 
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    });

    std::thread Thread2([&g]() { 
        while (true) {
            g.Battle(); 
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    });

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    while (time.count() < 30) {
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        g.Print();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    Thread1.join();
    Thread2.join();

    return 0;
}
