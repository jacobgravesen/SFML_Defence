#include "WaveManager.h"
#include "Enemy.h"
#include <iostream>

WaveManager::WaveManager(const std::vector<Wave>& waves)
    : waves(waves), currentWaveIndex(-1), timeSinceLastSpawn(0), currentEnemyIndex(0) {
    std::cout << "WaveManager initialized with " << waves.size() << " waves." << std::endl;
}

void WaveManager::startNextWave() {
    if (currentWaveIndex < static_cast<int>(waves.size()) - 1) {
        currentWaveIndex++;
        currentEnemyIndex = 0;
        timeSinceLastSpawn = 0;
        std::cout << "Starting wave " << currentWaveIndex + 1 << std::endl;
    }
    else {
        std::cout << "All waves completed!" << std::endl;
    }
}

void WaveManager::update(float deltaTime, std::vector<std::shared_ptr<Enemy>>& enemies, const Path& path) {
    if (currentWaveIndex >= static_cast<int>(waves.size())) {
        std::cout << "All waves completed." << std::endl;
        return;
    }
    if (currentWaveIndex == -1) {
        return;
    }

    Wave& currentWave = waves[currentWaveIndex];
    timeSinceLastSpawn += deltaTime;

    while (currentEnemyIndex < static_cast<int>(currentWave.enemyTypes.size()) && timeSinceLastSpawn >= currentWave.spawnInterval) {
        EnemyType enemyType = currentWave.enemyTypes[currentEnemyIndex].first;
        int& quantity = currentWave.enemyTypes[currentEnemyIndex].second;

        if (quantity > 0) {
            // Spawn enemy based on type
            switch (enemyType) {
            case EnemyType::Basic:
                enemies.push_back(std::make_shared<BasicEnemy>(path));
                break;
            case EnemyType::Fast:
                enemies.push_back(std::make_shared<FastEnemy>(path));
                break;
            case EnemyType::Strong:
                enemies.push_back(std::make_shared<StrongEnemy>(path));
                break;
            }
            std::cout << "Spawned enemy of type " << static_cast<int>(enemyType) << std::endl;
            quantity--;
            timeSinceLastSpawn -= currentWave.spawnInterval;  // Subtract spawnInterval instead of resetting to 0

            if (quantity == 0) currentEnemyIndex++;
        }
    }
}

bool WaveManager::isWaveCompleted(const std::vector<std::shared_ptr<Enemy>>& enemies) {
    if (currentWaveIndex == -1 || currentWaveIndex >= static_cast<int>(waves.size())) {
        std::cout << "No wave or all waves completed." << std::endl;
        return false;
    }
    for (const auto& enemy : enemies) {
        if (!enemy->isDead()) {
            return false;
        }
    }
    bool completed = currentEnemyIndex >= static_cast<int>(waves[currentWaveIndex].enemyTypes.size());
    std::cout << "Wave completed: " << (completed ? "yes" : "no") << std::endl;
    return completed;
}

float WaveManager::getEnemySpeed(EnemyType type) {
    switch (type) {
    case EnemyType::Basic: return 0.1f;
    case EnemyType::Fast: return 0.2f;
    case EnemyType::Strong: return 0.05f;
    default: return 0.1f;
    }
}

int WaveManager::getEnemyHealth(EnemyType type) {
    switch (type) {
    case EnemyType::Basic: return 100;
    case EnemyType::Fast: return 75;
    case EnemyType::Strong: return 200;
    default: return 100;
    }
}
