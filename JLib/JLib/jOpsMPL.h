// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/24/2017]
// Description : simple operation template meta.
#pragma once

namespace jLib 
{

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

}