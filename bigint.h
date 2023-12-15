#ifndef BIGINT_H_INCLUDED
#define BIGINT_H_INCLUDED

#include<bits/stdc++.h>
using namespace std;

class bigint
{
    private:

        // DATA MEMBERS
        string num = "0";
        bool isNegative = false;


        // VALIDITY CHECK
        bool isDigit(char ch)
        {
            return '0' <= ch && ch <= '9';
        }

        bool isValid(string num)
        {
            switch (num[0])
            {
                case '+':
                    break;

                case '-':
                    break;
                
                default:
                    if(!isDigit(num[0]))
                    {
                        return false;
                    }
            }

            int i=1;

            while(i<(int)num.size())
            {
                if(!isDigit(num[i]))
                {
                    return false;
                }

                i++;
            }

            return true;
        }


        // CONVERSION
        bigint convert(string num)
        {
            bigint b;
            b.isNegative = (num[0] == '-');

            int i = num[0] == '-' || num[0] == '+';

            while(i < (int)num.size() && num[i] == '0')
            {
                i++;
            }

            b.num = num.substr(i);

            if(b.num == "")
            {
                b.num += '0';
                b.isNegative = false;
            }

            return b;
        }

        
        // HELPER FUNCTIONS
        string divideBy2(bigint x)
        {
            int current = 0;
            string res = "";

            for(int i=0;i<(int)x.num.size();i++)
            {
                current = current * 10 + (x.num[i] - '0');

                if(current < 2)
                {
                    if(i > 0)
                    {
                        res += '0';
                    }
                }
                else
                {
                    res += ((current/2) + '0');
                    current = current % 2;
                }
            }

            if((int)res.size() == 0)
            {
                res = "0";
            }            

            return res;
        }

        string add(const string &a, const string &b)
        {
            string res = "";
            int length1 = a.length();
            int length2 = b.length();
            int carry = 0;

            while(length1 > 0 || length2 > 0 || carry > 0)
            {
                int currentDigit1 = (length1 > 0) ? a[length1 - 1] - '0' : 0;
                int currentDigit2 = (length2 > 0) ? b[length2 - 1] - '0' : 0;

                int currentDigit = currentDigit1 + currentDigit2 + carry;

                carry = currentDigit/10;
                currentDigit = currentDigit%10;

                res += (char)(currentDigit + '0');

                length1--;
                length2--;
            }

            reverse(res.begin(), res.end());

            return res;
        }

        string subtract(string a, string b)
        {
            if(a.length() < b.length() || (a.length() == b.length() and a < b))
            {
                return '-' + subtract(b, a);
            }

            string res = "";

            int length1 = a.length();
            int length2 = b.length();

            while(length1 > 0 || length2 > 0)
            {
                int currentDigit1 = a[length1 - 1] - '0';
                int currentDigit2 = (length2 > 0) ? b[length2 - 1] - '0' : 0;

                if(currentDigit2 > currentDigit1)
                {
                    int i = length1 - 2;

                    while(i >= 0 && a[i] == '0')
                    {
                        a[i] = '9';
                        i--;
                    }

                    if(i >= 0)
                    {
                        a[i]--;
                    }

                    currentDigit1+=10;
                }

                int currentDigit = currentDigit1 - currentDigit2;
                res += (char)(currentDigit + '0');

                length1--;
                length2--;
            }

            reverse(res.begin(), res.end());
            return res;
        }

        string multiply(const string &a, const string &b)
        {
            if(a.length() > b.length())
            {
                return multiply(b, a);
            }

            string res = "0";

            for(int i=a.length()-1;i>=0;i--)
            {
                string temp = b;
                int currentDigit = a[i] - '0';
                int carry = 0;

                for(int j=temp.length()-1;j>=0;j--)
                {
                    temp[j] = ((temp[j]-'0') * currentDigit) + carry;

                    if(temp[j] > 9)
                    {
                        carry = (temp[j]/10);
                        temp[j] -= (carry*10);
                    }
                    else
                    {
                        carry = 0;
                    }

                    temp[j] += '0';
                }

                if(carry > 0)
                {
                    temp.insert(0, 1, (carry + '0'));
                }

                temp.append(a.length()-i-1, '0');

                res = add(res, temp);
            }

            while(res[0] == '0' && res.length()!=1)
            {
                res.erase(0, 1);
            }

            return res;
        }

        string divide(const string &a, const string &b)
        {
            if(b == "1")
            {
                return a;
            }

            bigint l = (bigint)0;
            bigint r = (bigint)(a);
            bigint one = (bigint)1;

            while(r - l > one)
            {
                bigint mid = divideBy2(l + r);

                if(mid * b <= bigint(a))
                {
                    l = mid;
                }
                else
                {
                    r = mid;
                }
            }

            return l.num;
        }

