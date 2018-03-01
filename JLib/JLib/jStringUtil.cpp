#include <stack>
#include <cmath>
#include <cctype>
#include <algorithm>

#include "jStringUtil.h"
#include "jRange.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jStringUtil)

const std::vector<size_t> findAll(const std::string& Whole, const std::string& part)
{
    std::vector<size_t> ret;
    std::size_t found = Whole.find(part, 0);
    while (found != std::string::npos)
    {
        ret.push_back(found);
        found = Whole.find(part, found + 1);
    }
    return ret;
}

const size_t count(const std::string& Whole, const std::string& part) {
    return findAll(Whole, part).size();
}

const std::string escape(const std::string& prime) {
    std::string ret;
    for (auto orig_elem : prime)
    {
        unsigned char elem = (unsigned char)orig_elem;
        if (std::isdigit(elem) || std::islower(elem) || std::isupper(elem))
            ret.push_back(elem);
        else if (elem < 256) {
            ret.push_back('%');
            if (elem < 16)	ret.push_back('0');
            char buffer[4];
            _itoa_s(elem, buffer, 16);
            std::string toAppend = buffer;
            ret.append(toAppend);
        }
    }
    return ret;
}

const std::string trim(const std::string& prime) {
    std::string ret;
    auto itr_head = prime.begin();
    auto itr_end = prime.end();
    while ((itr_head != prime.end())) {
        if (!std::isspace((unsigned char)*itr_head))
            break;
        ++itr_head;
    }
    while ((itr_end != prime.begin())) {
        --itr_end;
        if (!std::isspace((unsigned char)*itr_end))
            break;
    }
    if (itr_head < itr_end)
        ret = std::string(itr_head, ++itr_end);
    return ret;
}

const std::string reverse(const std::string& prime)
{
    return std::string(prime.rbegin(), prime.rend());
}

const std::string toLower(const std::string& prime) {
    std::string ret;
    std::for_each(prime.begin(), prime.end(), [&ret](auto chr) {
        ret.push_back(tolower(chr));
    });
    return ret;
}

const std::string toUpper(const std::string& prime) {
    std::string ret;
    std::for_each(prime.begin(), prime.end(), [&ret](auto chr) {
        ret.push_back(toupper(chr));
    });
    return ret;
}

const std::string head(const std::string& prime, size_t num)
{
    return (num >= prime.size()) ? prime : std::string(prime.begin(), prime.begin() + num);
}

const std::string tail(const std::string& prime, size_t num)
{
    return (num >= prime.size()) ? prime : std::string(prime.begin() + prime.size() - num, prime.end());
}

const std::vector<std::string> split(const std::string& prime, const std::string& sep) {
    std::vector<std::string> ret;
    std::string sepString;

    if (sep.size() == 0) {
        for (auto chr : prime)
        {
            std::string tmp;
            tmp.insert(tmp.begin(), chr);
            ret.push_back(std::move(tmp));
        }
        return ret;
    }

    auto& sep_pos_vec = findAll(prime, sep);
    jRange<size_t> r;
    for (auto pos : sep_pos_vec)
    {
        r.addRange(pos, pos + sep.size() - 1);
    }

    for (size_t i = 0; i < prime.size(); ++i)
    {
        if (!r.contains(i)) {
            sepString.push_back(prime[i]);
        }
        else {
            if (sepString.size()) {
                ret.push_back(std::move(sepString));
                sepString.clear();
            }
        }
    }
    if (sepString.size()) {
        ret.push_back(std::move(sepString));
        sepString.clear();
    }
    return ret;
}

const std::string join(const std::vector<std::string> &strVec, const std::string& joiner) {
    std::string ret;
    for (auto& str : strVec) {
        if (str.size()) {
            ret.append(str);
            ret.append(joiner);
        }
    }
    if (ret.size())
    {
        for (auto i = 0; i < joiner.size(); ++i)
        {
            ret.pop_back();
        }
    }
    return ret;
}

