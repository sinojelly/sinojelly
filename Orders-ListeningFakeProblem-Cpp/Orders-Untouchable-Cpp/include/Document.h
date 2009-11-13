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

#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <string>

#include "Element.h"

class Document : public Element {
public:
	Document(std::string name)
	:	Element(0,name)
	{ document_ = this; }
	
	static Document* createDocument(std::string name);


	Element* getDocumentElement();
	Element* createTextNode(std::string s);
	Element* createElement(std::string s);
	std::string getStringContents();
};

#endif /*DOCUMENT_H_*/
