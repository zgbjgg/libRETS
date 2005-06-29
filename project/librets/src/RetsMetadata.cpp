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
#include <sstream>
#include "librets/RetsMetadata.h"
#include "librets/MetadataByLevelCollector.h"
#include "librets/MetadataSystem.h"
#include "librets/MetadataResource.h"
#include "librets/MetadataClass.h"
#include "librets/MetadataTable.h"
#include "librets/RetsException.h"

using namespace librets;
using std::string;
using std::vector;
using std::ostringstream;
namespace b = boost;

RetsMetadata::RetsMetadata(MetadataByLevelCollectorPtr collector)
{
    mCollector = collector;
    InitSystem();
    InitAllResources();
    InitAllClasses();
}

void RetsMetadata::InitSystem()
{
    MetadataElementListPtr elements =
        mCollector->Find(MetadataElement::SYSTEM, "");
    if (elements->size() != 1)
    {
        ostringstream message;
        message << "Expecting 1 system metadata element, found "
                << elements->size();
        throw RetsException(message.str());
    }
    MetadataElementPtr element = elements->at(0);
    mSystem = b::dynamic_pointer_cast<MetadataSystem>(element);
}

void RetsMetadata::InitAllClasses()
{
    mAllClasses.reset(new MetadataClassList());
    MetadataElementListPtr resources =
        mCollector->Find(MetadataElement::RESOURCE, "");
    MetadataElementList::iterator i;
    for (i = resources->begin(); i != resources->end(); i++)
    {
        MetadataResourcePtr resource =
            b::dynamic_pointer_cast<MetadataResource>(*i);
        string level = resource->GetResourceID();

        MetadataElementListPtr classes =
            mCollector->Find(MetadataElement::CLASS, level);
        MetadataElementList::iterator j;
        for (j = classes->begin(); j != classes->end(); j++)
        {
            MetadataClassPtr aClass =
                b::dynamic_pointer_cast<MetadataClass>(*j);
            mAllClasses->push_back(aClass);
        }
    }
}

void RetsMetadata::InitAllResources()
{
    mAllResources.reset(new MetadataResourceList());
    MetadataElementListPtr resources =
        mCollector->Find(MetadataElement::RESOURCE, "");
    MetadataElementList::iterator i;
    for (i = resources->begin(); i != resources->end(); i++)
    {
        MetadataResourcePtr resource =
            b::dynamic_pointer_cast<MetadataResource>(*i);
        mAllResources->push_back(resource);
    }
}

MetadataSystemPtr RetsMetadata::GetSystem() const
{
    return mSystem;
}

MetadataClassListPtr RetsMetadata::GetAllClasses() const
{
    return mAllClasses;
}

MetadataClassPtr RetsMetadata::GetClass(string resourceName, string className)
    const
{
    MetadataClassPtr metadataClass;

    MetadataClassListPtr classList = GetClassesForResource(resourceName);
    
    bool found = false;
    MetadataClassList::iterator i = classList->begin();
    
    while (i != classList->end() && !found)
    {
        MetadataClassPtr clazz = *i;
        string testName = clazz->GetClassName();
        if (testName == className)
        {
            metadataClass = clazz;
            found = true;
        }
        i++;
    }
    
    return metadataClass;
}

MetadataTableListPtr RetsMetadata::GetTablesForClass(
    MetadataClassPtr metadataClass) const
{
    return GetTablesForClass(metadataClass->GetLevel(),
                             metadataClass->GetClassName());
}

MetadataTableListPtr RetsMetadata::GetTablesForClass(
    string resourceName, string className) const
{
    string level = resourceName + ":" + className;
    MetadataElementListPtr elements =
        mCollector->Find(MetadataElement::TABLE, level);
    
    MetadataTableListPtr tables(new MetadataTableList());
    MetadataElementList::iterator i;
    for (i = elements->begin(); i != elements->end(); i++)
    {
        MetadataTablePtr table = b::dynamic_pointer_cast<MetadataTable>(*i);
        tables->push_back(table);
    }
    return tables;
}

MetadataResourceListPtr RetsMetadata::GetAllResources() const
{
    return mAllResources;
}

MetadataClassListPtr RetsMetadata::GetClassesForResource(
    string resourceName) const
{
    MetadataElementListPtr elements =
        mCollector->Find(MetadataElement::CLASS, resourceName);
    
    MetadataClassListPtr classes(new MetadataClassList());
    MetadataElementList::iterator i;
    for (i = elements->begin(); i != elements->end(); i++)
    {
        MetadataClassPtr aClass = b::dynamic_pointer_cast<MetadataClass>(*i);
        classes->push_back(aClass);
    }
    
    return classes;
}

MetadataResourcePtr RetsMetadata::GetResource(string resourceName) const
{
    MetadataResourcePtr metadataResource;

    bool found = false;
    MetadataResourceList::iterator i = mAllResources->begin();
    
    while (i != mAllResources->end() && !found)
    {
        MetadataResourcePtr res = *i;
        string testName = res->GetResourceID();
        if (testName == resourceName)
        {
            metadataResource = res;
            found = true;
        }
        i++;
    }
    
    return metadataResource;
}

MetadataTablePtr RetsMetadata::GetTable(string resourceName, string className,
                                        string tableName) const
{
    MetadataTablePtr metadataTable;

    MetadataTableListPtr tableList =
        GetTablesForClass(resourceName, className);
    
    bool found = false;
    MetadataTableList::iterator i = tableList->begin();
    
    while (i != tableList->end() && !found)
    {
        MetadataTablePtr table = *i;
        string testName = table->GetSystemName();
        if (testName == tableName)
        {
            metadataTable = table;
            found = true;
        }
        i++;
    }
    
    return metadataTable;
}