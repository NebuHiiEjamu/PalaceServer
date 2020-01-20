#ifndef _PARSER_H
#define _PARSER_H

#include <boost/spirit/include/qi.hpp>
#include <boost/variant.hpp>
#include <optional>
#include <string>

#include "../common/src/typedefs.hpp"

namespace ascii = boost::spirit::ascii;
namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;
namespace qi = boost::spirit::qi;

enum class ScriptBinaryOperator : Byte
{
	add,
	and,
	bitAnd,
	bitOr,
	bitShiftLeft,
	bitShiftRight,
	bitXor,
	concatenate,
	divide,
	equal,
	greater,
	greaterEqual,
	less,
	lessEqual,
	modulo,
	multiply,
	not,
	notEqual,
	or,
	subtract
};

class ScriptBinaryOperation;

using ScriptValue = boost::variant<long, std::string,
	boost::recursive_wrapper<std::vector<boost::variant<long, std::string>>>>;
using ScriptExpression = boost::variant<ScriptValue,
	boost::recursive_wrapper<ScriptBinaryOperation>>;

class ScriptBinaryOperation
{
private:
	ScriptExpression lhs;
	std::optional<ScriptExpression> rhs;
	ScriptBinaryOperator op;
};

template <class Iterator> class ScriptGrammar : public 

#endif // _PARSER_H
