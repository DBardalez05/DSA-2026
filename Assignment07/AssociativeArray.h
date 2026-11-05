#pragma once

#include <cstddef>
#include <functional>
#include <optional>
#include <utility>
#include <vector>

template <typename K, typename V>
class AssociativeArray {
private:
    // This associative array is basically a vector or vecotrs that contains pairs
    // THe outer vector are he buckets and the inner vector contains what is in the bucket
    std::vector<std::vector<std::pair<K, V>>> buckets;
    std::size_t entryCount = 0;
    

    std::size_t bucketIndex(const K& key){
        // Here we take in a key value and compute a hashnumber for it so that it knows what bucket to keep it in
        std::hash<K> hasher;
        std::size_t hashNumber = hasher(key);
        return hashNumber % buckets.size();
    }

    void rehash(){
        // We call this function whenever there are more entries than hashmap slots to prevent too much clumping in one bucket
        std::size_t newBucketCount = buckets.size() * 2 + 1;
        // Make new array with new size
        std::vector<std::vector<std::pair<K, V>>> newBuckets(newBucketCount);
        std::hash<K> hasher;
        // For every entry in the old hashmap we give it a new hash value and put them in new bins if they change
        for (const auto& bucket : buckets){
            for (const auto& entry : bucket){
                std::size_t newIndex = hasher(entry.first) % newBucketCount;
                newBuckets[newIndex].push_back(entry);
            }
        }
        // Bucketsis now newBuckets
        buckets.swap(newBuckets);
    }

public:
    // If no size is given we will simply have a iniital size be 5
    explicit AssociativeArray(std::size_t bucketCount = 5){
        if (bucketCount == 0){
            bucketCount = 5;
        }
        buckets.resize(bucketCount);
    }

    void set(const K& key, const V& value){
        auto& bucket = buckets[bucketIndex(key)];
        // Given the key we look within the bucket it should be in to change value
        for (auto& entry : bucket) {
            // Go trough all entries in the bucket and if it is there we change its value
            if (entry.first == key){
                entry.second = value;
                return;
            }
        }
        // If the key was not found in the bucket then we must add it as a new entry
        bucket.push_back({key, value});
        entryCount++;
        // Call th erehash function if more entries in hashmap compared to number of buckets
        if(entryCount > buckets.size()){
            rehash();
        }
    }

    std::optional<V> get(const K& key){
        const auto& bucket = buckets[bucketIndex(key)];
        // Given key go through all entries in that bucket and get value for that key
        for (const auto& entry : bucket){
            if (entry.first == key){
                return entry.second;
            }
        }
        return std::nullopt;
        // Only if key is not found return nothing
    }

    std::size_t size() const{
        return entryCount;
    }

    bool contains(const K& key){
        return get(key).has_value();
    }

    bool remove(const K& key){
        auto& bucket = buckets[bucketIndex(key)];
        // Find key within one of the buckets and if found will delete the entry
        for(std::size_t i = 0; i < bucket.size(); i++){
            if(bucket[i].first == key){
                bucket.erase(bucket.begin() + i);
                entryCount--;
                return true;
            }
        }
        return false;
    }

    std::vector<std::pair<K, V>> keyValuePairs() const{
        // Will return one vector that simply writes out all of the pairs in order
        std::vector<std::pair<K, V>> result;
        // Start at the first bucket then add all entrire within it then repeat for all later bucket
        for(const auto& bucket : buckets){
            for(const auto& entry : bucket){
                result.push_back(entry);
            }
        }
        return result;
    }

};