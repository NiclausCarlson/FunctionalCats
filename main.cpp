#include <iostream>
#include "pair.hpp"
#include <string>
#include <limits>
#include <unordered_map>
#include <unordered_set>

namespace cat {
    namespace names {
        std::unordered_map<int32_t, std::string> names_idx{};

        template<typename Func>
        auto Names(Func f) {
            return f(names_idx);
        }

        int32_t RegisterName(std::string name) {
            static int32_t idx = std::numeric_limits<int32_t>::min();
            static std::unordered_map<std::string, int32_t> all_names;
            auto it = all_names.find(name);
            if (it == all_names.end()) {
                Names([&](std::unordered_map<int32_t, std::string> &names) {
                    names[idx] = name;
                });
                all_names[name] = idx;
                return idx++;
            }
            return it->second;
        }

        std::string GetName(const int32_t &name_idx) {
            return Names([&](const std::unordered_map<int32_t, std::string> &names) {
                return names.at(name_idx);
            });
        }
    }

    auto Cat(std::string name, int32_t murlicity) {
        auto idx = names::RegisterName(name);
        return pair::Pair(idx, murlicity);
    }

    auto BornNewCat(std::string name, int32_t murlicity) {
        return Cat(name, murlicity);
    }

    template<typename Cat>
    std::string GetName(const Cat &cat) {
        return names::GetName(cat(0));
    }

    template<typename Cat>
    int32_t GetMurlicity(const Cat &cat) {
        return cat(1);
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
    std::cout << "Fst, Snd ex: " << Fst(p) << ' ' << Snd(p) << std::endl;

    auto curry_test = [](auto pair) {
        return Fst(pair) + Snd(pair);
    };

    std::cout << "Curry ex: " << Curry(curry_test, 3, 4) << std::endl;

    auto uncurry_test = [](int32_t a, int32_t b) {
        return a + b;
    };
    std::cout << "Uncurry ex: " << Uncurry(uncurry_test, Pair(1, 2)) << std::endl;
}

void RegisterNamesTest() {
    std::cout << "-----------RegisterNamesTest-----------" << std::endl << std::endl;

    using namespace cat;
    using namespace cat::names;

    RegisterName("Vaskya");
    RegisterName("Barsik");
    RegisterName("Hey, you");
    RegisterName("Hey, you");
    RegisterName("Cat");

    auto print_names = [](const std::unordered_map<int32_t, std::string> &names) {
        for (const auto &[fst, snd]: names) {
            std::cout << fst << " " << snd << std::endl;
        }
    };
    Names(print_names);
}

void CatsTest() {
    std::cout << "-----------CatsTest-----------" << std::endl << std::endl;

    using namespace cat;
    using namespace cat::names;

    auto cat1 = BornNewCat("Petya", 4);
    auto cat2 = BornNewCat("Barsik", 5);
    auto cat3 = BornNewCat("Hey, you", std::numeric_limits<int32_t>::min());

    auto print_names = [](const std::unordered_map<int32_t, std::string> &names) {
        for (const auto &[fst, snd]: names) {
            std::cout << fst << " " << snd << std::endl;
        }
    };
    Names(print_names);

    std::cout << "Print cat: " <<GetName(cat1) << ' ' << GetMurlicity(cat1) << std::endl;

    auto cat22 = ScratchCat(cat2);
    std::cout << "Not scratched cat: " <<GetName(cat2) << ' ' << GetMurlicity(cat2) << std::endl;
    std::cout << "Scratched cat: " <<GetName(cat22) << ' ' << GetMurlicity(cat22) << std::endl;

    // never pet an angry cat
//    for (auto i = std::numeric_limits<std::int32_t>::min(); i <= 0; ++i) {
//        auto cat33 = ScratchCat(cat3);
//    }
}

int main() {
    PairTest();
    RegisterNamesTest();
    CatsTest();
    return 0;
}
