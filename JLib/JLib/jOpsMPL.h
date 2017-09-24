#pragma once

template <int X, int Y>
struct _plus {
    enum {
        value = X + Y
    };
};

template <int X, int Y>
struct _minus {
    enum {
        value = X - Y
    };
};

template <int X, int Y>
struct _mult {
    enum {
        value = X * Y
    };
};

template <int X, int Y>
struct _div {
    enum {
        value = X / Y
    };
};

template <int X, int Y>
struct _mod {
    enum {
        value = X % Y
    };
};