template <template <typename> class m>
struct Monad {
    template <typename a>
    static m<a> mreturn(const a&);
    
    template <typename a, typename b>
    static m<b> mbind(const m<a>&, m<b>(*)(const a&));
};

template <typename a>
struct Maybe {
    bool isNothing;
    a value;
};

template <>
struct Monad<Maybe> {
    template <typename a>
    static Maybe<a> mreturn(const a& v) {
        Maybe<a> x;
        x.isNothing = false;
        x.value = v;
        return x;
    }
    
    template <typename a, typename b>
    static Maybe<b> mbind(const Maybe<a>& action, Maybe<b>(*function)(const a&)) {
        if (action.isNothing)
            return Maybe<b>{true, b{}};
        else
            return function(action.value);
    }
};