        string modulo(const string &a, const string &b)
        {
            bigint a_ = (bigint)a;
            bigint b_ = (bigint)b;

            return (a_ - ((a_ / b_) * b_)).num;
        }

    public:

        // CONSTRUCTORS
        bigint()
        {
            this->num = "";
            this->isNegative = false;
        }

        bigint(string num)
        {
            assert(isValid(num));

            *this = convert(num);
        }

        bigint(int num)
        {
            *this = convert(to_string(num));
        }


        // INPUT/OUTPUT OPERATOR OVERLOADING
        // friend function used because of two classes
        friend istream &operator>>(istream &input, bigint &b)
        {
            string s;
            input >> s;
            assert(b.isValid(s));
            b = b.convert(s);
            return input;
        }

        friend ostream &operator<<(ostream &output, const bigint &b)
        {
            if(b.isNegative)
            {
                output << "-" << b.num;
            }
            else
            {
                output << b.num;
            }

            return output;
        }


        // ASSIGNMENT OPERATORS OVERLOADING
        void operator=(const bigint &b)
        {
            this->num = b.num;
            this->isNegative = b.isNegative;
        }

        void operator=(const string &num)
        {
            assert(isValid(num));
            *this = convert(num);
        }

        void operator=(const int &num)
        {
            string x = to_string(num);
            *this = convert(x);
        }


        // COMPARISON OPERATORS OVERLOADING
        bool operator==(const bigint &b)
        {
            return this->num == b.num && this->isNegative == b.isNegative;
        }

        bool operator>(const bigint &b)
        {
            if(this->isNegative ^ b.isNegative)
            {
                return this->isNegative == false ? true : false;
            }
            
            if((int)this->num.size() > (int)b.num.size())
            {
                return this->isNegative == false ? true : false;
            }
            else if((int)this->num.size() < (int)b.num.size())
            {
                return this->isNegative == false ? false : true;
            }

            return this->isNegative == false ? this->num > b.num : this->num < b.num;
        }

        bool operator>=(const bigint &b)
        {
            return (*this) > b || (*this) == b;
        }

        bool operator<(const bigint &b)
        {
            return !((*this) > b || (*this) == b);
        }

        bool operator<=(const bigint &b)
        {
            return (*this) < b || (*this) == b;
        }

        bool operator!=(const bigint &b)
        {
            return !((*this) == b);
        }


        // ARITHMETIC OPERATORS OVERLOADING
        bigint operator+(const bigint &b)
        {
            bool differentSigns = (this->isNegative ^ b.isNegative);
            
            bigint result;

            if(differentSigns)
            {
                if(b.isNegative)
                {
                    result = convert(subtract(this->num, b.num));
                }
                else
                {
                    result = convert(subtract(b.num, this->num));
                }
            }
            else
            {
                result = convert(add(this->num, b.num));
                result.isNegative = (this->isNegative && b.isNegative);
            }

            return result;
        }

        bigint operator-(const bigint &b)
        {
            bool differentSigns = (b.isNegative ^ this->isNegative);

            bigint result;

            if(differentSigns)
            {
                if(b.isNegative)
                {
                    result = convert(add(this->num, b.num));
                }
                else
                {
                    result = convert(add(this->num, b.num));
                    result.isNegative = true;
                }
            }
            else
            {
                if(!this->isNegative && !b.isNegative)
                {
                    result = convert(subtract(this->num, b.num));
                }
                else
                {
                    result = convert(subtract(b.num, this->num));
                }
            }

            return result;
        }

        bigint operator*(const bigint &b)
        {
            bigint result;

            result = convert(multiply(this->num, b.num));

            result.isNegative = (this->isNegative ^ b.isNegative);

            return result;
        }

        bigint operator/(const bigint &b)
        {
            assert(b.num != "0");

            bigint result;

            result = convert(divide(this->num, b.num));
            result.isNegative = (result.num != "0" && (this->isNegative ^ b.isNegative));

            return result;
        }

        bigint operator%(const bigint &b)
        {
            bigint result;

            result = convert(modulo(this->num, b.num));
            result.isNegative = this->isNegative;

            return result;
        }    
};


// MATH FUNCTIONS

namespace MathFunctions
{

    bigint factorial(bigint n)
    {
        bigint res("1");

        for(bigint i=2;i<=n;i=i+1)
        {
            res = res * i;
        }

        return res;
    }

    bigint gcd(bigint a, bigint b)
    {
        if(b == (bigint)0)
        {
            return a;
        }

        return gcd(b, a%b);
    }

    bigint lcm(bigint a, bigint b)
    {
        return a * (b / gcd(a, b));
    }

    bigint power(bigint b, bigint e)
    {
        if(e==(bigint)0)
        {
            return (bigint)1;
        }

        bool setBit = (e % (bigint)2 == (bigint)1);

        return setBit ? power(b, e-(bigint)1) * b : power(b, e / (bigint)2) * power(b , e / (bigint)2);
    }
}

#endif
