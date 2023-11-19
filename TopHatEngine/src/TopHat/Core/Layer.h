#pragma once

#include "TopHat/Events/Events.h"
#include "DeltaTime.h"

namespace TopHat
{
	class  Layer
	{
	public:
		
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach(){}
		virtual void OnUpdate(DeltaTime& deltaT){}
		virtual void OnEvent(Event& e){}

		const inline std::string& GetLayerName() { return m_DebugName; }
	
	private:
		std::string m_DebugName;	
	
	};
}
 