#include "StringRandom.h"
#include <Engine/TypeDefs.h>

namespace {
 ubyte asciiList[] = {
	 (ubyte)0,  (ubyte)1,  (ubyte)2,  (ubyte)3,  (ubyte)4,  (ubyte)5,  (ubyte)6,  (ubyte)7,  (ubyte)8,  (ubyte)9,
	 (ubyte)10, (ubyte)11, (ubyte)12, (ubyte)13, (ubyte)14, (ubyte)15, (ubyte)16, (ubyte)17, (ubyte)18, (ubyte)19,
	 (ubyte)20, (ubyte)21, (ubyte)22, (ubyte)23, (ubyte)24, (ubyte)25, (ubyte)26, (ubyte)27, (ubyte)28, (ubyte)29,
	 (ubyte)30, (ubyte)31, (ubyte)32, (ubyte)33, (ubyte)34, (ubyte)35, (ubyte)36, (ubyte)37, (ubyte)38, (ubyte)39,
	 (ubyte)40, (ubyte)41, (ubyte)42, (ubyte)43, (ubyte)44, (ubyte)45, (ubyte)46, (ubyte)47, (ubyte)48, (ubyte)49,
	 (ubyte)50, (ubyte)51, (ubyte)52, (ubyte)53, (ubyte)54, (ubyte)55, (ubyte)56, (ubyte)57, (ubyte)58, (ubyte)59,
	 (ubyte)60, (ubyte)61, (ubyte)62, (ubyte)63, (ubyte)64, (ubyte)65, (ubyte)66, (ubyte)67, (ubyte)68, (ubyte)69,
	 (ubyte)70, (ubyte)71, (ubyte)72, (ubyte)73, (ubyte)74, (ubyte)75, (ubyte)76, (ubyte)77, (ubyte)78, (ubyte)79,
	 (ubyte)80, (ubyte)81, (ubyte)82, (ubyte)83, (ubyte)84, (ubyte)85, (ubyte)86, (ubyte)87, (ubyte)88, (ubyte)89,
	 (ubyte)90, (ubyte)91, (ubyte)92, (ubyte)93, (ubyte)94, (ubyte)95, (ubyte)96, (ubyte)97, (ubyte)98, (ubyte)99,
	 (ubyte)100,(ubyte)101,(ubyte)102,(ubyte)103,(ubyte)104,(ubyte)105,(ubyte)106,(ubyte)107,(ubyte)108,(ubyte)109,
	 (ubyte)110,(ubyte)111,(ubyte)112,(ubyte)113,(ubyte)114,(ubyte)115,(ubyte)116,(ubyte)117,(ubyte)118,(ubyte)119,
	 (ubyte)120,(ubyte)121,(ubyte)122,(ubyte)123,(ubyte)124,(ubyte)125,(ubyte)126,(ubyte)127,(ubyte)128,(ubyte)129,
	 (ubyte)130,(ubyte)131,(ubyte)132,(ubyte)133,(ubyte)134,(ubyte)135,(ubyte)136,(ubyte)137,(ubyte)138,(ubyte)139,
	 (ubyte)140,(ubyte)141,(ubyte)142,(ubyte)143,(ubyte)144,(ubyte)145,(ubyte)146,(ubyte)147,(ubyte)148,(ubyte)149,
	 (ubyte)150,(ubyte)151,(ubyte)152,(ubyte)153,(ubyte)154,(ubyte)155,(ubyte)156,(ubyte)157,(ubyte)158,(ubyte)159,
	 (ubyte)160,(ubyte)161,(ubyte)162,(ubyte)163,(ubyte)164,(ubyte)165,(ubyte)166,(ubyte)167,(ubyte)168,(ubyte)169,
	 (ubyte)170,(ubyte)171,(ubyte)172,(ubyte)173,(ubyte)174,(ubyte)175,(ubyte)176,(ubyte)177,(ubyte)178,(ubyte)179,
	 (ubyte)180,(ubyte)181,(ubyte)182,(ubyte)183,(ubyte)184,(ubyte)185,(ubyte)186,(ubyte)187,(ubyte)188,(ubyte)189,
	 (ubyte)190,(ubyte)191,(ubyte)192,(ubyte)193,(ubyte)194,(ubyte)195,(ubyte)196,(ubyte)197,(ubyte)198,(ubyte)199,
	 (ubyte)200,(ubyte)201,(ubyte)202,(ubyte)203,(ubyte)204,(ubyte)205,(ubyte)206,(ubyte)207,(ubyte)208,(ubyte)209,
	 (ubyte)210,(ubyte)211,(ubyte)212,(ubyte)213,(ubyte)214,(ubyte)215,(ubyte)216,(ubyte)217,(ubyte)218,(ubyte)219,
	 (ubyte)220,(ubyte)221,(ubyte)222,(ubyte)223,(ubyte)224,(ubyte)225,(ubyte)226,(ubyte)227,(ubyte)228,(ubyte)229,
	 (ubyte)230,(ubyte)231,(ubyte)232,(ubyte)233,(ubyte)234,(ubyte)235,(ubyte)236,(ubyte)237,(ubyte)238,(ubyte)239,
	 (ubyte)240,(ubyte)241,(ubyte)242,(ubyte)243,(ubyte)244,(ubyte)245,(ubyte)246,(ubyte)247,(ubyte)248,(ubyte)249,
	 (ubyte)250,(ubyte)251,(ubyte)252,(ubyte)253,(ubyte)254,(ubyte)255,
 };

 ubyte allLetters[] = {
	 (ubyte)65, (ubyte)66, (ubyte)67, (ubyte)68, (ubyte)69,
	 (ubyte)70, (ubyte)71, (ubyte)72, (ubyte)73, (ubyte)74, (ubyte)75, (ubyte)76, (ubyte)77, (ubyte)78, (ubyte)79,
	 (ubyte)80, (ubyte)81, (ubyte)82, (ubyte)83, (ubyte)84, (ubyte)85, (ubyte)86, (ubyte)87, (ubyte)88, (ubyte)89,
	 (ubyte)90,(ubyte)97, (ubyte)98, (ubyte)99,
	 (ubyte)100,(ubyte)101,(ubyte)102,(ubyte)103,(ubyte)104,(ubyte)105,(ubyte)106,(ubyte)107,(ubyte)108,(ubyte)109,
	 (ubyte)110,(ubyte)111,(ubyte)112,(ubyte)113,(ubyte)114,(ubyte)115,(ubyte)116,(ubyte)117,(ubyte)118,(ubyte)119,
	 (ubyte)120,(ubyte)121,(ubyte)122,
 };

}


std::string Random::rString::makeString(int len, int rangeStart,int rangeEnd)
{
	return makeString(len,(char*)&asciiList[rangeStart],rangeEnd - rangeStart);
}

std::string Random::rString::makeString(int len, char * options, int numOptions)
{
	std::string ret(len,'?');
	for (uint i = 0; i < ret.length(); i++)
	{
		ret[i] = options[Random::Int(0,numOptions-1)];
	}
	return ret;
}

std::string ENGINE_SHARED Random::rString::UppercaseLetters(int len)
{
	return makeString(len,'A','Z');
}

std::string ENGINE_SHARED Random::rString::LowercaseLetters(int len)
{
	return makeString(len,'a','z');
}

std::string ENGINE_SHARED Random::rString::Letters(int len)
{
	return makeString(len,(char*)allLetters,sizeof(allLetters)/sizeof(*allLetters));
}
