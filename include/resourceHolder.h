#ifndef RESOURCEHOLDER_H_INCLUDED
#define RESOURCEHOLDER_H_INCLUDED

#include <string>
#include <map>
#include <memory>

template<typename Resource, typename Identifier>
class ResourceHolder
{
    public:
        void load(Identifier ID, const std::string filename);
        Resource& get(Identifier ID);

    private:
        std::map<Identifier, std::unique_ptr<Resource>> mResources;
};

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier ID, const std::string filename)
{
    std::unique_ptr<Resource> res(new Resource());
    res->loadFromFile(filename);
    mResources.insert(std::make_pair(ID, std::move(res)));
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier ID)
{
    auto found = mResources.find(ID);
    return *found->second;
}

#endif // RESOURCEHOLDER_H_INCLUDED
