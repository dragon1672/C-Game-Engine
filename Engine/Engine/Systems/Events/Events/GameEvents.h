#pragma once

#include <Engine/Systems/Events/EventData.h>

class GLInited    : public EventData { };
class GameStarted : public EventData { };
class GameUpdate  : public EventData { };