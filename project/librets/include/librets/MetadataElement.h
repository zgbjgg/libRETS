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
#ifndef LIBRETS_METADATA_ELEMENT_H
#define LIBRETS_METADATA_ELEMENT_H

#include <string>
#include <vector>
#include "librets/std_forward.h"
#include "librets/metadata_forward.h"
#include "librets/RetsObject.h"

namespace librets {

/** A vector of MetadataElement objects. */
typedef std::vector<MetadataElementPtr> MetadataElementList;
/** A smart pointer to MetadataElementList. */
typedef boost::shared_ptr<MetadataElementList> MetadataElementListPtr;

/**
 * A metadata element.
 */
class MetadataElement : public RetsObject
{
  public:

    /**
     * Metadata types.
     */
    enum MetadataType
    {
        /** System metadata. */
        SYSTEM,
        /** Resource metadata. */
        RESOURCE,
        /** Class metadata. */
        CLASS,
        /** Table metadata. */
        TABLE,
        /** Update metadata. */
        UPDATE,
        /** Update type metadata. */
        UPDATE_TYPE,
        /** Object metadata. */
        OBJECT,
        /** Search help metadata. */
        SEARCH_HELP,
        /** Edit mask metadata. */
        EDIT_MASK,
        /** Lookup metadata. */
        LOOKUP,
        /** Lookup type metadata. */
        LOOKUP_TYPE,
        /** Update help metadata. */
        UPDATE_HELP,
        /** Validation lookup metadata. */
        VALIDATION_LOOKUP,
        /** Validation lookup type metadata. */
        VALIDATION_LOOKUP_TYPE,
        /** Validation external metadata. */
        VALIDATION_EXTERNAL,
        /** Validation external type metadata. */
        VALIDATION_EXTERNAL_TYPE,
        /** Validation expression metadata. */
        VALIDATION_EXPRESSION,
        /** Foreign key metadata. */
        FOREIGN_KEY
    };

    MetadataElement();

    virtual ~MetadataElement();

    /**
     * Returns the type of metadata element.
     *
     * @return the type of metadata element
     */
    virtual MetadataType GetType() const = 0;

    /**
     * Returns the value of an attribute.
     *
     * @param attributeName the name of an attribute
     * @param defaultValue the value to use if the attribute does not exist
     * @return the value of the attribute
     */
    std::string GetStringAttribute(std::string attributeName,
                                   std::string defaultValue = "") const;
   
    int GetIntAttribute(std::string attributeName, int defaultValue = 0) const;
    
    bool GetBoolAttribute(std::string attributeName, bool defaultValue = false)
        const;

    void SetAttribute(std::string attributeName, std::string attributeValue);

    /**
     * Returns the children of this element matching the given type.
     *
     * @param type The type of children to retrieve
     * @return a vector of children
     */
    std::vector<MetadataElementPtr> GetChildren(MetadataType type);

    std::string GetLevel() const;

    void SetLevel(std::string level);

    virtual std::ostream & Print(std::ostream & outputStream) const;

  protected:
    StringMap mAttributes;
    std::string mLevel;
};

};

#endif

/* Local Variables: */
/* mode: c++ */
/* End: */