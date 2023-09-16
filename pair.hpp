#pragma once

#include <functional>
#include <cassert>

namespace pair {

    auto Pair(int32_t fst, int32_t snd) {
        auto dispatcher = [=](const std::size_t &idx) {
            assert(idx < 2);
            if (idx == 0) return fst;
            return snd;
        };
        return dispatcher;
    }

    template<typename Pair>
    int32_t Fst(Pair p) {
        return p(0);
    }

    template<typename Pair>
    int32_t Snd(Pair p) {
        return p(1);
    }

    template<typename F>
    auto Curry(F f, int32_t fst, int32_t snd) {
        return f(Pair(fst, snd));
    }

    template<typename F, typename Pair>
    auto Uncurry(F f, Pair pair) {
        return f(Fst(pair), Snd(pair));
    }
}
