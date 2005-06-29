/*
 * Copyright (C) 2005 National Association of REALTORS(R)
 *
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, and/or sell copies of the
 * Software, and to permit persons to whom the Software is furnished
 * to do so, provided that the above copyright notice(s) and this
 * permission notice appear in all copies of the Software and that
 * both the above copyright notice(s) and this permission notice
 * appear in supporting documentation.
 */
#ifndef LIBRETS_RETS_XML_PARSER_H
#define LIBRETS_RETS_XML_PARSER_H

#include "librets/std_forward.h"
#include "librets/xml_forward.h"

namespace librets {

class RetsXmlParser
{
  public:
    static RetsXmlParserPtr CreateDefault(istreamPtr inputStream);

    virtual ~RetsXmlParser();

    virtual bool HasNext() = 0;

    /**
     * Returns next XML event, blocking if necessary.
     *
     * @return Next XML event
     * @throw RetsException
     */
    virtual RetsXmlEventPtr GetNextEvent() = 0;

    RetsXmlEventPtr GetNextSkippingEmptyText();
    
    RetsXmlStartElementEventPtr AssertNextIsStartEvent();

    RetsXmlEndElementEventPtr AssertNextIsEndEvent();

    RetsXmlTextEventPtr AssertNextIsTextEvent();
};

};

#endif

/* Local Variables: */
/* mode: c++ */
/* End: */