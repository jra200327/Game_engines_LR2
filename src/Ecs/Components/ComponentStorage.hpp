#ifndef COMPONENTSTORAGE_H
#define COMPONENTSTORAGE_H

#include <vector>

#include "BaseComponentStorage.h"
#include "../World/IWorldInternal.h"

template <typename T>
class ComponentStorage final : public BaseComponentStorage {
    internal::IWorldInternal& _world;

    std::vector<T> _data;      // Для плотного хранения данных
    std::vector<int> _sparse;  // Для разреженного хранения индексов элементов (сущностей)
    std::vector<int> _dense;   // Для плотного хранения реально существующих элементов (сущностей, на которых есть компоненты)
    
    int _count = 0;            // Текущее число элементов

    int _id;

    void Resize(const int sparseSize, const int dataSize);

public:
    ComponentStorage(internal::IWorldInternal& w, const int id);

    bool Has(const int e) const override;
    T& Get(const int e);
    T& Add(const int e, const T& value);
    void Remove(const int e) override;

    std::span<const T> All() const;
    std::span<const int> Entities() const override;

    int Count() const override;
    int Id() const override;
};

#endif //COMPONENTSTORAGE_H
