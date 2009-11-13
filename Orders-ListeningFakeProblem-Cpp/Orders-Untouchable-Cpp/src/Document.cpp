/// ***************************************************************************
/// Copyright (c) 2009, Industrial Logic, Inc., All Rights Reserved.
///
/// This code is the exclusive property of Industrial Logic, Inc. It may ONLY be
/// used by students during Industrial Logic's workshops or by individuals
/// who are being coached by Industrial Logic on a project.
///
/// This code may NOT be copied or used for any other purpose without the prior
/// written consent of Industrial Logic, Inc.
/// ****************************************************************************

#include "Document.h"

class TextNode : public Element 
{
public:
	TextNode(Document* d,std::string value) 
	:	Element(d,value) 
	{
		value_ = value;
	}

	void toStringHelper(std::string& result) 
	{
		result+=value_;
	}
};

Document* Document::createDocument(std::string name) 
{
	return new Document(name);
}

Element* Document::createTextNode(std::string s) 
{
	return new TextNode(this,s);
}

Element* Document::createElement(std::string s) 
{
	return new Element(this,s);
}

std::string Document::getStringContents() 
{
	std::string result;
	toStringHelper(result);
	return result;
}

