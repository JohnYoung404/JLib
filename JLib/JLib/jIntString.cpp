#include <iostream>
#include <stdexcept>
#include <boost/assert.hpp>
#include "jIntString.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jNum)

jIntString::jIntString(const std::string initString, const unsigned char initRadix) : radix_(initRadix), mstring_(initString), sign_(true)
{
    if (radix_ > 16 || radix_ < 2) throw std::invalid_argument("Only support index less or equal than 16.");
    auto itr = mstring_.begin();
    if (*itr == '+')
    {
        sign_ = true;
        ++itr;
    }
    else if (*itr == '-')
    {
        sign_ = false;
        ++itr;
    }
    char val = -1;
    for (; itr != mstring_.end(); ++itr)
    {
        if (*itr >= '0' && *itr <= '9')
        {
            val = *itr - '0';
            if (val < 0 || val >= radix_) throw std::invalid_argument("Invalid number string input.");
            numVec_.push_back(val);
        }
        else if (*itr >= 'a' && *itr <= 'f') {
            val = *itr - 'a' + 10;
            if (val < 0 || val >= radix_) throw std::invalid_argument("Invalid number string input.");
            numVec_.push_back(val);
        }
        else throw std::invalid_argument("Invalid number string input.");
    }
    auto tmp = std::move(numVec_);
    numVec_ = std::vector<char>(tmp.rbegin(), tmp.rend());
}

jIntString::jIntString(const std::vector<char>& numVec, bool sign, unsigned char radix)
    : numVec_(numVec)
    , radix_(radix)
    , sign_(sign)
{
    if (radix_ > 16 || radix_ < 2) throw std::invalid_argument("Only support index less or equal than 16.");
    for (const auto & num : numVec)
    {
        if (num < 0 || num >= radix_) throw std::invalid_argument("Invalid number string input.");
    }
    rebuiltString();
}

jIntString::jIntString(const jIntString& rhs)
    : mstring_(rhs.mstring_)
    , numVec_(rhs.numVec_)
    , radix_(rhs.radix_)
    , sign_(rhs.sign_)
{
}

jIntString::jIntString(jIntString && rhs) noexcept
    : radix_(rhs.radix_)
    , sign_(rhs.sign_)
{
    mstring_ = std::move(rhs.mstring_);
    numVec_ = std::move(rhs.numVec_);
}

const jIntString& jIntString::operator=(const jIntString& rhs)
{
    if (this != &rhs) {
        mstring_ = rhs.mstring_;
        numVec_ = rhs.numVec_;
        radix_ = rhs.radix_;
        sign_ = rhs.sign_;
    }
    return *this;
}

const jIntString& jIntString::operator=(jIntString && rhs) noexcept
{
    if (this != &rhs) {
        this->radix_ = rhs.radix_;
        this->sign_ = rhs.sign_;
        this->mstring_ = std::move(rhs.mstring_);
        this->numVec_ = std::move(rhs.numVec_);
    }
    return *this;
}

jIntString& jIntString::changeRadix(const unsigned char toRadix) {
    if (toRadix > radix_) {
        changeRadix(2);
        binaryToHex();
        changeRadix(toRadix);
    }
    else if (toRadix == radix_) {
        return *this;
    }
    else {
        std::vector<char> dividend(numVec_), result;
        int t, i;
        while (dividend.size())
        {
            std::vector<char> quatiant;
            for (t = 0, i = static_cast<int>(dividend.size()) - 1; i >= 0; --i)
            {
                t = t * radix_ + dividend[i];
                quatiant.push_back(t / toRadix);
                t = t % toRadix;
            }
            result.push_back(t);
            std::vector<char> tmp(quatiant.rbegin(), quatiant.rend());
            quatiant = std::move(tmp);
            auto itr = quatiant.end() - 1;
            while (*itr == 0)
            {
                quatiant.erase(itr);
                if (!quatiant.empty())
                    itr = quatiant.end() - 1;
                else
                    break;
            }
            dividend = std::move(quatiant);
        }
        numVec_ = std::move(result);
        radix_ = toRadix;
        rebuiltString();
        return *this;
    }
#ifdef _DEBUG
    BOOST_ASSERT_MSG(true, "Control flow shouldn't reach there.");
#endif 
    return *this;
}

void jIntString::binaryToHex() {
#ifdef _DEBUG
    BOOST_ASSERT_MSG(radix_ == 2, "radix here must be 2.");
#endif
    std::vector<char> retVec;
    while (numVec_.size() >= 4)
    {
        char t = numVec_[0] + numVec_[1] * 2 + numVec_[2] * 4 + numVec_[3] * 8;
        retVec.push_back(t);
        auto itr = numVec_.begin();
        numVec_.erase(itr, itr + 4);
    }
    char t = -1;
    switch (numVec_.size())
    {
    case  1:
        t = numVec_[0];
        break;
    case 2:
        t = numVec_[0] + numVec_[1] * 2;
        break;
    case 3:
        t = numVec_[0] + numVec_[1] * 2 + numVec_[2] * 4;
        break;
    default:
        break;
    }
    if (t >= 0)
    {
        retVec.push_back(t);
    }
    radix_ = 16;
    numVec_ = std::move(retVec);
}

void jIntString::rebuiltString() {
    mstring_.clear();
    auto tmp = std::string(numVec_.rbegin(), numVec_.rend());
    if (sign_ == false) mstring_.push_back('-');
    for (auto i = 0; i < tmp.size(); ++i)
    {
        if (tmp[i] < 10)
            mstring_.push_back(tmp[i] + '0');
        else
            mstring_.push_back(tmp[i] - 10 + 'a');
    }
}

std::ostream& operator << (std::ostream &output, const jIntString &jis)
{
    output << jis.toString() << "(" << static_cast<int>(jis.radix()) << ")";
    return output;
}

NAME_SPACE_END
NAME_SPACE_END