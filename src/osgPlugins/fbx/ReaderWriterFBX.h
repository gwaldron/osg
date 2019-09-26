/******************************************************************************
** Copyright(c) 2019 MAK Technologies, Inc.
** All rights reserved.
******************************************************************************/

#ifndef READERWRITERFBX_H
#define READERWRITERFBX_H

#include <osgDB/ReaderWriter>
#include <fbxsdk/fbxsdk_def.h>
#include <string>

///////////////////////////////////////////////////////////////////////////
// OSG reader plugin for the ".fbx" format.
// See http://www.autodesk.com/fbx
// This plugin requires the FBX SDK version 2019.0 

#if FBXSDK_VERSION_MAJOR < 2019 || (FBXSDK_VERSION_MAJOR == 2019 && FBXSDK_VERSION_MINOR < 0)
#error Wrong FBX SDK version
#endif

class ReaderWriterFBX : public osgDB::ReaderWriter
{
public:
    ReaderWriterFBX()
    {
        supportsExtension("fbx", "FBX format");
        supportsOption("Embedded", "(Write option) Embed textures in FBX file");
        supportsOption("UseFbxRoot", "(Read/write option) If the source OSG root node is a simple group with no stateset, the writer will put its children directly under the FBX root, and vice-versa for reading");
        supportsOption("LightmapTextures", "(Read option) Interpret texture maps as overriding the lighting. 3D Studio Max may export files that should be interpreted in this way.");
        supportsOption("TessellatePolygons", "(Read option) Tessellate mesh polygons. If the model contains concave polygons this may be necessary, however tessellating can be very slow and may erroneously produce triangle shards.");
    }

    const char* className() const { return "FBX reader/writer"; }

    virtual ReadResult readObject(const std::string& filename, const Options* options) const
    {
        return readNode(filename, options);
    }

    virtual WriteResult writeObject(const osg::Node& node, const std::string& filename, const Options* options) const
    {
        return writeNode(node, filename, options);
    }

    virtual ReadResult readNode(const std::string& filename, const Options*) const;
    virtual WriteResult writeNode(const osg::Node&, const std::string& filename, const Options*) const;

protected:
    std::string currentFilePath;
};

///////////////////////////////////////////////////////////////////////////

#endif
