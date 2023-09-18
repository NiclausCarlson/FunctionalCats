#include <iostream>
#include "pair.hpp"
#include <string>
#include <limits>

namespace cat {
    auto Cat(std::string name, int32_t murlicity) {
        return pair::Pair(name, murlicity);
    }

    auto BornNewCat(std::string name, int32_t murlicity) {
        return Cat(name, murlicity);
    }

    template<typename Cat>
    std::string GetName(const Cat &cat) {
        return pair::Fst<std::string>(cat);
    }

    template<typename Cat>
    int32_t GetMurlicity(const Cat &cat) {
        return pair::Snd<int32_t>(cat);
    }

    template<typename Cat>
    auto ScratchCat(const Cat &cat) {
        return BornNewCat(GetName(cat), GetMurlicity(cat) + 1);
    }
}

void PairTest() {
    std::cout << "-----------PairTest-----------" << std::endl << std::endl;
    using namespace pair;
    auto p = Pair(1, 2);
    std::cout << "Fst, Snd ex: " << Fst<int32_t>(p) << ' ' << Snd<int32_t>(p) << std::endl;

    auto curry_test = [](auto pair) {
        return Fst<int32_t>(pair) + Snd<int32_t>(pair);
    };

    std::cout << "Curry ex: " << Curry(curry_test, 3, 4) << std::endl;

    auto uncurry_test = [](int32_t a, int32_t b) {
        return a + b;
    };
    std::cout << "Uncurry ex: " << Uncurry<int32_t, int32_t>(uncurry_test, Pair(1, 2)) << std::endl;

    auto arg_1 = "bla";
    auto arg_2 = 3.14;
    using U = decltype(arg_1);
    using V = decltype(arg_2);

    auto pp = Pair(arg_1, arg_2);
    std::cout << "Fst, Snd ex: " << Fst<U>(pp) << ' ' << Snd<V>(pp) << std::endl;

    auto auto_ = [](auto pair) {
        return Fst<U>(pair) + std::to_string(Snd<V>(pair));
    };
    std::cout << "Curry ex: " << Curry(auto_, "bla", 4.567) << std::endl;

    auto auto__ = [](auto a, auto b) {
        return std::to_string(b);
    };
    std::cout << "Uncurry ex: " << Uncurry<U, V>(auto__, Pair("bla", 2)) << std::endl;

}

void CatsTest() {
    std::cout << "-----------CatsTest-----------" << std::endl << std::endl;

    using namespace cat;

    auto cat1 = BornNewCat("Petya", 4);
    auto cat2 = BornNewCat("Barsik", 5);
    auto cat3 = BornNewCat("Hey, you", std::numeric_limits<int32_t>::min());

    std::cout << "Print cat: " << GetName(cat1) << ' ' << GetMurlicity(cat1) << std::endl;

    auto cat22 = ScratchCat(cat2);
    std::cout << "Not scratched cat: " << GetName(cat2) << ' ' << GetMurlicity(cat2) << std::endl;
    std::cout << "Scratched cat: " << GetName(cat22) << ' ' << GetMurlicity(cat22) << std::endl;

    // never pet an angry cat
//    for (auto i = std::numeric_limits<std::int32_t>::min(); i <= 0; ++i) {
//        auto cat33 = ScratchCat(cat3);
//    }
}

int main() {
    PairTest();
    CatsTest();
    return 0;
}
