module;

#include <variant>
#include <iostream>
#include <string>
#include <optional>

export module Token;

namespace Quarrel {

	export class Token {
	public:
		enum class Kind {
			LEFT_PAREN,
			RIGHT_PAREN,
			LEFT_BRACE,
			RIGHT_BRACE,
			COMMA,
			DOT,
			MINUS,
			PLUS,
			SEMICOLON,
			SLASH,
			STAR,

			BANG,
			BANG_EQUAL,
			EQUAL,
			EQUAL_EQUAL,
			GREATER,
			GREATER_EQUAL,
			LESS,
			LESS_EQUAL,

			IDENTIFIER,
			STRING,
			NUMBER,

			AND,
			CLASS,
			ELSE,
			FALSE,
			FUN,
			FOR,
			IF,
			NIL,
			OR,
			PRINT,
			RETURN,
			SUPER,
			THIS,
			TRUE,
			VAR,
			WHILE,
			END_OF_FILE
		};

		static std::optional<Kind> ReservedIdent(std::string identifier) {
			if (identifier == "and")    return Kind::AND;
			if (identifier == "class")  return Kind::CLASS;
			if (identifier == "else")   return Kind::ELSE;
			if (identifier == "false")  return Kind::FALSE;
			if (identifier == "fun")    return Kind::FUN;
			if (identifier == "for")    return Kind::FOR;
			if (identifier == "if")     return Kind::IF;
			if (identifier == "nil")    return Kind::NIL;
			if (identifier == "or")     return Kind::OR;
			if (identifier == "print")  return Kind::PRINT;
			if (identifier == "return") return Kind::RETURN;
			if (identifier == "super")  return Kind::SUPER;
			if (identifier == "this")   return Kind::THIS;
			if (identifier == "true")   return Kind::TRUE;
			if (identifier == "var")    return Kind::VAR;
			if (identifier == "while")  return Kind::WHILE;
			return {};
		}

		Kind type;

		std::string lexeme;

		std::variant<std::monostate, std::string, int, float> literal;
		static_assert(std::variant_size_v<decltype(literal)> == 4);

		int line;

		Token(Kind t, std::string x, int l, int n) {
			type = t; lexeme = x; literal = l; line = n;
		}

		Token(Kind t, std::string x, float l, int n) {
			type = t; lexeme = x; literal = l; line = n;
		}

		Token(Kind t, std::string x, std::string l, int n) {
			type = t; lexeme = x; literal = l; line = n;
		}

		Token(Kind t, std::string x, std::monostate l, int n) {
			type = t; lexeme = x; literal = l; line = n;
		}

		~Token() {}

	};
}

export std::ostream& operator<<(std::ostream& strm, const Quarrel::Token& t) {
	std::string type;
	switch (t.type) {
	using enum Quarrel::Token::Kind;
	case LEFT_PAREN: type = "LEFT_PAREN"; break;
	case RIGHT_PAREN: type = "RIGHT_PAREN"; break;
	case LEFT_BRACE: type = "LEFT_BRACE"; break;
	case RIGHT_BRACE: type = "RIGHT_BRACE"; break;
	case COMMA: type = "COMMA"; break;
	case DOT: type = "DOT"; break;
	case MINUS: type = "MINUS"; break;
	case PLUS: type = "PLUS"; break;
	case SEMICOLON: type = "SEMICOLON"; break;
	case SLASH: type = "SLASH"; break;
	case STAR: type = "STAR"; break;
	case BANG: type = "BANG"; break;
	case BANG_EQUAL: type = "BANG_EQUAL"; break;
	case EQUAL: type = "EQUAL"; break;
	case EQUAL_EQUAL: type = "EQUAL_EQUAL"; break;
	case GREATER: type = "GREATER"; break;
	case GREATER_EQUAL: type = "GREATER_EQUAL"; break;
	case LESS: type = "LESS"; break;
	case LESS_EQUAL: type = "LESS_EQUAL"; break;
	case IDENTIFIER: type = "IDENTIFIER"; break;
	case STRING: type = "STRING"; break;
	case NUMBER: type = "NUMBER"; break;
	case AND: type = "AND"; break;
	case CLASS: type = "CLASS"; break;
	case ELSE: type = "ELSE"; break;
	case FALSE: type = "FALSE"; break;
	case FUN: type = "FUN"; break;
	case FOR: type = "FOR"; break;
	case IF: type = "IF"; break;
	case NIL: type = "NIL"; break;
	case OR: type = "OR"; break;
	case PRINT: type = "PRINT"; break;
	case RETURN: type = "RETURN"; break;
	case SUPER: type = "SUPER"; break;
	case THIS: type = "THIS"; break;
	case TRUE: type = "TRUE"; break;
	case VAR: type = "VAR"; break;
	case WHILE: type = "WHILE"; break;
	case END_OF_FILE: type = "END_OF_FILE"; break;
	default: throw std::invalid_argument("Unexpected token kind.");
	}

	if (const auto intPtr (std::get_if<int>(&t.literal)); intPtr)
		return strm << type << " " << t.lexeme << " " << *intPtr;
	else if (const auto floatPtr (std::get_if<float>(&t.literal)); floatPtr)
		return strm << type << " " << t.lexeme << " " << *floatPtr;
	else if (const auto stringPtr (std::get_if<std::string>(&t.literal)); stringPtr)
		return strm << type << " " << t.lexeme << " " << *stringPtr;
	else
		return strm << type << " " << t.lexeme;
}