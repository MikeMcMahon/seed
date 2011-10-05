/**
*
*    filename: XMLHelper.h 
*
* description: XML Helper class module.  This provides helper 
*              classes for a structured document object
*              module interface.
*
*/

#pragma once

#include <comutil.h> 

class DOMInterfaceCollections;

namespace Xml
{

struct Status { enum code 
{
    ok,
    ready = ok,
    noDocument,
    noNode = noDocument,
    invalidDocument,
    invalidNode = invalidDocument,
    failed
};};

class Attribute
{
public:
    // Identifies whether the attribute exists.
    __declspec (property (get=x_existsRef)) bool exists;
    // Retrieves the read-only name of the attribute.
    __declspec (property (get=x_nameRef)) class ::_bstr_t name;
    // retrieves a char pointer to the attribute.
    __declspec (property (get=x_getPtr)) const char *ptr;
    // retrieves a bstr class reference to the attribute.
    __declspec (property (get=x_getBstr)) class::_bstr_t bstr;
    // retrieves a flag indicating if the attribute is numeric...
    __declspec (property (get=x_getIsNumeric)) bool isNumeric;

    // retrieves the value of the attribute...
    virtual operator bool () { return false; }
    virtual operator char () { return 0; }
    virtual operator unsigned char () { return 0; }
    virtual operator short () { return 0; }
    virtual operator unsigned short () { return 0; }
    virtual operator int () { return 0; }
    virtual operator unsigned int () { return 0; }
    virtual operator long () { return 0; }
    virtual operator unsigned long () { return 0; }
    virtual operator class ::_bstr_t () { return _bstr_t (); }
    // sets the value of the attribute...
    virtual Attribute &operator= (Attribute &value) { return *this; }
    virtual bool operator = (bool value) { return false; }
    virtual char operator = (char value) { return 0; }
    virtual unsigned char operator = (unsigned char value) { return 0; }
    virtual short operator = (short value) { return 0; }
    virtual unsigned short operator = (unsigned short value) { return 0; }
    virtual int operator = (int value) { return 0; }
    virtual unsigned int operator = (unsigned int value) { return 0; }
    virtual long operator = (long value) { return 0; }
    virtual unsigned long operator = (unsigned long value) { return 0; }
    virtual class::_bstr_t operator = (char *value) { return _bstr_t (); }
    virtual class::_bstr_t operator = (wchar_t *value) { return _bstr_t (); }

    // reference function for exists property.
    virtual bool x_existsRef () = 0;
    // reference function for name property.
    virtual _bstr_t x_nameRef () = 0;
    // reference function for ptr property.
    virtual const char *x_getPtr () = 0;
    // reference function for bstr property.
    virtual _bstr_t x_getBstr () = 0;
    // reference function for isNumeric property.
    virtual bool x_getIsNumeric () = 0;
};

class AttributeArray
{
public:
    // Retrieves the number of attributes.
    // i.e. if (node.attribute.count > 10)
    __declspec (property (get=x_countRef)) long count;
    // Adds an attribute.
    // i.e. node.attribute.add ("size",100);
    virtual bool add (const char *attributeName,_variant_t attributeValue) = 0;
    // Removes an attribute.
    // i.e. node.attribute.remove ("width");
    virtual bool remove (const char *attributeName) = 0;
    // Accesses attributes by index.
    // i.e. BstrT name = node.attribute[0].name;
    virtual class Xml::Attribute &operator [] (long attributeIndex) = 0;
    // Accesses attributes by name.
    // i.e. int width = node.attribute["width"];
    virtual class Xml::Attribute &operator [] (const char *attributeName) = 0;
    // reference function for count property.
    virtual long x_countRef () = 0;
};

class Node;

class NodeArray 
{
public:
    // Retrieves the number of nodes.
    // i.e. long total = node.node.count;
    __declspec (property (get=x_countRef)) long count;
    // Adds a new node at the specified insert postion.
    // i.e. node.node.add ("nodeName");
    virtual class Xml::Node &add (const char *nodeName,long insertPosition = -1) = 0;
    // Removes a node found by search string.
    // i.e. node.node.remove ("name[attrib='value'");
    virtual bool remove (const char *searchString) = 0;
    // Accesses nodes by index.
    // i.e. _bstr_t name = node.node[0].name;
    virtual class Xml::Node &operator[] (long nodeIndex) = 0;
    // Accesses nodes by search string.
    // i.e. node.node["form[@name = mainPage]"];
    virtual class Xml::Node &operator[] (const char *searchString) = 0;
    // reference function for count property.
    virtual long x_countRef () = 0;
};

class Node
{
private:
    friend class DOMInterfaceCollections;
    void *x_xmlNode;

public:
    Node ();
    // Copy constructor.
    Node (Xml::Node &xmlNode);
    virtual ~Node ();

    // Copies one node object to another.
    // i.e. Xml::Node myNode = document.rootNode;
    Xml::Node &operator= (Xml::Node &xmlNode);

    // Retrieves the read-only name of the node.
    // i.e. _bstr_t name = node.name;
    __declspec (property (get=x_getNameRef)) class ::_bstr_t name;
    // Sets or gets the text section of the node.
    // i.e. node.textSection = "some text";
    __declspec (property (get=x_getTextRef, put=x_putTextRef)) class ::_bstr_t textSection;
    // Retrieves the node's status...
    // i.e. if (node.status == Xml::Status::noNode)
    __declspec (property (get=x_statusRef)) Xml::Status::code status;

    // Accesses sub-nodes by search string or index.
    // i.e. node.node[0].name;
    Xml::NodeArray &child;
    // Retrieves attributes of the node.
    // i.e. if (node.attribute.count > 0)
    Xml::AttributeArray &attribute;

    // finds a node in this node.
    // returns the first node matching the criteria.
    Xml::Node &find (const char *nodeName,const char *attributeName,const char *attributeValue);
    // reference function for name property.
    _bstr_t x_getNameRef ();
    // reference function for textSection property.
    _bstr_t x_getTextRef ();
    // reference function for textSection property.
    void x_putTextRef (_bstr_t textString);
    // reference function for status property.
    Xml::Status::code x_statusRef ();
};

class Document
{
private:
    void *x_xmlDocument;

public:
    Document ();
    // Loads the xml document while instantiating.
    // i.e. Xml::Document myDoc = "filename.xml";
    Document (_bstr_t &xmlDocumentFilename);
    virtual ~Document ();

    // Loads the xml document as a file or string.
    // i.e. document.load ("filename.xml");
    Xml::Status::code load (_bstr_t xmlDocumentFilename);
    // Saves the xml document as a file.
    // i.e. document.save ("filename.xml");
    Xml::Status::code save (_bstr_t xmlDocumentFilename);
    // Retrieves the document's status.
    // i.e. if (document.status == Xml::Status::ready)
    __declspec (property (get=x_statusRef)) Xml::Status::code status;
    // References the document's root node.
    // i.e. name = document.rootNode.name;
    Xml::Node rootNode;

    // reference function for status property.
    Xml::Status::code x_statusRef ();
};

class Default
{
public:
    static Document document;
    static Node node;
};

#define safeBSTR(b) !b.length()?L"empty":(wchar_t*)b

} // namespace Xml

/* eof */