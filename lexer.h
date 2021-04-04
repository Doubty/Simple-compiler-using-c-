#include <unordered_map>
#include <string>
#include <sstream>
using std::stringstream;
using std::unordered_map;
using std::string;

// cada token possui uma tag (número a partir de 256)
// a tag de caracteres individuais é seu código ASCII
enum Tag { TYPE = 256, NUM, ID };

// classes para representar tokens
struct Token
{ 

	int tag;
	Token() : tag(0) {}
	Token(int t) : tag(t) {}
	virtual string toString() { stringstream ss; ss << char(tag); return ss.str(); }
};

struct Num : public Token
{
		// atributo para guardar o tipo do número no token e o valor em caso de ser float
	string tipo;
	float fvalue;
	int value;

	Num(int vi, string tp, float v ): Token(Tag::NUM), value(vi), tipo(tp), fvalue(v)  {}
	Num(): Token(Tag::NUM), value(0) {}
	Num(int v, string) : Token(Tag::NUM), value(v) {}
	virtual string toString() { stringstream ss; if(tipo == "int"){ ss << value; return ss.str();} else {  ss << fvalue; return ss.str();} }
};

struct Id : public Token
{
	string name;
	Id(): Token(Tag::ID) {}
	Id(int t, string s) : Token(t), name(s) {}
	virtual string toString() { return name; }
};

// analisador léxico
class Lexer
{
private:
	// tipos de token da linguagem
	struct
	{
		Token t;
		Num n;
		Id i;
	} 
	token;
	
	int line = 1;
	char peek;
	unordered_map<string, Id> id_table;

public:
	Lexer();
	int Lineno();
	Token * Scan();
};
