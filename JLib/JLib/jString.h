#pragma once
#include <vector>
#include <string>
#include <stack>


//////////////////////////////////////////////////////////////////////////
// Discarded, it's dumb to inherit from std::string. 
//////////////////////////////////////////////////////////////////////////
namespace jLib {
	enum metaType { VALUE, OPERATOR };
	enum operatorType { PLUS, MINUS, MULTIPLY, DIVIDE, POWER, LEFT_BRACKET, RIGHT_BRACKET };
	struct expMeta {
		metaType type;
		union
		{
			double value;
			operatorType op;
		};
	};

	class jStringList : public std::vector<std::string> {
	public:
		jStringList() {}
		jStringList(std::vector<std::string> ls) {
			this->assign(ls.begin(), ls.end());
		}

	public:
		std::string join(std::string);
	};

	std::string jStringList::join(std::string joiner) {
		std::string ret;
		std::vector<std::string>::iterator itr;
		for (itr = this->begin(); itr != this->end(); ++itr)
		{
			ret.append(*itr);
			if (itr != this->end() - 1)
			{
				ret.append(joiner);
			}
		}
		return ret;
	}

	class jString : public std::string {
	public:
		jString() {}
		jString(std::string s) {
			this->append(s.begin(), s.end());
		}

	public:
		jString reverse();
		jString removeBlank();
		std::string toString();
		jStringList split(char seperator);
		std::vector<size_t> KMP_match(std::string P);
		double calExpVal(std::string exp);

	private:
		std::vector<size_t> prefixFunc;
		void computePrefixFunc(std::string P);
		std::vector<expMeta> calculateReversePolish(std::string exp);
		double calculateValueFromReversePolish(std::vector<expMeta> reversePolish);
	};

	jString jString::reverse() {
		std::string tmp(*this);
		this->clear();
		this->append(tmp.rbegin(), tmp.rend());
		return *this;
	};

	jString jString::removeBlank() {
		jString::iterator itr = this->begin();
		while (itr != this->end())
		{
			if ((*itr) == ' ' || (*itr) == '\n' || (*itr) == '\t') {
				itr = this->erase(itr);
				continue;
			}
			++itr;
		}
		return *this;
	};

	std::string jString::toString() {
		return static_cast<std::string> (*this);
	}

	jStringList jString::split(char seperator) {
		std::string tmp(*this);
		std::string::iterator beg = tmp.begin();
		std::string::iterator end = beg;
		std::vector<std::string> ret;
		std::string segment;
		while (true)
		{
			if (end == tmp.end())
			{
				if (segment.size() > 0)
				{
					ret.push_back(segment);
				}
				break;
			}
			else if ((*end) == seperator)
			{
				end++;
				beg = end;
				if (segment.size() > 0)
				{
					ret.push_back(segment);
					segment.clear();
				}
				continue;
			}
			else {
				segment.push_back(*end);
				end++;
			}
		}
		return jStringList(ret);
	}

	void jString::computePrefixFunc(std::string P) {
		size_t k = 0;
		prefixFunc.resize(P.size());
		prefixFunc[0] = 0;
		for (size_t q = 1; q < P.size(); ++q)
		{
			while (k > 0 && P[k] != P[q])
			{
				k = prefixFunc[k - 1];
			}
			if (P[k] == P[q])
			{
				k = k + 1;
			}
			prefixFunc[q] = k;
		}
	}

