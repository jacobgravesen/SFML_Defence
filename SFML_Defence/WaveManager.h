#pragma once
#include <vector>
#include <memory>
#include "Enemy.h"
#include "Path.h"

enum class EnemyType {
    Basic,
    Fast,
    Strong,
    // Add more types as needed
};

class Wave {
public:
    std::vector<std::pair<EnemyType, int>> enemyTypes; // Pair of enemy type and quantity
    float spawnInterval; // Time between spawning each enemy in seconds

    Wave(std::vector<std::pair<EnemyType, int>> enemyTypes, float spawnInterval)
        : enemyTypes(enemyTypes), spawnInterval(spawnInterval) {}
};

class WaveManager {
public:
    std::vector<Wave> waves;
    int currentWaveIndex;
    float timeSinceLastSpawn;
    int currentEnemyIndex;

    WaveManager(const std::vector<Wave>& waves);

    void startNextWave();
    void update(float deltaTime, std::vector<std::shared_ptr<Enemy>>& enemies, const Path& path);
    bool isWaveCompleted(const std::vector<std::shared_ptr<Enemy>>& enemies);

private:
    float getEnemySpeed(EnemyType type);
    int getEnemyHealth(EnemyType type);
};
