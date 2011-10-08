#include "XmlIngester.h"
#include <XmlHelper.h>


using namespace GameUtil;

::XmlIngester::XmlIngester(void) { 
    std::string dir = DIRECTORY_PREFIX;
    dir.append("ui/");
    docPrefix = dir;
}

::XmlIngester::~XmlIngester(void) { 

}

bool ::XmlIngester::Load(LPWSTR className) {
    // TODO - at some point I need to figure out this goddamn library, work with Dennis.  
    bstr_t name(className);

    Xml::Document _document(name);
    Xml::Status::code status = _document.status;
    // Okay do some magic
    if (status == Xml::Status::ok) {
        return true;
    }

    return false;
}