const std::string replace(const std::string & prime, const std::string& oldSub, const std::string & newSub)
{
    std::string ret = prime;
    std::size_t found = ret.find(oldSub, 0);
    while (found != std::string::npos)
    {
        ret.replace(found, oldSub.size(), newSub);
        found = ret.find(oldSub, found + newSub.size());
    }
    return ret;
}

const bool constains(const std::string& Whole, const std::string& part) {
    std::size_t found = Whole.find(part, 0);
    return found != std::string::npos;
}

const bool endsWith(const std::string& Whole, const std::string& part) {
    auto itrWhole = Whole.rbegin();
    auto itrPart = part.rbegin();
    while (itrPart != part.rend())
    {
        if (itrWhole == Whole.rend())
        {
            return false;
        }
        if (*itrWhole != *itrPart)
        {
            return false;
        }
        ++itrWhole, ++itrPart;
    }
    return true;
}

const bool startsWith(const std::string& Whole, const std::string& part) {
    auto itrWhole = Whole.begin();
    auto itrPart = part.begin();
    while (itrPart != part.end())
    {
        if (itrWhole == Whole.end())
        {
            return false;
        }
        if (*itrWhole != *itrPart)
        {
            return false;
        }
        ++itrWhole, ++itrPart;
    }
    return true;
}

namespace
{
    const std::vector<size_t> _PrefixFunc(const std::string & inputStr)
    {
        size_t k = 0;
        std::vector<size_t> ret;
        ret.resize(inputStr.size());
        ret[0] = 0;
        for (size_t q = 1; q < inputStr.size(); ++q)
        {
            while (k > 0 && inputStr[k] != inputStr[q])
            {
                k = ret[k - 1];
            }
            if (inputStr[k] == inputStr[q])
            {
                k = k + 1;
            }
            ret[q] = k;
        }
        return ret;
    }
}

const std::vector<size_t> KMP_match(const std::string& Whole, const std::string &part) {
    size_t n = Whole.size();
    size_t m = part.size();
    auto & prefixFunc = _PrefixFunc(part);
    size_t q = 0;
    std::vector<size_t> ret;
    for (size_t i = 0; i < n; ++i)
    {
        while (q > 0 && part[q] != Whole[i])
        {
            q = prefixFunc[q - 1];
        }
        if (part[q] == Whole[i])
        {
            q = q + 1;
        }
        if (q == m)
        {
            ret.push_back(i - m + 1);
            q = prefixFunc[q - 1];
        }
    }
    return ret;
}

namespace {
    enum class ElemType { VALUE, OPERATOR };
    enum class OperatorType { PLUS, MINUS, MULTIPLY, DIVIDE, POWER, LEFT_BRACKET, RIGHT_BRACKET };
    struct ExpressionElem {
        ElemType type;
        union
        {
            double value;
            OperatorType op;
        };
    };

    int priorityOfOps(OperatorType op)
    {
        switch (op)
        {
        case OperatorType::PLUS:
        case OperatorType::MINUS:
        {
            return 0;
        }
        case OperatorType::MULTIPLY:
        case OperatorType::DIVIDE:
        {
            return 1;
        }
        case OperatorType::POWER:
        {
            return 2;
        }
        case OperatorType::RIGHT_BRACKET:
        {
            return -1;
        }
        default:
            return 3;
        }
    }

