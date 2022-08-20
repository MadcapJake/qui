module;

#include <iostream>
#include <string>
#include <vector>
#include <optional>


export module Scanner;

export import Token;

namespace Quarrel {

	export class Scanner {
	private:
		int start = 0;
		int current = 0;
		int line = 1;
		bool hadError = false;

		void report(std::string where, std::string message) {
			std::cout << "[line " << line << "] Error " << where << ": " << message << std::endl;
			hadError = true;
		}

		bool isAtEnd() { return current >= source.length(); }

		bool isDigit(char c) { return c >= '0' && c <= '9'; }

		bool isAlpha(char c) {
			return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
		}

		bool isAlphaNumeric(char c) {
			return isAlpha(c) || isDigit(c);
		}

		bool match(char expected) {
			if (isAtEnd()) return false;
			if (source[current] != expected) return false;
			current++;
			return true;
		}

		char advance() { return source[current++]; }

		char peek() { return isAtEnd() ? '\0' : source[current]; }

		char peekNext() {
			if (current + 1 >= source.length()) return '\0';
			else return source[current + 1];
		}

		void string() {
			while (peek() != '"' && !isAtEnd()) {
				if (peek() == '\n') line++;
				advance();
			}

			if (isAtEnd()) { error("Unterminated string"); return; }

			advance(); // Eat the closing "

			// Trim surrounding quotes from string
			std::string value(source.substr(start + 1, current + 1));
			// TODO: Add unescape here
			addToken(Token::Kind::STRING, value);
		}

		void number() {
			while (isDigit(peek())) advance();
			if (peek() == '.' && isDigit(peekNext())) {
				advance();
				while (isDigit(peek())) advance();
			}
			addToken(Token::Kind::NUMBER, std::stof(source.substr(start, current)));
		}

		void identifier() {
			while (isAlphaNumeric(peek())) advance();
			std::string text(source.substr(start, current));
			std::optional<Token::Kind> reserved = Quarrel::Token::ReservedIdent(text);
			if (reserved) addToken(reserved.value());
			else addToken(Token::Kind::IDENTIFIER, text);
		}

		void scanToken() {
			char c = advance();
			switch (c) {
			using enum Token::Kind;
			case '(': addToken(LEFT_PAREN); break;
			case ')': addToken(RIGHT_PAREN); break;
			case '{': addToken(LEFT_BRACE); break;
			case '}': addToken(RIGHT_BRACE); break;
			case ',': addToken(COMMA); break;
			case '.': addToken(DOT); break;
			case '-': addToken(MINUS); break;
			case '+': addToken(PLUS); break;
			case ';': addToken(SEMICOLON); break;
			case '*': addToken(STAR); break;
			case '!': addToken(match('=') ? BANG_EQUAL    : BANG); break;
			case '=': addToken(match('=') ? EQUAL_EQUAL   : EQUAL); break;
			case '<': addToken(match('=') ? LESS_EQUAL    : LESS); break;
			case '>': addToken(match('=') ? GREATER_EQUAL : GREATER); break;
			case '/':
				if (match('/')) while (peek() != '\n' && !isAtEnd()) { advance(); }
				else { addToken(SLASH); } break;
			case ' ':
			case '\r': /* ignore whitespace */
			case '\t': break;
			case '\n': line++; break;
			case '"': string(); break;
			default:
				if (isDigit(c)) number();
				else if (isAlpha(c)) identifier();
				else error("Unexpected character");
			}
		}

		void addToken(Token::Kind t) { addToken(t, std::monostate{}); }
		void addToken(Token::Kind type, int literal) {
			std::string text(source.substr(start, current));
			Quarrel::Token tok(type, text, literal, line);
			tokens.push_back(tok);
		}
		void addToken(Token::Kind type, float literal) {
			std::string text = source.substr(start, current);
			Quarrel::Token tok(type, text, literal, line);
			tokens.push_back(tok);
		}
		void addToken(Token::Kind type, std::string literal) {
			std::string text = source.substr(start, current);
			Quarrel::Token tok(type, text, literal, line);
			tokens.push_back(tok);
		}
		void addToken(Token::Kind type, std::monostate literal) {
			std::string text = source.substr(start, current);
			Quarrel::Token tok(type, text, literal, line);
			tokens.push_back(tok);
		}

	public:
		const std::string source;
		std::vector<Token> tokens;

		Scanner(std::string source) : source(source) {}

		bool didHaveError() { return hadError; }

		void error(std::string message) {
			report("", message);
		}

		std::vector<Token> scanTokens() {
			while (!isAtEnd()) {
				start = current;
				scanToken();
			}

			Token end(Token::Kind::END_OF_FILE, "", std::monostate{}, line);
			tokens.push_back(end);
			return tokens;
		}

	};

}