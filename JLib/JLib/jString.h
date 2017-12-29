#pragma once
#include <vector>
#include <string>
#include <stack>


//////////////////////////////////////////////////////////////////////////
// Discarded, it's numb to inherit from std::string. 
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

	class jString : public std::string {
	public:
		jString() {}
		jString(std::string s) {
			this->append(s.begin(), s.end());
		}

	public:
		double calExpVal(std::string exp);

	private:
		std::vector<expMeta> calculateReversePolish(std::string exp);
		double calculateValueFromReversePolish(std::vector<expMeta> reversePolish);
	};

	

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
