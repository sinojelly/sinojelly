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

#include "Element.h"



void Element::setAttribute(std::string key, std::string value) {
	attributes_ += " ";
	attributes_ += key;
	attributes_ += "=\"";
	attributes_ += value;
	attributes_ += "\"";

}

void Element::appendChild(Element* child) {
	children_.push_back(child);
}

Element* Element::getFirstChild() { 
	if(children_.size()==0) return 0;
	return *children_.begin();
}

std::string Element::getNodeName() {
		return name_;
	}

Document* Element::getOwnerDocument() {
	return document_;
}

void Element::toStringHelper(std::string& result) 
{
	writeOpenTagTo(result);
	writeValueTo(result);
	writeChildrenTo(result);
	writeEndTagTo(result);
}

void Element::writeChildrenTo(std::string& result) 
{
	ElementList::iterator it;
	for(it=children_.begin(); it!=children_.end(); ++it)
	{
		Element* node = *it;
		node->toStringHelper(result);
	}
}

void Element::writeValueTo(std::string& result) 
{
	if (0 != value_.compare(""))
		result += value_;
}

void Element::writeEndTagTo(std::string& result) 
{
	if (noValueOrChildren())
		return;
	result += "</";
	result += name_;
	result += ">";
}

void Element::writeOpenTagTo(std::string& result) 
{
	result += "<";
	result += name_;
	result += attributes_;
	if (noValueOrChildren())
		result += "/";
	result += ">";
}

bool Element::noValueOrChildren() 
{
	return (0 == value_.compare("") && children_.size() == 0);
}
