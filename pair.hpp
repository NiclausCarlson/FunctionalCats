#pragma once

#include <functional>
#include <cassert>

namespace pair {

    template<typename U, typename V>
    auto Pair(U fst, V snd) {
        return [=](const auto& outer_dispatcher) {
            return outer_dispatcher(fst, snd);
        };
    }

    template<typename U, typename Pair>
    U Fst(const Pair &p) {
        return p([](const auto &fst, const auto &snd) { return fst; });
    }

    template<typename V, typename Pair>
    V Snd(const Pair &p) {
        return p([](const auto &fst, const auto &snd) { return snd; });
    }

    template<typename U, typename V, typename F>
    auto Curry(F f, U fst, V snd) {
        return f(Pair(fst, snd));
    }

    template<typename U, typename V, typename Pair, typename F>
    auto Uncurry(F f, Pair pair) {
        return f(Fst<U>(pair), Snd<V>(pair));
    }
}
