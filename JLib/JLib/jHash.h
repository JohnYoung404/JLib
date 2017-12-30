#pragma once
#include <string>
#include <tuple>
#include <boost/functional/hash.hpp>
#include <boost/type_traits.hpp>
#include <type_traits>
#include "jMPL.h"
#include "jTestBase.h"
#include <unordered_map>

namespace std
{
    template<typename... Args>
    struct hash<tuple<Args...> >
    {
        inline size_t operator()(const tuple<Args...>& t) const {
            size_t seed = 0;
            tuple_for_each(t, [&seed] (auto & e) {
                size_t std_hash = hash<boost::remove_cv_ref_t<decltype(e)> >{}(e);
                boost::hash_combine(seed, std_hash);
            });
            return seed;
        }
    };
}

namespace jLib {
    class jHashTest final : public jITestable {
    public:
        virtual void test() override {
            jITestable::test();
            
            auto t = std::make_tuple(1, 2, "hello,");
            auto f = std::make_tuple(t, "tuple of tuple");

            std::unordered_map<decltype(t), std::string> umap;
            std::unordered_map<decltype(f), std::string> umap_1;

            umap.emplace(t, "hello,");
            umap.emplace(std::make_tuple(3, 4, "world."), "world.");
            umap_1.emplace(f, "Ahoy~");

            std::cout << umap[t] << umap[std::make_tuple(3, 4, "world.")] << std::endl;
            std::cout << umap_1[f] << std::endl;
        }
    };
}
