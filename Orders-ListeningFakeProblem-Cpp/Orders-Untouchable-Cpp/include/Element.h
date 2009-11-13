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

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <string>
#include <list>

class Element;
class Document;

typedef std::list<Element*> ElementList;

class Element {
protected:
	Document* document_;
	ElementList children_;
	std::string name_;
	std::string attributes_;
	std::string value_;

	virtual void toStringHelper(std::string& result); 
	void writeChildrenTo(std::string& result);
	void writeEndTagTo(std::string& result);
	void writeOpenTagTo(std::string& result); 
	void writeValueTo(std::string& result);
	bool noValueOrChildren();
public:
	Element(Document* document,std::string name)
	:	document_(document),name_(name)
	{ }
	
	Element* getFirstChild();
	void setAttribute(std::string key, std::string value);
	void appendChild(Element* child);
	std::string getNodeName();
	Document* getOwnerDocument();
};

#endif /*ELEMENT_H_*/
