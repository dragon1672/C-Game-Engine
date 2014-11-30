#pragma once

#include <glm/glm.hpp>
#include <Engine/Systems/Events/EventManager.h>
#include <Engine/IO/StreamableObject.h>
#include <Engine/IO/Stream.h>

class Dims : public StreamableObject {
	bool hasChanged;
	bool percent;
	glm::vec2 start,end, masterDims;
public:
	glm::vec2& ref_start() { return start; }
	glm::vec2& ref_end()   { return end;   }

	Dims() : hasChanged(true), percent(true), start(0,0), end(1,1) {}
	void resetChanged() { hasChanged = false; }
	void setChanged()   { hasChanged = true; }
	bool HasChanged()      const { return hasChanged; }
	glm::vec2 Start()      const { return start; }
	glm::vec2 End()        const { return end; }
	bool      IsPercent()  const { return percent; }
	bool      IsPixel()    const { return !percent; }
	glm::vec2 MasterDims() const { return masterDims; }

	void Start     (float x, float y) { Start     (glm::vec2(x,y)); }
	void End       (float x, float y) { End       (glm::vec2(x,y)); }
	void MasterDims(float x, float y) { MasterDims(glm::vec2(x,y)); }
	void Start     (glm::vec2 set)    { hasChanged = hasChanged || Start     () != set; start      =  set; }
	void End       (glm::vec2 set)    { hasChanged = hasChanged || End       () != set; end        =  set; }
	void MasterDims(glm::vec2 set)    { hasChanged = hasChanged || MasterDims() != set; masterDims =  set; }
	void IsPercent (bool set)         { hasChanged = hasChanged || IsPercent () != set; percent    =  set; }
	void IsPixel   (bool set)         { hasChanged = hasChanged || IsPixel   () != set; percent    = !set; }

	//will convert insides
	void SetPercent() {
		if(IsPercent()) return;
		hasChanged = true;
		start = StartPercent();
		end   = StartPercent();
		IsPercent(true);
	}
	void SetPixel  () {
		if(IsPixel()) return;
		hasChanged = true;
		start = StartPixel();
		end   = EndPixel();
		IsPixel(true);
	}
	Dims toPixel()   const { Dims ret = *this; ret.SetPixel();   return ret; }
	Dims toPercent() const { Dims ret = *this; ret.SetPercent(); return ret; }

	float Width()            const { return end.x; }
	float Height()           const { return end.y; }
	float WidthPercent()     const { return IsPercent() ? Width()  : Width()  / masterDims.x; }
	float WidthPixel()       const { return IsPixel()   ? Width()  : Width()  * masterDims.x; }
	float HeightPercent()    const { return IsPercent() ? Height() : Height() / masterDims.y; }
	float HeightPixel()      const { return IsPixel()   ? Height() : Height() * masterDims.y; }
	glm::vec2 StartPercent() const { return IsPercent() ? Start()  : Start()  / masterDims;   }
	glm::vec2 StartPixel()   const { return IsPixel()   ? Start()  : Start()  * masterDims;   }
	glm::vec2 EndPercent()   const { return IsPercent() ? End()    : End()    / masterDims;   }
	glm::vec2 EndPixel()     const { return IsPixel()   ? End()    : End()    * masterDims;   }

	virtual void Save(Stream&s)
	{
		s << hasChanged << percent << start << end << masterDims;
	}

	virtual void Load(Stream&s)
	{
		s << hasChanged << percent << start << end << masterDims;
		hasChanged = true;
	}

};