    const std::vector<ExpressionElem> _ReversePolish(const std::string exp)
    {
        std::string blankRemoved = replace(exp, "\t", "");
        blankRemoved = replace(exp, "\n", "");
        blankRemoved = replace(exp, " ", "");

        auto itr = blankRemoved.begin();
        std::stack<OperatorType> theStack;
        std::string valString;
        std::vector<ExpressionElem> ret;
        for (; itr != blankRemoved.end(); ++itr)
        {
            if (*itr != '+' && *itr != '-' && *itr != '*' && *itr != '/' && *itr != '(' && *itr != ')' && *itr != '^')
            {
                valString.push_back(*itr);
                continue;
            }
            else {
                ExpressionElem toInsert;
                if (!valString.empty())
                {
                    double val = std::atof(valString.c_str());
                    valString.clear();
                    toInsert.type = ElemType::VALUE;
                    toInsert.value = val;
                    ret.push_back(toInsert);
                }
                OperatorType toPush;
                switch (*itr)
                {
                case '+':
                    toPush = OperatorType::PLUS;
                    break;
                case '-':
                    toPush = OperatorType::MINUS;
                    break;
                case '*':
                    toPush = OperatorType::MULTIPLY;
                    break;
                case '/':
                    toPush = OperatorType::DIVIDE;
                    break;
                case '^':
                    toPush = OperatorType::POWER;
                    break;
                case '(':
                    toPush = OperatorType::LEFT_BRACKET;
                    break;
                case ')':
                    toPush = OperatorType::RIGHT_BRACKET;
                    break;
                default:
                    break;
                }
                if (toPush != OperatorType::POWER)
                {
                    while (!theStack.empty() && priorityOfOps(theStack.top()) >= priorityOfOps(toPush))
                    {
                        if (theStack.top() != OperatorType::LEFT_BRACKET) {
                            toInsert.type = ElemType::OPERATOR;
                            toInsert.op = theStack.top();
                            ret.push_back(toInsert);
                            theStack.pop();
                            continue;
                        }
                        if (theStack.top() == OperatorType::LEFT_BRACKET && toPush == OperatorType::RIGHT_BRACKET)
                        {
                            theStack.pop();
                            break;
                        }
                        else if (theStack.top() == OperatorType::LEFT_BRACKET && toPush != OperatorType::RIGHT_BRACKET)
                        {
                            break;
                        }
                    }
                    if (toPush != OperatorType::RIGHT_BRACKET)
                    {
                        theStack.push(toPush);
                    }
                }
                else {
                    while (!theStack.empty() && priorityOfOps(theStack.top()) > priorityOfOps(toPush))
                    {
                        if (theStack.top() != OperatorType::LEFT_BRACKET) {
                            toInsert.type = ElemType::OPERATOR;
                            toInsert.op = theStack.top();
                            ret.push_back(toInsert);
                            theStack.pop();
                            continue;
                        }
                        if (theStack.top() == OperatorType::LEFT_BRACKET && toPush == OperatorType::RIGHT_BRACKET)
                        {
                            theStack.pop();
                            break;
                        }
                        else if (theStack.top() == OperatorType::LEFT_BRACKET && toPush != OperatorType::RIGHT_BRACKET)
                        {
                            break;
                        }
                    }
                    theStack.push(toPush);
                }
            }
        }
        ExpressionElem toInsert;
        if (!valString.empty())
        {
            double val = atof(valString.c_str());
            valString.clear();
            toInsert.type = ElemType::VALUE;
            toInsert.value = val;
            ret.push_back(toInsert);
        }

        while (!theStack.empty())
        {
            toInsert.type = ElemType::OPERATOR;
            toInsert.op = theStack.top();
            ret.push_back(toInsert);
            theStack.pop();
        }
        return ret;
    }

    double _CalculateValueOf_RP(const std::vector<ExpressionElem> &reversePolish)
    {
        std::stack<double> theStack;
        auto itr = reversePolish.begin();
        for (; itr != reversePolish.end(); ++itr)
        {
            if (itr->type == ElemType::VALUE)
            {
                theStack.push(itr->value);
                continue;
            }
            else if (itr->type == ElemType::OPERATOR)
            {
                double val2 = theStack.top();
                theStack.pop();
                double val1 = theStack.top();
                theStack.pop();
                double val3;
                switch (itr->op)
                {
                case OperatorType::PLUS:
                    val3 = val1 + val2;
                    break;
                case OperatorType::MINUS:
                    val3 = val1 - val2;
                    break;
                case OperatorType::MULTIPLY:
                    val3 = val1 * val2;
                    break;
                case OperatorType::DIVIDE:
                    val3 = val1 / val2;
                    break;
                case OperatorType::POWER:
                    val3 = pow(val1, val2);
                    break;
                default:
                    break;
                }
                theStack.push(val3);
            }
        }
        return theStack.top();
    }
}

const double calExpressionValue(const std::string& expression)
{
    return _CalculateValueOf_RP(_ReversePolish(expression));
}

NAME_SPACE_END
NAME_SPACE_END
