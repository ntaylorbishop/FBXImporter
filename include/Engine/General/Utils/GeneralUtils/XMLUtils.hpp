#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "ThirdParty/Parsers/xmlParser.h"
#include "Engine/General/Utils/StringUtils.hpp"
#include "Engine/Renderer/General/RGBA.hpp"
#include "Engine/Math/RangeInt.hpp"

namespace XMLUtils {

	//---------------------------------------------------------------------------------------------------------------------------
	//STRUCTS
	//---------------------------------------------------------------------------------------------------------------------------
	struct Attribute {
		Attribute(const String& name, const String& value) : name(name), value(value) { }

		String name;
		String value;
	};
	
	IntVector2 ParseIntVector2FromXML(const String& attribValue);
	int ParseIntFromXML(const String& attribValue);
	char ParseCharFromXML(const String& attribValue);
	RGBA ParseHexColorFromXML(const String& attribValue);
	RGBA ParseFloatColorFromXML(const String& attribValue);
	RangeInt ParseRangeIntFromXML(const String& attribValue);
	RangeInt ParseRangeIntFromXML(const String& attribValue, char delimiter);
	float ParseFloatFromXML(const String& attribValue);

	bool GetAttributeByName(const String& name, const XMLNode& node, Attribute& outAttrib);
	bool DoesAttributeExist(const String& attribName, const std::vector<Attribute>& attribPairs);
	bool GetAllAttributesOfNode(const XMLNode& node, std::vector<Attribute>& outAttribPairs);
}