#include <unordered_map>
#include <list>

template <typename T, typename KeyT = int>
class cache_t
{
private:
    std::size_t sz_;
    std::list<T> cache_;
    using ListIt = std::list<int>::iterator;
    std::unordered_map<KeyT, ListIt> hash_;

public:
    cache_t(std::size_t size) : sz_(size) {}

    bool full()
    {
        return (hash_.size() == sz_);
    }
    bool lookup_update(KeyT key)
    {
        auto hit = hash_.find(key);
        if (hit == hash_.end())
        {
            if (full())
            {
                hash_.erase(cache_.back());
                cache_.pop_back();
            }
            cache_.push_front(key);
            hash_[key] = cache_.begin();
            return false;
        }
        auto eltit = hit->second;
        if (eltit != cache_.begin())
        {
            cache_.splice(cache_.begin(), cache_, eltit, std::next(eltit));
        }
        return true;
    }
};

int main(int argc, char const *argv[])
{
    cache_t<int> cache(3);
    cache.lookup_update(13);
    cache.lookup_update(76);
    cache.lookup_update(2);
    cache.lookup_update(9);
    cache.lookup_update(76);
    cache.lookup_update(76);

    return 0;
}
