#include "World.h"

void World::EntityComponentsChanged(const int e, const int storageId, const bool added)
{
   auto& entity = _entities[e];
    if (added) {
        entity.AddComponent(storageId);
    } else {
        const int newComponentsCount = entity.RemoveComponent(storageId);
        if (newComponentsCount == 0)
            RemoveEntity(e);
    }
}

World::World()
{
    const int DefaultEntitiesCapacity = 64;
    std::vector<EntityId> _entities; std::vector<int> _freeEntities;
    std::unordered_map<size_t, std::shared_ptr<BaseComponentStorage>> _componentStoragesHash;
    std::vector<std::shared_ptr<BaseComponentStorage>> _componentStorages; int _storagesCount = 0;
}

int World::CreateEntity()
{
    int entityId;
    if (!_freeEntities.empty()) {
        entityId = _freeEntities.back();
        _freeEntities.pop_back();
        _entities[entityId].Recycle();
    } else {
        entityId = _entities.size();
        _entities.emplace_back(entityId, 1);
    }
    return entityId;
}

void World::RemoveEntity(int e) {
    auto& entity = _entities[e];
    if (entity.IsRemoved())
        return;
    const auto& components = entity.Components();
    if (!components.empty()) {
        for (int i = components.size() - 1; i >= 0; i--)
            _componentStorages[components[i]]->Remove(e);
    } else {
        entity.Remove();
    _freeEntities.push_back(entity.Id);
    }
}

EntityId World::GetPackedEntity(const int e) const
{
    return _entities[e];
}

bool World::UnpackEntity(const EntityId &eId, int &e) const
{
    e = eId.Id;
    return IsEntityAlive(e) && eId.Gen() == _entities[e].Gen();
}

bool World::IsEntityAlive(const int e) const
{
    auto& entity = _entities[e];
    return !entity.IsRemoved() && entity.Id > 0 && entity.Id < _entities.size() && e == entity.Id; 
}

template <typename T>
ComponentStorage<T>& World::GetStorage()
{
    const auto typeHash = typeid(T).hash_code();
    const auto foundStorageIterator = _componentStoragesHash.find(typeHash);
    if (foundStorageIterator != _componentStoragesHash.end())
        return *std::static_pointer_cast<ComponentStorage<T>>(foundStorageIterator-
        >second);
    int storagesCount = _componentStorages.size();
    auto storage = std::make_shared<ComponentStorage<T>>(*this, storagesCount);
    _componentStoragesHash.insert({typeHash, storage});
    if (storagesCount == _componentStorages.capacity())
    {
        const int newSize = _storagesCount << 1;
        _componentStorages.reserve(newSize);
    }
    _componentStorages.push_back(storage);
    return *storage;
}

template <typename T>
std::shared_ptr<ComponentStorage<T>> World::GetRawStorage()
{
    const auto typeHash = typeid(T).hash_code();
    auto it = _componentStoragesHash.find(typeHash);
    if (it != _componentStoragesHash.end())
    {
        return std::static_pointer_cast<ComponentStorage<T>>(it->second);
    }
    int storageId = _componentStorages.size();
    auto storage = std::make_shared<ComponentStorage<T>>(*this, storageId);
    _componentStoragesHash.insert({ typeHash, storage });
    if (_componentStorages.size() == _componentStorages.capacity())
    {
        size_t newSize = (_componentStorages.capacity() == 0)
            ? 1
            : _componentStorages.capacity() * 2;

        _componentStorages.reserve(newSize);
    }
    _componentStorages.push_back(storage);
    return storage;
}