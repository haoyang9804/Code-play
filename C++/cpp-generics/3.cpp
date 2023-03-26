#include <tuple>

// The 2nd and 3rd fehs are partial 
// specializations of the 1st feh

template<typename Fn>
inline
void feh(Fn&, const std::tuple<>*)
{}

template<typename Fn, typename H>
inline
void feh(Fn& fn, const std::tuple<H>*)
{
    fn(H{});
}

template<typename  Fn, typename H, typename... R>
inline
void feh(Fn& fn, const std::tuple<H, R...>*)
{
    fn(H{});
    using Rest = const std::tuple<R...>*;
    feh<Fn, R...>(fn, static_cast<Rest>(nullptr));
}