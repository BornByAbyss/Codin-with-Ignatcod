#include <iostream>

using namespace std;

class Token
{
public:
    char kind;
    double value;
    Token(char k, double n) : kind(k), value(n) {}
    Token(char k) : kind(k), value(0) {}
};

class Token_stream
{

private:
    bool full;
    Token buffer;

public:
    Token get()
    {
        if (full)
        {
            full = false;
            return buffer;
        }
        double result;
        char ch;
        cin >> ch;

        switch (ch)
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case 'q':
        case '=':

            return Token(ch);
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        {
            cin.putback(ch);
            cin >> result;
            return Token('8', result);
        }
        }
    }
    void putback(Token t)
    {

        if (full)
        {
            cout << "overflow";
        }

        full = true;
        buffer = t;
    }
    Token_stream() : full(false), buffer(0) {}
};

Token_stream ts;

double expression();

double primary()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '(':
    {
        double d = expression();
        t = ts.get();
        return d;
    }
    case '8':
        return t.value;
    }
}

double term()
{
    double left = primary();
    Token t = ts.get();
    while (true)
    {
        switch (t.kind)
        {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
            left /= primary();
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

double expression()
{
    double left = term();
    Token t = ts.get();
    while (true)
    {
        switch (t.kind)
        {
        case '+':
            left += term();
            t = ts.get();
            break;
        case '-':
            left -= term();
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
            break;
        }
    }
}

int main()
{
    double val = 0;
    while (cin)
    {
        Token t = ts.get();
        if (t.kind == 'q')
            break;
        if (t.kind == '=')
            cout << '=' << val << '\n';
        else
        {
            ts.putback(t);
            val = expression();
        }
    }
}