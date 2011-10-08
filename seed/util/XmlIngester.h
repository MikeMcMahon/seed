#pragma once
// TODO - is this the right way of loading sprites?  I don't think so, so I won't spend too much time here. 
// Think speed, is reading the sprites in via XML really the answer?  how much time does it cost...etc

#include "../main/GameHeaders.h"


namespace GameUtil { 
	class XmlIngester { 
    private: 
        std::string docPrefix;
        std::string docName;
        void ingest();
    public:
        XmlIngester();
        ~XmlIngester();
        bool Load(LPWSTR className);
    };
} // Util
/* eof */