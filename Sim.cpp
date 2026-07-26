#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <random>
#include <algorithm>

using namespace std;

//=========================================================
// Entity Interface
//=========================================================

class IEntity {

public:

    virtual void initialize() = 0;
    virtual void update(double deltaTime) = 0;
    virtual void render() = 0;
    virtual ~IEntity() = default;

};

//=========================================================
// Simulation Object
//=========================================================

class Agent : public IEntity {

private:

    int id;
    double x;
    double y;
    double velocity;

public:

    Agent(int id)
        : id(id), x(0), y(0), velocity(1.5) {}

    void initialize() override {

        random_device rd;
        mt19937 gen(rd());

        uniform_real_distribution<> dist(0,100);

        x = dist(gen);
        y = dist(gen);

    }

    void update(double deltaTime) override {

        x += velocity * deltaTime;
        y += velocity * deltaTime;

    }

    void render() override {

        cout
            << "Agent "
            << id
            << " Position("
            << x
            << ", "
            << y
            << ")\n";

    }

};

//=========================================================
// Simulation Engine
//=========================================================

class Simulation {

private:

    vector<unique_ptr<IEntity>> entities;

    bool running = true;

    double deltaTime = 0.016;

public:

    void initialize() {

        cout << "Initializing Simulation...\n";

        for(int i = 1; i <= 10; i++) {

            auto agent = make_unique<Agent>(i);

            agent->initialize();

            entities.push_back(move(agent));

        }

    }

    void update() {

        for(auto& entity : entities)
            entity->update(deltaTime);

    }

    void render() {

        cout << "\n========== FRAME ==========\n";

        for(auto& entity : entities)
            entity->render();

    }

    void loop() {

        int frame = 0;

        while(running && frame < 5) {

            auto start = chrono::high_resolution_clock::now();

            update();

            render();

            auto end = chrono::high_resolution_clock::now();

            auto duration =
                chrono::duration_cast
                <chrono::milliseconds>
                (end-start);

            cout << "Frame Time: "
                 << duration.count()
                 << " ms\n\n";

            this_thread::sleep_for(
                chrono::milliseconds(500));

            frame++;

        }

    }

    void shutdown() {

        entities.clear();

        cout << "\nSimulation Finished.\n";

    }

};

//=========================================================
// Main
//=========================================================

int main() {

    Simulation simulator;

    simulator.initialize();

    simulator.loop();

    simulator.shutdown();

    return 0;

}