	std::vector<size_t> jString::KMP_match(std::string P) {
		size_t n = this->size();
		size_t m = P.size();
		prefixFunc.clear();
		computePrefixFunc(P);
		size_t q = 0;
		std::vector<size_t> ret;
		for (size_t i = 0; i < n; ++i)
		{
			while (q > 0 && P[q] != (*this)[i])
			{
				q = prefixFunc[q - 1];
			}
			if (P[q] == (*this)[i])
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

	double jString::calExpVal(std::string exp) {
		return calculateValueFromReversePolish(calculateReversePolish(exp));
	}

	int priorityOfOps(operatorType op) {
		if (op == MINUS || op == PLUS)
		{
			return 0;
		}
		else if (op == MULTIPLY || op == DIVIDE) {
			return 1;
		}
		else if (op == POWER)
		{
			return 2;
		}
		else if (op == RIGHT_BRACKET) {
			return -1;
		}
		else {
			return 3;
		}
	}

	std::vector<expMeta> jString::calculateReversePolish(std::string exp) {
		jString js(exp);
		exp = js.removeBlank().toString();
		std::string::iterator itr = exp.begin();
		std::stack<operatorType> theStack;
		std::string valString;
		std::vector<expMeta> ret;
		for (; itr != exp.end(); ++itr)
		{
			if (*itr != '+' && *itr != '-' && *itr != '*' && *itr != '/' && *itr != '(' && *itr != ')' && *itr != '^')
			{
				valString.push_back(*itr);
				continue;
			}
			else {
				expMeta toInsert;
				if (!valString.empty())
				{
					double val = atof(valString.c_str());
					valString.clear();
					toInsert.type = VALUE;
					toInsert.value = val;
					ret.push_back(toInsert);
				}
				operatorType toPush;
				switch (*itr)
				{
				case '+':
					toPush = PLUS;
					break;
				case '-':
					toPush = MINUS;
					break;
				case '*':
					toPush = MULTIPLY;
					break;
				case '/':
					toPush = DIVIDE;
					break;
				case '^':
					toPush = POWER;
					break;
				case '(':
					toPush = LEFT_BRACKET;
					break;
				case ')':
					toPush = RIGHT_BRACKET;
					break;
				default:
					break;
				}
				if (toPush != POWER)
				{
					while (!theStack.empty() && priorityOfOps(theStack.top()) >= priorityOfOps(toPush))
					{
						if (theStack.top() != LEFT_BRACKET) {
							toInsert.type = OPERATOR;
							toInsert.op = theStack.top();
							ret.push_back(toInsert);
							theStack.pop();
							continue;
						}
						if (theStack.top() == LEFT_BRACKET && toPush == RIGHT_BRACKET)
						{
							theStack.pop();
							break;
						}
						else if (theStack.top() == LEFT_BRACKET && toPush != RIGHT_BRACKET)
						{
							break;
						}
					}
					if (toPush != RIGHT_BRACKET)
					{
						theStack.push(toPush);
					}
				}
				else {
					while (!theStack.empty() && priorityOfOps(theStack.top()) > priorityOfOps(toPush))
					{
						if (theStack.top() != LEFT_BRACKET) {
							toInsert.type = OPERATOR;
							toInsert.op = theStack.top();
							ret.push_back(toInsert);
							theStack.pop();
							continue;
						}
						if (theStack.top() == LEFT_BRACKET && toPush == RIGHT_BRACKET)
						{
							theStack.pop();
							break;
						}
						else if (theStack.top() == LEFT_BRACKET && toPush != RIGHT_BRACKET)
						{
							break;
						}
					}
					theStack.push(toPush);
				}
			}
		}
		expMeta toInsert;
		if (!valString.empty())
		{
			double val = atof(valString.c_str());
			valString.clear();
			toInsert.type = VALUE;
			toInsert.value = val;
			ret.push_back(toInsert);
		}

		while (!theStack.empty())
		{
			toInsert.type = OPERATOR;
			toInsert.op = theStack.top();
			ret.push_back(toInsert);
			theStack.pop();
		}
		return ret;
	}

	double jString::calculateValueFromReversePolish(std::vector<expMeta> reversePolish) {
		std::stack<double> theStack;
		std::vector<expMeta>::iterator itr = reversePolish.begin();
		for (; itr != reversePolish.end(); ++itr)
		{
			if (itr->type == VALUE)
			{
				theStack.push(itr->value);
				continue;
			}
			else if (itr->type == OPERATOR)
			{
				double val2 = theStack.top();
				theStack.pop();
				double val1 = theStack.top();
				theStack.pop();
				double val3;
				switch (itr->op)
				{
				case PLUS:
					val3 = val1 + val2;
					break;
				case MINUS:
					val3 = val1 - val2;
					break;
				case MULTIPLY:
					val3 = val1 * val2;
					break;
				case DIVIDE:
					val3 = val1 / val2;
					break;
				case POWER:
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
