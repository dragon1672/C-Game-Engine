#pragma once

//name, type, constructor prams
#define SAFE_NEW(name,type,...) if(name != nullptr) delete name; name = new type( __VA_ARGS__ )
#define SAFE_DELETE(name) if(name != nullptr) delete name;